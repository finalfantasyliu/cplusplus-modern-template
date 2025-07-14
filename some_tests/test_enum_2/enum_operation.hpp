

#ifndef ENUM_OPERATION_HPP
#define ENUM_OPERATION_HPP
#include <algorithm>
#include <array>
#include <string_view>
#include <utility>
#include <unordered_map>
#include <cctype>
#include <optional>
#include <type_traits>
namespace EnumUtils
{

constexpr bool IsNameChar(unsigned char c) noexcept
{
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '_' || c == ':';
}

constexpr std::string_view GetPrettyName(std::string_view sv) noexcept
{
    while (!sv.empty() && !IsNameChar(sv.back()))
    {
        sv.remove_suffix(1);
    }
    // Phase 2: find start of name
    size_t end = sv.size();
    size_t start = end;
    while (start > 0 && IsNameChar(sv[start - 1]))
    {
        --start;
    }
    // Extract just that block
    auto block = sv.substr(start, end - start);
    // If scoped (contains "::"), drop everything up to the last "::"
    if (auto pos = block.rfind("::"); pos != std::string_view::npos)
    {
        block.remove_prefix(pos + 2);
    }
    return block;
}

template <typename E, E V>
constexpr auto EnumRawStr() noexcept
{
#if defined(__clang__) || defined(__GNUC__)
    return GetPrettyName({__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 1});
#elif defined(_MSC_VER)
    return GetPrettyName({__FUNCSIG__, sizeof(__FUNCSIG__) - 1});
#else
#    error "Unsupported compiler for EnumUtils::EumRawStr()";
#endif
}
constexpr int ENUM_MIN = 0;
template <typename E>
constexpr E EnumValue(size_t i) noexcept
{
    return static_cast<E>(ENUM_MIN + static_cast<int>(i));
}

template <typename E, size_t... I>
constexpr auto MakeEntries(std::index_sequence<I...>) noexcept
{
    return std::array<std::pair<E, std::string_view>, sizeof...(I)> {
        std::pair {EnumValue<E>(I), EnumRawStr<E, EnumValue<E>(I)>()}...};
}

template <typename E>
constexpr auto EnumEntries() noexcept
{
    return MakeEntries<E>(std::make_index_sequence<1024> {});
}

template <typename E>
const std::unordered_map<E, std::string_view> &EnumMap()
{
    constexpr auto entries = EnumEntries<E>();
    static  const std::unordered_map<E, std::string_view> map = [&entries]
    {
        std::unordered_map<E, std::string_view> m;
        m.reserve(entries.size());
        for (auto const &p : entries)
        {
            auto name = p.second;
            if (!name.empty() && !std::isdigit(static_cast<unsigned char>(name[0])))
            {
                m.emplace(p.first, name);
            }
        }
        return m;
    }();
    return map;
}
template <typename E>
struct DefinedMap : std::false_type
{
};


template <typename E>
std::string_view EnumToString(E v)
{
    if constexpr (DefinedMap<E>::value)
    {
        const auto &m = DefinedMap<E>::map;
        auto it = m.find(v);
        return it != m.end() ? it->second : "unknown";
    }
    /*
    auto const &m = EnumMap<E>();
    auto it = m.find(v);
    return (it != m.end() ? it->second : std::string_view{});
*/
}

template <typename E>
const std::unordered_map<std::string_view, E> &StringEnumMap()
{
    if constexpr (DefinedMap<E>::value)
    {
        static const auto rev = []
        {
            std::unordered_map<std::string_view, E> tmp;
            for (auto const &[e, name] : DefinedMap<E>::map)
            {
                tmp.emplace(name, e);
            }
            return tmp;
        }();
        return rev;
    }
    else
    {
        static const auto rev = []
        {
            std::unordered_map<std::string_view, E> tmp;
            for (auto const &[e, name] : EnumMap<E>())
            {
                tmp.emplace(name, e);
            }
            return tmp;
        }();
        return rev;
    }
}

template <typename E>
std::optional<E> StringToEnum(std::string_view enum_name)
{
    const auto &m = StringEnumMap<E>();
    if (auto it = m.find(enum_name); it != m.end())
    {
        return it->second;
    }
    E best {};
    size_t best_len = 0;
    for (auto const &[name, e] : m)
    {
        if (name.size() > best_len and enum_name.find(name) != std::string_view::npos)
        {
            best = e;
            best_len = name.size();
        }
    }
    return best_len ? std::optional<E>{best} : std::nullopt;
}

}    // namespace EnumUtils

#endif    // ENUM_OPERATION_HPP

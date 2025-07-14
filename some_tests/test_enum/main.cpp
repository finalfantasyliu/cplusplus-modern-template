#include <array>
#include <string_view>
#include <utility>
#include <cstddef>
#include <unordered_map>

// Example Usage
#include <iostream>
// [1] Name extraction
constexpr bool is_name_char(char c) noexcept {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           (c == '_') || (c == ':');
}

constexpr bool has_leading_digit(std::string_view sv) noexcept
{
    return !sv.empty() &&
           std::isdigit(static_cast<unsigned char>(sv.front()));   // one-byte check
}

template<typename E, std::size_t N>
auto make_filtered_map(const std::array<std::pair<E,std::string_view>, N>& entries)
{
    std::unordered_map<E,std::string_view> m;
    for (auto const& [val, name] : entries)
        if (!has_leading_digit(name))          // reject names like "0", "123", "9Foo"
            m.emplace(val, name);
    return m;
}

constexpr std::string_view pretty_name(std::string_view sv) noexcept {
    // Phase 1: strip trailing non-name chars
    while (!sv.empty() && !is_name_char(sv.back())) {
        sv.remove_suffix(1);
    }
    // Phase 2: find start of name
    size_t end = sv.size();
    size_t start = end;
    while (start > 0 && is_name_char(sv[start - 1])) {
        --start;
    }
    // Extract just that block
    auto block = sv.substr(start, end - start);
    // If scoped (contains "::"), drop everything up to the last "::"
    if (auto pos = block.rfind("::"); pos != std::string_view::npos) {
        return block.substr(pos + 2);
    }

    return block;
}

template <typename E, E V>
constexpr auto enum_raw_name() noexcept {
#if defined(__clang__) || defined(__GNUC__)
    return pretty_name({ __PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 1 });
#elif defined(_MSC_VER)
    return pretty_name({ __FUNCSIG__,       sizeof(__FUNCSIG__) - 1 });
#endif
}

// A helper that just forwards whatever __PRETTY_FUNCTION__ gives us:
void print_pretty() {
    std::cout
        << "__PRETTY_FUNCTION__ in print_pretty():\n    "
        << __PRETTY_FUNCTION__
        << "\n\n";
}

// If you want to see it for a particular template instantiation:
template<typename E, E V>
void print_template_pretty() {
    std::cout
        << "__PRETTY_FUNCTION__ in print_template_pretty<"
        << ">():\n    "
        << __PRETTY_FUNCTION__
        << "\n\n";
}



// [2] Candidate generator
constexpr int ENUM_MIN = 0;
template <typename E>
constexpr E enum_value(size_t i) noexcept {
    return static_cast<E>(ENUM_MIN + static_cast<int>(i));
}
// (2) Build a constexpr array of pairs <E, name>
template<typename E, std::size_t... I>
constexpr auto make_entries(std::index_sequence<I...>) {
    return std::array{
        std::pair{ enum_value<E>(I),
                   enum_raw_name<E, enum_value<E>(I)>() }...
    };
}

template<typename E, std::size_t N>
auto make_map(const std::array<std::pair<E,std::string_view>, N>& entries) {
    // std::unordered_map has average-O(1) lookup :contentReference[oaicite:2]{index=2}
    return std::unordered_map<E,std::string_view>{
        entries.begin(), entries.end()
    };
}

// [3] Lookup implementation
template <typename E, size_t... I>
constexpr std::string_view enum_to_string_impl(
    E v, std::index_sequence<I...>) noexcept
{
    // Build constexpr array of (value, name) pairs using CTAD
    constexpr auto entries = std::array{
        std::pair{ enum_value<E>(I), enum_raw_name<E, enum_value<E>(I)>() }...
    };
    for (auto const &p : entries) {
        if (p.first == v)
            return p.second;
    }
    return {};
}


// Public API: scans 0..255
template <typename E>
constexpr std::string_view enum_to_string(E v) noexcept {

    // Compile-time array of entries 0..255
    constexpr auto entries = make_entries<E>(std::make_index_sequence<4096>{});
    // Single static map, initialized once at startup
    static const auto map = make_filtered_map(entries);

    // Lookup
    auto it = map.find(v);
    if (it != map.end())
        return it->second;
    return {};  // or throw if you prefer
}

// 1) A generic printer for an array of (E, name) pairs:
template<typename E, size_t N>
void PrintEntries(const std::array<std::pair<E,std::string_view>,N>& arr) {
    for (auto const& [val, name] : arr) {
        // print the numeric value and its raw name:
        std::cout
            << static_cast<std::underlying_type_t<E>>(val)
            << " -> "
            << name
            << "\n";
    }
}

// 2) A convenience wrapper that invokes your MakeEntries / EnumEntries:
template<typename E>
void PrintEnumRawNames() {
    // If you’ve switched to a fixed size via EnumCount<E>, use that:
    // constexpr auto entries = MakeEntries<E>(std::make_index_sequence<EnumCount<E>>{});
    //
    // Otherwise (with your 4096 fallback) just do:
    constexpr auto entries = make_entries<E>(std::make_index_sequence<4096>{});
    PrintEntries<E, entries.size()>(entries);
}
enum class Color : int { Red = 5, Green = 6, Blue = 10 };

enum class LicenseConfigStatus : uint32_t
{
    None=0,
    Uninitialized = 1u<<0,
    Loaded = 1u << 1,
    Updated = 1u << 2,
    Invalid = 1u << 3,
    Expired = 1u << 4,
    Error = 1u << 5,
};

void GetEnum(Color c) {
    enum_to_string(c);
}
namespace  wahaha {
    namespace  hihihi {
        enum class juju {
            Red,
            Blue,
        };
    }
}

int main() {
    Color c=Color::Red;
    wahaha::hihihi::juju a=wahaha::hihihi::juju::Red;
    print_template_pretty<Color, Color::Green>();
    print_template_pretty<Color, Color::Red>();
    print_pretty();

    std::cout << enum_to_string(Color::Blue) << '\n';  // prints "Blue"
    std::cout<< enum_to_string(c) << '\n'; // prints empty line
    std::cout<<enum_to_string(LicenseConfigStatus::Loaded) << '\n';
    std::cout<<enum_to_string(a) << '\n';
    return 0;

}

/*
#include <array>
#include <string_view>
#include <utility>
#include <cstddef>
#include <unordered_map>
#include <cctype>  // for std::isalpha

// [1] Name extraction
constexpr bool is_name_char(char c) noexcept {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           (c == '_') || (c == ':');
}

constexpr std::string_view pretty_name(std::string_view sv) noexcept {
    // Phase 1: strip trailing non-name chars
    while (!sv.empty() && !is_name_char(sv.back())) {
        sv.remove_suffix(1);
    }
    // Phase 2: find continuous block of name chars
    size_t end = sv.size();
    size_t start = end;
    while (start > 0 && is_name_char(sv[start - 1])) {
        --start;
    }
    auto block = sv.substr(start, end - start);
    // If scoped ("::"), strip the scope
    if (auto pos = block.rfind("::"); pos != std::string_view::npos) {
        block.remove_prefix(pos + 2);
    }
    return block;
}

template <typename E, E V>
constexpr auto enum_raw_name() noexcept {
#if defined(__clang__) || defined(__GNUC__)
    return pretty_name({ __PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 1 });
#elif defined(_MSC_VER)
    return pretty_name({ __FUNCSIG__,       sizeof(__FUNCSIG__) - 1 });
#endif
}

// [2] Candidate generator
constexpr int ENUM_MIN = 0;
template <typename E>
constexpr E enum_value(size_t i) noexcept {
    return static_cast<E>(ENUM_MIN + static_cast<int>(i));
}

// [3] Build constexpr array of all (value,name) pairs
template <typename E, size_t... I>
constexpr auto make_entries(std::index_sequence<I...>) noexcept {
    return std::array<std::pair<E,std::string_view>, sizeof...(I)>{
        std::pair{ enum_value<E>(I), enum_raw_name<E, enum_value<E>(I)>() }...
    };
}

template <typename E>
constexpr auto enum_entries() noexcept {
    return make_entries<E>(std::make_index_sequence<4096>{});
}

// [4] Build and filter into a runtime unordered_map
template <typename E>
const std::unordered_map<E, std::string_view>& enum_map() {
    static const auto entries = enum_entries<E>();
    static std::unordered_map<E, std::string_view> map = []{
        std::unordered_map<E, std::string_view> m;
        m.reserve(entries.size());
        for (auto const &p : entries) {
            auto name = p.second;
            // only insert if name is non-empty and starts with alpha
            if (!name.empty() && std::isalpha(static_cast<unsigned char>(name[0]))) {
                m.emplace(p.first, name);
            }
        }
        return m;
    }();
    return map;
}

// [5] Public API
template <typename E>
std::string_view enum_to_string(E v) {
    auto const &m = enum_map<E>();
    auto it = m.find(v);
    return (it != m.end() ? it->second : std::string_view{});
}

// Usage example
#include <iostream>
enum class Color : int { Red = 5, Green = 6, Blue = 10 };
int main() {
    std::cout << enum_to_string(Color::Red) << '\n';    // prints "Red"
    std::cout << enum_to_string(Color::Green) << '\n';  // prints "Green"
    std::cout << enum_to_string(Color::Blue) << '\n';   // prints "Blue"
    std::cout << enum_to_string(static_cast<Color>(7)) << '\n'; // prints empty line
    return 0;
}
*/

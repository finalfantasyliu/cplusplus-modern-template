//
// Created by finalfantasyliu on 2025/6/5.
//

#ifndef LICENSE_STATUS_HPP
#define LICENSE_STATUS_HPP
#include "enum_operation.hpp"
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
template<>
struct EnumUtils::DefinedMap<LicenseConfigStatus>:std::true_type {
    static inline const std::unordered_map<LicenseConfigStatus,std::string_view> map{
        {LicenseConfigStatus::None,"None"},
        {LicenseConfigStatus::Uninitialized,"uninitialized"},
        {LicenseConfigStatus::Loaded,"Loaded"},
        {LicenseConfigStatus::Updated,"Updated"},
        {LicenseConfigStatus::Invalid,"Invalid"},
        {LicenseConfigStatus::Expired,"Expired"},
        {LicenseConfigStatus::Error,"Error"},
    };
};
#endif //LICENSE_STATUS_HPP

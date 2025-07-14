#include <iostream>

#include "enum_operation.hpp"
#include "license_status.hpp"


int main() {
LicenseConfigStatus c=LicenseConfigStatus::Loaded;
    std::cout<<EnumUtils::EnumToString<LicenseConfigStatus>(c);
    return 0;
}
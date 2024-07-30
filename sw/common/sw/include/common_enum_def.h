/*
Copyright (C) 2024 Andreas Lagler

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef COMMON_ENUM_DEF_H
#define COMMON_ENUM_DEF_H

#include <stdint.h>

/*
This macro is used to define an enum class or enum typedef depending on __cplusplus flag.
In both cases, the same enum name and enum values are used.
Three special enum values will be appended: NOFENTRIES, MIN = 0 and MAX = NOFENTRIES - 1

Example usage:

DEFINE_ENUM(MyEnum, VALUE_ONE, VALUE_TWO, VALUE_THREE)

int main() {
#ifdef __cplusplus
MyEnum value = MyEnum::VALUE_ONE;
#else
MY_ENUM_T value = E_MY_ENUM_VALUE_ONE;
#endif

return 0;
}
*/

// Helper macros for string manipulation
#define CONCATENATE(arg1, arg2) CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2

// Convert CamelCase to UPPER_CASE_WITH_UNDERSCORE for C enum typedef name
#define CONVERT_TO_UNDERSCORE_CASE(name) CONVERT_TO_UNDERSCORE_CASE1(name)
#define CONVERT_TO_UNDERSCORE_CASE1(first, ...) UNDERSCORE_CASE_HELPER(first) CONVERT_TO_UNDERSCORE_CASE2(__VA_ARGS__)
#define CONVERT_TO_UNDERSCORE_CASE2(...) __VA_ARGS__
#define UNDERSCORE_CASE_HELPER(x) _##x

// Check if compiling with C++
#ifdef __cplusplus
#define IF_CPP(cpp_code, c_code) cpp_code
#else
#define IF_CPP(cpp_code, c_code) c_code
#endif

// Define enum class for C++
#define DEFINE_ENUM_CLASS(EnumName, ...) \
enum class EnumName : uint8_t { \
    __VA_ARGS__, \
    NOFENTRIES, \
    MIN = 0, \
    MAX = NOFENTRIES - 1 \
};

// Define enum typedef for C
#define DEFINE_ENUM_TYPEDEF(EnumName, ...) \
typedef enum { \
    PREFIX_ENUM_VALUES(EnumName, __VA_ARGS__), \
    CONCATENATE(E, CONCATENATE(EnumName, _NOFENTRIES)), \
    CONCATENATE(E, CONCATENATE(EnumName, _MIN)) = 0, \
    CONCATENATE(E, CONCATENATE(EnumName, _MAX)) = CONCATENATE(E, CONCATENATE(EnumName, _NOFENTRIES)) - 1 \
} EnumName;

// Main macro to define either C++ enum class or C enum typedef
#define DEFINE_ENUM(EnumName, ...) \
IF_CPP( \
DEFINE_ENUM_CLASS(EnumName, __VA_ARGS__), \
DEFINE_ENUM_TYPEDEF(CONVERT_TO_UNDERSCORE_CASE(EnumName), __VA_ARGS__) \
)

// Prefix enum values for C enum typedef
#define PREFIX_ENUM_VALUES(EnumName, ...) PREFIX_ENUM_VALUES1(EnumName, __VA_ARGS__)
#define PREFIX_ENUM_VALUES1(EnumName, first, ...) \
CONCATENATE(E_, CONCATENATE(EnumName, _)) first, PREFIX_ENUM_VALUES2(EnumName, __VA_ARGS__)
#define PREFIX_ENUM_VALUES2(EnumName, ...) PREFIX_ENUM_VALUES_HELPER(__VA_ARGS__)
#define PREFIX_ENUM_VALUES_HELPER(...) __VA_ARGS__


//// Example usage
//DEFINE_ENUM(MyEnum, VALUE_ONE, VALUE_TWO, VALUE_THREE)
//
//int main() {
    //#ifdef __cplusplus
    //MyEnum value = MyEnum::VALUE_ONE;
    //#else
    //MY_ENUM_T value = E_MY_ENUM_VALUE_ONE;
    //#endif
//
    //return 0;
//}

#endif
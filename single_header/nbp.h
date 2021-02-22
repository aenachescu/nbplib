/*
No Bugs in Production (NBP) Library
https://github.com/aenachescu/nbplib

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright (c) 2019-2020 Alin Enachescu <https://github.com/aenachescu>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _H_NBP_NBP
#define _H_NBP_NBP

#define NBP_MAKE_VERSION(major, minor, rev)                                    \
    (((major & 0xFFFF) << 16) | ((minor & 0xFF) << 8) | ((rev & 0xFF) << 8))

#define NBP_VERSION_MAJOR    1
#define NBP_VERSION_MINOR    0
#define NBP_VERSION_REVISION 0

#define NBP_VERSION_STR "1.0.0"

#define NBP_VERSION                                                            \
    NBP_MAKE_VERSION(NBP_VERSION_MAJOR, NBP_VERSION_MINOR, NBP_VERSION_REVISION)

/*
 * Make sure there is only one compiler defined
 */
#undef INTERNAL_NBP_COMPILER_DEFINED

#ifdef NBP_COMPILER_GCC
#define INTERNAL_NBP_COMPILER_DEFINED
#endif // end if NBP_COMPILER_GCC

#ifdef NBP_COMPILER_GXX
#ifndef INTERNAL_NBP_COMPILER_DEFINED
#define INTERNAL_NBP_COMPILER_DEFINED
#else // INTERNAL_NBP_COMPILER_DEFINED is defined
#error "More NBP_COMPILER_* macros are defined"
#endif // end if INTERNAL_NBP_COMPILER_DEFINED
#endif // end if NBP_COMPILER_GXX

#ifdef NBP_COMPILER_CLANG
#ifndef INTERNAL_NBP_COMPILER_DEFINED
#define INTERNAL_NBP_COMPILER_DEFINED
#else // INTERNAL_NBP_COMPILER_DEFINED is defined
#error "More NBP_COMPILER_* macros are defined"
#endif // end if INTERNAL_NBP_COMPILER_DEFINED
#endif // end if NBP_COMPILER_CLANG

#ifdef NBP_COMPILER_CUSTOM
#ifndef INTERNAL_NBP_COMPILER_DEFINED
#define INTERNAL_NBP_COMPILER_DEFINED
#else // INTERNAL_NBP_COMPILER_DEFINED is defined
#error "More NBP_COMPILER_* macros are defined"
#endif // end if INTERNAL_NBP_COMPILER_DEFINED
#endif // end if NBP_COMPILER_CUSTOM

/*
 * If there is no compiler defined then try to detect the compiler
 */
#ifndef INTERNAL_NBP_COMPILER_DEFINED
#ifdef __clang__
#define NBP_COMPILER_CLANG
#elif __GNUG__
#define NBP_COMPILER_GXX
#elif __GNUC__
#define NBP_COMPILER_GCC
#else // no compiler detected
#error "Failed to detect any compiler"
#endif // end if __clang__
#endif // end if INTERNAL_NBP_COMPILER_DEFINED

#undef INTERNAL_NBP_COMPILER_DEFINED

/*
 * If there is no compiler version defined then try to detect the compiler
 * version
 */
#ifndef NBP_COMPILER_VERSION
#ifdef NBP_COMPILER_GCC
#define NBP_COMPILER_VERSION __GNUC__
#elif defined NBP_COMPILER_GXX
#define NBP_COMPILER_VERSION __GNUG__
#elif defined NBP_COMPILER_CLANG
#define NBP_COMPILER_VERSION __clang_major__
#elif defined NBP_COMPILER_CUSTOM
#error "Cannot detect compiler version when a custom compiler is used"
#else
#error "Failed to detect compiler version because no compiler is defined"
#endif // end if NBP_COMPILER_GCC
#endif // end if NBP_COMPILER_VERSION

/*
 * Make sure there is only one C or C++ standard defined
 */
#undef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED

#ifdef NBP_LANGUAGE_STANDARD_C99
#define INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#elif defined NBP_LANGUAGE_STANDARD_C11
#ifndef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#define INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#else // INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED is defined
#error "More NBP_LANGUAGE_STANDARD_* macros are defined"
#endif // end if INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#elif defined NBP_LANGUAGE_STANDARD_CPP03
#ifndef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#define INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#else // INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED is defined
#error "More NBP_LANGUAGE_STANDARD_* macros are defined"
#endif // end if INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#elif defined NBP_LANGUAGE_STANDARD_CPP11
#ifndef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#define INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#else // INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED is defined
#error "More NBP_LANGUAGE_STANDARD_* macros are defined"
#endif // end if INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#elif defined NBP_LANGUAGE_STANDARD_CPP14
#ifndef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#define INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#else // INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED is defined
#error "More NBP_LANGUAGE_STANDARD_* macros are defined"
#endif // end if INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#elif defined NBP_LANGUAGE_STANDARD_CPP17
#ifndef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#define INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#else // INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED is defined
#error "More NBP_LANGUAGE_STANDARD_* macros are defined"
#endif // end if INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#endif // end if NBP_LANGUAGE_STANDARD_C99

/*
 * If there is no C or C++ standard defined then try to detect the standard
 */
#ifndef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED
#ifdef NBP_COMPILER_GCC
#if __STDC_VERSION__ == 201112
#define NBP_LANGUAGE_STANDARD_C11
#elif __STDC_VERSION__ == 199901
#define NBP_LANGUAGE_STANDARD_C99
#else
#error "Failed to detect language standard for gcc compiler"
#endif // end if __STDC_VERSION__ == 201112
#elif defined NBP_COMPILER_GXX
#if __cplusplus >= 201500
#define NBP_LANGUAGE_STANDARD_CPP17
#elif __cplusplus >= 201400
#define NBP_LANGUAGE_STANDARD_CPP14
#elif __cplusplus >= 201100
#define NBP_LANGUAGE_STANDARD_CPP11
#elif __cplusplus >= 199700
#define NBP_LANGUAGE_STANDARD_CPP03
#else
#error "Failed to detect language standard for g++ compiler"
#endif // end if __cplusplus >= 201500
#elif defined NBP_COMPILER_CLANG
#if __STDC_VERSION__ == 201112
#define NBP_LANGUAGE_STANDARD_C11
#elif __STDC_VERSION__ == 199901
#define NBP_LANGUAGE_STANDARD_C99
#else
#error "Failed to detect language standard for clang compiler"
#endif // end if __STDC_VERSION__ == 201112
#elif defined NBP_COMPILER_CUSTOM
#error "Cannot detect language standard when a custom compiler is used"
#else
#error "Failed to detect language standard because no compiler is set"
#endif // end if NBP_COMPILER_GCC
#endif // end if INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED

#undef INTERNAL_NBP_LANGUAGE_STANDARD_DEFINED

/*
 * Define NBP_LANGUAGE_ macro
 */
#undef NBP_LANGUAGE_C
#undef NBP_LANGUAGE_CPP

#ifdef NBP_LANGUAGE_STANDARD_C99
#define NBP_LANGUAGE_C
#endif // end if NBP_LANGUAGE_STANDARD_C99

#ifdef NBP_LANGUAGE_STANDARD_C11
#define NBP_LANGUAGE_C
#endif // end if NBP_LANGUAGE_STANDARD_C11

#ifdef NBP_LANGUAGE_STANDARD_CPP03
#define NBP_LANGUAGE_CPP
#endif // end if NBP_LANGUAGE_STANDARD_CPP03

#ifdef NBP_LANGUAGE_STANDARD_CPP11
#define NBP_LANGUAGE_CPP
#endif // end if NBP_LANGUAGE_STANDARD_CPP11

#ifdef NBP_LANGUAGE_STANDARD_CPP14
#define NBP_LANGUAGE_CPP
#endif // end if NBP_LANGUAGE_STANDARD_CPP14

#ifdef NBP_LANGUAGE_STANDARD_CPP17
#define NBP_LANGUAGE_CPP
#endif // end if NBP_LANGUAGE_STANDARD_CPP17

/*
 * Make sure there is only one platform defined
 */
#undef INTERNAL_NBP_PLATFORM_DEFINED

#ifdef NBP_PLATFORM_32_BIT
#define INTERNAL_NBP_PLATFORM_DEFINED
#endif // end if NBP_PLATFORM_32_BIT

#ifdef NBP_PLATFORM_64_BIT
#ifndef INTERNAL_NBP_PLATFORM_DEFINED
#define INTERNAL_NBP_PLATFORM_DEFINED
#else // INTERNAL_NBP_PLATFORM_DEFINED is defined
#error "More NBP_PLATFORM_* macros are defined"
#endif // end if INTERNAL_NBP_PLATFORM_DEFINED
#endif // end if NBP_PLATFORM_64_BIT

/*
 * If there is no platform defined then try to detect the platform
 */
#ifndef INTERNAL_NBP_PLATFORM_DEFINED
#ifdef NBP_COMPILER_GCC
#include <stdint.h>
#if UINTPTR_MAX == 0xffffffff
#define NBP_PLATFORM_32_BIT
#elif UINTPTR_MAX == 0xffffffffffffffff
#define NBP_PLATFORM_64_BIT
#else
#error "Failed to detect platform for gcc compiler"
#endif // end if UINTPTR_MAX == 0xffffffff
#elif defined NBP_COMPILER_GXX
#include <stdint.h>
#if UINTPTR_MAX == 0xffffffff
#define NBP_PLATFORM_32_BIT
#elif UINTPTR_MAX == 0xffffffffffffffff
#define NBP_PLATFORM_64_BIT
#else
#error "Failed to detect platform for g++ compiler"
#endif // end if UINTPTR_MAX == 0xffffffff
#elif defined NBP_COMPILER_CLANG
#include <stdint.h>
#if UINTPTR_MAX == 0xffffffff
#define NBP_PLATFORM_32_BIT
#elif UINTPTR_MAX == 0xffffffffffffffff
#define NBP_PLATFORM_64_BIT
#else
#error "Failed to detect platform for clang compiler"
#endif // end if UINTPTR_MAX == 0xffffffff
#elif defined NBP_COMPILER_CUSTOM
#error "Cannot detect platform when a custom compiler is used"
#else
#error "Failed to detect platform because no compiler is set"
#endif // end if NBP_COMPILER_GCC
#endif // end if INTERNAL_NBP_PLATFORM_DEFINED

#undef INTERNAL_NBP_PLATFORM_DEFINED

/*
 * Make sure there is only one OS defined
 */
#undef INTERNAL_NBP_OS_DEFINED

#ifdef NBP_OS_LINUX
#define INTERNAL_NBP_OS_DEFINED
#endif // end if NBP_OS_LINUX

#ifdef NBP_OS_WINDOWS
#ifndef INTERNAL_NBP_OS_DEFINED
#define INTERNAL_NBP_OS_DEFINED
#else // INTERNAL_NBP_OS_DEFINED is defined
#error "More NBP_OS_* macros are defined"
#endif // end if INTERNAL_NBP_OS_DEFINED
#endif // end if NBP_OS_WINDOWS

#ifdef NBP_OS_MAC
#ifndef INTERNAL_NBP_OS_DEFINED
#define INTERNAL_NBP_OS_DEFINED
#else // INTERNAL_NBP_OS_DEFINED is defined
#error "More NBP_OS_* macros are defined"
#endif // end if INTERNAL_NBP_OS_DEFINED
#endif // end if NBP_OS_MAC

#ifdef NBP_OS_CUSTOM
#ifndef INTERNAL_NBP_OS_DEFINED
#define INTERNAL_NBP_OS_DEFINED
#else // INTERNAL_NBP_OS_DEFINED is defined
#error "More NBP_OS_* macros are defined"
#endif // end if INTERNAL_NBP_OS_DEFINED
#endif // end if NBP_OS_CUSTOM

/*
 * If there is no OS defined then try to detect the OS
 */
#ifndef INTERNAL_NBP_OS_DEFINED
#ifdef __linux__
#define NBP_OS_LINUX
#else // no OS detected
#error "Failed to detect any OS"
#endif // end if __linux__
#endif // end if INTERNAL_NBP_OS_DEFINED

#undef INTERNAL_NBP_OS_DEFINED

/*
 * Make sure there is only one defined scheduler
 */
#undef INTERNAL_NBP_SCHEDULER_DEFINED

#ifdef NBP_CUSTOM_SCHEDULER
#define INTERNAL_NBP_SCHEDULER_DEFINED
#endif // end if NBP_CUSTOM_SCHEDULER

#ifdef NBP_MT_SCHEDULER
#ifdef INTERNAL_NBP_SCHEDULER_DEFINED
#error "Cannot enable NBP_MT_SCHEDULER because another scheduler is enabled"
#else // INTERNAL_NBP_SCHEDULER_DEFINED not defined
#define INTERNAL_NBP_SCHEDULER_DEFINED
#define NBP_MT_SUPPORT
#endif // end if INTERNAL_NBP_SCHEDULER_DEFINED
#endif // end if NBP_MT_SCHEDULER

#ifdef NBP_BASIC_SCHEDULER
#ifdef INTERNAL_NBP_SCHEDULER_DEFINED
#error "Cannot enable NBP_BASIC_SCHEDULER because another scheduler is enabled"
#else // INTERNAL_NBP_SCHEDULER_DEFINED not defined
#define INTERNAL_NBP_SCHEDULER_DEFINED
#endif // end if INTERNAL_NBP_SCHEDULER_DEFINED
#endif // end if NBP_BASIC_SCHEDULER

/*
 * If no scheduler is defined then define the default scheduler
 */
#ifndef INTERNAL_NBP_SCHEDULER_DEFINED
#define NBP_BASIC_SCHEDULER
#endif // end if INTERNAL_NBP_SCHEDULER_DEFINED

#undef INTERNAL_NBP_SCHEDULER_DEFINED

/*
 * If no printer is defined then define the default printer
 */
#if ! defined NBP_CUSTOM_PRINTER && ! defined NBP_DEFAULT_PRINTER
#define NBP_DEFAULT_PRINTER
#endif // end if ! defined NBP_CUSTOM_PRINTER && ! defined NBP_DEFAULT_PRINTER

#ifdef NBP_COMPILER_GCC

#define NBP_MAYBE_UNUSED_PARAMETER __attribute__((unused))

#define NBP_SOURCE_FILE __FILE__
#define NBP_SOURCE_LINE __LINE__

#endif // end if NBP_COMPILER_GCC

#ifdef NBP_COMPILER_GXX

#define NBP_MAYBE_UNUSED_PARAMETER __attribute__((unused))

#define NBP_SOURCE_FILE __FILE__
#define NBP_SOURCE_LINE __LINE__

#endif // end if NBP_COMPILER_GXX

#ifdef NBP_COMPILER_CLANG

#define NBP_MAYBE_UNUSED_PARAMETER __attribute__((unused))

#define NBP_SOURCE_FILE __FILE__
#define NBP_SOURCE_LINE __LINE__

#endif // end if NBP_COMPILER_CLANG

#ifndef NBP_MAYBE_UNUSED_PARAMETER
#define NBP_MAYBE_UNUSED_PARAMETER
#error "NBP_MAYBE_UNUSED_PARAMETER is not defined!"
#endif // end if NBP_MAYBE_UNUSED_PARAMETER

#ifndef NBP_SOURCE_FILE
#define NBP_SOURCE_FILE "not defined"
#error "NBP_SOURCE_FILE is not defined!"
#endif // end if NBP_SOURCE_FILE

#ifndef NBP_SOURCE_LINE
#define NBP_SOURCE_LINE 0
#error "NBP_SOURCE_LINE is not defined!"
#endif // end if NBP_SOURCE_LINE

#define INTERNAL_NBP_PP_CONCAT_IMPL(a, b) a##b

#define NBP_PP_CONCAT(a, b) INTERNAL_NBP_PP_CONCAT_IMPL(a, b)

#define INTERNAL_NBP_PP_COUNT_IMPL(                                            \
    _,                                                                         \
    _32,                                                                       \
    _31,                                                                       \
    _30,                                                                       \
    _29,                                                                       \
    _28,                                                                       \
    _27,                                                                       \
    _26,                                                                       \
    _25,                                                                       \
    _24,                                                                       \
    _23,                                                                       \
    _22,                                                                       \
    _21,                                                                       \
    _20,                                                                       \
    _19,                                                                       \
    _18,                                                                       \
    _17,                                                                       \
    _16,                                                                       \
    _15,                                                                       \
    _14,                                                                       \
    _13,                                                                       \
    _12,                                                                       \
    _11,                                                                       \
    _10,                                                                       \
    _9,                                                                        \
    _8,                                                                        \
    _7,                                                                        \
    _6,                                                                        \
    _5,                                                                        \
    _4,                                                                        \
    _3,                                                                        \
    _2,                                                                        \
    _n,                                                                        \
    ...)                                                                       \
    _n

#define NBP_PP_COUNT(...)                                                      \
    INTERNAL_NBP_PP_COUNT_IMPL(                                                \
        P##__VA_ARGS__,                                                        \
        32,                                                                    \
        31,                                                                    \
        30,                                                                    \
        29,                                                                    \
        28,                                                                    \
        27,                                                                    \
        26,                                                                    \
        25,                                                                    \
        24,                                                                    \
        23,                                                                    \
        22,                                                                    \
        21,                                                                    \
        20,                                                                    \
        19,                                                                    \
        18,                                                                    \
        17,                                                                    \
        16,                                                                    \
        15,                                                                    \
        14,                                                                    \
        13,                                                                    \
        12,                                                                    \
        11,                                                                    \
        10,                                                                    \
        9,                                                                     \
        8,                                                                     \
        7,                                                                     \
        6,                                                                     \
        5,                                                                     \
        4,                                                                     \
        3,                                                                     \
        2,                                                                     \
        1, )

#define NBP_PP_PARSE_PARAMETER_1(prefix, parameter) INTERNAL_NBP_##parameter
#define NBP_PP_PARSE_PARAMETER_2(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_1(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_3(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_4(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_3(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_5(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_4(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_6(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_5(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_7(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_6(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_8(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_7(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_9(prefix, parameter, ...)                       \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_8(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_10(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_9(                         \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_11(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_10(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_12(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_11(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_13(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_12(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_14(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_13(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_15(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_14(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_16(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_15(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_17(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_16(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_18(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_17(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_19(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_18(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_20(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_19(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_21(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_20(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_22(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_21(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_23(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_22(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_24(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_23(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_25(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_24(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_26(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_25(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_27(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_26(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_28(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_27(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_29(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_28(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_30(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_29(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_31(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_30(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_32(prefix, parameter, ...)                      \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_31(                        \
        prefix,                                                                \
        prefix##__VA_ARGS__)

#define NBP_PP_PARSE_PARAMETER_2_1(prefix, parameter) INTERNAL_NBP_##parameter
#define NBP_PP_PARSE_PARAMETER_2_2(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_1(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_3(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_2(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_4(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_3(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_5(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_4(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_6(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_5(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_7(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_6(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_8(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_7(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_9(prefix, parameter, ...)                     \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_8(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_10(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_9(                       \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_11(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_10(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_12(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_11(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_13(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_12(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_14(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_13(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_15(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_14(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_16(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_15(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_17(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_16(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_18(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_17(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_19(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_18(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_20(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_19(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_21(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_20(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_22(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_21(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_23(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_22(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_24(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_23(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_25(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_24(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_26(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_25(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_27(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_26(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_28(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_27(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_29(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_28(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_30(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_29(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_31(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_30(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_2_32(prefix, parameter, ...)                    \
    INTERNAL_NBP_##parameter NBP_PP_PARSE_PARAMETER_2_31(                      \
        prefix,                                                                \
        prefix##__VA_ARGS__)

/**
 * TODO: add docs
 */
enum nbp_error_context_type_e
{
    ect_empty  = 0x10000000,
    ect_string = 0x10000001,
    ect_custom = 0x10000002
};
typedef enum nbp_error_context_type_e nbp_error_context_type_e;

/**
 * TODO: add docs
 */
enum nbp_error_code_e
{
    ec_success                     = 0,
    ec_tests_failed                = 1,
    ec_out_of_memory               = 2,
    ec_sync_error                  = 3,
    ec_invalid_command_line        = 4,
    ec_not_all_tests_were_run      = 5,
    ec_invalid_scheduler_interface = 6,
    ec_invalid_number_of_runs      = 7,
    ec_scheduler_run_is_disabled   = 8,
    ec_unexpected_state            = 9,
    ec_invalid_parent              = 10,
    ec_no_test_case_instantiated   = 11,
};
typedef enum nbp_error_code_e nbp_error_code_e;

struct nbp_error_t
{
    nbp_error_code_e errorCode;
    int line;
    const char* file;

    nbp_error_context_type_e contextType;
    union
    {
        const char* stringContext;
        void* customContext;
    };
};
typedef struct nbp_error_t nbp_error_t;

enum internal_nbp_skip_flag_e
{
    sf_is_not_set   = 0x50000000,
    sf_is_set       = 0x50000001,
    sf_is_processed = 0x50000002,
};
typedef enum internal_nbp_skip_flag_e internal_nbp_skip_flag_e;

enum nbp_memory_tag_e
{
    mt_test_case_instance  = 0x4E425000,
    mt_test_case           = 0x4E425001,
    mt_test_suite_instance = 0x4E425002,
    mt_test_suite          = 0x4E425003,
    mt_module_instance     = 0x4E425004,
    mt_module              = 0x4E425005,
    mt_default_printer     = 0x4E425006,
    mt_basic_scheduler     = 0x4E425007,
};
typedef enum nbp_memory_tag_e nbp_memory_tag_e;

#ifdef NBP_MT_SUPPORT

#ifdef NBP_OS_LINUX
#include <semaphore.h>

/*
 * Atomic int wrapper
 */

#define NBP_ATOMIC_INT_TYPE int

#define NBP_ATOMIC_INT_INIT(val) val

#define NBP_ATOMIC_INT_LOAD(ptr) __atomic_load_n((ptr), __ATOMIC_SEQ_CST)

#define NBP_ATOMIC_INT_STORE(ptr, value)                                       \
    __atomic_store_n((ptr), (value), __ATOMIC_SEQ_CST)

#define NBP_ATOMIC_INT_ADD_AND_FETCH(ptr, value)                               \
    __sync_add_and_fetch((ptr), (value))

#define NBP_ATOMIC_INT_SUB_AND_FETCH(ptr, value)                               \
    __sync_sub_and_fetch((ptr), (value))

#define NBP_ATOMIC_INT_COMPARE_AND_SWAP(ptr, oldVal, newVal)                   \
    __sync_val_compare_and_swap((ptr), (oldVal), (newVal))

/*
 * Atomic unsigned int wrapper
 */

#define NBP_ATOMIC_UINT_TYPE unsigned int

#define NBP_ATOMIC_UINT_INIT(val) val

#define NBP_ATOMIC_UINT_LOAD(ptr) __atomic_load_n((ptr), __ATOMIC_SEQ_CST)

#define NBP_ATOMIC_UINT_STORE(ptr, value)                                      \
    __atomic_store_n((ptr), (value), __ATOMIC_SEQ_CST)

#define NBP_ATOMIC_UINT_ADD_AND_FETCH(ptr, value)                              \
    __sync_add_and_fetch((ptr), (value))

#define NBP_ATOMIC_UINT_SUB_AND_FETCH(ptr, value)                              \
    __sync_sub_and_fetch((ptr), (value))

#define NBP_ATOMIC_UINT_COMPARE_AND_SWAP(ptr, oldVal, newVal)                  \
    __sync_val_compare_and_swap((ptr), (oldVal), (newVal))

/*
 * Event wrapper
 */

#define NBP_SYNC_EVENT_TYPE sem_t

#define NBP_SYNC_EVENT_DEFAULT_VALUE                                           \
    {                                                                          \
        .__align = 0                                                           \
    }

#define NBP_SYNC_EVENT_INIT(ev) internal_nbp_linux_sync_event_init(&ev)

#define NBP_SYNC_EVENT_UNINIT(ev) internal_nbp_linux_sync_event_uninit(&ev)

#define NBP_SYNC_EVENT_WAIT(ev) internal_nbp_linux_sync_event_wait(&ev)

#define NBP_SYNC_EVENT_NOTIFY(ev) internal_nbp_linux_sync_event_notify(&ev)

#endif // end if NBP_OS_LINUX

#ifdef NBP_OS_WINDOWS
#error "Not supported"
#endif // end if NBP_OS_WINDOWS

#ifdef NBP_OS_MAC
#error "Not supported"
#endif // end if NBP_OS_MAC

#ifdef NBP_OS_CUSTOM
#error "Not supported"
#endif // end if NBP_OS_CUSTOM

/*
 * Check if atomic int wrapper is defined, otherwise define a dummy atomic int
 * wrapper.
 * If NBP_OS_* is not defined then the atomic int wrapper will not be defined
 * so the compiler will generate a lot of errors and the error message that
 * says that there is no NBP_OS_* defined is hard to see.
 */

#ifndef NBP_ATOMIC_INT_TYPE
#define NBP_ATOMIC_INT_TYPE int
#endif // end if NBP_ATOMIC_INT_TYPE

#ifndef NBP_ATOMIC_INT_INIT
#define NBP_ATOMIC_INT_INIT(val) val
#endif // end if NBP_ATOMIC_INT_INIT

#ifndef NBP_ATOMIC_INT_LOAD
#define NBP_ATOMIC_INT_LOAD(ptr) (*(ptr))
#endif // end if NBP_ATOMIC_INT_LOAD

#ifndef NBP_ATOMIC_INT_STORE
#define NBP_ATOMIC_INT_STORE(ptr, value) *(ptr) = (value)
#endif // end if NBP_ATOMIC_INT_STORE

#ifndef NBP_ATOMIC_INT_ADD_AND_FETCH
#define NBP_ATOMIC_INT_ADD_AND_FETCH(ptr, value) ((*(ptr)) += (value))
#endif // end if NBP_ATOMIC_INT_ADD_AND_FETCH

#ifndef NBP_ATOMIC_INT_SUB_AND_FETCH
#define NBP_ATOMIC_INT_SUB_AND_FETCH(ptr, value) ((*(ptr)) -= (value))
#endif // end if NBP_ATOMIC_INT_SUB_AND_FETCH

#ifndef NBP_ATOMIC_INT_COMPARE_AND_SWAP
#define NBP_ATOMIC_INT_COMPARE_AND_SWAP(ptr, oldVal, newVal)                   \
    ((*(ptr)) == (oldVal) ? (*(ptr)) = (newVal), (oldVal) : (*(ptr)))
#endif // end if NBP_ATOMIC_INT_COMPARE_AND_SWAP

/*
 * Check if atomic uint wrapper is defined, otherwise define a dummy atomic uint
 * wrapper.
 * If NBP_OS_* is not defined then the atomic uint wrapper will not be defined
 * so the compiler will generate a lot of errors and the error message that
 * says that there is no NBP_OS_* defined is hard to see.
 */

#ifndef NBP_ATOMIC_UINT_TYPE
#define NBP_ATOMIC_UINT_TYPE unsigned int
#endif // end if NBP_ATOMIC_UINT_TYPE

#ifndef NBP_ATOMIC_UINT_INIT
#define NBP_ATOMIC_UINT_INIT(val) val
#endif // end if NBP_ATOMIC_UINT_INIT

#ifndef NBP_ATOMIC_UINT_LOAD
#define NBP_ATOMIC_UINT_LOAD(ptr) (*(ptr))
#endif // end if NBP_ATOMIC_UINT_LOAD

#ifndef NBP_ATOMIC_UINT_STORE
#define NBP_ATOMIC_UINT_STORE(ptr, value) *(ptr) = (value)
#endif // end if NBP_ATOMIC_UINT_STORE

#ifndef NBP_ATOMIC_UINT_ADD_AND_FETCH
#define NBP_ATOMIC_UINT_ADD_AND_FETCH(ptr, value) ((*(ptr)) += (value))
#endif // end if NBP_ATOMIC_UINT_ADD_AND_FETCH

#ifndef NBP_ATOMIC_UINT_SUB_AND_FETCH
#define NBP_ATOMIC_UINT_SUB_AND_FETCH(ptr, value) ((*(ptr)) -= (value))
#endif // end if NBP_ATOMIC_UINT_SUB_AND_FETCH

#ifndef NBP_ATOMIC_UINT_COMPARE_AND_SWAP
#define NBP_ATOMIC_UINT_COMPARE_AND_SWAP(ptr, oldVal, newVal)                  \
    ((*(ptr)) == (oldVal) ? (*(ptr)) = (newVal), (oldVal) : (*(ptr)))
#endif // end if NBP_ATOMIC_UINT_COMPARE_AND_SWAP

/*
 * Check if event wrapper is defined, otherwise define a dummy event wrapper.
 * If NBP_OS_* is not defined then the event wrapper will not be defined so the
 * compiler will generate a lot of errors and the error message that says that
 * there is no NBP_OS_* defined is hard to see.
 */

#ifndef NBP_SYNC_EVENT_TYPE
#define NBP_SYNC_EVENT_TYPE int
#endif // end if NBP_SYNC_EVENT_TYPE

#ifndef NBP_SYNC_EVENT_DEFAULT_VALUE
#define NBP_SYNC_EVENT_DEFAULT_VALUE 0
#endif // end if NBP_SYNC_EVENT_DEFAULT_VALUE

#ifndef NBP_SYNC_EVENT_INIT
#define NBP_SYNC_EVENT_INIT(ev) ec_success
#endif // end if NBP_SYNC_EVENT_INIT

#ifndef NBP_SYNC_EVENT_UNINIT
#define NBP_SYNC_EVENT_UNINIT(ev) ec_success
#endif // end if NBP_SYNC_EVENT_UNINIT

#ifndef NBP_SYNC_EVENT_WAIT
#define NBP_SYNC_EVENT_WAIT(ev) ec_success
#endif // end if NBP_SYNC_EVENT_WAIT

#ifndef NBP_SYNC_EVENT_NOTIFY
#define NBP_SYNC_EVENT_NOTIFY(ev) ec_success
#endif // end if NBP_SYNC_EVENT_NOTIFY

#else

/*
 * Atomic int wrapper
 */

#define NBP_ATOMIC_INT_TYPE int

#define NBP_ATOMIC_INT_INIT(val) val

#define NBP_ATOMIC_INT_LOAD(ptr) (*(ptr))

#define NBP_ATOMIC_INT_STORE(ptr, value) *(ptr) = (value)

#define NBP_ATOMIC_INT_ADD_AND_FETCH(ptr, value) ((*(ptr)) += (value))

#define NBP_ATOMIC_INT_SUB_AND_FETCH(ptr, value) ((*(ptr)) -= (value))

#define NBP_ATOMIC_INT_COMPARE_AND_SWAP(ptr, oldVal, newVal)                   \
    ((*(ptr)) == (oldVal) ? (*(ptr)) = (newVal), (oldVal) : (*(ptr)))

/*
 * Atomic unsigned int wrapper
 */

#define NBP_ATOMIC_UINT_TYPE unsigned int

#define NBP_ATOMIC_UINT_INIT(val) val

#define NBP_ATOMIC_UINT_LOAD(ptr) (*(ptr))

#define NBP_ATOMIC_UINT_STORE(ptr, value) *(ptr) = (value)

#define NBP_ATOMIC_UINT_ADD_AND_FETCH(ptr, value) ((*(ptr)) += (value))

#define NBP_ATOMIC_UINT_SUB_AND_FETCH(ptr, value) ((*(ptr)) -= (value))

#define NBP_ATOMIC_UINT_COMPARE_AND_SWAP(ptr, oldVal, newVal)                  \
    ((*(ptr)) == (oldVal) ? (*(ptr)) = (newVal), (oldVal) : (*(ptr)))

/*
 * Event wrapper
 */

#define NBP_SYNC_EVENT_TYPE int

#define NBP_SYNC_EVENT_DEFAULT_VALUE 0

#define NBP_SYNC_EVENT_INIT(ev) ec_success

#define NBP_SYNC_EVENT_UNINIT(ev) ec_success

#define NBP_SYNC_EVENT_WAIT(ev) ec_success

#define NBP_SYNC_EVENT_NOTIFY(ev) ec_success

#endif // end if NBP_MT_SUPPORT

#define NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_TEST_CASE_STATES          ((unsigned int) 5)

struct nbp_module_t;

struct nbp_test_suite_t;

struct nbp_test_case_details_t;
struct nbp_test_case_instance_t;
struct nbp_test_case_t;

typedef void (*nbp_test_case_setup_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

typedef void (*nbp_test_case_teardown_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

typedef void (*nbp_test_case_config_pfn_t)(
    struct nbp_test_case_details_t* /* testCaseDetails */
);

typedef void (*nbp_test_case_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

enum nbp_test_case_instance_state_e
{
    tcis_ready   = 0x20000000,
    tcis_running = 0x20000001,
    tcis_passed  = 0x20000002,
    tcis_failed  = 0x20000003,
    tcis_skipped = 0x20000004,
};
typedef enum nbp_test_case_instance_state_e nbp_test_case_instance_state_e;

enum nbp_test_case_state_e
{
    tcs_ready   = 0x21000000,
    tcs_running = 0x21000001,
    tcs_passed  = 0x21000002,
    tcs_failed  = 0x21000003,
    tcs_skipped = 0x21000004,
};
typedef enum nbp_test_case_state_e nbp_test_case_state_e;

struct nbp_test_case_setup_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_case_setup_pfn_t function;
};
typedef struct nbp_test_case_setup_details_t nbp_test_case_setup_details_t;

struct nbp_test_case_teardown_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_case_teardown_pfn_t function;
};
typedef struct nbp_test_case_teardown_details_t
    nbp_test_case_teardown_details_t;

struct nbp_test_case_details_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_test_case_config_pfn_t configFunction;
    nbp_test_case_pfn_t function;

    nbp_test_case_setup_details_t* setupDetails;
    nbp_test_case_teardown_details_t* teardownDetails;
};
typedef struct nbp_test_case_details_t nbp_test_case_details_t;

struct nbp_test_case_instance_t
{
    nbp_test_case_details_t* testCaseDetails;

    nbp_test_case_instance_state_e state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* module;
    struct nbp_test_suite_t* testSuite;
    unsigned int depth;

    int instantiationLine;

    nbp_test_case_setup_details_t* setupDetails;
    nbp_test_case_teardown_details_t* teardownDetails;

    struct nbp_test_case_t* runs;
    unsigned int numberOfRuns;

    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];

    struct nbp_test_case_instance_t* next;
    struct nbp_test_case_instance_t* prev;
};
typedef struct nbp_test_case_instance_t nbp_test_case_instance_t;

struct nbp_test_case_t
{
    nbp_test_case_instance_t* testCaseInstance;

    nbp_test_case_state_e state;

    NBP_ATOMIC_INT_TYPE isSkipped;
};
typedef struct nbp_test_case_t nbp_test_case_t;

#define NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_TEST_SUITE_STATES          ((unsigned int) 5)

struct nbp_module_t;

struct nbp_test_suite_details_t;
struct nbp_test_suite_instance_t;
struct nbp_test_suite_t;

typedef void (*nbp_test_suite_setup_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */
);

typedef void (*nbp_test_suite_teardown_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */
);

typedef void (*nbp_test_suite_config_pfn_t)(
    struct nbp_test_suite_details_t* /* testSuiteDetails */
);

typedef void (*nbp_test_suite_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */,
    struct nbp_test_suite_t* /* nbpParamTciParentTestSuite */,
    struct nbp_module_t* /*nbpParamTciParentModule */
);

enum nbp_test_suite_instance_state_e
{
    tsis_ready   = 0x30000000,
    tsis_running = 0x30000001,
    tsis_passed  = 0x30000002,
    tsis_failed  = 0x30000003,
    tsis_skipped = 0x30000004,
};
typedef enum nbp_test_suite_instance_state_e nbp_test_suite_instance_state_e;

enum nbp_test_suite_state_e
{
    tss_ready   = 0x31000000,
    tss_running = 0x31000001,
    tss_passed  = 0x31000002,
    tss_failed  = 0x31000003,
    tss_skipped = 0x31000004,
};
typedef enum nbp_test_suite_state_e nbp_test_suite_state_e;

struct nbp_test_suite_setup_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_suite_setup_pfn_t function;
};
typedef struct nbp_test_suite_setup_details_t nbp_test_suite_setup_details_t;

struct nbp_test_suite_teardown_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_suite_teardown_pfn_t function;
};
typedef struct nbp_test_suite_teardown_details_t
    nbp_test_suite_teardown_details_t;

struct nbp_test_suite_details_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_test_suite_config_pfn_t configFunction;
    nbp_test_suite_pfn_t function;

    nbp_test_suite_setup_details_t* setupDetails;
    nbp_test_suite_teardown_details_t* teardownDetails;
};
typedef struct nbp_test_suite_details_t nbp_test_suite_details_t;

struct nbp_test_suite_instance_t
{
    nbp_test_suite_details_t* testSuiteDetails;

    nbp_test_suite_instance_state_e state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* module;
    unsigned int depth;

    int instantiationLine;

    nbp_test_suite_setup_details_t* setupDetails;
    nbp_test_suite_teardown_details_t* teardownDetails;

    struct nbp_test_suite_t* runs;
    unsigned int numberOfRuns;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];

    struct nbp_test_suite_instance_t* next;
    struct nbp_test_suite_instance_t* prev;
};
typedef struct nbp_test_suite_instance_t nbp_test_suite_instance_t;

struct nbp_test_suite_t
{
    nbp_test_suite_instance_t* testSuiteInstance;

    nbp_test_suite_state_e state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    nbp_test_case_instance_t* firstTestCaseInstance;
    nbp_test_case_instance_t* lastTestCaseInstance;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
};
typedef struct nbp_test_suite_t nbp_test_suite_t;

#define NBP_NUMBER_OF_MODULE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_MODULE_STATES          ((unsigned int) 5)

struct nbp_module_details_t;
struct nbp_module_instance_t;
struct nbp_module_t;

typedef void (*nbp_module_setup_pfn_t)(
    struct nbp_module_t* /* nbpParamModule */);

typedef void (*nbp_module_teardown_pfn_t)(
    struct nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_mdoule_config_pfn_t)(
    struct nbp_module_details_t* /* moduleDetails */
);

typedef void (*nbp_module_pfn_t)(
    struct nbp_module_t* /* nbpParamModule*/,
    struct nbp_test_suite_t* /* nbpParamTciParentTestSuite */,
    struct nbp_module_t* /* nbpParamTciParentModule */,
    struct nbp_module_t* /* nbpParamTsiParentModule */,
    struct nbp_module_t* /* nbpParamMiParentModule */
);

enum nbp_module_instance_state_e
{
    mis_ready   = 0x40000000,
    mis_running = 0x40000001,
    mis_passed  = 0x40000002,
    mis_failed  = 0x40000003,
    mis_skipped = 0x40000004,
};
typedef enum nbp_module_instance_state_e nbp_module_instance_state_e;

enum nbp_module_state_e
{
    ms_ready   = 0x41000000,
    ms_running = 0x41000001,
    ms_passed  = 0x41000002,
    ms_failed  = 0x41000003,
    ms_skipped = 0x41000004,
};
typedef enum nbp_module_state_e nbp_module_state_e;

struct nbp_module_setup_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_module_setup_pfn_t function;
};
typedef struct nbp_module_setup_details_t nbp_module_setup_details_t;

struct nbp_module_teardown_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_module_teardown_pfn_t function;
};
typedef struct nbp_module_teardown_details_t nbp_module_teardown_details_t;

struct nbp_module_details_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_mdoule_config_pfn_t configFunction;
    nbp_module_pfn_t function;

    nbp_module_setup_details_t* setupDetails;
    nbp_module_teardown_details_t* teardownDetails;
};
typedef struct nbp_module_details_t nbp_module_details_t;

struct nbp_module_instance_t
{
    nbp_module_details_t* moduleDetails;

    nbp_module_instance_state_e state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* parent;
    unsigned int depth;

    int instantiationLine;

    nbp_module_setup_details_t* setupDetails;
    nbp_module_teardown_details_t* teardownDetails;

    struct nbp_module_t* runs;
    unsigned int numberOfRuns;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    unsigned int totalNumberOfTestSuites;
    unsigned int totalNumberOfTestSuiteInstances;
    unsigned int totalNumberOfModules;
    unsigned int totalNumberOfModuleInstances;

    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestSuiteInstances[NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfModules[NBP_NUMBER_OF_MODULE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfModuleInstances[NBP_NUMBER_OF_MODULE_INSTANCE_STATES];

    struct nbp_module_instance_t* next;
    struct nbp_module_instance_t* prev;
};
typedef struct nbp_module_instance_t nbp_module_instance_t;

struct nbp_module_t
{
    nbp_module_instance_t* moduleInstance;

    nbp_module_state_e state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    nbp_test_case_instance_t* firstTestCaseInstance;
    nbp_test_case_instance_t* lastTestCaseInstance;

    nbp_test_suite_instance_t* firstTestSuiteInstance;
    nbp_test_suite_instance_t* lastTestSuiteInstance;

    nbp_module_instance_t* firstModuleInstance;
    nbp_module_instance_t* lastModuleInstance;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    unsigned int totalNumberOfTestSuites;
    unsigned int totalNumberOfTestSuiteInstances;
    unsigned int totalNumberOfModules;
    unsigned int totalNumberOfModuleInstances;

    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestSuiteInstances[NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfModules[NBP_NUMBER_OF_MODULE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfModuleInstances[NBP_NUMBER_OF_MODULE_INSTANCE_STATES];
};
typedef struct nbp_module_t nbp_module_t;

struct nbp_printer_interface_t;

typedef void (*nbp_printer_config_pfn_t)(
    struct nbp_printer_interface_t* /* printerInterface */
);

typedef void (*nbp_printer_callback_init_pfn_t)(void);

typedef void (*nbp_printer_callback_uninit_pfn_t)(void);

typedef void (*nbp_printer_callback_handle_version_command_pfn_t)(void);

typedef void (*nbp_printer_callback_on_error_pfn_t)(
    nbp_error_t /* nbpParamError */
);

typedef void (*nbp_printer_callback_on_exit_pfn_t)(
    nbp_error_code_e /* nbpParamErrorCode */
);

typedef void (*nbp_printer_callback_on_instantiate_test_case_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_instantiate_test_suite_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_instantiate_test_suite_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_instantiate_module_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_instantiate_module_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_case_started_pfn_t)(
    nbp_test_case_t* /* nbpParamTestCase */,
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_case_completed_pfn_t)(
    nbp_test_case_t* /* nbpParamTestCase */,
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_case_instance_started_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_case_instance_completed_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_suite_started_pfn_t)(
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_suite_completed_pfn_t)(
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_suite_instance_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_test_suite_instance_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_printer_callback_on_module_started_pfn_t)(
    nbp_module_t* /* nbpParamModule */,
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_printer_callback_on_module_completed_pfn_t)(
    nbp_module_t* /* nbpParamModule */,
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_printer_callback_on_module_instance_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_printer_callback_on_module_instance_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

struct nbp_printer_interface_t
{
    const char* printerName;
    nbp_printer_config_pfn_t configFunction;

    int isInitialized;

    nbp_printer_callback_init_pfn_t initCbk;
    nbp_printer_callback_uninit_pfn_t uninitCbk;

    nbp_printer_callback_handle_version_command_pfn_t handleVersionCommandCbk;

    nbp_printer_callback_on_error_pfn_t errorCbk;
    nbp_printer_callback_on_exit_pfn_t exitCbk;

    nbp_printer_callback_on_instantiate_test_case_pfn_t instantiateTestCaseCbk;

    nbp_printer_callback_on_instantiate_test_suite_started_pfn_t
        instantiateTestSuiteStartedCbk;
    nbp_printer_callback_on_instantiate_test_suite_completed_pfn_t
        instantiateTestSuiteCompletedCbk;

    nbp_printer_callback_on_instantiate_module_started_pfn_t
        instantiateModuleStartedCbk;
    nbp_printer_callback_on_instantiate_module_completed_pfn_t
        instantiateModuleCompletedCbk;

    nbp_printer_callback_on_test_case_started_pfn_t testCaseStartedCbk;
    nbp_printer_callback_on_test_case_completed_pfn_t testCaseCompletedCbk;
    nbp_printer_callback_on_test_case_instance_started_pfn_t
        testCaseInstanceStartedCbk;
    nbp_printer_callback_on_test_case_instance_completed_pfn_t
        testCaseInstanceCompletedCbk;

    nbp_printer_callback_on_test_suite_started_pfn_t testSuiteStartedCbk;
    nbp_printer_callback_on_test_suite_completed_pfn_t testSuiteCompletedCbk;
    nbp_printer_callback_on_test_suite_instance_started_pfn_t
        testSuiteInstanceStartedCbk;
    nbp_printer_callback_on_test_suite_instance_completed_pfn_t
        testSuiteInstanceCompletedCbk;

    nbp_printer_callback_on_module_started_pfn_t moduleStartedCbk;
    nbp_printer_callback_on_module_completed_pfn_t moduleCompletedCbk;
    nbp_printer_callback_on_module_instance_started_pfn_t
        moduleInstanceStartedCbk;
    nbp_printer_callback_on_module_instance_completed_pfn_t
        moduleInstanceCompletedCbk;
};
typedef struct nbp_printer_interface_t nbp_printer_interface_t;

struct nbp_scheduler_interface_t;

typedef void (*nbp_scheduler_config_pfn_t)(
    struct nbp_scheduler_interface_t* /* schedulerInterface */
);

typedef void (*nbp_scheduler_callback_init_pfn_t)(void);

typedef void (*nbp_scheduler_callback_uninit_pfn_t)(void);

typedef void (*nbp_scheduler_callback_run_pfn_t)(void);

typedef void (*nbp_scheduler_callback_on_instantiate_test_case_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);
typedef void (*nbp_scheduler_callback_on_instantiate_test_suite_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);

typedef void (
    *nbp_scheduler_callback_on_instantiate_test_suite_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_scheduler_callback_on_instantiate_module_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);

typedef void (*nbp_scheduler_callback_on_instantiate_module_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

struct nbp_scheduler_interface_t
{
    const char* schedulerName;
    nbp_scheduler_config_pfn_t configFunction;

    nbp_scheduler_callback_init_pfn_t initCbk;
    nbp_scheduler_callback_uninit_pfn_t uninitCbk;
    nbp_scheduler_callback_run_pfn_t runCbk;
    nbp_scheduler_callback_on_instantiate_test_case_pfn_t
        instantiateTestCaseCbk;
    nbp_scheduler_callback_on_instantiate_test_suite_started_pfn_t
        instantiateTestSuiteStartedCbk;
    nbp_scheduler_callback_on_instantiate_test_suite_completed_pfn_t
        instantiateTestSuiteCompletedCbk;
    nbp_scheduler_callback_on_instantiate_module_started_pfn_t
        instantiateModuleStartedCbk;
    nbp_scheduler_callback_on_instantiate_module_completed_pfn_t
        instantiateModuleCompletedCbk;
};
typedef struct nbp_scheduler_interface_t nbp_scheduler_interface_t;

void internal_nbp_module_update_state_stats(
    nbp_module_t* module,
    nbp_module_state_e oldState,
    nbp_module_state_e newState);

void internal_nbp_module_instance_update_state_stats(
    nbp_module_instance_t* moduleInstance,
    nbp_module_instance_state_e oldState,
    nbp_module_instance_state_e newState);

unsigned int internal_nbp_get_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state);

unsigned int internal_nbp_get_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state);

nbp_module_instance_t* internal_nbp_instantiate_module(
    nbp_module_details_t* moduleDetails,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

#define INTERNAL_NBP_INCLUDE_PRINTER(name)                                     \
    extern nbp_printer_interface_t gInternalNbpPrinterInterface##name

#define INTERNAL_NBP_GET_POINTER_TO_PRINTER(name)                              \
    &gInternalNbpPrinterInterface##name

void internal_nbp_notify_printer_init();

void internal_nbp_notify_printer_uninit();

void internal_nbp_notify_printer_handle_version_command();

void internal_nbp_notify_printer_on_error(
    nbp_error_code_e errorCode,
    int line,
    const char* file);

void internal_nbp_notify_printer_on_error_string_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    const char* context);

void internal_nbp_notify_printer_on_error_custom_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    void* context);

void internal_nbp_notify_printer_on_exit(nbp_error_code_e errorCode);

void internal_nbp_notify_printer_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_printer_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_instantiate_module_started(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_printer_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_printer_test_case_started(nbp_test_case_t* testCase);

void internal_nbp_notify_printer_test_case_completed(nbp_test_case_t* testCase);

void internal_nbp_notify_printer_test_case_instance_started(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_printer_test_case_instance_completed(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_printer_test_suite_started(
    nbp_test_suite_t* testSuite);

void internal_nbp_notify_printer_test_suite_completed(
    nbp_test_suite_t* testSuite);

void internal_nbp_notify_printer_test_suite_instance_started(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_test_suite_instance_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_module_started(nbp_module_t* module);

void internal_nbp_notify_printer_module_completed(nbp_module_t* module);

void internal_nbp_notify_printer_module_instance_started(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_printer_module_instance_completed(
    nbp_module_instance_t* moduleInstance);

#define INTERNAL_NBP_INCLUDE_SCHEDULER(name)                                   \
    extern nbp_scheduler_interface_t gInternalNbpSchedulerInterface##name

#define INTERNAL_NBP_GET_POINTER_TO_SCHEDULER(name)                            \
    &gInternalNbpSchedulerInterface##name

void internal_nbp_run_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_scheduler_init();

void internal_nbp_notify_scheduler_uninit();

void internal_nbp_notify_scheduler_run();

void internal_nbp_notify_scheduler_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance,
    void* context);

void internal_nbp_notify_scheduler_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance,
    void* context);

void internal_nbp_notify_scheduler_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_scheduler_instantiate_module_started(
    nbp_module_instance_t* moduleInstance,
    void* context);

void internal_nbp_notify_scheduler_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance);

#ifdef NBP_MT_SUPPORT

#ifdef NBP_OS_LINUX

nbp_error_code_e internal_nbp_linux_sync_event_init(sem_t* event);

nbp_error_code_e internal_nbp_linux_sync_event_uninit(sem_t* event);

nbp_error_code_e internal_nbp_linux_sync_event_wait(sem_t* event);

nbp_error_code_e internal_nbp_linux_sync_event_notify(sem_t* event);

#endif // end if NBP_OS_LINUX

#endif // end if NBP_MT_SUPPORT

void internal_nbp_test_case_update_state_stats(
    nbp_test_case_t* testCase,
    nbp_test_case_state_e oldState,
    nbp_test_case_state_e newState);

void internal_nbp_test_case_instance_update_state_stats(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_test_case_instance_state_e oldState,
    nbp_test_case_instance_state_e newState);

unsigned int internal_nbp_get_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state);

unsigned int internal_nbp_get_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state);

nbp_test_case_instance_t* internal_nbp_instantiate_test_case(
    nbp_test_case_details_t* testCaseDetails,
    nbp_module_t* parentModule,
    nbp_test_suite_t* parentTestSuite,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

void internal_nbp_test_suite_update_state_stats(
    nbp_test_suite_t* testSuite,
    nbp_test_suite_state_e oldState,
    nbp_test_suite_state_e newState);

void internal_nbp_test_suite_instance_update_state_stats(
    nbp_test_suite_instance_t* testSuiteInstance,
    nbp_test_suite_instance_state_e oldState,
    nbp_test_suite_instance_state_e newState);

unsigned int internal_nbp_get_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state);

unsigned int internal_nbp_get_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state);

nbp_test_suite_instance_t* internal_nbp_instantiate_test_suite(
    nbp_test_suite_details_t* testSuiteDetails,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR(errCode)                                              \
    internal_nbp_notify_printer_on_error(                                      \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE)

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR_STRING_CONTEXT(errCode, context)                      \
    internal_nbp_notify_printer_on_error_string_context(                       \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE,                                                       \
        context)

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR_CUSTOM_CONTEXT(errCode, context)                      \
    internal_nbp_notify_printer_on_error_custom_context(                       \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE,                                                       \
        context)

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_CODE(err) err.errorCode

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_LINE(err) err.line

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_FILE(err) err.file

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_CONTEXT_TYPE(err) err.contextType

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_STRING_CONTEXT(err) err.stringContext

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_CUSTOM_CONTEXT(err) err.customContext

#ifndef NBP_CUSTOM_EXIT

#include <stdlib.h>

/**
 * TODO: add docs
 */
#define NBP_EXIT(errorCode)                                                    \
    internal_nbp_notify_printer_on_exit(errorCode);                            \
    exit((int) errorCode)

#else // NBP_CUSTOM_EXIT is defined

/**
 * TODO: add docs
 */
#ifndef NBP_EXIT_FUNCTION
#error "Custom exit is enabled but no exit function is provided"
#define NBP_EXIT_FUNCTION(errorCode)
#endif // end if NBP_EXIT_FUNCTION

#define NBP_EXIT(errorCode)                                                    \
    internal_nbp_notify_printer_on_exit(errorCode);                            \
    NBP_EXIT_FUNCTION(errorCode)

#endif // end if NBP_CUSTOM_EXIT

/**
 * TODO: add docs
 */
#ifndef NBP_CUSTOM_MEMORY_ALLOCATOR

#include <stdlib.h>

/**
 * TODO: add docs
 */
#define NBP_NULLPTR NULL

/**
 * TODO: add docs
 */
#define NBP_MEMORY_ALLOC(size) malloc(size)

/**
 * TODO: add docs
 */
#define NBP_MEMORY_FREE(ptr) free(ptr)

/**
 * TODO: add docs
 */
#define NBP_MEMORY_ALLOC_TAG(size, tag) malloc(size)

/**
 * TODO: add docs
 */
#define NBP_MEMORY_FREE_TAG(ptr, tag) free(ptr)

#else // if custom memory allocator is enabled

#ifndef NBP_NULLPTR
#error "Custom memory allocator is enabled but NBP_NULLPTR is undefined"
#endif // end if NBP_NULLPTR

#ifndef NBP_MEMORY_ALLOC
#error "Custom memory allocator is enabled but NBP_MEMORY_ALLOC is undefined"
#endif // end if NBP_MEMORY_ALLOC

#ifndef NBP_MEMORY_FREE
#error "Custom memory allocator is enabled but NBP_MEMORY_FREE is undefined"
#endif // end if NBP_MEMORY_FREE

#ifndef NBP_MEMORY_ALLOC_TAG
#error                                                                         \
    "Custom memory allocator is enabled but NBP_MEMORY_ALLOC_TAG is undefined"
#endif // end if NBP_MEMORY_ALLOC_TAG

#ifndef NBP_MEMORY_FREE_TAG
#error "Custom memory allocator is enabled but NBP_MEMORY_FREE_TAG is undefined"
#endif // end if NBP_MEMORY_FREE_TAG

#endif // end if NBP_CUSTOM_MEMORY_ALLOCATOR

/**
 * TODO: add docs
 */
#define NBP_MODULE_SETUP(func)                                                 \
    void nbp_module_setup_function_##func(                                     \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule);              \
    nbp_module_setup_details_t gInternalNbpModuleSetupDetails##func = {        \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_module_setup_function_##func,                      \
    };                                                                         \
    void nbp_module_setup_function_##func(                                     \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_MODULE_TEARDOWN(func)                                              \
    void nbp_module_teardown_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule);              \
    nbp_module_teardown_details_t gInternalNbpModuleTeardownDetails##func = {  \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_module_teardown_function_##func,                   \
    };                                                                         \
    void nbp_module_teardown_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_MODULE(func, ...)                                                  \
    void nbp_module_config_function_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_details_t* moduleDetails)        \
    {                                                                          \
        if (moduleDetails->isConfigured == 1) {                                \
            return;                                                            \
        } else {                                                               \
            moduleDetails->isConfigured = 1;                                   \
        }                                                                      \
        INTERNAL_NBP_GENERATE_MODULE_CONFIG_FUNCTION(F_##__VA_ARGS__)          \
    }                                                                          \
    void nbp_module_function_##func(                                           \
        nbp_module_t* nbpParamModule,                                          \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        nbp_module_t* nbpParamTsiParentModule,                                 \
        nbp_module_t* nbpParamMiParentModule);                                 \
    nbp_module_details_t gInternalNbpModuleDetails##func = {                   \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_module_config_function_##func,                  \
        .function        = nbp_module_function_##func,                         \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    void nbp_module_function_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTsiParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamMiParentModule)

/**
 * TODO: add docs
 */
#define NBP_MODULE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_MODULE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE_SETUP(func)                                         \
    extern nbp_module_setup_details_t gInternalNbpModuleSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_SETUP(func)                                  \
    &gInternalNbpModuleSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE_TEARDOWN(func)                                      \
    extern nbp_module_teardown_details_t gInternalNbpModuleTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_TEARDOWN(func)                               \
    &gInternalNbpModuleTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE(func)                                               \
    extern nbp_module_details_t gInternalNbpModuleDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_DETAILS(func) &gInternalNbpModuleDetails##func

/**
 * TODO: add docs
 */
#define NBP_THIS_MODULE nbpParamModule

/**
 * TODO: add docs
 */
#define NBP_THIS_MODULE_INSTANCE nbpParamModuleInstance

/**
 * TODO: add docs
 */
#define NBP_GET_MODULE_INSTANCE_NAME(moduleInstance)                           \
    moduleInstance->moduleDetails->name

/**
 * TODO: add docs
 */
#define NBP_GET_MODULE_NAME(module)                                            \
    NBP_GET_MODULE_INSTANCE_NAME(module->moduleInstance)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASES(moduleInstance)     \
    moduleInstance->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_CASES(moduleInstance, state)    \
    internal_nbp_get_number_of_test_cases(                                     \
        moduleInstance->numberOfTestCases,                                     \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(           \
    moduleInstance)                                                            \
    moduleInstance->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_CASE_INSTANCES(                 \
    moduleInstance,                                                            \
    state)                                                                     \
    internal_nbp_get_number_of_test_case_instances(                            \
        moduleInstance->numberOfTestCaseInstances,                             \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_SUITES(moduleInstance)    \
    moduleInstance->totalNumberOfTestSuites

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_SUITES(moduleInstance, state)   \
    internal_nbp_get_number_of_test_suites(                                    \
        moduleInstance->numberOfTestSuites,                                    \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_SUITE_INSTANCES(          \
    moduleInstance)                                                            \
    moduleInstance->totalNumberOfTestSuiteInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_SUITE_INSTANCES(                \
    moduleInstance,                                                            \
    state)                                                                     \
    internal_nbp_get_number_of_test_suite_instances(                           \
        moduleInstance->numberOfTestSuiteInstances,                            \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_MODULES(moduleInstance)        \
    moduleInstance->totalNumberOfModules

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_MODULES(moduleInstance, state)       \
    internal_nbp_get_number_of_modules(moduleInstance->numberOfModules, state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_MODULE_INSTANCES(              \
    moduleInstance)                                                            \
    moduleInstance->totalNumberOfModuleInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_MODULE_INSTANCES(                    \
    moduleInstance,                                                            \
    state)                                                                     \
    internal_nbp_get_number_of_module_instances(                               \
        moduleInstance->numberOfModuleInstances,                               \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_CASES(module)                      \
    module->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_CASES(module, state)                     \
    internal_nbp_get_number_of_test_cases(module->numberOfTestCases, state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(module)             \
    module->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_CASE_INSTANCES(module, state)            \
    internal_nbp_get_number_of_test_case_instances(                            \
        module->numberOfTestCaseInstances,                                     \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_SUITES(module)                     \
    module->totalNumberOfTestSuites

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_SUITES(module, state)                    \
    internal_nbp_get_number_of_test_suites(                                    \
        moduleInstance->numberOfTestSuites,                                    \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_SUITE_INSTANCES(module)            \
    module->totalNumberOfTestSuiteInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_SUITE_INSTANCES(module, state)           \
    internal_nbp_get_number_of_test_suite_instances(                           \
        module->numberOfTestSuiteInstances,                                    \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_MODULES(module)                         \
    module->totalNumberOfModules

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_MODULES(module, state)                        \
    internal_nbp_get_number_of_modules(module->numberOfModules, state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_MODULE_INSTANCES(module)                \
    module->totalNumberOfModuleInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_MODULE_INSTANCES(module, state)               \
    internal_nbp_get_number_of_module_instances(                               \
        module->numberOfModuleInstances,                                       \
        state)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_MODULE(func, ...)                                      \
    NBP_INCLUDE_MODULE(func);                                                  \
    internal_nbp_instantiate_module(                                           \
        NBP_GET_POINTER_TO_MODULE_DETAILS(func),                               \
        nbpParamMiParentModule,                                                \
        NBP_SOURCE_LINE,                                                       \
        1,                                                                     \
        NBP_NULLPTR)

#define INTERNAL_NBP_GENERATE_MODULE_CONFIG_FUNCTION(...)                      \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GMC##__VA_ARGS__))     \
    (GMCF_, GMC##__VA_ARGS__)

// This macro is generated when NBP_MODULE macro is used without parameters
#define INTERNAL_NBP_GMCF_

#define INTERNAL_NBP_GMCF_NBP_MODULE_NAME(newName)                             \
    moduleDetails->name = newName;

#define INTERNAL_NBP_GMCF_NBP_MODULE_SETUP(func)                               \
    NBP_INCLUDE_MODULE_SETUP(func);                                            \
    moduleDetails->setupDetails = NBP_GET_POINTER_TO_MODULE_SETUP(func);

#define INTERNAL_NBP_GMCF_NBP_MODULE_TEARDOWN(func)                            \
    NBP_INCLUDE_MODULE_TEARDOWN(func);                                         \
    moduleDetails->teardownDetails = NBP_GET_POINTER_TO_MODULE_TEARDOWN(func);

#define INTERNAL_NBP_GMCF_NBP_MODULE_FIXTURES(setupFunc, teardownFunc)         \
    INTERNAL_NBP_GMCF_NBP_MODULE_SETUP(setupFunc)                              \
    INTERNAL_NBP_GMCF_NBP_MODULE_TEARDOWN(teardownFunc)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INIT(func)                                        \
    static void nbp_printer_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_UNINIT(func)                                      \
    static void nbp_printer_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(func)                      \
    static void nbp_printer_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_ON_ERROR(func)                                    \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_t nbpParamError)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_ON_EXIT(func)                                     \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_code_e nbpParamErrorCode)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_CASE(func)                       \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)              \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)            \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                  \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)                \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_STARTED(func)                           \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_COMPLETED(func)                         \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)                  \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(func)                \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_STARTED(func)                          \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_COMPLETED(func)                        \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func)                 \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(func)               \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_STARTED(func)                              \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_COMPLETED(func)                            \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_INSTANCE_STARTED(func)                     \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)                   \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_PRINTER(name, ...)                                                 \
    void nbp_printer_interface_config_function_##name(                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_printer_interface_t* printerInterface)  \
    {                                                                          \
        INTERNAL_NBP_GENERATE_PRINTER_CONFIG_FUNCTION(F_##__VA_ARGS__)         \
        return;                                                                \
    }                                                                          \
    nbp_printer_interface_t gInternalNbpPrinterInterface##name = {             \
        .printerName    = #name,                                               \
        .configFunction = INTERNAL_NBP_GENERATE_PRINTER_INTERFACE_NAME(name),  \
        .isInitialized  = 0,                                                   \
        .initCbk        = NBP_NULLPTR,                                         \
        .uninitCbk      = NBP_NULLPTR,                                         \
        .handleVersionCommandCbk          = NBP_NULLPTR,                       \
        .errorCbk                         = NBP_NULLPTR,                       \
        .exitCbk                          = NBP_NULLPTR,                       \
        .instantiateTestCaseCbk           = NBP_NULLPTR,                       \
        .instantiateTestSuiteStartedCbk   = NBP_NULLPTR,                       \
        .instantiateTestSuiteCompletedCbk = NBP_NULLPTR,                       \
        .instantiateModuleStartedCbk      = NBP_NULLPTR,                       \
        .instantiateModuleCompletedCbk    = NBP_NULLPTR,                       \
        .testCaseStartedCbk               = NBP_NULLPTR,                       \
        .testCaseCompletedCbk             = NBP_NULLPTR,                       \
        .testCaseInstanceStartedCbk       = NBP_NULLPTR,                       \
        .testCaseInstanceCompletedCbk     = NBP_NULLPTR,                       \
        .testSuiteStartedCbk              = NBP_NULLPTR,                       \
        .testSuiteCompletedCbk            = NBP_NULLPTR,                       \
        .testSuiteInstanceStartedCbk      = NBP_NULLPTR,                       \
        .testSuiteInstanceCompletedCbk    = NBP_NULLPTR,                       \
        .moduleStartedCbk                 = NBP_NULLPTR,                       \
        .moduleCompletedCbk               = NBP_NULLPTR,                       \
        .moduleInstanceStartedCbk         = NBP_NULLPTR,                       \
        .moduleInstanceCompletedCbk       = NBP_NULLPTR,                       \
    }

/**
 * TODO: add docs
 */
#define NBP_THIS_ERROR nbpParamError

#define INTERNAL_NBP_GENERATE_PRINTER_INTERFACE_NAME(name)                     \
    nbp_printer_interface_config_function_##name

#define INTERNAL_NBP_GENERATE_PRINTER_CONFIG_FUNCTION(...)                     \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GPC##__VA_ARGS__))     \
    (GPCF_, GPC##__VA_ARGS__)

#define INTERNAL_NBP_GPCF_NBP_PRINTER_CALLBACKS(...)                           \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(PC_##__VA_ARGS__))   \
    (PC_, PC_##__VA_ARGS__)

// This macro is generated when NBP_PRINTER macro is used without parameters
#define INTERNAL_NBP_GPCF_

// This macro is generated when NBP_PRINTER_CALLBACKS macro is used without
// parameters
#define INTERNAL_NBP_PC_

#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_INIT(func)                        \
    printerInterface->initCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_UNINIT(func)                      \
    printerInterface->uninitCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(func)      \
    printerInterface->handleVersionCommandCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_ON_ERROR(func)                    \
    printerInterface->errorCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_ON_EXIT(func)                     \
    printerInterface->exitCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_CASE(func)       \
    printerInterface->instantiateTestCaseCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(   \
    func)                                                                      \
    printerInterface->instantiateTestSuiteStartedCbk =                         \
        nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                      \
    printerInterface->instantiateTestSuiteCompletedCbk =                       \
        nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)  \
    printerInterface->instantiateModuleStartedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(     \
    func)                                                                      \
    printerInterface->instantiateModuleCompletedCbk =                          \
        nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_CASE_STARTED(func)           \
    printerInterface->testCaseStartedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_CASE_COMPLETED(func)         \
    printerInterface->testCaseCompletedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)  \
    printerInterface->testCaseInstanceStartedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(     \
    func)                                                                      \
    printerInterface->testCaseInstanceCompletedCbk =                           \
        nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_SUITE_STARTED(func)          \
    printerInterface->testSuiteStartedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_SUITE_COMPLETED(func)        \
    printerInterface->testSuiteCompletedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func) \
    printerInterface->testSuiteInstanceStartedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(    \
    func)                                                                      \
    printerInterface->testSuiteInstanceCompletedCbk =                          \
        nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_MODULE_STARTED(func)              \
    printerInterface->moduleStartedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_MODULE_COMPLETED(func)            \
    printerInterface->moduleCompletedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_MODULE_INSTANCE_STARTED(func)     \
    printerInterface->moduleInstanceStartedCbk = nbp_printer_callback_##func;
#define INTERNAL_NBP_PC_NBP_PRINTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)   \
    printerInterface->moduleInstanceCompletedCbk = nbp_printer_callback_##func;

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_SETUP(func)                                             \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_setup_details_t gInternalNbpTestSuiteSetupDetails##func = { \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_test_suite_setup_function_##func,                  \
    };                                                                         \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_TEARDOWN(func)                                          \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_teardown_details_t                                          \
        gInternalNbpTestSuiteTeardownDetails##func = {                         \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_suite_teardown_function_##func,           \
    };                                                                         \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE(func, ...)                                              \
    void nbp_test_suite_config_function_##func(                                \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_details_t* testSuiteDetails) \
    {                                                                          \
        if (testSuiteDetails->isConfigured == 1) {                             \
            return;                                                            \
        } else {                                                               \
            testSuiteDetails->isConfigured = 1;                                \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(F_##__VA_ARGS__)      \
    }                                                                          \
    void nbp_test_suite_function_##func(                                       \
        nbp_test_suite_t* nbpParamTestSuite,                                   \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule);                                \
    nbp_test_suite_details_t gInternalNbpTestSuiteDetails##func = {            \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_test_suite_config_function_##func,              \
        .function        = nbp_test_suite_function_##func,                     \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    void nbp_test_suite_function_##func(                                       \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_SETUP(func)                                     \
    extern nbp_test_suite_setup_details_t                                      \
        gInternalNbpTestSuiteSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_SETUP(func)                              \
    &gInternalNbpTestSuiteSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_TEARDOWN(func)                                  \
    extern nbp_test_suite_teardown_details_t                                   \
        gInternalNbpTestSuiteTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN(func)                           \
    &gInternalNbpTestSuiteTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE(func)                                           \
    extern nbp_test_suite_details_t gInternalNbpTestSuiteDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_DETAILS(func)                            \
    &gInternalNbpTestSuiteDetails##func

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_SUITE nbpParamTestSuite

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_SUITE_INSTANCE nbpParamTestSuiteInstance

/**
 * TODO: add docs
 */
#define NBP_GET_TEST_SUITE_INSTANCE_NAME(testSuiteInstance)                    \
    testSuiteInstance->testSuiteDetails->name

/**
 * TODO: add docs
 */
#define NBP_GET_TEST_SUITE_NAME(testSuite)                                     \
    NBP_GET_TEST_SUITE_INSTANCE_NAME(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASES(                \
    testSuiteInstance)                                                         \
    testSuiteInstace->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_TEST_CASES(                      \
    testSuiteInstance,                                                         \
    state)                                                                     \
    internal_nbp_get_number_of_test_cases(                                     \
        testSuiteInstance->numberOfTestCases,                                  \
        state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(       \
    testSuiteInstance)                                                         \
    testSuiteInstace->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_TEST_CASE_INSTANCES(             \
    testSuiteInstance,                                                         \
    state)                                                                     \
    internal_nbp_get_number_of_test_case_instances(                            \
        testSuiteInstance->numberOfTestCaseInstances,                          \
        state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_SUITES(               \
    testSuiteInstance)                                                         \
    testSuiteInstace->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_TEST_SUITES(                     \
    testSuiteInstance,                                                         \
    state)                                                                     \
    internal_nbp_get_number_of_test_suites(                                    \
        testSuiteInstance->numberOfTestSuites,                                 \
        state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_TOTAL_NUMBER_OF_TEST_CASES(testSuite)               \
    testSuite->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_NUMBER_OF_TEST_CASES(testSuite, state)              \
    internal_nbp_get_number_of_test_cases(testSuite->numberOfTestCases, state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(testSuite)      \
    testSuite->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_NUMBER_OF_TEST_CASE_INSTANCES(testSuite, state)     \
    internal_nbp_get_number_of_test_case_instances(                            \
        testSuite->numberOfTestCaseInstances,                                  \
        state)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_TEST_SUITE(func, ...)                                  \
    NBP_INCLUDE_TEST_SUITE(func);                                              \
    internal_nbp_instantiate_test_suite(                                       \
        NBP_GET_POINTER_TO_TEST_SUITE_DETAILS(func),                           \
        nbpParamTsiParentModule,                                               \
        NBP_SOURCE_LINE,                                                       \
        1,                                                                     \
        NBP_NULLPTR)

#define INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(...)                  \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GTSC##__VA_ARGS__))    \
    (GTSCF_, GTSC##__VA_ARGS__)

// This macro is generated when NBP_TEST_SUITE macro is used without parameters
#define INTERNAL_NBP_GTSCF_

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_NAME(newName)                        \
    testSuiteDetails->name = newName;

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(func)                          \
    NBP_INCLUDE_TEST_SUITE_SETUP(func);                                        \
    testSuiteDetails->setupDetails = NBP_GET_POINTER_TO_TEST_SUITE_SETUP(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(func)                       \
    NBP_INCLUDE_TEST_SUITE_TEARDOWN(func);                                     \
    testSuiteDetails->teardownDetails =                                        \
        NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_FIXTURES(setupFunc, teardownFunc)    \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(setupFunc)                         \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(teardownFunc)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_SETUP(func)                                              \
    void nbp_test_case_setup_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase);         \
    nbp_test_case_setup_details_t gInternalNbpTestCaseSetupDetails##func = {   \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_test_case_setup_function_##func,                   \
    };                                                                         \
    void nbp_test_case_setup_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_TEARDOWN(func)                                           \
    void nbp_test_case_teardown_function_##func(                               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase);         \
    nbp_test_case_teardown_details_t                                           \
        gInternalNbpTestCaseTeardownDetails##func = {                          \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_case_teardown_function_##func,            \
    };                                                                         \
    void nbp_test_case_teardown_function_##func(                               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE(func, ...)                                               \
    void nbp_test_case_config_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_details_t* testCaseDetails)   \
    {                                                                          \
        if (testCaseDetails->isConfigured == 1) {                              \
            return;                                                            \
        } else {                                                               \
            testCaseDetails->isConfigured = 1;                                 \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(F_##__VA_ARGS__)       \
    }                                                                          \
    void nbp_test_case_function_##func(nbp_test_case_t* nbpParamTestCase);     \
    nbp_test_case_details_t gInternalNbpTestCaseDetails##func = {              \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_test_case_config_function_##func,               \
        .function        = nbp_test_case_function_##func,                      \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    void nbp_test_case_function_##func(                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_SETUP(func)                                      \
    extern nbp_test_case_setup_details_t gInternalNbpTestCaseSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_SETUP(func)                               \
    &gInternalNbpTestCaseSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_TEARDOWN(func)                                   \
    extern nbp_test_case_teardown_details_t                                    \
        gInternalNbpTestCaseTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN(func)                            \
    &gInternalNbpTestCaseTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE(func)                                            \
    extern nbp_test_case_details_t gInternalNbpTestCaseDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_DETAILS(func)                             \
    &gInternalNbpTestCaseDetails##func

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_CASE nbpParamTestCase

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_CASE_INSTANCE nbpParamTestCaseInstance

/**
 * TODO: add docs
 */
#define NBP_GET_TEST_CASE_INSTANCE_NAME(testCaseInstance)                      \
    testCaseInstance->testCaseDetails->name

/**
 * TODO: add docs
 */
#define NBP_GET_TEST_CASE_NAME(testCase)                                       \
    NBP_GET_TEST_CASE_INSTANCE_NAME(testCase->testCaseInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASES(                 \
    testCaseInstance)                                                          \
    testCaseInstance->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_TEST_CASES(                       \
    testCaseInstance,                                                          \
    state)                                                                     \
    internal_nbp_get_number_of_test_cases(                                     \
        testCaseInstance->numberOfTestCases,                                   \
        state)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_TEST_CASE(func, ...)                                   \
    NBP_INCLUDE_TEST_CASE(func);                                               \
    internal_nbp_instantiate_test_case(                                        \
        NBP_GET_POINTER_TO_TEST_CASE_DETAILS(func),                            \
        nbpParamTciParentModule,                                               \
        nbpParamTciParentTestSuite,                                            \
        NBP_SOURCE_LINE,                                                       \
        1,                                                                     \
        NBP_NULLPTR)

#define INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(...)                   \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GTCC##__VA_ARGS__))    \
    (GTCCF_, GTCC##__VA_ARGS__)

// This macro is generated when NBP_TEST_CASE macro is used without parameters
#define INTERNAL_NBP_GTCCF_

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_NAME(newName)                         \
    testCaseDetails->name = newName;

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(func)                           \
    NBP_INCLUDE_TEST_CASE_SETUP(func);                                         \
    testCaseDetails->setupDetails = NBP_GET_POINTER_TO_TEST_CASE_SETUP(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(func)                        \
    NBP_INCLUDE_TEST_CASE_TEARDOWN(func);                                      \
    testCaseDetails->teardownDetails =                                         \
        NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_FIXTURES(setupFunc, teardownFunc)     \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(setupFunc)                          \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(teardownFunc)

#ifdef NBP_LIBRARY_MAIN

/**
 * TODO: add docs
 */
#define NBP_MAIN_MODULE(func, ...)                                             \
    void nbp_module_config_function_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_details_t* moduleDetails)        \
    {                                                                          \
        if (moduleDetails->isConfigured == 1) {                                \
            return;                                                            \
        } else {                                                               \
            moduleDetails->isConfigured = 1;                                   \
        }                                                                      \
        INTERNAL_NBP_GENERATE_MAIN_MODULE_CONFIG_FUNCTION(F_##__VA_ARGS__)     \
    }                                                                          \
    void nbp_module_function_##func(                                           \
        nbp_module_t* nbpParamModule,                                          \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        nbp_module_t* nbpParamTsiParentModule,                                 \
        nbp_module_t* nbpParamMiParentModule);                                 \
    nbp_module_details_t gInternalNbpModuleDetails##func = {                   \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_module_config_function_##func,                  \
        .function        = nbp_module_function_##func,                         \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    nbp_module_details_t* gInternalNbpMainModuleDetails =                      \
        &gInternalNbpModuleDetails##func;                                      \
    void nbp_module_function_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTsiParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamMiParentModule)

#define INTERNAL_NBP_GENERATE_MAIN_MODULE_CONFIG_FUNCTION(...)                 \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GMMC##__VA_ARGS__))    \
    (GMMCF_, GMMC##__VA_ARGS__)

// This macro is generated when NBP_MAIN_MODULE macro is used without parameters
#define INTERNAL_NBP_GMMCF_

#define INTERNAL_NBP_GMMCF_NBP_MODULE_NAME(newName)                            \
    moduleDetails->name = newName;

#define INTERNAL_NBP_GMMCF_NBP_MODULE_SETUP(func)                              \
    NBP_INCLUDE_MODULE_SETUP(func);                                            \
    moduleDetails->setupDetails = NBP_GET_POINTER_TO_MODULE_SETUP(func);

#define INTERNAL_NBP_GMMCF_NBP_MODULE_TEARDOWN(func)                           \
    NBP_INCLUDE_MODULE_TEARDOWN(func);                                         \
    moduleDetails->teardownDetails = NBP_GET_POINTER_TO_MODULE_TEARDOWN(func);

#define INTERNAL_NBP_GMMCF_NBP_MODULE_FIXTURES(setupFunc, teardownFunc)        \
    INTERNAL_NBP_GMMCF_NBP_MODULE_SETUP(setupFunc)                             \
    INTERNAL_NBP_GMMCF_NBP_MODULE_TEARDOWN(teardownFunc)

#endif // end if NBP_LIBRARY_MAIN

#ifdef NBP_LIBRARY_MAIN

extern nbp_module_details_t* gInternalNbpMainModuleDetails;

INTERNAL_NBP_INCLUDE_PRINTER(nbpDefaultPrinter);

nbp_printer_interface_t* gInternalNbpDefaultPrinterInterfaces[] = {
    INTERNAL_NBP_GET_POINTER_TO_PRINTER(nbpDefaultPrinter)};

nbp_printer_interface_t** gInternalNbpPrinterInterfaces = NBP_NULLPTR;
unsigned int gInternalNbpPrinterInterfacesSize          = 0;

unsigned int gInternalNbpNumberOfTestCases            = 0;
NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRanTestCases = NBP_ATOMIC_UINT_INIT(0);

int gInternalNbpSchedulerRunEnabled = 0;

#ifdef NBP_BASIC_SCHEDULER
INTERNAL_NBP_INCLUDE_SCHEDULER(nbpBasicScheduler);
nbp_scheduler_interface_t* gInternalNbpSchedulerInterface =
    INTERNAL_NBP_GET_POINTER_TO_SCHEDULER(nbpBasicScheduler);
#endif // end if NBP_BASIC_SCHEDULER

#ifdef NBP_MT_SCHEDULER
nbp_scheduler_interface_t* gInternalNbpSchedulerInterface = NBP_NULLPTR;
#endif // end if NBP_MT_SCHEDULER

static int internal_nbp_string_equal(const char* a, const char* b)
{
    while (*a == *b && *a != '\0') {
        a++;
        b++;
    }

    return *a != *b ? 0 : 1;
}

static int internal_nbp_command_run_all()
{
    internal_nbp_notify_printer_init();
    internal_nbp_notify_scheduler_init();

    if (gInternalNbpSchedulerInterface->instantiateTestCaseCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_scheduler_interface);
        NBP_EXIT(ec_invalid_scheduler_interface);
        return ec_invalid_scheduler_interface;
    }
    if (gInternalNbpSchedulerInterface->runCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_scheduler_interface);
        NBP_EXIT(ec_invalid_scheduler_interface);
        return ec_invalid_scheduler_interface;
    }

    nbp_module_instance_t* mainModuleInstance = internal_nbp_instantiate_module(
        gInternalNbpMainModuleDetails,
        NBP_NULLPTR,
        0,
        1,
        NBP_NULLPTR);

    if (mainModuleInstance == NBP_NULLPTR) {
        return ec_out_of_memory;
    }

    // TODO: send some stats to printers about instances

    internal_nbp_notify_scheduler_run();

    unsigned int numberOfRunTestsCases =
        NBP_ATOMIC_UINT_LOAD(&gInternalNbpNumberOfRanTestCases);
    if (numberOfRunTestsCases != gInternalNbpNumberOfTestCases) {
        NBP_REPORT_ERROR(ec_not_all_tests_were_run);
        NBP_EXIT(ec_not_all_tests_were_run);
        return ec_not_all_tests_were_run;
    }

    // TODO: send some stats to printers about asserts, test cases etc

    internal_nbp_notify_scheduler_uninit();
    internal_nbp_notify_printer_uninit();

    // TODO: return error if main module state is not passed

    // TODO: free data!!!

    return (int) ec_success;
}

static int internal_nbp_command_version()
{
    internal_nbp_notify_printer_init();
    internal_nbp_notify_printer_handle_version_command();
    internal_nbp_notify_printer_uninit();

    return (int) ec_success;
}

int main(int argc, const char** argv)
{
    if (argc < 1) {
        return (int) ec_invalid_command_line;
    }

    gInternalNbpPrinterInterfaces     = gInternalNbpDefaultPrinterInterfaces;
    gInternalNbpPrinterInterfacesSize = 1;

    if (argc == 1) {
        return internal_nbp_command_run_all();
    }

    if (internal_nbp_string_equal(argv[1], "--version") == 1) {
        return internal_nbp_command_version();
    }

    return (int) ec_invalid_command_line;
}

extern nbp_module_details_t* gInternalNbpMainModuleDetails;

static void internal_nbp_increment_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) ms_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) ms_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e oldState,
    nbp_module_state_e newState)
{
    internal_nbp_decrement_number_of_modules(statsArray, oldState, 1);
    internal_nbp_increment_number_of_modules(statsArray, newState, 1);
}

static void internal_nbp_increment_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) mis_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) mis_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e oldState,
    nbp_module_instance_state_e newState)
{
    internal_nbp_decrement_number_of_module_instances(statsArray, oldState, 1);
    internal_nbp_increment_number_of_module_instances(statsArray, newState, 1);
}

static void internal_nbp_module_instance_update_stats(
    nbp_module_instance_t* moduleInstance)
{
    nbp_module_t* parent         = moduleInstance->parent;
    unsigned int numberOfModules = moduleInstance->numberOfRuns;

    internal_nbp_increment_number_of_modules(
        moduleInstance->numberOfModules,
        ms_ready,
        numberOfModules);

    while (parent != NBP_NULLPTR) {
        parent->totalNumberOfModuleInstances += 1;
        parent->totalNumberOfModules += numberOfModules;

        parent->moduleInstance->totalNumberOfModuleInstances += 1;
        parent->moduleInstance->totalNumberOfModules += numberOfModules;

        internal_nbp_increment_number_of_module_instances(
            parent->numberOfModuleInstances,
            mis_ready,
            1);
        internal_nbp_increment_number_of_modules(
            parent->numberOfModules,
            ms_ready,
            numberOfModules);

        internal_nbp_increment_number_of_module_instances(
            parent->moduleInstance->numberOfModuleInstances,
            mis_ready,
            1);
        internal_nbp_increment_number_of_modules(
            parent->moduleInstance->numberOfModules,
            ms_ready,
            numberOfModules);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_module_update_state_stats(
    nbp_module_t* module,
    nbp_module_state_e oldState,
    nbp_module_state_e newState)
{
    nbp_module_t* parent = module->moduleInstance->parent;

    internal_nbp_update_number_of_modules(
        module->moduleInstance->numberOfModules,
        oldState,
        newState);

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_modules(
            parent->numberOfModules,
            oldState,
            newState);

        internal_nbp_update_number_of_modules(
            parent->moduleInstance->numberOfModules,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_module_instance_update_state_stats(
    nbp_module_instance_t* moduleInstance,
    nbp_module_instance_state_e oldState,
    nbp_module_instance_state_e newState)
{
    nbp_module_t* parent = moduleInstance->parent;

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_module_instances(
            parent->numberOfModuleInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_module_instances(
            parent->moduleInstance->numberOfModuleInstances,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state)
{
    int pos = ((int) state) - ((int) ms_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state)
{
    int pos = ((int) state) - ((int) mis_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_module_instance_t* internal_nbp_instantiate_module(
    nbp_module_details_t* moduleDetails,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    if (numberOfRuns == 0) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_number_of_runs,
            "the number of runs must be greater than 0");
        NBP_EXIT(ec_invalid_number_of_runs);
        return NBP_NULLPTR;
    }

    if (parentModule == NBP_NULLPTR
        && moduleDetails != gInternalNbpMainModuleDetails) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "module instance has no parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    if (parentModule != NBP_NULLPTR) {
        if (parentModule->moduleInstance->moduleDetails == moduleDetails) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_invalid_parent,
                "a module cannot self instantiate");
            NBP_EXIT(ec_invalid_parent);
            return NBP_NULLPTR;
        }

        nbp_module_t* p = parentModule->moduleInstance->parent;
        while (p != NBP_NULLPTR) {
            if (p->moduleInstance->moduleDetails == moduleDetails) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_invalid_parent,
                    "a module cannot instantiate a parent module");
                NBP_EXIT(ec_invalid_parent);
                return NBP_NULLPTR;
            }
            p = p->moduleInstance->parent;
        }
    }

    nbp_module_instance_t* moduleInstance = (nbp_module_instance_t*)
        NBP_MEMORY_ALLOC_TAG(sizeof(nbp_module_instance_t), mt_module_instance);

    if (moduleInstance == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate module instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    nbp_module_t* runs = (nbp_module_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_module_t),
        mt_module);

    if (runs == NBP_NULLPTR) {
        NBP_MEMORY_FREE_TAG(moduleInstance, mt_module_instance);

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate the runs for module instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        runs[i].moduleInstance                  = moduleInstance;
        runs[i].state                           = ms_ready;
        runs[i].firstTestCaseInstance           = NBP_NULLPTR;
        runs[i].lastTestCaseInstance            = NBP_NULLPTR;
        runs[i].firstTestSuiteInstance          = NBP_NULLPTR;
        runs[i].lastTestSuiteInstance           = NBP_NULLPTR;
        runs[i].firstModuleInstance             = NBP_NULLPTR;
        runs[i].lastModuleInstance              = NBP_NULLPTR;
        runs[i].totalNumberOfTestCases          = 0;
        runs[i].totalNumberOfTestCaseInstances  = 0;
        runs[i].totalNumberOfTestSuites         = 0;
        runs[i].totalNumberOfTestSuiteInstances = 0;
        runs[i].totalNumberOfModules            = 0;
        runs[i].totalNumberOfModuleInstances    = 0;

        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);

        unsigned int j;
        for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestCases[j], 0);
        }
        for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestCaseInstances[j], 0);
        }
        for (j = 0; j < NBP_NUMBER_OF_TEST_SUITE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestSuites[j], 0);
        }
        for (j = 0; j < NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestSuiteInstances[j], 0);
        }
        for (j = 0; j < NBP_NUMBER_OF_MODULE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfModules[j], 0);
        }
        for (j = 0; j < NBP_NUMBER_OF_MODULE_INSTANCE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfModuleInstances[j], 0);
        }
    }

    moduleInstance->moduleDetails     = moduleDetails;
    moduleInstance->state             = mis_ready;
    moduleInstance->parent            = parentModule;
    moduleInstance->depth             = 0;
    moduleInstance->instantiationLine = instantiationLine;
    moduleInstance->setupDetails      = moduleDetails->setupDetails;
    moduleInstance->teardownDetails   = moduleDetails->teardownDetails;
    moduleInstance->runs              = runs;
    moduleInstance->numberOfRuns      = numberOfRuns;
    moduleInstance->next              = NBP_NULLPTR;
    moduleInstance->prev              = NBP_NULLPTR;

    moduleInstance->totalNumberOfTestCases          = 0;
    moduleInstance->totalNumberOfTestCaseInstances  = 0;
    moduleInstance->totalNumberOfTestSuites         = 0;
    moduleInstance->totalNumberOfTestSuiteInstances = 0;
    moduleInstance->totalNumberOfModules            = 0;
    moduleInstance->totalNumberOfModuleInstances    = 0;

    NBP_ATOMIC_INT_STORE(&moduleInstance->isSkipped, (int) sf_is_not_set);

    unsigned int j;
    for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_STATES; j++) {
        NBP_ATOMIC_UINT_STORE(&moduleInstance->numberOfTestCases[j], 0);
    }
    for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES; j++) {
        NBP_ATOMIC_UINT_STORE(&moduleInstance->numberOfTestCaseInstances[j], 0);
    }
    for (j = 0; j < NBP_NUMBER_OF_TEST_SUITE_STATES; j++) {
        NBP_ATOMIC_UINT_STORE(&moduleInstance->numberOfTestSuites[j], 0);
    }
    for (j = 0; j < NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES; j++) {
        NBP_ATOMIC_UINT_STORE(
            &moduleInstance->numberOfTestSuiteInstances[j],
            0);
    }
    for (j = 0; j < NBP_NUMBER_OF_MODULE_STATES; j++) {
        NBP_ATOMIC_UINT_STORE(&moduleInstance->numberOfModules[j], 0);
    }
    for (j = 0; j < NBP_NUMBER_OF_MODULE_INSTANCE_STATES; j++) {
        NBP_ATOMIC_UINT_STORE(&moduleInstance->numberOfModuleInstances[j], 0);
    }

    if (parentModule != NBP_NULLPTR) {
        moduleInstance->depth = parentModule->moduleInstance->depth + 1;

        if (parentModule->firstModuleInstance == NBP_NULLPTR) {
            parentModule->firstModuleInstance = moduleInstance;
            parentModule->lastModuleInstance  = moduleInstance;
        } else {
            moduleInstance->prev = parentModule->lastModuleInstance;
            parentModule->lastModuleInstance->next = moduleInstance;
            parentModule->lastModuleInstance       = moduleInstance;
        }
    }

    internal_nbp_module_instance_update_stats(moduleInstance);

    internal_nbp_notify_printer_instantiate_module_started(moduleInstance);

    internal_nbp_notify_scheduler_instantiate_module_started(
        moduleInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        moduleInstance->moduleDetails->function(
            &moduleInstance->runs[i],
            NBP_NULLPTR,
            &moduleInstance->runs[i],
            &moduleInstance->runs[i],
            &moduleInstance->runs[i]);

        if (moduleInstance->runs[i].totalNumberOfTestCaseInstances == 0) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_no_test_case_instantiated,
                "module has no test case");
            NBP_EXIT(ec_no_test_case_instantiated);
        }
    }

    internal_nbp_notify_scheduler_instantiate_module_completed(moduleInstance);

    internal_nbp_notify_printer_instantiate_module_completed(moduleInstance);

    return moduleInstance;
}

extern nbp_printer_interface_t** gInternalNbpPrinterInterfaces;
extern unsigned int gInternalNbpPrinterInterfacesSize;

#define INTERNAL_NBP_CALLBACK_IS_SET(cbk)                                      \
    gInternalNbpPrinterInterfaces[i]->cbk != NBP_NULLPTR

void internal_nbp_notify_printer_init()
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        gInternalNbpPrinterInterfaces[i]->configFunction(
            gInternalNbpPrinterInterfaces[i]);
        if (INTERNAL_NBP_CALLBACK_IS_SET(initCbk)) {
            gInternalNbpPrinterInterfaces[i]->initCbk();
        }
        gInternalNbpPrinterInterfaces[i]->isInitialized = 1;
    }
}

void internal_nbp_notify_printer_uninit()
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(uninitCbk)) {
            gInternalNbpPrinterInterfaces[i]->uninitCbk();
        }
        gInternalNbpPrinterInterfaces[i]->isInitialized = 0;
    }
}

void internal_nbp_notify_printer_handle_version_command()
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(handleVersionCommandCbk)) {
            gInternalNbpPrinterInterfaces[i]->handleVersionCommandCbk();
        }
    }
}

void internal_nbp_notify_printer_on_error(
    nbp_error_code_e errorCode,
    int line,
    const char* file)
{
    nbp_error_t error;

    error.errorCode   = errorCode;
    error.line        = line;
    error.file        = file;
    error.contextType = ect_empty;

    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpPrinterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_printer_on_error_string_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    const char* context)
{
    nbp_error_t error;

    error.errorCode     = errorCode;
    error.line          = line;
    error.file          = file;
    error.contextType   = ect_string;
    error.stringContext = context;

    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpPrinterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_printer_on_error_custom_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    void* context)
{
    nbp_error_t error;

    error.errorCode     = errorCode;
    error.line          = line;
    error.file          = file;
    error.contextType   = ect_custom;
    error.customContext = context;

    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpPrinterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_printer_on_exit(nbp_error_code_e errorCode)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(exitCbk)) {
            gInternalNbpPrinterInterfaces[i]->exitCbk(errorCode);
        }
    }
}

void internal_nbp_notify_printer_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestCaseCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateTestCaseCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateTestSuiteStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateTestSuiteCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_instantiate_module_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateModuleStartedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_printer_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateModuleCompletedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_printer_test_case_started(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseStartedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_case_completed(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseCompletedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_case_instance_started(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseInstanceStartedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_case_instance_completed(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseInstanceCompletedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_started(nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteStartedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_completed(
    nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteCompletedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_instance_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteInstanceStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_instance_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteInstanceCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_module_started(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleStartedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_printer_module_completed(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleCompletedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_printer_module_instance_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleInstanceStartedCbk(
                moduleInstance);
        }
    }
}

void internal_nbp_notify_printer_module_instance_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleInstanceCompletedCbk(
                moduleInstance);
        }
    }
}

#undef INTERNAL_NBP_CALLBACK_IS_SET

extern int gInternalNbpSchedulerRunEnabled;

extern NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRanTestCases;

void internal_nbp_run_test_case(nbp_test_case_t* testCase)
{
    if (gInternalNbpSchedulerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_scheduler_run_is_disabled,
            "a test case can be run only from scheduler's run callback");
        NBP_EXIT(ec_scheduler_run_is_disabled);
        return;
    }

    testCase->testCaseInstance->testCaseDetails->function(testCase);

    NBP_ATOMIC_UINT_ADD_AND_FETCH(&gInternalNbpNumberOfRanTestCases, 1);
}

void internal_nbp_run_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance)
{
    if (gInternalNbpSchedulerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_scheduler_run_is_disabled,
            "a test case instance can be run only from scheduler's run "
            "callback");
        NBP_EXIT(ec_scheduler_run_is_disabled);
        return;
    }

    for (unsigned int i = 0; i < testCaseInstance->numberOfRuns; i++) {
        internal_nbp_run_test_case(&testCaseInstance->runs[i]);
    }
}

extern nbp_scheduler_interface_t* gInternalNbpSchedulerInterface;

extern int gInternalNbpSchedulerRunEnabled;

#define INTERNAL_NBP_CALLBACK_IS_SET(cbk)                                      \
    gInternalNbpSchedulerInterface->cbk != NBP_NULLPTR

void internal_nbp_notify_scheduler_init()
{
    gInternalNbpSchedulerInterface->configFunction(
        gInternalNbpSchedulerInterface);

    if (INTERNAL_NBP_CALLBACK_IS_SET(initCbk)) {
        gInternalNbpSchedulerInterface->initCbk();
    }
}

void internal_nbp_notify_scheduler_uninit()
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(uninitCbk)) {
        gInternalNbpSchedulerInterface->uninitCbk();
    }
}

void internal_nbp_notify_scheduler_run()
{
    gInternalNbpSchedulerRunEnabled = 1;

    if (INTERNAL_NBP_CALLBACK_IS_SET(runCbk)) {
        gInternalNbpSchedulerInterface->runCbk();
    }

    gInternalNbpSchedulerRunEnabled = 0;
}

void internal_nbp_notify_scheduler_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance,
    void* context)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestCaseCbk)) {
        gInternalNbpSchedulerInterface->instantiateTestCaseCbk(
            testCaseInstance,
            testCaseInstance->testSuite,
            testCaseInstance->module,
            context);
    }
}

void internal_nbp_notify_scheduler_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance,
    void* context)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteStartedCbk)) {
        gInternalNbpSchedulerInterface->instantiateTestSuiteStartedCbk(
            testSuiteInstance,
            testSuiteInstance->module,
            context);
    }
}

void internal_nbp_notify_scheduler_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteCompletedCbk)) {
        gInternalNbpSchedulerInterface->instantiateTestSuiteCompletedCbk(
            testSuiteInstance,
            testSuiteInstance->module);
    }
}

void internal_nbp_notify_scheduler_instantiate_module_started(
    nbp_module_instance_t* moduleInstance,
    void* context)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleStartedCbk)) {
        gInternalNbpSchedulerInterface->instantiateModuleStartedCbk(
            moduleInstance,
            moduleInstance->parent,
            context);
    }
}

void internal_nbp_notify_scheduler_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleCompletedCbk)) {
        gInternalNbpSchedulerInterface->instantiateModuleCompletedCbk(
            moduleInstance,
            moduleInstance->parent);
    }
}

#undef INTERNAL_NBP_CALLBACK_IS_SET

#ifdef NBP_MT_SUPPORT

#ifdef NBP_OS_LINUX

nbp_error_code_e internal_nbp_linux_sync_event_init(sem_t* event)
{
    if (sem_init(event, 0, 0) == 0) {
        return ec_success;
    }

    return ec_sync_error;
}

nbp_error_code_e internal_nbp_linux_sync_event_uninit(sem_t* event)
{
    if (sem_destroy(event) == 0) {
        return ec_success;
    }

    return ec_sync_error;
}

nbp_error_code_e internal_nbp_linux_sync_event_wait(sem_t* event)
{
    if (sem_wait(event) != 0) {
        return ec_sync_error;
    }
    if (sem_post(event) != 0) {
        return ec_sync_error;
    }

    return ec_success;
}

nbp_error_code_e internal_nbp_linux_sync_event_notify(sem_t* event)
{
    if (sem_post(event) == 0) {
        return ec_success;
    }

    return ec_sync_error;
}

#endif // end if NBP_OS_LINUX

#endif // end if NBP_MT_SUPPORT

extern unsigned int gInternalNbpNumberOfTestCases;

static void internal_nbp_increment_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tcs_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tcs_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e oldState,
    nbp_test_case_state_e newState)
{
    internal_nbp_decrement_number_of_test_cases(statsArray, oldState, 1);
    internal_nbp_increment_number_of_test_cases(statsArray, newState, 1);
}

static void internal_nbp_increment_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tcis_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tcis_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e oldState,
    nbp_test_case_instance_state_e newState)
{
    internal_nbp_decrement_number_of_test_case_instances(
        statsArray,
        oldState,
        1);
    internal_nbp_increment_number_of_test_case_instances(
        statsArray,
        newState,
        1);
}

static void internal_nbp_test_case_instance_update_stats(
    nbp_test_case_instance_t* testCaseInstance)
{
    nbp_module_t* parent                         = testCaseInstance->module;
    nbp_test_suite_t* testSuite                  = testCaseInstance->testSuite;
    nbp_test_suite_instance_t* testSuiteInstance = NBP_NULLPTR;
    unsigned int numberOfTestCases = testCaseInstance->numberOfRuns;

    internal_nbp_increment_number_of_test_cases(
        testCaseInstance->numberOfTestCases,
        tcs_ready,
        numberOfTestCases);

    if (testSuite != NBP_NULLPTR) {
        testSuiteInstance = testSuite->testSuiteInstance;

        testSuite->totalNumberOfTestCaseInstances += 1;
        testSuite->totalNumberOfTestCases += numberOfTestCases;

        testSuiteInstance->totalNumberOfTestCaseInstances += 1;
        testSuiteInstance->totalNumberOfTestCases += numberOfTestCases;

        internal_nbp_increment_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            testSuite->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        internal_nbp_increment_number_of_test_case_instances(
            testSuiteInstance->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            testSuiteInstance->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        parent = testCaseInstance->testSuite->testSuiteInstance->module;
    }

    while (parent != NBP_NULLPTR) {
        parent->totalNumberOfTestCaseInstances += 1;
        parent->totalNumberOfTestCases += numberOfTestCases;

        parent->moduleInstance->totalNumberOfTestCaseInstances += 1;
        parent->moduleInstance->totalNumberOfTestCases += numberOfTestCases;

        internal_nbp_increment_number_of_test_case_instances(
            parent->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            parent->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        internal_nbp_increment_number_of_test_case_instances(
            parent->moduleInstance->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            parent->moduleInstance->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_test_case_update_state_stats(
    nbp_test_case_t* testCase,
    nbp_test_case_state_e oldState,
    nbp_test_case_state_e newState)
{
    nbp_module_t* parent        = testCase->testCaseInstance->module;
    nbp_test_suite_t* testSuite = testCase->testCaseInstance->testSuite;

    internal_nbp_update_number_of_test_cases(
        testCase->testCaseInstance->numberOfTestCases,
        oldState,
        newState);

    if (testSuite != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_cases(
            testSuite->numberOfTestCases,
            oldState,
            newState);

        internal_nbp_update_number_of_test_cases(
            testSuite->testSuiteInstance->numberOfTestCases,
            oldState,
            newState);

        parent = testSuite->testSuiteInstance->module;
    }

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_cases(
            parent->numberOfTestCases,
            oldState,
            newState);

        internal_nbp_update_number_of_test_cases(
            parent->moduleInstance->numberOfTestCases,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_test_case_instance_update_state_stats(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_test_case_instance_state_e oldState,
    nbp_test_case_instance_state_e newState)
{
    nbp_module_t* parent        = testCaseInstance->module;
    nbp_test_suite_t* testSuite = testCaseInstance->testSuite;

    if (testSuite != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_test_case_instances(
            testSuite->testSuiteInstance->numberOfTestCaseInstances,
            oldState,
            newState);

        parent = testSuite->testSuiteInstance->module;
    }

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_case_instances(
            parent->numberOfTestCaseInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_test_case_instances(
            parent->moduleInstance->numberOfTestCaseInstances,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state)
{
    int pos = ((int) state) - ((int) tcs_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state)
{
    int pos = ((int) state) - ((int) tcis_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_test_case_instance_t* internal_nbp_instantiate_test_case(
    nbp_test_case_details_t* testCaseDetails,
    nbp_module_t* parentModule,
    nbp_test_suite_t* parentTestSuite,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    if (numberOfRuns == 0) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_number_of_runs,
            "the number of runs must be greater than 0");
        NBP_EXIT(ec_invalid_number_of_runs);
        return NBP_NULLPTR;
    }

    if (parentModule != NBP_NULLPTR && parentTestSuite != NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "a test case instance must have one single parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    if (parentModule == NBP_NULLPTR && parentTestSuite == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "test case instance has no parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    nbp_test_case_instance_t* testCaseInstance =
        (nbp_test_case_instance_t*) NBP_MEMORY_ALLOC_TAG(
            sizeof(nbp_test_case_instance_t),
            mt_test_case_instance);

    if (testCaseInstance == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate test case instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    nbp_test_case_t* runs = (nbp_test_case_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_test_case_t),
        mt_test_case);

    if (runs == NBP_NULLPTR) {
        NBP_MEMORY_FREE_TAG(testCaseInstance, mt_test_case_instance);

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate the runs for test case instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    gInternalNbpNumberOfTestCases += numberOfRuns;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        runs[i].testCaseInstance = testCaseInstance;
        runs[i].state            = tcs_ready;

        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);
    }

    testCaseInstance->testCaseDetails   = testCaseDetails;
    testCaseInstance->state             = tcis_ready;
    testCaseInstance->module            = parentModule;
    testCaseInstance->testSuite         = parentTestSuite;
    testCaseInstance->depth             = 0;
    testCaseInstance->instantiationLine = instantiationLine;
    testCaseInstance->setupDetails      = testCaseDetails->setupDetails;
    testCaseInstance->teardownDetails   = testCaseDetails->teardownDetails;
    testCaseInstance->runs              = runs;
    testCaseInstance->numberOfRuns      = numberOfRuns;
    testCaseInstance->next              = NBP_NULLPTR;
    testCaseInstance->prev              = NBP_NULLPTR;

    NBP_ATOMIC_INT_STORE(&testCaseInstance->isSkipped, (int) sf_is_not_set);

    for (unsigned int i = 0; i < NBP_NUMBER_OF_TEST_CASE_STATES; i++) {
        NBP_ATOMIC_UINT_STORE(&testCaseInstance->numberOfTestCases[i], 0U);
    }

    if (parentModule != NBP_NULLPTR) {
        testCaseInstance->depth = parentModule->moduleInstance->depth + 1;

        if (parentModule->firstTestCaseInstance == NBP_NULLPTR) {
            parentModule->firstTestCaseInstance = testCaseInstance;
            parentModule->lastTestCaseInstance  = testCaseInstance;
        } else {
            testCaseInstance->prev = parentModule->lastTestCaseInstance;
            parentModule->lastTestCaseInstance->next = testCaseInstance;
            parentModule->lastTestCaseInstance       = testCaseInstance;
        }
    }

    if (parentTestSuite != NBP_NULLPTR) {
        testCaseInstance->depth = parentTestSuite->testSuiteInstance->depth + 1;

        if (parentTestSuite->firstTestCaseInstance == NBP_NULLPTR) {
            parentTestSuite->firstTestCaseInstance = testCaseInstance;
            parentTestSuite->lastTestCaseInstance  = testCaseInstance;
        } else {
            testCaseInstance->prev = parentTestSuite->lastTestCaseInstance;
            parentTestSuite->lastTestCaseInstance->next = testCaseInstance;
            parentTestSuite->lastTestCaseInstance       = testCaseInstance;
        }
    }

    internal_nbp_test_case_instance_update_stats(testCaseInstance);

    internal_nbp_notify_printer_instantiate_test_case(testCaseInstance);
    internal_nbp_notify_scheduler_instantiate_test_case(
        testCaseInstance,
        context);

    return testCaseInstance;
}

static void internal_nbp_increment_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tss_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tss_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e oldState,
    nbp_test_suite_state_e newState)
{
    internal_nbp_decrement_number_of_test_suites(statsArray, oldState, 1);
    internal_nbp_increment_number_of_test_suites(statsArray, newState, 1);
}

static void internal_nbp_increment_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tsis_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tsis_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e oldState,
    nbp_test_suite_instance_state_e newState)
{
    internal_nbp_decrement_number_of_test_suite_instances(
        statsArray,
        oldState,
        1);
    internal_nbp_increment_number_of_test_suite_instances(
        statsArray,
        newState,
        1);
}

static void internal_nbp_test_suite_instance_update_stats(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    nbp_module_t* parent            = testSuiteInstance->module;
    unsigned int numberOfTestSuites = testSuiteInstance->numberOfRuns;

    internal_nbp_increment_number_of_test_suites(
        testSuiteInstance->numberOfTestSuites,
        tss_ready,
        numberOfTestSuites);

    while (parent != NBP_NULLPTR) {
        parent->totalNumberOfTestSuiteInstances += 1;
        parent->totalNumberOfTestSuites += numberOfTestSuites;

        parent->moduleInstance->totalNumberOfTestSuiteInstances += 1;
        parent->moduleInstance->totalNumberOfTestSuites += numberOfTestSuites;

        internal_nbp_increment_number_of_test_suite_instances(
            parent->numberOfTestSuiteInstances,
            tsis_ready,
            1);
        internal_nbp_increment_number_of_test_suites(
            parent->numberOfTestSuites,
            tss_ready,
            numberOfTestSuites);

        internal_nbp_increment_number_of_test_suite_instances(
            parent->moduleInstance->numberOfTestSuiteInstances,
            tsis_ready,
            1);
        internal_nbp_increment_number_of_test_suites(
            parent->moduleInstance->numberOfTestSuites,
            tss_ready,
            numberOfTestSuites);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_test_suite_update_state_stats(
    nbp_test_suite_t* testSuite,
    nbp_test_suite_state_e oldState,
    nbp_test_suite_state_e newState)
{
    nbp_module_t* parent = testSuite->testSuiteInstance->module;

    internal_nbp_update_number_of_test_suites(
        testSuite->testSuiteInstance->numberOfTestSuites,
        oldState,
        newState);

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_suites(
            parent->numberOfTestSuites,
            oldState,
            newState);

        internal_nbp_update_number_of_test_suites(
            parent->moduleInstance->numberOfTestSuites,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_test_suite_instance_update_state_stats(
    nbp_test_suite_instance_t* testSuiteInstance,
    nbp_test_suite_instance_state_e oldState,
    nbp_test_suite_instance_state_e newState)
{
    nbp_module_t* parent = testSuiteInstance->module;

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_suite_instances(
            parent->numberOfTestSuiteInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_test_suite_instances(
            parent->moduleInstance->numberOfTestSuiteInstances,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state)
{
    int pos = ((int) state) - ((int) tss_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state)
{
    int pos = ((int) state) - ((int) tsis_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_test_suite_instance_t* internal_nbp_instantiate_test_suite(
    nbp_test_suite_details_t* testSuiteDetails,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    if (numberOfRuns == 0) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_number_of_runs,
            "the number of runs must be greater than 0");
        NBP_EXIT(ec_invalid_number_of_runs);
        return NBP_NULLPTR;
    }

    if (parentModule == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "test suite instance has no parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    nbp_test_suite_instance_t* testSuiteInstance =
        (nbp_test_suite_instance_t*) NBP_MEMORY_ALLOC_TAG(
            sizeof(nbp_test_suite_instance_t),
            mt_test_suite_instance);

    if (testSuiteInstance == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate test suite instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    nbp_test_suite_t* runs = (nbp_test_suite_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_test_suite_t),
        mt_test_suite);

    if (runs == NBP_NULLPTR) {
        NBP_MEMORY_FREE_TAG(testSuiteInstance, mt_test_suite);

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate the runs for test suite instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        runs[i].testSuiteInstance              = testSuiteInstance;
        runs[i].state                          = tss_ready;
        runs[i].firstTestCaseInstance          = NBP_NULLPTR;
        runs[i].lastTestCaseInstance           = NBP_NULLPTR;
        runs[i].totalNumberOfTestCases         = 0;
        runs[i].totalNumberOfTestCaseInstances = 0;

        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);

        unsigned int j;
        for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestCases[j], 0);
        }
        for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestCaseInstances[j], 0);
        }
    }

    testSuiteInstance->testSuiteDetails  = testSuiteDetails;
    testSuiteInstance->state             = tsis_ready;
    testSuiteInstance->module            = parentModule;
    testSuiteInstance->instantiationLine = instantiationLine;
    testSuiteInstance->setupDetails      = testSuiteDetails->setupDetails;
    testSuiteInstance->teardownDetails   = testSuiteDetails->teardownDetails;
    testSuiteInstance->runs              = runs;
    testSuiteInstance->numberOfRuns      = numberOfRuns;
    testSuiteInstance->next              = NBP_NULLPTR;
    testSuiteInstance->prev              = NBP_NULLPTR;
    testSuiteInstance->depth = parentModule->moduleInstance->depth + 1;
    testSuiteInstance->totalNumberOfTestCases         = 0;
    testSuiteInstance->totalNumberOfTestCaseInstances = 0;

    NBP_ATOMIC_INT_STORE(&testSuiteInstance->isSkipped, (int) sf_is_not_set);

    for (unsigned int i = 0; i < NBP_NUMBER_OF_TEST_CASE_STATES; i++) {
        NBP_ATOMIC_UINT_STORE(&testSuiteInstance->numberOfTestCases[i], 0U);
    }
    for (unsigned int i = 0; i < NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES; i++) {
        NBP_ATOMIC_UINT_STORE(
            &testSuiteInstance->numberOfTestCaseInstances[i],
            0U);
    }
    for (unsigned int i = 0; i < NBP_NUMBER_OF_TEST_SUITE_STATES; i++) {
        NBP_ATOMIC_UINT_STORE(&testSuiteInstance->numberOfTestSuites[i], 0U);
    }

    if (parentModule->firstTestSuiteInstance == NBP_NULLPTR) {
        parentModule->firstTestSuiteInstance = testSuiteInstance;
        parentModule->lastTestSuiteInstance  = testSuiteInstance;
    } else {
        testSuiteInstance->prev = parentModule->lastTestSuiteInstance;
        parentModule->lastTestSuiteInstance->next = testSuiteInstance;
        parentModule->lastTestSuiteInstance       = testSuiteInstance;
    }

    internal_nbp_test_suite_instance_update_stats(testSuiteInstance);

    internal_nbp_notify_printer_instantiate_test_suite_started(
        testSuiteInstance);

    internal_nbp_notify_scheduler_instantiate_test_suite_started(
        testSuiteInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testSuiteInstance->testSuiteDetails->function(
            &testSuiteInstance->runs[i],
            &testSuiteInstance->runs[i],
            NBP_NULLPTR);

        if (testSuiteInstance->runs[i].totalNumberOfTestCaseInstances == 0) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_no_test_case_instantiated,
                "test suite has no test case");
            NBP_EXIT(ec_no_test_case_instantiated);
        }
    }

    internal_nbp_notify_printer_instantiate_test_suite_completed(
        testSuiteInstance);

    internal_nbp_notify_scheduler_instantiate_test_suite_completed(
        testSuiteInstance);

    return testSuiteInstance;
}

#endif // end if NBP_LIBRARY_MAIN

#ifdef NBP_DEFAULT_PRINTER

#ifdef NBP_LIBRARY_MAIN

/*
 * Default nbp printer for Linux
 */
#ifdef NBP_OS_LINUX

#include <stdio.h>

NBP_PRINTER_CALLBACK_INIT(nbp_dp_init)
{
    printf("init\n");
}

NBP_PRINTER_CALLBACK_UNINIT(nbp_dp_uninit)
{
    printf("uninit\n");
}

NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(nbp_dp_handle_version_command)
{
    printf("nbp version: %s\n", NBP_VERSION_STR);
}

NBP_PRINTER_CALLBACK_ON_ERROR(nbp_dp_on_error)
{
    switch (NBP_GET_ERROR_CONTEXT_TYPE(NBP_THIS_ERROR)) {
    case ect_string:
        printf(
            "[error] code = %d, line = %d, file = %s, message = %s\n",
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR),
            NBP_GET_ERROR_STRING_CONTEXT(NBP_THIS_ERROR));
        break;
    default:
        printf(
            "[error] code = %d, line = %d, file = %s\n",
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR));
        break;
    }
}

NBP_PRINTER(
    nbpDefaultPrinter,
    NBP_PRINTER_CALLBACKS(
        NBP_PRINTER_CALLBACK_INIT(nbp_dp_init),
        NBP_PRINTER_CALLBACK_UNINIT(nbp_dp_uninit),
        NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(
            nbp_dp_handle_version_command),
        NBP_PRINTER_CALLBACK_ON_ERROR(nbp_dp_on_error)));

#endif // end if NBP_OS_LINUX

/*
 * Default nbp printer for Windows
 */
#ifdef NBP_OS_WINDOWS
#error "Not supported yet"
#endif // end if NBP_OS_WINDOWS

/*
 * Default nbp printer for Mac
 */
#ifdef NBP_OS_MAC
#error "Not supported yet"
#endif // end if NBP_OS_MAC

/*
 * We don't have default printer for custom OS
 */
#ifdef NBP_OS_CUSTOM
#error "Default printer is not supported on custom OS"
#endif // end if NBP_OS_CUSTOM

#endif // end if NBP_LIBRARY_MAIN

#endif // end if NBP_DEFAULT_PRINTER

/*
 * if custom scheduler is not used then use a default scheduler
 */
#ifndef NBP_CUSTOM_SCHEDULER

/**
 * TODO: add docs
 */
#ifdef NBP_MT_SCHEDULER
#error "Not supported yet"
#endif // end if NBP_MT_SCHEDULER

/**
 * TODO: add docs
 */
#ifdef NBP_BASIC_SCHEDULER
#ifdef NBP_LIBRARY_MAIN

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INIT(func)                                      \
    static void nbp_scheduler_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_UNINIT(func)                                    \
    static void nbp_scheduler_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_RUN(func)                                       \
    static void nbp_scheduler_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(func)                     \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)            \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)          \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)              \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER(name, ...)                                               \
    void nbp_scheduler_interface_config_function_##name(                       \
        NBP_MAYBE_UNUSED_PARAMETER nbp_scheduler_interface_t*                  \
            schedulerInterface)                                                \
    {                                                                          \
        INTERNAL_NBP_GENERATE_SCHEDULER_CONFIG_FUNCTION(F_##__VA_ARGS__)       \
        return;                                                                \
    }                                                                          \
    nbp_scheduler_interface_t gInternalNbpSchedulerInterface##name = {         \
        .schedulerName  = #name,                                               \
        .configFunction = nbp_scheduler_interface_config_function_##name,      \
        .initCbk        = NBP_NULLPTR,                                         \
        .uninitCbk      = NBP_NULLPTR,                                         \
        .runCbk         = NBP_NULLPTR,                                         \
        .instantiateTestCaseCbk           = NBP_NULLPTR,                       \
        .instantiateTestSuiteStartedCbk   = NBP_NULLPTR,                       \
        .instantiateTestSuiteCompletedCbk = NBP_NULLPTR,                       \
        .instantiateModuleStartedCbk      = NBP_NULLPTR,                       \
        .instantiateModuleCompletedCbk    = NBP_NULLPTR,                       \
    }

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_RUN_TEST_CASE_INSTANCE(testCaseInstance)                 \
    internal_nbp_run_test_case_instance(testCaseInstance)

#define INTERNAL_NBP_GENERATE_SCHEDULER_CONFIG_FUNCTION(...)                   \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GSC##__VA_ARGS__))     \
    (GSCF_, GSC##__VA_ARGS__)

#define INTERNAL_NBP_GSCF_NBP_SCHEDULER_CALLBACKS(...)                         \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(SC_##__VA_ARGS__))   \
    (SC_, SC_##__VA_ARGS__)

// This macro is generated when NBP_SCHEDULER macro is used without parameters
#define INTERNAL_NBP_GSCF_

// This macro is generated when NBP_SCHEDULER_CALLBACKS macro is used without
// parameters
#define INTERNAL_NBP_SC_

#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INIT(func)                      \
    schedulerInterface->initCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_UNINIT(func)                    \
    schedulerInterface->uninitCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_RUN(func)                       \
    schedulerInterface->runCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(func)     \
    schedulerInterface->instantiateTestCaseCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED( \
    func)                                                                      \
    schedulerInterface->instantiateTestSuiteStartedCbk =                       \
        nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                        \
    schedulerInterface->instantiateTestSuiteCompletedCbk =                       \
        nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_STARTED(     \
    func)                                                                      \
    schedulerInterface->instantiateModuleStartedCbk =                          \
        nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(   \
    func)                                                                      \
    schedulerInterface->instantiateModuleCompletedCbk =                        \
        nbp_scheduler_callback_##func;

struct nbp_bs_task_queue_t
{
    nbp_test_case_instance_t* testCaseInstance;
    struct nbp_bs_task_queue_t* next;
};
typedef struct nbp_bs_task_queue_t nbp_bs_task_queue_t;

static nbp_bs_task_queue_t* gInternalNbpBsFirstTask = NBP_NULLPTR;
static nbp_bs_task_queue_t* gInternalNbpBsLastTask  = NBP_NULLPTR;

NBP_SCHEDULER_CALLBACK_UNINIT(nbp_bs_uninit)
{
    nbp_bs_task_queue_t* task = gInternalNbpBsFirstTask;
    nbp_bs_task_queue_t* tmp  = NBP_NULLPTR;

    while (task != NBP_NULLPTR) {
        tmp  = task;
        task = task->next;

        NBP_MEMORY_FREE_TAG(tmp, mt_basic_scheduler);
    }
}

NBP_SCHEDULER_CALLBACK_RUN(nbp_bs_run)
{
    nbp_bs_task_queue_t* task = gInternalNbpBsFirstTask;
    while (task != NBP_NULLPTR) {
        NBP_SCHEDULER_RUN_TEST_CASE_INSTANCE(task->testCaseInstance);
        task = task->next;
    }
}

NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_bs_instantiate_test_case)
{
    nbp_bs_task_queue_t* task = (nbp_bs_task_queue_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_bs_task_queue_t),
        mt_basic_scheduler);

    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate basic scheduler task");
        NBP_EXIT(ec_out_of_memory);
    }

    task->testCaseInstance = NBP_THIS_TEST_CASE_INSTANCE;
    task->next             = NBP_NULLPTR;

    if (gInternalNbpBsFirstTask == NBP_NULLPTR) {
        gInternalNbpBsFirstTask = task;
        gInternalNbpBsLastTask  = task;
    } else {
        gInternalNbpBsLastTask->next = task;
        gInternalNbpBsLastTask       = task;
    }
}

NBP_SCHEDULER(
    nbpBasicScheduler,
    NBP_SCHEDULER_CALLBACKS(
        NBP_SCHEDULER_CALLBACK_UNINIT(nbp_bs_uninit),
        NBP_SCHEDULER_CALLBACK_RUN(nbp_bs_run),
        NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_bs_instantiate_test_case)));

#endif // end if NBP_LIBRARY_MAIN

#endif // end if NBP_BASIC_SCHEDULER

#endif // end if NBP_CUSTOM_SCHEDULER

#endif // end if _H_NBP_NBP

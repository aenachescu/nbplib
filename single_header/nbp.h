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
 * Make sure there is only one defined runner
 */
#undef INTERNAL_NBP_RUNNER_DEFINED

#ifdef NBP_CUSTOM_RUNNER
#define INTERNAL_NBP_RUNNER_DEFINED
#endif // end if NBP_CUSTOM_RUNNER

#ifdef NBP_MT_RUNNER
#ifdef INTERNAL_NBP_RUNNER_DEFINED
#error "Cannot enable NBP_MT_RUNNER because another runner is enabled"
#else // INTERNAL_NBP_RUNNER_DEFINED not defined
#define INTERNAL_NBP_RUNNER_DEFINED
#define NBP_MT_SUPPORT
#endif // end if INTERNAL_NBP_RUNNER_DEFINED
#endif // end if NBP_MT_RUNNER

#ifdef NBP_BASIC_RUNNER
#ifdef INTERNAL_NBP_RUNNER_DEFINED
#error "Cannot enable NBP_BASIC_RUNNER because another runner is enabled"
#else // INTERNAL_NBP_RUNNER_DEFINED not defined
#define INTERNAL_NBP_RUNNER_DEFINED
#endif // end if INTERNAL_NBP_RUNNER_DEFINED
#endif // end if NBP_BASIC_RUNNER

/*
 * If no runner is defined then define the default runner
 */
#ifndef INTERNAL_NBP_RUNNER_DEFINED
#define NBP_BASIC_RUNNER
#endif // end if INTERNAL_NBP_RUNNER_DEFINED

#undef INTERNAL_NBP_RUNNER_DEFINED

/*
 * If no reporter is defined then define the default reporter
 */
#if ! defined NBP_CUSTOM_REPORTER && ! defined NBP_CONSOLE_REPORTER
#define NBP_CONSOLE_REPORTER
#endif // end if ! defined NBP_CUSTOM_REPORTER && ! defined NBP_CONSOLE_REPORTER

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
    ec_success                   = 0,
    ec_tests_failed              = 1,
    ec_out_of_memory             = 2,
    ec_sync_error                = 3,
    ec_invalid_command_line      = 4,
    ec_not_all_tests_were_run    = 5,
    ec_invalid_runner_interface  = 6,
    ec_invalid_number_of_runs    = 7,
    ec_runner_run_is_disabled    = 8,
    ec_unexpected_state          = 9,
    ec_invalid_parent            = 10,
    ec_no_test_case_instantiated = 11,
    ec_unexpected_internal_data  = 12,
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
    mt_console_reporter    = 0x4E425006,
    mt_basic_runner        = 0x4E425007,
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

struct nbp_test_case_function_t;
struct nbp_test_case_instance_t;
struct nbp_test_case_t;

typedef void (*nbp_test_case_setup_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

typedef void (*nbp_test_case_teardown_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

typedef void (*nbp_test_case_config_pfn_t)(
    struct nbp_test_case_function_t* /* testCaseFunction */
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

struct nbp_test_case_setup_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_case_setup_pfn_t function;
};
typedef struct nbp_test_case_setup_function_t nbp_test_case_setup_function_t;

struct nbp_test_case_teardown_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_case_teardown_pfn_t function;
};
typedef struct nbp_test_case_teardown_function_t
    nbp_test_case_teardown_function_t;

struct nbp_test_case_function_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_test_case_config_pfn_t configFunction;
    nbp_test_case_pfn_t function;

    nbp_test_case_setup_function_t* setupFunction;
    nbp_test_case_teardown_function_t* teardownFunction;
};
typedef struct nbp_test_case_function_t nbp_test_case_function_t;

struct nbp_test_case_instance_t
{
    nbp_test_case_function_t* testCaseFunction;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* module;
    struct nbp_test_suite_t* testSuite;
    unsigned int depth;

    int instantiationLine;

    nbp_test_case_setup_function_t* setupFunction;
    nbp_test_case_teardown_function_t* teardownFunction;

    struct nbp_test_case_t* runs;
    unsigned int numberOfRuns;
    NBP_ATOMIC_UINT_TYPE numberOfCompletedRuns;

    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];

    struct nbp_test_case_instance_t* next;
    struct nbp_test_case_instance_t* prev;
};
typedef struct nbp_test_case_instance_t nbp_test_case_instance_t;

struct nbp_test_case_t
{
    nbp_test_case_instance_t* testCaseInstance;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;
};
typedef struct nbp_test_case_t nbp_test_case_t;

#define NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_TEST_SUITE_STATES          ((unsigned int) 5)

struct nbp_module_t;

struct nbp_test_suite_function_t;
struct nbp_test_suite_instance_t;
struct nbp_test_suite_t;

typedef void (*nbp_test_suite_setup_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */
);

typedef void (*nbp_test_suite_teardown_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */
);

typedef void (*nbp_test_suite_config_pfn_t)(
    struct nbp_test_suite_function_t* /* testSuiteFunction */
);

typedef void (*nbp_test_suite_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */,
    struct nbp_test_suite_t* /* nbpParamTciParentTestSuite */,
    struct nbp_module_t* /*nbpParamTciParentModule */,
    unsigned int /* nbpParamNumberOfRuns */
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

struct nbp_test_suite_setup_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_suite_setup_pfn_t function;
};
typedef struct nbp_test_suite_setup_function_t nbp_test_suite_setup_function_t;

struct nbp_test_suite_teardown_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_suite_teardown_pfn_t function;
};
typedef struct nbp_test_suite_teardown_function_t
    nbp_test_suite_teardown_function_t;

struct nbp_test_suite_function_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_test_suite_config_pfn_t configFunction;
    nbp_test_suite_pfn_t function;

    nbp_test_suite_setup_function_t* setupFunction;
    nbp_test_suite_teardown_function_t* teardownFunction;
};
typedef struct nbp_test_suite_function_t nbp_test_suite_function_t;

struct nbp_test_suite_instance_t
{
    nbp_test_suite_function_t* testSuiteFunction;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* module;
    unsigned int depth;

    int instantiationLine;

    nbp_test_suite_setup_function_t* setupFunction;
    nbp_test_suite_teardown_function_t* teardownFunction;

    struct nbp_test_suite_t* runs;
    unsigned int numberOfRuns;
    NBP_ATOMIC_UINT_TYPE numberOfCompletedRuns;

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

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    NBP_SYNC_EVENT_TYPE runEvent;
    NBP_SYNC_EVENT_TYPE setupEvent;

    nbp_test_case_instance_t* firstTestCaseInstance;
    nbp_test_case_instance_t* lastTestCaseInstance;

    NBP_ATOMIC_UINT_TYPE numberOfCompletedTasks;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
};
typedef struct nbp_test_suite_t nbp_test_suite_t;

#define NBP_NUMBER_OF_MODULE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_MODULE_STATES          ((unsigned int) 5)

struct nbp_module_function_t;
struct nbp_module_instance_t;
struct nbp_module_t;

typedef void (*nbp_module_setup_pfn_t)(
    struct nbp_module_t* /* nbpParamModule */);

typedef void (*nbp_module_teardown_pfn_t)(
    struct nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_module_config_pfn_t)(
    struct nbp_module_function_t* /* moduleFunction */
);

typedef void (*nbp_module_pfn_t)(
    struct nbp_module_t* /* nbpParamModule*/,
    struct nbp_test_suite_t* /* nbpParamTciParentTestSuite */,
    struct nbp_module_t* /* nbpParamTciParentModule */,
    struct nbp_module_t* /* nbpParamTsiParentModule */,
    struct nbp_module_t* /* nbpParamMiParentModule */,
    unsigned int /* nbpParamNumberOfRuns */
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

struct nbp_module_setup_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_module_setup_pfn_t function;
};
typedef struct nbp_module_setup_function_t nbp_module_setup_function_t;

struct nbp_module_teardown_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_module_teardown_pfn_t function;
};
typedef struct nbp_module_teardown_function_t nbp_module_teardown_function_t;

struct nbp_module_function_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_module_config_pfn_t configFunction;
    nbp_module_pfn_t function;

    nbp_module_setup_function_t* setupFunction;
    nbp_module_teardown_function_t* teardownFunction;
};
typedef struct nbp_module_function_t nbp_module_function_t;

struct nbp_module_instance_t
{
    nbp_module_function_t* moduleFunction;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* parent;
    unsigned int depth;

    int instantiationLine;

    nbp_module_setup_function_t* setupFunction;
    nbp_module_teardown_function_t* teardownFunction;

    struct nbp_module_t* runs;
    unsigned int numberOfRuns;
    NBP_ATOMIC_UINT_TYPE numberOfCompletedRuns;

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

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    NBP_SYNC_EVENT_TYPE runEvent;
    NBP_SYNC_EVENT_TYPE setupEvent;

    nbp_test_case_instance_t* firstTestCaseInstance;
    nbp_test_case_instance_t* lastTestCaseInstance;

    nbp_test_suite_instance_t* firstTestSuiteInstance;
    nbp_test_suite_instance_t* lastTestSuiteInstance;

    nbp_module_instance_t* firstModuleInstance;
    nbp_module_instance_t* lastModuleInstance;

    unsigned int numberOfTasks;
    NBP_ATOMIC_UINT_TYPE numberOfCompletedTasks;

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

struct nbp_reporter_interface_t;

struct nbp_reporter_statistics_t
{
    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    unsigned int totalNumberOfTestSuites;
    unsigned int totalNumberOfTestSuiteInstances;
    unsigned int totalNumberOfModules;
    unsigned int totalNumberOfModuleInstances;

    unsigned int numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    unsigned int
        numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    unsigned int numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];
    unsigned int
        numberOfTestSuiteInstances[NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES];
    unsigned int numberOfModules[NBP_NUMBER_OF_MODULE_STATES];
    unsigned int numberOfModuleInstances[NBP_NUMBER_OF_MODULE_INSTANCE_STATES];
};
typedef struct nbp_reporter_statistics_t nbp_reporter_statistics_t;

typedef void (*nbp_reporter_config_pfn_t)(
    struct nbp_reporter_interface_t* /* reporterInterface */
);

typedef void (*nbp_reporter_callback_init_pfn_t)(void);

typedef void (*nbp_reporter_callback_uninit_pfn_t)(void);

typedef void (*nbp_reporter_callback_handle_version_command_pfn_t)(void);

typedef void (*nbp_reporter_callback_on_error_pfn_t)(
    nbp_error_t /* nbpParamError */
);

typedef void (*nbp_reporter_callback_on_exit_pfn_t)(
    nbp_error_code_e /* nbpParamErrorCode */
);

typedef void (*nbp_reporter_callback_before_run_pfn_t)(
    nbp_reporter_statistics_t* /* nbpParamStatistics */
);

typedef void (*nbp_reporter_callback_after_run_pfn_t)(
    nbp_reporter_statistics_t* /* nbpParamStatistics */
);

typedef void (*nbp_reporter_callback_on_instantiate_test_case_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_test_suite_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_test_suite_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_module_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_module_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_started_pfn_t)(
    nbp_test_case_t* /* nbpParamTestCase */,
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_completed_pfn_t)(
    nbp_test_case_t* /* nbpParamTestCase */,
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_instance_started_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_instance_completed_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_started_pfn_t)(
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_completed_pfn_t)(
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_instance_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_instance_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_module_started_pfn_t)(
    nbp_module_t* /* nbpParamModule */,
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_reporter_callback_on_module_completed_pfn_t)(
    nbp_module_t* /* nbpParamModule */,
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_reporter_callback_on_module_instance_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_reporter_callback_on_module_instance_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

struct nbp_reporter_interface_t
{
    const char* reporterName;
    nbp_reporter_config_pfn_t configFunction;

    int isInitialized;

    nbp_reporter_callback_init_pfn_t initCbk;
    nbp_reporter_callback_uninit_pfn_t uninitCbk;

    nbp_reporter_callback_handle_version_command_pfn_t handleVersionCommandCbk;

    nbp_reporter_callback_on_error_pfn_t errorCbk;
    nbp_reporter_callback_on_exit_pfn_t exitCbk;

    nbp_reporter_callback_before_run_pfn_t beforeRunCbk;
    nbp_reporter_callback_after_run_pfn_t afterRunCbk;

    nbp_reporter_callback_on_instantiate_test_case_pfn_t instantiateTestCaseCbk;

    nbp_reporter_callback_on_instantiate_test_suite_started_pfn_t
        instantiateTestSuiteStartedCbk;
    nbp_reporter_callback_on_instantiate_test_suite_completed_pfn_t
        instantiateTestSuiteCompletedCbk;

    nbp_reporter_callback_on_instantiate_module_started_pfn_t
        instantiateModuleStartedCbk;
    nbp_reporter_callback_on_instantiate_module_completed_pfn_t
        instantiateModuleCompletedCbk;

    nbp_reporter_callback_on_test_case_started_pfn_t testCaseStartedCbk;
    nbp_reporter_callback_on_test_case_completed_pfn_t testCaseCompletedCbk;
    nbp_reporter_callback_on_test_case_instance_started_pfn_t
        testCaseInstanceStartedCbk;
    nbp_reporter_callback_on_test_case_instance_completed_pfn_t
        testCaseInstanceCompletedCbk;

    nbp_reporter_callback_on_test_suite_started_pfn_t testSuiteStartedCbk;
    nbp_reporter_callback_on_test_suite_completed_pfn_t testSuiteCompletedCbk;
    nbp_reporter_callback_on_test_suite_instance_started_pfn_t
        testSuiteInstanceStartedCbk;
    nbp_reporter_callback_on_test_suite_instance_completed_pfn_t
        testSuiteInstanceCompletedCbk;

    nbp_reporter_callback_on_module_started_pfn_t moduleStartedCbk;
    nbp_reporter_callback_on_module_completed_pfn_t moduleCompletedCbk;
    nbp_reporter_callback_on_module_instance_started_pfn_t
        moduleInstanceStartedCbk;
    nbp_reporter_callback_on_module_instance_completed_pfn_t
        moduleInstanceCompletedCbk;
};
typedef struct nbp_reporter_interface_t nbp_reporter_interface_t;

struct nbp_runner_interface_t;

typedef void (*nbp_runner_config_pfn_t)(
    struct nbp_runner_interface_t* /* runnerInterface */
);

typedef void (*nbp_runner_callback_init_pfn_t)(void);

typedef void (*nbp_runner_callback_uninit_pfn_t)(void);

typedef void (*nbp_runner_callback_run_pfn_t)(void);

typedef void (*nbp_runner_callback_on_instantiate_test_case_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);
typedef void (*nbp_runner_callback_on_instantiate_test_suite_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);

typedef void (*nbp_runner_callback_on_instantiate_test_suite_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_runner_callback_on_instantiate_module_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);

typedef void (*nbp_runner_callback_on_instantiate_module_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

struct nbp_runner_interface_t
{
    const char* runnerName;
    nbp_runner_config_pfn_t configFunction;

    nbp_runner_callback_init_pfn_t initCbk;
    nbp_runner_callback_uninit_pfn_t uninitCbk;
    nbp_runner_callback_run_pfn_t runCbk;
    nbp_runner_callback_on_instantiate_test_case_pfn_t instantiateTestCaseCbk;
    nbp_runner_callback_on_instantiate_test_suite_started_pfn_t
        instantiateTestSuiteStartedCbk;
    nbp_runner_callback_on_instantiate_test_suite_completed_pfn_t
        instantiateTestSuiteCompletedCbk;
    nbp_runner_callback_on_instantiate_module_started_pfn_t
        instantiateModuleStartedCbk;
    nbp_runner_callback_on_instantiate_module_completed_pfn_t
        instantiateModuleCompletedCbk;
};
typedef struct nbp_runner_interface_t nbp_runner_interface_t;

enum nbp_statistics_type_e
{
    st_total_number_of_test_cases           = 0x70000000,
    st_total_number_of_test_case_instances  = 0x70000001,
    st_total_number_of_test_suites          = 0x70000002,
    st_total_number_of_test_suite_instances = 0x70000003,
    st_total_number_of_modules              = 0x70000004,
    st_total_number_of_module_instances     = 0x70000005,
    st_number_of_test_cases                 = 0x70000006,
    st_number_of_test_case_instances        = 0x70000007,
    st_number_of_test_suites                = 0x70000008,
    st_number_of_test_suite_instances       = 0x70000009,
    st_number_of_modules                    = 0x7000000A,
    st_number_of_module_instances           = 0x7000000B,
};
typedef enum nbp_statistics_type_e nbp_statistics_type_e;

unsigned int internal_nbp_get_module_state_position(nbp_module_state_e state);

unsigned int internal_nbp_get_module_instance_state_position(
    nbp_module_instance_state_e state);

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

nbp_module_t* internal_nbp_get_module_from_instance(
    nbp_module_instance_t* moduleInstance,
    unsigned int runId);

nbp_module_instance_t* internal_nbp_instantiate_module(
    nbp_module_function_t* moduleFunction,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

#define INTERNAL_NBP_INCLUDE_REPORTER(name)                                    \
    extern nbp_reporter_interface_t gInternalNbpReporterInterface##name

#define INTERNAL_NBP_GET_POINTER_TO_REPORTER(name)                             \
    &gInternalNbpReporterInterface##name

void internal_nbp_notify_reporter_init();

void internal_nbp_notify_reporter_uninit();

void internal_nbp_notify_reporter_handle_version_command();

void internal_nbp_notify_reporter_on_error(
    nbp_error_code_e errorCode,
    int line,
    const char* file);

void internal_nbp_notify_reporter_on_error_string_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    const char* context);

void internal_nbp_notify_reporter_on_error_custom_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    void* context);

void internal_nbp_notify_reporter_on_exit(nbp_error_code_e errorCode);

void internal_nbp_notify_reporter_before_run();

void internal_nbp_notify_reporter_after_run();

void internal_nbp_notify_reporter_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_reporter_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_reporter_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_reporter_instantiate_module_started(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_reporter_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_reporter_test_case_started(nbp_test_case_t* testCase);

void internal_nbp_notify_reporter_test_case_completed(
    nbp_test_case_t* testCase);

void internal_nbp_notify_reporter_test_case_instance_started(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_reporter_test_case_instance_completed(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_reporter_test_suite_started(
    nbp_test_suite_t* testSuite);

void internal_nbp_notify_reporter_test_suite_completed(
    nbp_test_suite_t* testSuite);

void internal_nbp_notify_reporter_test_suite_instance_started(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_reporter_test_suite_instance_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_reporter_module_started(nbp_module_t* module);

void internal_nbp_notify_reporter_module_completed(nbp_module_t* module);

void internal_nbp_notify_reporter_module_instance_started(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_reporter_module_instance_completed(
    nbp_module_instance_t* moduleInstance);

#define INTERNAL_NBP_INCLUDE_RUNNER(name)                                      \
    extern nbp_runner_interface_t gInternalNbpRunnerInterface##name

#define INTERNAL_NBP_GET_POINTER_TO_RUNNER(name)                               \
    &gInternalNbpRunnerInterface##name

void internal_nbp_runner_run_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_runner_init();

void internal_nbp_notify_runner_uninit();

void internal_nbp_notify_runner_run();

void internal_nbp_notify_runner_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance,
    void* context);

void internal_nbp_notify_runner_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance,
    void* context);

void internal_nbp_notify_runner_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_runner_instantiate_module_started(
    nbp_module_instance_t* moduleInstance,
    void* context);

void internal_nbp_notify_runner_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance);

#ifdef NBP_MT_SUPPORT

#ifdef NBP_OS_LINUX

nbp_error_code_e internal_nbp_linux_sync_event_init(sem_t* event);

nbp_error_code_e internal_nbp_linux_sync_event_uninit(sem_t* event);

nbp_error_code_e internal_nbp_linux_sync_event_wait(sem_t* event);

nbp_error_code_e internal_nbp_linux_sync_event_notify(sem_t* event);

#endif // end if NBP_OS_LINUX

#endif // end if NBP_MT_SUPPORT

unsigned int internal_nbp_get_test_case_state_position(
    nbp_test_case_state_e state);

unsigned int internal_nbp_get_test_case_instance_state_position(
    nbp_test_case_instance_state_e state);

int internal_nbp_is_failed_test_case(nbp_test_case_t* testCase);

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

nbp_test_case_t* internal_nbp_get_test_case_from_instance(
    nbp_test_case_instance_t* testCaseInstance,
    unsigned int runId);

nbp_test_case_instance_t* internal_nbp_instantiate_test_case(
    nbp_test_case_function_t* testCaseFunction,
    nbp_module_t* parentModule,
    nbp_test_suite_t* parentTestSuite,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

unsigned int internal_nbp_get_test_suite_state_position(
    nbp_test_suite_state_e state);

unsigned int internal_nbp_get_test_suite_instance_state_position(
    nbp_test_suite_instance_state_e state);

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

nbp_test_suite_t* internal_nbp_get_test_suite_from_instance(
    nbp_test_suite_instance_t* testSuiteInstance,
    unsigned int runId);

nbp_test_suite_instance_t* internal_nbp_instantiate_test_suite(
    nbp_test_suite_function_t* testSuiteFunction,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

void internal_nbp_initialize_array_of_atomic_uint(
    NBP_ATOMIC_UINT_TYPE* array,
    unsigned int size,
    unsigned int value);

void internal_nbp_copy_array_of_atomic_uint(
    NBP_ATOMIC_UINT_TYPE* source,
    unsigned int* dest,
    unsigned int size);

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR(errCode)                                              \
    internal_nbp_notify_reporter_on_error(                                     \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE)

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR_STRING_CONTEXT(errCode, context)                      \
    internal_nbp_notify_reporter_on_error_string_context(                      \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE,                                                       \
        context)

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR_CUSTOM_CONTEXT(errCode, context)                      \
    internal_nbp_notify_reporter_on_error_custom_context(                      \
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
    internal_nbp_notify_reporter_on_exit(errorCode);                           \
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
    internal_nbp_notify_reporter_on_exit(errorCode);                           \
    NBP_EXIT_FUNCTION(errorCode)

#endif // end if NBP_CUSTOM_EXIT

/**
 * TODO: add docs
 */
#define NBP_NUMBER_OF_RUNS(num)

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
    nbp_module_setup_function_t gInternalNbpModuleSetupFunction##func = {      \
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
    nbp_module_teardown_function_t gInternalNbpModuleTeardownFunction##func =  \
        {                                                                      \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_module_teardown_function_##func,               \
    };                                                                         \
    void nbp_module_teardown_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_MODULE(func, ...)                                                  \
    void nbp_module_config_function_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_function_t* moduleFunction)      \
    {                                                                          \
        if (moduleFunction->isConfigured == 1) {                               \
            return;                                                            \
        } else {                                                               \
            moduleFunction->isConfigured = 1;                                  \
        }                                                                      \
        INTERNAL_NBP_GENERATE_MODULE_CONFIG_FUNCTION(F_##__VA_ARGS__)          \
    }                                                                          \
    void nbp_module_function_##func(                                           \
        nbp_module_t* nbpParamModule,                                          \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        nbp_module_t* nbpParamTsiParentModule,                                 \
        nbp_module_t* nbpParamMiParentModule,                                  \
        unsigned int nbpParamNumberOfRuns);                                    \
    nbp_module_function_t gInternalNbpModuleFunction##func = {                 \
        .name             = #func,                                             \
        .functionName     = #func,                                             \
        .file             = NBP_SOURCE_FILE,                                   \
        .line             = NBP_SOURCE_LINE,                                   \
        .isConfigured     = 0,                                                 \
        .configFunction   = nbp_module_config_function_##func,                 \
        .function         = nbp_module_function_##func,                        \
        .setupFunction    = NBP_NULLPTR,                                       \
        .teardownFunction = NBP_NULLPTR,                                       \
    };                                                                         \
    void nbp_module_function_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTsiParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamMiParentModule,       \
        NBP_MAYBE_UNUSED_PARAMETER unsigned int nbpParamNumberOfRuns)

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
#define NBP_INCLUDE_MODULE_SETUP_FUNCTION(func)                                \
    extern nbp_module_setup_function_t gInternalNbpModuleSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_SETUP_FUNCTION(func)                         \
    &gInternalNbpModuleSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE_TEARDOWN_FUNCTION(func)                             \
    extern nbp_module_teardown_function_t                                      \
        gInternalNbpModuleTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_TEARDOWN_FUNCTION(func)                      \
    &gInternalNbpModuleTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE_FUNCTION(func)                                      \
    extern nbp_module_function_t gInternalNbpModuleFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_FUNCTION(func)                               \
    &gInternalNbpModuleFunction##func

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
#define NBP_MODULE_GET_NAME(module)                                            \
    NBP_MODULE_INSTANCE_GET_NAME(module->moduleInstance)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_STATE(module)                                           \
    (nbp_module_state_e) NBP_ATOMIC_INT_LOAD(&(module)->state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_DEPTH(module)                                           \
    NBP_MODULE_INSTANCE_GET_DEPTH(module->moduleInstance)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_STATISTICS(module, type, ...)                           \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_MGS_,                                                     \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (module, INTERNAL_NBP_MGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_INSTANCE(module) module->moduleInstance

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NAME(moduleInstance)                           \
    moduleInstance->moduleFunction->name

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_STATE(moduleInstance)                          \
    (nbp_module_instance_state_e) NBP_ATOMIC_INT_LOAD(&(moduleInstance)->state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_DEPTH(moduleInstance) moduleInstance->depth

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_STATISTICS(moduleInstance, type, ...)          \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_MIGS_,                                                    \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (moduleInstance, INTERNAL_NBP_MIGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(moduleInstance)                 \
    moduleInstance->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_MODULE(moduleInstance, runId)                  \
    internal_nbp_get_module_from_instance(moduleInstance, runId)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_MODULE(func, ...)                                      \
    NBP_INCLUDE_MODULE_FUNCTION(func);                                         \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(MPIO_##__VA_ARGS__))   \
    (MPIO_, MPIO_##__VA_ARGS__);                                               \
    internal_nbp_instantiate_module(                                           \
        NBP_GET_POINTER_TO_MODULE_FUNCTION(func),                              \
        nbpParamMiParentModule,                                                \
        NBP_SOURCE_LINE,                                                       \
        nbpParamNumberOfRuns,                                                  \
        NBP_NULLPTR);                                                          \
    nbpParamNumberOfRuns = 1;

#define INTERNAL_NBP_GENERATE_MODULE_CONFIG_FUNCTION(...)                      \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GMC##__VA_ARGS__))     \
    (GMCF_, GMC##__VA_ARGS__)

// This macro is generated when NBP_MODULE macro is used without parameters
#define INTERNAL_NBP_GMCF_

#define INTERNAL_NBP_GMCF_NBP_MODULE_NAME(newName)                             \
    moduleFunction->name = newName;

#define INTERNAL_NBP_GMCF_NBP_MODULE_SETUP(func)                               \
    NBP_INCLUDE_MODULE_SETUP_FUNCTION(func);                                   \
    moduleFunction->setupFunction =                                            \
        NBP_GET_POINTER_TO_MODULE_SETUP_FUNCTION(func);

#define INTERNAL_NBP_GMCF_NBP_MODULE_TEARDOWN(func)                            \
    NBP_INCLUDE_MODULE_TEARDOWN_FUNCTION(func);                                \
    moduleFunction->teardownFunction =                                         \
        NBP_GET_POINTER_TO_MODULE_TEARDOWN_FUNCTION(func);

#define INTERNAL_NBP_GMCF_NBP_MODULE_FIXTURES(setupFunc, teardownFunc)         \
    INTERNAL_NBP_GMCF_NBP_MODULE_SETUP(setupFunc)                              \
    INTERNAL_NBP_GMCF_NBP_MODULE_TEARDOWN(teardownFunc)

// This macro is generated when NBP_INSTANTIATE_MODULE macro is used without
// parameters
#define INTERNAL_NBP_MPIO_

#define INTERNAL_NBP_MPIO_NBP_NUMBER_OF_RUNS(num) nbpParamNumberOfRuns = num;

// Helpers for NBP_MODULE_GET_STATISTICS

#define INTERNAL_NBP_MGS_PARAM_

#define INTERNAL_NBP_MGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_MGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_MGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_MGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_MGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_MGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_MGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_MGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_MGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_MGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_MGS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_MGS_PARAM_tss_running tss_running
#define INTERNAL_NBP_MGS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_MGS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_MGS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_MGS_PARAM_tsis_ready   tsis_ready
#define INTERNAL_NBP_MGS_PARAM_tsis_running tsis_running
#define INTERNAL_NBP_MGS_PARAM_tsis_passed  tsis_passed
#define INTERNAL_NBP_MGS_PARAM_tsis_failed  tsis_failed
#define INTERNAL_NBP_MGS_PARAM_tsis_skipped tsis_skipped

#define INTERNAL_NBP_MGS_PARAM_ms_ready   ms_ready
#define INTERNAL_NBP_MGS_PARAM_ms_running ms_running
#define INTERNAL_NBP_MGS_PARAM_ms_passed  ms_passed
#define INTERNAL_NBP_MGS_PARAM_ms_failed  ms_failed
#define INTERNAL_NBP_MGS_PARAM_ms_skipped ms_skipped

#define INTERNAL_NBP_MGS_PARAM_mis_ready   mis_ready
#define INTERNAL_NBP_MGS_PARAM_mis_running mis_running
#define INTERNAL_NBP_MGS_PARAM_mis_passed  mis_passed
#define INTERNAL_NBP_MGS_PARAM_mis_failed  mis_failed
#define INTERNAL_NBP_MGS_PARAM_mis_skipped mis_skipped

#define INTERNAL_NBP_MGS_st_total_number_of_test_cases1(m, unused)             \
    unused m->totalNumberOfTestCases
#define INTERNAL_NBP_MGS_st_total_number_of_test_case_instances1(m, unused)    \
    unused m->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_MGS_st_total_number_of_test_suites1(m, unused)            \
    unused m->totalNumberOfTestSuites
#define INTERNAL_NBP_MGS_st_total_number_of_test_suite_instances1(m, unused)   \
    unused m->totalNumberOfTestSuiteInstances
#define INTERNAL_NBP_MGS_st_total_number_of_modules1(m, unused)                \
    unused m->totalNumberOfModules
#define INTERNAL_NBP_MGS_st_total_number_of_module_instances1(m, unused)       \
    unused m->totalNumberOfModuleInstances

#define INTERNAL_NBP_MGS_st_number_of_test_cases1(m, state)                    \
    internal_nbp_get_number_of_test_cases(m->numberOfTestCases, state)
#define INTERNAL_NBP_MGS_st_number_of_test_case_instances1(m, state)           \
    internal_nbp_get_number_of_test_case_instances(                            \
        m->numberOfTestCaseInstances,                                          \
        state)
#define INTERNAL_NBP_MGS_st_number_of_test_suites1(m, state)                   \
    internal_nbp_get_number_of_test_suites(m->numberOfTestSuites, state)
#define INTERNAL_NBP_MGS_st_number_of_test_suite_instances1(m, state)          \
    internal_nbp_get_number_of_test_suite_instances(                           \
        m->numberOfTestSuiteInstances,                                         \
        state)
#define INTERNAL_NBP_MGS_st_number_of_modules1(m, state)                       \
    internal_nbp_get_number_of_modules(m->numberOfModules, state)
#define INTERNAL_NBP_MGS_st_number_of_module_instances1(m, state)              \
    internal_nbp_get_number_of_module_instances(                               \
        m->numberOfModuleInstances,                                            \
        state)

// Helpers for NBP_MODULE_INSTANCE_GET_STATISTICS

#define INTERNAL_NBP_MIGS_PARAM_

#define INTERNAL_NBP_MIGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_MIGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_MIGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_MIGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_MIGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_MIGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_MIGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_MIGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_MIGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_MIGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_MIGS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_MIGS_PARAM_tss_running tss_running
#define INTERNAL_NBP_MIGS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_MIGS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_MIGS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_MIGS_PARAM_tsis_ready   tsis_ready
#define INTERNAL_NBP_MIGS_PARAM_tsis_running tsis_running
#define INTERNAL_NBP_MIGS_PARAM_tsis_passed  tsis_passed
#define INTERNAL_NBP_MIGS_PARAM_tsis_failed  tsis_failed
#define INTERNAL_NBP_MIGS_PARAM_tsis_skipped tsis_skipped

#define INTERNAL_NBP_MIGS_PARAM_ms_ready   ms_ready
#define INTERNAL_NBP_MIGS_PARAM_ms_running ms_running
#define INTERNAL_NBP_MIGS_PARAM_ms_passed  ms_passed
#define INTERNAL_NBP_MIGS_PARAM_ms_failed  ms_failed
#define INTERNAL_NBP_MIGS_PARAM_ms_skipped ms_skipped

#define INTERNAL_NBP_MIGS_PARAM_mis_ready   mis_ready
#define INTERNAL_NBP_MIGS_PARAM_mis_running mis_running
#define INTERNAL_NBP_MIGS_PARAM_mis_passed  mis_passed
#define INTERNAL_NBP_MIGS_PARAM_mis_failed  mis_failed
#define INTERNAL_NBP_MIGS_PARAM_mis_skipped mis_skipped

#define INTERNAL_NBP_MIGS_st_total_number_of_test_cases1(mi, unused)           \
    unused mi->totalNumberOfTestCases
#define INTERNAL_NBP_MIGS_st_total_number_of_test_case_instances1(mi, unused)  \
    unused mi->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_MIGS_st_total_number_of_test_suites1(mi, unused)          \
    unused mi->totalNumberOfTestSuites
#define INTERNAL_NBP_MIGS_st_total_number_of_test_suite_instances1(mi, unused) \
    unused mi->totalNumberOfTestSuiteInstances
#define INTERNAL_NBP_MIGS_st_total_number_of_modules1(mi, unused)              \
    unused mi->totalNumberOfModules
#define INTERNAL_NBP_MIGS_st_total_number_of_module_instances1(mi, unused)     \
    unused mi->totalNumberOfModuleInstances

#define INTERNAL_NBP_MIGS_st_number_of_test_cases1(mi, state)                  \
    internal_nbp_get_number_of_test_cases(mi->numberOfTestCases, state)
#define INTERNAL_NBP_MIGS_st_number_of_test_case_instances1(mi, state)         \
    internal_nbp_get_number_of_test_case_instances(                            \
        mi->numberOfTestCaseInstances,                                         \
        state)
#define INTERNAL_NBP_MIGS_st_number_of_test_suites1(mi, state)                 \
    internal_nbp_get_number_of_test_suites(mi->numberOfTestSuites, state)
#define INTERNAL_NBP_MIGS_st_number_of_test_suite_instances1(mi, state)        \
    internal_nbp_get_number_of_test_suite_instances(                           \
        mi->numberOfTestSuiteInstances,                                        \
        state)
#define INTERNAL_NBP_MIGS_st_number_of_modules1(mi, state)                     \
    internal_nbp_get_number_of_modules(mi->numberOfModules, state)
#define INTERNAL_NBP_MIGS_st_number_of_module_instances1(mi, state)            \
    internal_nbp_get_number_of_module_instances(                               \
        mi->numberOfModuleInstances,                                           \
        state)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INIT(func) void nbp_reporter_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_UNINIT(func) void nbp_reporter_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(func)                     \
    void nbp_reporter_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_ON_ERROR(func)                                   \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_t nbpParamError)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_ON_EXIT(func)                                    \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_code_e nbpParamErrorCode)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_BEFORE_RUN(func)                                 \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_reporter_statistics_t*                  \
            nbpParamStatistics)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_AFTER_RUN(func)                                  \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_reporter_statistics_t*                  \
            nbpParamStatistics)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(func)                      \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)             \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)           \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                 \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)               \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_STARTED(func)                          \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(func)                        \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)                 \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(func)               \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_STARTED(func)                         \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_COMPLETED(func)                       \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func)                \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(func)              \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_STARTED(func)                             \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_COMPLETED(func)                           \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_INSTANCE_STARTED(func)                    \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)                  \
    void nbp_reporter_callback_##func(                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_REPORTER(name, ...)                                                \
    void nbp_reporter_interface_config_function_##name(                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_reporter_interface_t*                   \
            reporterInterface)                                                 \
    {                                                                          \
        INTERNAL_NBP_GENERATE_REPORTER_CONFIG_FUNCTION(F_##__VA_ARGS__)        \
        return;                                                                \
    }                                                                          \
    nbp_reporter_interface_t gInternalNbpReporterInterface##name = {           \
        .reporterName   = #name,                                               \
        .configFunction = INTERNAL_NBP_GENERATE_REPORTER_INTERFACE_NAME(name), \
        .isInitialized  = 0,                                                   \
        .initCbk        = NBP_NULLPTR,                                         \
        .uninitCbk      = NBP_NULLPTR,                                         \
        .handleVersionCommandCbk          = NBP_NULLPTR,                       \
        .errorCbk                         = NBP_NULLPTR,                       \
        .exitCbk                          = NBP_NULLPTR,                       \
        .beforeRunCbk                     = NBP_NULLPTR,                       \
        .afterRunCbk                      = NBP_NULLPTR,                       \
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

/**
 * TODO: add docs
 */
#define NBP_REPORTER_GET_STATISTICS(type, ...)                                 \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_RS_,                                                      \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (INTERNAL_NBP_RS_PARAM_##__VA_ARGS__)

#define INTERNAL_NBP_GENERATE_REPORTER_INTERFACE_NAME(name)                    \
    nbp_reporter_interface_config_function_##name

#define INTERNAL_NBP_GENERATE_REPORTER_CONFIG_FUNCTION(...)                    \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GRC##__VA_ARGS__))     \
    (GRCF_, GRC##__VA_ARGS__)

#define INTERNAL_NBP_GRCF_NBP_REPORTER_CALLBACKS(...)                          \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(R_##__VA_ARGS__))    \
    (R_, R_##__VA_ARGS__)

// This macro is generated when NBP_REPORTER macro is used without parameters
#define INTERNAL_NBP_GRCF_

// This macro is generated when NBP_REPORTER_CALLBACKS macro is used without
// parameters
#define INTERNAL_NBP_R_

#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INIT(func)                        \
    NBP_REPORTER_CALLBACK_INIT(func);                                          \
    reporterInterface->initCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_UNINIT(func)                      \
    NBP_REPORTER_CALLBACK_UNINIT(func);                                        \
    reporterInterface->uninitCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(func)      \
    NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(func);                        \
    reporterInterface->handleVersionCommandCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_ON_ERROR(func)                    \
    NBP_REPORTER_CALLBACK_ON_ERROR(func);                                      \
    reporterInterface->errorCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_ON_EXIT(func)                     \
    NBP_REPORTER_CALLBACK_ON_EXIT(func);                                       \
    reporterInterface->exitCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_BEFORE_RUN(func)                  \
    NBP_REPORTER_CALLBACK_BEFORE_RUN(func);                                    \
    reporterInterface->beforeRunCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_AFTER_RUN(func)                   \
    NBP_REPORTER_CALLBACK_AFTER_RUN(func);                                     \
    reporterInterface->afterRunCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(func)       \
    NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(func);                         \
    reporterInterface->instantiateTestCaseCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(   \
    func)                                                                      \
    NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func);                \
    reporterInterface->instantiateTestSuiteStartedCbk =                        \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                      \
    NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func);              \
    reporterInterface->instantiateTestSuiteCompletedCbk =                      \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)  \
    NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func);                    \
    reporterInterface->instantiateModuleStartedCbk =                           \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(     \
    func)                                                                      \
    NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func);                  \
    reporterInterface->instantiateModuleCompletedCbk =                         \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_STARTED(func)           \
    NBP_REPORTER_CALLBACK_TEST_CASE_STARTED(func);                             \
    reporterInterface->testCaseStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(func)         \
    NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(func);                           \
    reporterInterface->testCaseCompletedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)  \
    NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func);                    \
    reporterInterface->testCaseInstanceStartedCbk =                            \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(     \
    func)                                                                      \
    NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(func);                  \
    reporterInterface->testCaseInstanceCompletedCbk =                          \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_STARTED(func)          \
    NBP_REPORTER_CALLBACK_TEST_SUITE_STARTED(func);                            \
    reporterInterface->testSuiteStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_COMPLETED(func)        \
    NBP_REPORTER_CALLBACK_TEST_SUITE_COMPLETED(func);                          \
    reporterInterface->testSuiteCompletedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func) \
    NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func);                   \
    reporterInterface->testSuiteInstanceStartedCbk =                           \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(    \
    func)                                                                      \
    NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(func);                 \
    reporterInterface->testSuiteInstanceCompletedCbk =                         \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_STARTED(func)              \
    NBP_REPORTER_CALLBACK_MODULE_STARTED(func);                                \
    reporterInterface->moduleStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_COMPLETED(func)            \
    NBP_REPORTER_CALLBACK_MODULE_COMPLETED(func);                              \
    reporterInterface->moduleCompletedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_INSTANCE_STARTED(func)     \
    NBP_REPORTER_CALLBACK_MODULE_INSTANCE_STARTED(func);                       \
    reporterInterface->moduleInstanceStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)   \
    NBP_REPORTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func);                     \
    reporterInterface->moduleInstanceCompletedCbk =                            \
        nbp_reporter_callback_##func;

#define INTERNAL_NBP_RS_PARAM_

#define INTERNAL_NBP_RS_st_total_number_of_test_cases1(unused)                 \
    unused nbpParamStatistics->totalNumberOfTestCases
#define INTERNAL_NBP_RS_st_total_number_of_test_case_instances1(unused)        \
    unused nbpParamStatistics->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_RS_st_total_number_of_test_suites1(unused)                \
    unused nbpParamStatistics->totalNumberOfTestSuites
#define INTERNAL_NBP_RS_st_total_number_of_test_suite_instances1(unused)       \
    unused nbpParamStatistics->totalNumberOfTestSuiteInstances
#define INTERNAL_NBP_RS_st_total_number_of_modules1(unused)                    \
    unused nbpParamStatistics->totalNumberOfModules
#define INTERNAL_NBP_RS_st_total_number_of_module_instances1(unused)           \
    unused nbpParamStatistics->totalNumberOfModuleInstances

#define INTERNAL_NBP_RS_st_number_of_test_cases1(state)                        \
    nbpParamStatistics                                                         \
        ->numberOfTestCases[internal_nbp_get_test_case_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_test_case_instances1(state)               \
    nbpParamStatistics->numberOfTestCaseInstances                              \
        [internal_nbp_get_test_case_instance_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_test_suites1(state)                       \
    nbpParamStatistics                                                         \
        ->numberOfTestSuites[internal_nbp_get_test_suite_state_position(       \
            state)]
#define INTERNAL_NBP_RS_st_number_of_test_suite_instances1(state)              \
    nbpParamStatistics->numberOfTestSuiteInstances                             \
        [internal_nbp_get_test_suite_instance_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_modules1(state)                           \
    nbpParamStatistics                                                         \
        ->numberOfModules[internal_nbp_get_module_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_module_instances1(state)                  \
    nbpParamStatistics->numberOfModuleInstances                                \
        [internal_nbp_get_module_instance_state_position(state)]

#define INTERNAL_NBP_RS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_RS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_RS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_RS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_RS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_RS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_RS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_RS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_RS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_RS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_RS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_RS_PARAM_tss_running tss_running
#define INTERNAL_NBP_RS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_RS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_RS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_RS_PARAM_tsis_ready   tsis_ready
#define INTERNAL_NBP_RS_PARAM_tsis_running tsis_running
#define INTERNAL_NBP_RS_PARAM_tsis_passed  tsis_passed
#define INTERNAL_NBP_RS_PARAM_tsis_failed  tsis_failed
#define INTERNAL_NBP_RS_PARAM_tsis_skipped tsis_skipped

#define INTERNAL_NBP_RS_PARAM_ms_ready   ms_ready
#define INTERNAL_NBP_RS_PARAM_ms_running ms_running
#define INTERNAL_NBP_RS_PARAM_ms_passed  ms_passed
#define INTERNAL_NBP_RS_PARAM_ms_failed  ms_failed
#define INTERNAL_NBP_RS_PARAM_ms_skipped ms_skipped

#define INTERNAL_NBP_RS_PARAM_mis_ready   mis_ready
#define INTERNAL_NBP_RS_PARAM_mis_running mis_running
#define INTERNAL_NBP_RS_PARAM_mis_passed  mis_passed
#define INTERNAL_NBP_RS_PARAM_mis_failed  mis_failed
#define INTERNAL_NBP_RS_PARAM_mis_skipped mis_skipped

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_SETUP(func)                                             \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_setup_function_t gInternalNbpTestSuiteSetupFunction##func = \
        {                                                                      \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_suite_setup_function_##func,              \
    };                                                                         \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_TEARDOWN(func)                                          \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_teardown_function_t                                         \
        gInternalNbpTestSuiteTeardownFunction##func = {                        \
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
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_function_t*                  \
            testSuiteFunction)                                                 \
    {                                                                          \
        if (testSuiteFunction->isConfigured == 1) {                            \
            return;                                                            \
        } else {                                                               \
            testSuiteFunction->isConfigured = 1;                               \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(F_##__VA_ARGS__)      \
    }                                                                          \
    void nbp_test_suite_function_##func(                                       \
        nbp_test_suite_t* nbpParamTestSuite,                                   \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        unsigned int nbpParamNumberOfRuns);                                    \
    nbp_test_suite_function_t gInternalNbpTestSuiteFunction##func = {          \
        .name             = #func,                                             \
        .functionName     = #func,                                             \
        .file             = NBP_SOURCE_FILE,                                   \
        .line             = NBP_SOURCE_LINE,                                   \
        .isConfigured     = 0,                                                 \
        .configFunction   = nbp_test_suite_config_function_##func,             \
        .function         = nbp_test_suite_function_##func,                    \
        .setupFunction    = NBP_NULLPTR,                                       \
        .teardownFunction = NBP_NULLPTR,                                       \
    };                                                                         \
    void nbp_test_suite_function_##func(                                       \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER unsigned int nbpParamNumberOfRuns)

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
#define NBP_INCLUDE_TEST_SUITE_SETUP_FUNCTION(func)                            \
    extern nbp_test_suite_setup_function_t                                     \
        gInternalNbpTestSuiteSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_SETUP_FUNCTION(func)                     \
    &gInternalNbpTestSuiteSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_TEARDOWN_FUNCTION(func)                         \
    extern nbp_test_suite_teardown_function_t                                  \
        gInternalNbpTestSuiteTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN_FUNCTION(func)                  \
    &gInternalNbpTestSuiteTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_FUNCTION(func)                                  \
    extern nbp_test_suite_function_t gInternalNbpTestSuiteFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_FUNCTION(func)                           \
    &gInternalNbpTestSuiteFunction##func

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
#define NBP_TEST_SUITE_GET_NAME(testSuite)                                     \
    NBP_TEST_SUITE_INSTANCE_GET_NAME(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_STATE(testSuite)                                    \
    (nbp_test_suite_state_e) NBP_ATOMIC_INT_LOAD(&(testSuite)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_DEPTH(testSuite)                                    \
    NBP_TEST_SUITE_INSTANCE_GET_DEPTH(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_MODULE(testSuite)                                   \
    NBP_TEST_SUITE_INSTANCE_GET_MODULE(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_STATISTICS(testSuite, type, ...)                    \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TSGS_,                                                    \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testSuite, INTERNAL_NBP_TSGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_INSTANCE(testSuite) testSuite->testSuiteInstance

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NAME(testSuiteInstance)                    \
    testSuiteInstance->testSuiteFunction->name

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_STATE(testSuiteInstance)                   \
    (nbp_test_suite_instance_state_e)                                          \
        NBP_ATOMIC_INT_LOAD(&(testSuiteInstance)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_DEPTH(testSuiteInstance)                   \
    testSuiteInstance->depth

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_MODULE(testSuiteInstance)                  \
    testSuiteInstance->module

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_STATISTICS(testSuiteInstance, type, ...)   \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TSIGS_,                                                   \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testSuiteInstance, INTERNAL_NBP_TSIGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(testSuiteInstance)          \
    testSuiteInstance->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TEST_SUITE(testSuiteInstance, runId)       \
    internal_nbp_get_test_suite_from_instance(testSuiteInstance, runId)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_TEST_SUITE(func, ...)                                  \
    NBP_INCLUDE_TEST_SUITE_FUNCTION(func);                                     \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(TSPIO_##__VA_ARGS__))  \
    (TSPIO_, TSPIO_##__VA_ARGS__);                                             \
    internal_nbp_instantiate_test_suite(                                       \
        NBP_GET_POINTER_TO_TEST_SUITE_FUNCTION(func),                          \
        nbpParamTsiParentModule,                                               \
        NBP_SOURCE_LINE,                                                       \
        nbpParamNumberOfRuns,                                                  \
        NBP_NULLPTR);                                                          \
    nbpParamNumberOfRuns = 1;

#define INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(...)                  \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GTSC##__VA_ARGS__))    \
    (GTSCF_, GTSC##__VA_ARGS__)

// This macro is generated when NBP_TEST_SUITE macro is used without parameters
#define INTERNAL_NBP_GTSCF_

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_NAME(newName)                        \
    testSuiteFunction->name = newName;

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(func)                          \
    NBP_INCLUDE_TEST_SUITE_SETUP_FUNCTION(func);                               \
    testSuiteFunction->setupFunction =                                         \
        NBP_GET_POINTER_TO_TEST_SUITE_SETUP_FUNCTION(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(func)                       \
    NBP_INCLUDE_TEST_SUITE_TEARDOWN_FUNCTION(func);                            \
    testSuiteFunction->teardownFunction =                                      \
        NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN_FUNCTION(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_FIXTURES(setupFunc, teardownFunc)    \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(setupFunc)                         \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(teardownFunc)

// This macro is generated when NBP_INSTANTIATE_MODULE macro is used without
// parameters
#define INTERNAL_NBP_TSPIO_

#define INTERNAL_NBP_TSPIO_NBP_NUMBER_OF_RUNS(num) nbpParamNumberOfRuns = num;

// Helpers for NBP_TEST_SUITE_GET_STATISTICS

#define INTERNAL_NBP_TSGS_PARAM_

#define INTERNAL_NBP_TSGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_TSGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_TSGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_TSGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_TSGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_TSGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_TSGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_TSGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_TSGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_TSGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_TSGS_st_total_number_of_test_cases1(ts, unused)           \
    unused ts->totalNumberOfTestCases
#define INTERNAL_NBP_TSGS_st_total_number_of_test_case_instances1(ts, unused)  \
    unused ts->totalNumberOfTestCaseInstances

#define INTERNAL_NBP_TSGS_st_number_of_test_cases1(ts, state)                  \
    internal_nbp_get_number_of_test_cases(ts->numberOfTestCases, state)
#define INTERNAL_NBP_TSGS_st_number_of_test_case_instances1(ts, state)         \
    internal_nbp_get_number_of_test_case_instances(                            \
        ts->numberOfTestCaseInstances,                                         \
        state)

// Helpers for NBP_TEST_SUITE_INSTANCE_GET_STATISTICS

#define INTERNAL_NBP_TSIGS_PARAM_

#define INTERNAL_NBP_TSIGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_TSIGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_TSIGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_TSIGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_TSIGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_TSIGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_TSIGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_TSIGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_TSIGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_TSIGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_TSIGS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_TSIGS_PARAM_tss_running tss_running
#define INTERNAL_NBP_TSIGS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_TSIGS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_TSIGS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_TSIGS_st_total_number_of_test_cases1(tsi, unused)         \
    unused tsi->totalNumberOfTestCases
#define INTERNAL_NBP_TSIGS_st_total_number_of_test_case_instances1(            \
    tsi,                                                                       \
    unused)                                                                    \
    unused tsi->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_TSIGS_st_total_number_of_test_suites1(tsi, unused)        \
    unused tsi->numberOfRuns

#define INTERNAL_NBP_TSIGS_st_number_of_test_cases1(tsi, state)                \
    internal_nbp_get_number_of_test_cases(tsi->numberOfTestCases, state)
#define INTERNAL_NBP_TSIGS_st_number_of_test_case_instances1(tsi, state)       \
    internal_nbp_get_number_of_test_case_instances(                            \
        tsi->numberOfTestCaseInstances,                                        \
        state)
#define INTERNAL_NBP_TSIGS_st_number_of_test_suites1(tsi, state)               \
    internal_nbp_get_number_of_test_suites(tsi->numberOfTestSuites, state)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_SETUP(func)                                              \
    void nbp_test_case_setup_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase);         \
    nbp_test_case_setup_function_t gInternalNbpTestCaseSetupFunction##func = { \
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
    nbp_test_case_teardown_function_t                                          \
        gInternalNbpTestCaseTeardownFunction##func = {                         \
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
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_function_t* testCaseFunction) \
    {                                                                          \
        if (testCaseFunction->isConfigured == 1) {                             \
            return;                                                            \
        } else {                                                               \
            testCaseFunction->isConfigured = 1;                                \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(F_##__VA_ARGS__)       \
    }                                                                          \
    void nbp_test_case_function_##func(nbp_test_case_t* nbpParamTestCase);     \
    nbp_test_case_function_t gInternalNbpTestCaseFunction##func = {            \
        .name             = #func,                                             \
        .functionName     = #func,                                             \
        .file             = NBP_SOURCE_FILE,                                   \
        .line             = NBP_SOURCE_LINE,                                   \
        .isConfigured     = 0,                                                 \
        .configFunction   = nbp_test_case_config_function_##func,              \
        .function         = nbp_test_case_function_##func,                     \
        .setupFunction    = NBP_NULLPTR,                                       \
        .teardownFunction = NBP_NULLPTR,                                       \
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
#define NBP_INCLUDE_TEST_CASE_SETUP_FUNCTION(func)                             \
    extern nbp_test_case_setup_function_t                                      \
        gInternalNbpTestCaseSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_SETUP_FUNCTION(func)                      \
    &gInternalNbpTestCaseSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_TEARDOWN_FUNCTION(func)                          \
    extern nbp_test_case_teardown_function_t                                   \
        gInternalNbpTestCaseTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN_FUNCTION(func)                   \
    &gInternalNbpTestCaseTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_FUNCTION(func)                                   \
    extern nbp_test_case_function_t gInternalNbpTestCaseFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_FUNCTION(func)                            \
    &gInternalNbpTestCaseFunction##func

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
#define NBP_TEST_CASE_GET_NAME(testCase)                                       \
    NBP_TEST_CASE_INSTANCE_GET_NAME(testCase->testCaseInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_STATE(testCase)                                      \
    (nbp_test_case_state_e) NBP_ATOMIC_INT_LOAD(&(testCase)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_DEPTH(testCase)                                      \
    NBP_TEST_CASE_INSTANCE_GET_DEPTH(testCase->testCaseInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_STATISTICS(testCase, type, ...)                      \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TCGS_,                                                    \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testCase, INTERNAL_NBP_TCGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_INSTANCE(testCase) testCase->testCaseInstance

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_NAME(testCaseInstance)                      \
    testCaseInstance->testCaseFunction->name

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_STATE(testCaseInstance)                     \
    (nbp_test_case_instance_state_e)                                           \
        NBP_ATOMIC_INT_LOAD(&(testCaseInstance)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_DEPTH(testCaseInstance)                     \
    testCaseInstance->depth

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_STATISTICS(testCaseInstance, type, ...)     \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TCIGS_,                                                   \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testCaseInstance, INTERNAL_NBP_TCIGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance)            \
    testCaseInstance->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_TEST_CASE(testCaseInstance, runId)          \
    internal_nbp_get_test_case_from_instance(testCaseInstance, runId)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_TEST_CASE(func, ...)                                   \
    NBP_INCLUDE_TEST_CASE_FUNCTION(func);                                      \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(TCPIO_##__VA_ARGS__))  \
    (TCPIO_, TCPIO_##__VA_ARGS__);                                             \
    internal_nbp_instantiate_test_case(                                        \
        NBP_GET_POINTER_TO_TEST_CASE_FUNCTION(func),                           \
        nbpParamTciParentModule,                                               \
        nbpParamTciParentTestSuite,                                            \
        NBP_SOURCE_LINE,                                                       \
        nbpParamNumberOfRuns,                                                  \
        NBP_NULLPTR);                                                          \
    nbpParamNumberOfRuns = 1;

#define INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(...)                   \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GTCC##__VA_ARGS__))    \
    (GTCCF_, GTCC##__VA_ARGS__)

// This macro is generated when NBP_TEST_CASE macro is used without
// parameters
#define INTERNAL_NBP_GTCCF_

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_NAME(newName)                         \
    testCaseFunction->name = newName;

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(func)                           \
    NBP_INCLUDE_TEST_CASE_SETUP_FUNCTION(func);                                \
    testCaseFunction->setupFunction =                                          \
        NBP_GET_POINTER_TO_TEST_CASE_SETUP_FUNCTION(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(func)                        \
    NBP_INCLUDE_TEST_CASE_TEARDOWN_FUNCTION(func);                             \
    testCaseFunction->teardownFunction =                                       \
        NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN_FUNCTION(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_FIXTURES(setupFunc, teardownFunc)     \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(setupFunc)                          \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(teardownFunc)

// This macro is generated when NBP_INSTANTIATE_TEST_CASE macro is used
// without parameters
#define INTERNAL_NBP_TCPIO_

#define INTERNAL_NBP_TCPIO_NBP_NUMBER_OF_RUNS(num) nbpParamNumberOfRuns = num;

// Helpers for NBP_TEST_CASE_GET_STATISTICS

#define INTERNAL_NBP_TCGS_PARAM_

// Helpers for NBP_TEST_CASE_INSTANCE_GET_STATISTICS

#define INTERNAL_NBP_TCIGS_PARAM_

#define INTERNAL_NBP_TCIGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_TCIGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_TCIGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_TCIGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_TCIGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_TCIGS_st_total_number_of_test_cases1(tci, unused)         \
    unused tci->numberOfRuns

#define INTERNAL_NBP_TCIGS_st_number_of_test_cases1(tci, state)                \
    internal_nbp_get_number_of_test_cases(tci->numberOfTestCases, state)

#ifdef NBP_LIBRARY_MAIN

/**
 * TODO: add docs
 */
#define NBP_MAIN_MODULE(func, ...)                                             \
    void nbp_module_config_function_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_function_t* moduleFunction)      \
    {                                                                          \
        if (moduleFunction->isConfigured == 1) {                               \
            return;                                                            \
        } else {                                                               \
            moduleFunction->isConfigured = 1;                                  \
        }                                                                      \
        INTERNAL_NBP_GENERATE_MAIN_MODULE_CONFIG_FUNCTION(F_##__VA_ARGS__)     \
    }                                                                          \
    void nbp_module_function_##func(                                           \
        nbp_module_t* nbpParamModule,                                          \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        nbp_module_t* nbpParamTsiParentModule,                                 \
        nbp_module_t* nbpParamMiParentModule,                                  \
        unsigned int nbpParamNumberOfRuns);                                    \
    nbp_module_function_t gInternalNbpModuleFunction##func = {                 \
        .name             = #func,                                             \
        .functionName     = #func,                                             \
        .file             = NBP_SOURCE_FILE,                                   \
        .line             = NBP_SOURCE_LINE,                                   \
        .isConfigured     = 0,                                                 \
        .configFunction   = nbp_module_config_function_##func,                 \
        .function         = nbp_module_function_##func,                        \
        .setupFunction    = NBP_NULLPTR,                                       \
        .teardownFunction = NBP_NULLPTR,                                       \
    };                                                                         \
    nbp_module_function_t* gInternalNbpMainModuleFunction =                    \
        &gInternalNbpModuleFunction##func;                                     \
    void nbp_module_function_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTsiParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamMiParentModule,       \
        NBP_MAYBE_UNUSED_PARAMETER unsigned int nbpParamNumberOfRuns)

#define INTERNAL_NBP_GENERATE_MAIN_MODULE_CONFIG_FUNCTION(...)                 \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GMMC##__VA_ARGS__))    \
    (GMMCF_, GMMC##__VA_ARGS__)

// This macro is generated when NBP_MAIN_MODULE macro is used without parameters
#define INTERNAL_NBP_GMMCF_

#define INTERNAL_NBP_GMMCF_NBP_MODULE_NAME(newName)                            \
    moduleFunction->name = newName;

#define INTERNAL_NBP_GMMCF_NBP_MODULE_SETUP(func)                              \
    NBP_INCLUDE_MODULE_SETUP_FUNCTION(func);                                   \
    moduleFunction->setupFunction =                                            \
        NBP_GET_POINTER_TO_MODULE_SETUP_FUNCTION(func);

#define INTERNAL_NBP_GMMCF_NBP_MODULE_TEARDOWN(func)                           \
    NBP_INCLUDE_MODULE_TEARDOWN_FUNCTION(func);                                \
    moduleFunction->teardownFunction =                                         \
        NBP_GET_POINTER_TO_MODULE_TEARDOWN_FUNCTION(func);

#define INTERNAL_NBP_GMMCF_NBP_MODULE_FIXTURES(setupFunc, teardownFunc)        \
    INTERNAL_NBP_GMMCF_NBP_MODULE_SETUP(setupFunc)                             \
    INTERNAL_NBP_GMMCF_NBP_MODULE_TEARDOWN(teardownFunc)

#endif // end if NBP_LIBRARY_MAIN

#ifdef NBP_LIBRARY_MAIN

extern nbp_module_function_t* gInternalNbpMainModuleFunction;

nbp_module_instance_t* gInternalNbpMainModuleInstance = NBP_NULLPTR;

INTERNAL_NBP_INCLUDE_REPORTER(nbpConsoleReporter);

nbp_reporter_interface_t* gInternalNbpDefaultReporterInterfaces[] = {
    INTERNAL_NBP_GET_POINTER_TO_REPORTER(nbpConsoleReporter)};

nbp_reporter_interface_t** gInternalNbpReporterInterfaces = NBP_NULLPTR;
unsigned int gInternalNbpReporterInterfacesSize           = 0;

unsigned int gInternalNbpNumberOfTestCases            = 0;
NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRanTestCases = NBP_ATOMIC_UINT_INIT(0);

int gInternalNbpRunnerRunEnabled = 0;

#ifdef NBP_BASIC_RUNNER
INTERNAL_NBP_INCLUDE_RUNNER(nbpBasicRunner);
nbp_runner_interface_t* gInternalNbpRunnerInterface =
    INTERNAL_NBP_GET_POINTER_TO_RUNNER(nbpBasicRunner);
#endif // end if NBP_BASIC_RUNNER

#ifdef NBP_MT_RUNNER
nbp_runner_interface_t* gInternalNbpRunnerInterface = NBP_NULLPTR;
#endif // end if NBP_MT_RUNNER

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
    internal_nbp_notify_reporter_init();
    internal_nbp_notify_runner_init();

    if (gInternalNbpRunnerInterface->instantiateTestCaseCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_runner_interface);
        NBP_EXIT(ec_invalid_runner_interface);
        return ec_invalid_runner_interface;
    }
    if (gInternalNbpRunnerInterface->runCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_runner_interface);
        NBP_EXIT(ec_invalid_runner_interface);
        return ec_invalid_runner_interface;
    }

    gInternalNbpMainModuleInstance = internal_nbp_instantiate_module(
        gInternalNbpMainModuleFunction,
        NBP_NULLPTR,
        0,
        1,
        NBP_NULLPTR);

    if (gInternalNbpMainModuleInstance == NBP_NULLPTR) {
        return ec_out_of_memory;
    }

    // TODO: send some stats to reporters about instances

    internal_nbp_notify_reporter_before_run();

    internal_nbp_notify_runner_run();

    internal_nbp_notify_reporter_after_run();

    unsigned int numberOfRunTestsCases =
        NBP_ATOMIC_UINT_LOAD(&gInternalNbpNumberOfRanTestCases);
    if (numberOfRunTestsCases != gInternalNbpNumberOfTestCases) {
        NBP_REPORT_ERROR(ec_not_all_tests_were_run);
        NBP_EXIT(ec_not_all_tests_were_run);
        return ec_not_all_tests_were_run;
    }

    // TODO: send some stats to reporters about asserts, test cases etc

    internal_nbp_notify_runner_uninit();
    internal_nbp_notify_reporter_uninit();

    // TODO: return error if main module state is not passed

    // TODO: free data!!!

    return (int) ec_success;
}

static int internal_nbp_command_version()
{
    internal_nbp_notify_reporter_init();
    internal_nbp_notify_reporter_handle_version_command();
    internal_nbp_notify_reporter_uninit();

    return (int) ec_success;
}

int main(int argc, const char** argv)
{
    if (argc < 1) {
        return (int) ec_invalid_command_line;
    }

    gInternalNbpReporterInterfaces     = gInternalNbpDefaultReporterInterfaces;
    gInternalNbpReporterInterfacesSize = 1;

    if (argc == 1) {
        return internal_nbp_command_run_all();
    }

    if (internal_nbp_string_equal(argv[1], "--version") == 1) {
        return internal_nbp_command_version();
    }

    return (int) ec_invalid_command_line;
}

extern nbp_module_function_t* gInternalNbpMainModuleFunction;

static void internal_nbp_increment_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_module_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_module_state_position(state);
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
    unsigned int pos = internal_nbp_get_module_instance_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_module_instance_state_position(state);
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

unsigned int internal_nbp_get_module_state_position(nbp_module_state_e state)
{
    if ((unsigned int) state < (unsigned int) ms_ready
        || (unsigned int) state > (unsigned int) ms_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid module state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) ms_ready);
}

unsigned int internal_nbp_get_module_instance_state_position(
    nbp_module_instance_state_e state)
{
    if ((unsigned int) state < (unsigned int) mis_ready
        || (unsigned int) state > (unsigned int) mis_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid module instance state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) mis_ready);
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
    unsigned int pos = internal_nbp_get_module_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state)
{
    unsigned int pos = internal_nbp_get_module_instance_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_module_t* internal_nbp_get_module_from_instance(
    nbp_module_instance_t* moduleInstance,
    unsigned int runId)
{
    if (runId >= moduleInstance->numberOfRuns) {
        return NBP_NULLPTR;
    }
    return &moduleInstance->runs[runId];
}

nbp_module_instance_t* internal_nbp_instantiate_module(
    nbp_module_function_t* moduleFunction,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    moduleFunction->configFunction(moduleFunction);

    if (numberOfRuns == 0) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_number_of_runs,
            "the number of runs must be greater than 0");
        NBP_EXIT(ec_invalid_number_of_runs);
        return NBP_NULLPTR;
    }

    if (parentModule == NBP_NULLPTR
        && moduleFunction != gInternalNbpMainModuleFunction) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "module instance has no parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    if (parentModule != NBP_NULLPTR) {
        if (parentModule->moduleInstance->moduleFunction == moduleFunction) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_invalid_parent,
                "a module cannot self instantiate");
            NBP_EXIT(ec_invalid_parent);
            return NBP_NULLPTR;
        }

        nbp_module_t* p = parentModule->moduleInstance->parent;
        while (p != NBP_NULLPTR) {
            if (p->moduleInstance->moduleFunction == moduleFunction) {
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
        runs[i].firstTestCaseInstance           = NBP_NULLPTR;
        runs[i].lastTestCaseInstance            = NBP_NULLPTR;
        runs[i].firstTestSuiteInstance          = NBP_NULLPTR;
        runs[i].lastTestSuiteInstance           = NBP_NULLPTR;
        runs[i].firstModuleInstance             = NBP_NULLPTR;
        runs[i].lastModuleInstance              = NBP_NULLPTR;
        runs[i].numberOfTasks                   = 0;
        runs[i].totalNumberOfTestCases          = 0;
        runs[i].totalNumberOfTestCaseInstances  = 0;
        runs[i].totalNumberOfTestSuites         = 0;
        runs[i].totalNumberOfTestSuiteInstances = 0;
        runs[i].totalNumberOfModules            = 0;
        runs[i].totalNumberOfModuleInstances    = 0;

        NBP_ATOMIC_INT_STORE(&runs[i].state, (int) ms_ready);
        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);
        NBP_ATOMIC_UINT_STORE(&runs[i].numberOfCompletedTasks, 0U);

        if (NBP_SYNC_EVENT_INIT(&runs[i].runEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init runEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        if (NBP_SYNC_EVENT_INIT(&runs[i].setupEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init setupEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCases,
            NBP_NUMBER_OF_TEST_CASE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCaseInstances,
            NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestSuites,
            NBP_NUMBER_OF_TEST_SUITE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestSuiteInstances,
            NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfModules,
            NBP_NUMBER_OF_MODULE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfModuleInstances,
            NBP_NUMBER_OF_MODULE_INSTANCE_STATES,
            0U);
    }

    moduleInstance->moduleFunction    = moduleFunction;
    moduleInstance->parent            = parentModule;
    moduleInstance->depth             = 0;
    moduleInstance->instantiationLine = instantiationLine;
    moduleInstance->setupFunction     = moduleFunction->setupFunction;
    moduleInstance->teardownFunction  = moduleFunction->teardownFunction;
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

    NBP_ATOMIC_INT_STORE(&moduleInstance->state, (int) mis_ready);
    NBP_ATOMIC_INT_STORE(&moduleInstance->isSkipped, (int) sf_is_not_set);
    NBP_ATOMIC_UINT_STORE(&moduleInstance->numberOfCompletedRuns, 0U);

    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestCaseInstances,
        NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestSuites,
        NBP_NUMBER_OF_TEST_SUITE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestSuiteInstances,
        NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfModules,
        NBP_NUMBER_OF_MODULE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfModuleInstances,
        NBP_NUMBER_OF_MODULE_INSTANCE_STATES,
        0U);

    if (parentModule != NBP_NULLPTR) {
        moduleInstance->depth = parentModule->moduleInstance->depth + 1;

        parentModule->numberOfTasks += 1;

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

    internal_nbp_notify_reporter_instantiate_module_started(moduleInstance);

    internal_nbp_notify_runner_instantiate_module_started(
        moduleInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        moduleInstance->moduleFunction->function(
            &moduleInstance->runs[i],
            NBP_NULLPTR,
            &moduleInstance->runs[i],
            &moduleInstance->runs[i],
            &moduleInstance->runs[i],
            1);

        if (moduleInstance->runs[i].totalNumberOfTestCaseInstances == 0) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_no_test_case_instantiated,
                "module has no test case");
            NBP_EXIT(ec_no_test_case_instantiated);
        }
    }

    internal_nbp_notify_runner_instantiate_module_completed(moduleInstance);

    internal_nbp_notify_reporter_instantiate_module_completed(moduleInstance);

    return moduleInstance;
}

extern nbp_module_instance_t* gInternalNbpMainModuleInstance;
extern nbp_reporter_interface_t** gInternalNbpReporterInterfaces;
extern unsigned int gInternalNbpReporterInterfacesSize;

#define INTERNAL_NBP_CALLBACK_IS_SET(cbk)                                      \
    gInternalNbpReporterInterfaces[i]->cbk != NBP_NULLPTR

static void internal_nbp_initialize_reporter_statistics(
    nbp_reporter_statistics_t* statistics)
{
    statistics->totalNumberOfTestCases =
        gInternalNbpMainModuleInstance->totalNumberOfTestCases;
    statistics->totalNumberOfTestCaseInstances =
        gInternalNbpMainModuleInstance->totalNumberOfTestCaseInstances;
    statistics->totalNumberOfTestSuites =
        gInternalNbpMainModuleInstance->totalNumberOfTestSuites;
    statistics->totalNumberOfTestSuiteInstances =
        gInternalNbpMainModuleInstance->totalNumberOfTestSuiteInstances;
    statistics->totalNumberOfModules =
        gInternalNbpMainModuleInstance->totalNumberOfModules;
    statistics->totalNumberOfModuleInstances =
        gInternalNbpMainModuleInstance->totalNumberOfModuleInstances;

    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestCases,
        statistics->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestCaseInstances,
        statistics->numberOfTestCaseInstances,
        NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestSuites,
        statistics->numberOfTestSuites,
        NBP_NUMBER_OF_TEST_SUITE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestSuiteInstances,
        statistics->numberOfTestSuiteInstances,
        NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfModules,
        statistics->numberOfModules,
        NBP_NUMBER_OF_MODULE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfModuleInstances,
        statistics->numberOfModuleInstances,
        NBP_NUMBER_OF_MODULE_INSTANCE_STATES);

    statistics->totalNumberOfModuleInstances += 1;
    statistics->totalNumberOfModules +=
        gInternalNbpMainModuleInstance->numberOfRuns;

    unsigned int pos = internal_nbp_get_module_instance_state_position(
        NBP_MODULE_INSTANCE_GET_STATE(gInternalNbpMainModuleInstance));
    statistics->numberOfModuleInstances[pos] += 1;
}

void internal_nbp_notify_reporter_init()
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        gInternalNbpReporterInterfaces[i]->configFunction(
            gInternalNbpReporterInterfaces[i]);
        if (INTERNAL_NBP_CALLBACK_IS_SET(initCbk)) {
            gInternalNbpReporterInterfaces[i]->initCbk();
        }
        gInternalNbpReporterInterfaces[i]->isInitialized = 1;
    }
}

void internal_nbp_notify_reporter_uninit()
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(uninitCbk)) {
            gInternalNbpReporterInterfaces[i]->uninitCbk();
        }
        gInternalNbpReporterInterfaces[i]->isInitialized = 0;
    }
}

void internal_nbp_notify_reporter_handle_version_command()
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(handleVersionCommandCbk)) {
            gInternalNbpReporterInterfaces[i]->handleVersionCommandCbk();
        }
    }
}

void internal_nbp_notify_reporter_on_error(
    nbp_error_code_e errorCode,
    int line,
    const char* file)
{
    nbp_error_t error;

    error.errorCode   = errorCode;
    error.line        = line;
    error.file        = file;
    error.contextType = ect_empty;

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpReporterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_reporter_on_error_string_context(
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

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpReporterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_reporter_on_error_custom_context(
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

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpReporterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_reporter_on_exit(nbp_error_code_e errorCode)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(exitCbk)) {
            gInternalNbpReporterInterfaces[i]->exitCbk(errorCode);
        }
    }
}

void internal_nbp_notify_reporter_before_run()
{
    nbp_reporter_statistics_t statistics;

    internal_nbp_initialize_reporter_statistics(&statistics);

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(beforeRunCbk)) {
            gInternalNbpReporterInterfaces[i]->beforeRunCbk(&statistics);
        }
    }
}

void internal_nbp_notify_reporter_after_run()
{
    nbp_reporter_statistics_t statistics;

    internal_nbp_initialize_reporter_statistics(&statistics);

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(afterRunCbk)) {
            gInternalNbpReporterInterfaces[i]->afterRunCbk(&statistics);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestCaseCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateTestCaseCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateTestSuiteStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateTestSuiteCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_module_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateModuleStartedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateModuleCompletedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_reporter_test_case_started(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseStartedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_case_completed(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseCompletedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_case_instance_started(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseInstanceStartedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_case_instance_completed(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseInstanceCompletedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_started(
    nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteStartedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_completed(
    nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteCompletedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_instance_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteInstanceStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_instance_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteInstanceCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_module_started(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleStartedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_reporter_module_completed(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleCompletedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_reporter_module_instance_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleInstanceStartedCbk(
                moduleInstance);
        }
    }
}

void internal_nbp_notify_reporter_module_instance_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleInstanceCompletedCbk(
                moduleInstance);
        }
    }
}

#undef INTERNAL_NBP_CALLBACK_IS_SET

extern int gInternalNbpRunnerRunEnabled;

extern NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRanTestCases;

static int internal_nbp_runner_run_module(nbp_module_t* module)
{
    if (module == NBP_NULLPTR) {
        return (int) ms_running;
    }

    int oldModuleInstanceState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &module->moduleInstance->state,
        mis_ready,
        mis_running);
    if (oldModuleInstanceState != mis_ready
        && oldModuleInstanceState != mis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "module instance is not ready or running");
        NBP_EXIT(ec_unexpected_state);
        return ms_failed;
    }

    int oldModuleState =
        NBP_ATOMIC_INT_COMPARE_AND_SWAP(&module->state, ms_ready, ms_running);
    if (oldModuleState == ms_running) {
        nbp_error_code_e err = NBP_SYNC_EVENT_WAIT(module->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "wait for module runEvent failed");
            NBP_EXIT(ec_sync_error);
            return ms_failed;
        }

        return ms_running;
    }

    if (oldModuleState == ms_ready) {
        int parentModuleState =
            internal_nbp_runner_run_module(module->moduleInstance->parent);
        if (parentModuleState != ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "parent module is not running");
            NBP_EXIT(ec_unexpected_state);
            return ms_failed;
        }

        if (oldModuleInstanceState == mis_ready) {
            internal_nbp_module_instance_update_state_stats(
                module->moduleInstance,
                mis_ready,
                mis_running);

            internal_nbp_notify_reporter_module_instance_started(
                module->moduleInstance);
        }

        internal_nbp_module_update_state_stats(module, ms_ready, ms_running);

        internal_nbp_notify_reporter_module_started(module);

        nbp_error_code_e err = NBP_SYNC_EVENT_NOTIFY(module->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to notify module runEvent");
            NBP_EXIT(ec_sync_error);
            return ms_failed;
        }

        return ms_running;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_state,
        "module is not ready or running");
    NBP_EXIT(ec_unexpected_state);
    return ms_failed;
}

static int internal_nbp_runner_run_test_suite(nbp_test_suite_t* testSuite)
{
    int oldTestSuiteInstanceState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->testSuiteInstance->state,
        tsis_ready,
        tsis_running);
    if (oldTestSuiteInstanceState != tsis_ready
        && oldTestSuiteInstanceState != tsis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test suite instance is not ready or running");
        NBP_EXIT(ec_unexpected_state);
        return tss_failed;
    }

    int oldTestSuiteState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->state,
        tss_ready,
        tss_running);

    if (oldTestSuiteState == tss_running) {
        nbp_error_code_e err = NBP_SYNC_EVENT_WAIT(testSuite->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "wait for test suite runEvent failed");
            NBP_EXIT(ec_sync_error);
            return tss_failed;
        }

        return tss_running;
    }

    if (oldTestSuiteState == tss_ready) {
        int moduleState = internal_nbp_runner_run_module(
            testSuite->testSuiteInstance->module);
        if (moduleState != ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "parent module is not running");
            NBP_EXIT(ec_unexpected_state);
            return tss_failed;
        }

        if (oldTestSuiteInstanceState == tsis_ready) {
            internal_nbp_test_suite_instance_update_state_stats(
                testSuite->testSuiteInstance,
                tsis_ready,
                tsis_running);

            internal_nbp_notify_reporter_test_suite_instance_started(
                testSuite->testSuiteInstance);
        }

        internal_nbp_test_suite_update_state_stats(
            testSuite,
            tss_ready,
            tss_running);

        internal_nbp_notify_reporter_test_suite_started(testSuite);

        nbp_error_code_e err = NBP_SYNC_EVENT_NOTIFY(testSuite->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to notify test suite runEvent");
            NBP_EXIT(ec_sync_error);
            return tss_failed;
        }

        return tss_running;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_state,
        "test suite is not ready or running");
    NBP_EXIT(ec_unexpected_state);
    return tss_failed;
}

static int internal_nbp_runner_setup_module(nbp_module_t* module)
{
    if (module == NBP_NULLPTR) {
        return (int) sf_is_processed;
    }

    nbp_error_code_e err;

    int oldModuleInstanceValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &module->moduleInstance->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldModuleInstanceValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    int oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &module->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    if (oldValue == (int) sf_is_processed) {
        err = NBP_SYNC_EVENT_WAIT(module->setupEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to wait for module setupEvent");
            NBP_EXIT(ec_sync_error);
            return (int) sf_is_not_set;
        }

        oldValue = NBP_ATOMIC_INT_LOAD(&module->isSkipped);
        if (oldValue == (int) sf_is_set || oldValue == (int) sf_is_processed) {
            return oldValue;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected module isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    if (oldValue == (int) sf_is_not_set) {
        int parentValue =
            internal_nbp_runner_setup_module(module->moduleInstance->parent);

        if (parentValue == (int) sf_is_processed) {
            if (module->moduleInstance->setupFunction != NBP_NULLPTR) {
                module->moduleInstance->setupFunction->function(module);
            }

            err = NBP_SYNC_EVENT_NOTIFY(module->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify module setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_processed;
        }

        if (parentValue == (int) sf_is_set) {
            oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
                &module->isSkipped,
                sf_is_processed,
                sf_is_set);

            if (oldValue != (int) sf_is_processed) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_unexpected_internal_data,
                    "unexpected module isSkipped flag value");
                NBP_EXIT(ec_unexpected_internal_data);
            }

            err = NBP_SYNC_EVENT_NOTIFY(module->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify module setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_set;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected module isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_internal_data,
        "unexpected module isSkipped flag value");
    NBP_EXIT(ec_unexpected_internal_data);
    return (int) sf_is_not_set;
}

static int internal_nbp_runner_compute_module_instance_state(
    nbp_module_instance_t* moduleInstance)
{
    unsigned int numberOfPassedModules  = 0;
    unsigned int numberOfSkippedModules = 0;

    for (unsigned int i = 0; i < moduleInstance->numberOfRuns; i++) {
        nbp_module_state_e state =
            NBP_MODULE_GET_STATE(&moduleInstance->runs[i]);
        if (state == ms_passed) {
            numberOfPassedModules++;
        } else if (state == ms_skipped) {
            numberOfSkippedModules++;
        }
    }

    if (numberOfPassedModules == moduleInstance->numberOfRuns) {
        return mis_passed;
    }

    if (numberOfSkippedModules == moduleInstance->numberOfRuns) {
        return mis_skipped;
    }

    return mis_failed;
}

static int internal_nbp_runner_complete_module_instance(
    nbp_module_instance_t* moduleInstance)
{
    unsigned int num = NBP_ATOMIC_UINT_ADD_AND_FETCH(
        &moduleInstance->numberOfCompletedRuns,
        1U);
    if (num != moduleInstance->numberOfRuns) {
        return 0;
    }

    int newState =
        internal_nbp_runner_compute_module_instance_state(moduleInstance);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &moduleInstance->state,
        mis_running,
        newState);

    if (oldState != mis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "module instance is not running");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    internal_nbp_module_instance_update_state_stats(
        moduleInstance,
        mis_running,
        (nbp_module_instance_state_e) newState);

    internal_nbp_notify_reporter_module_instance_completed(moduleInstance);

    return 1;
}

static int internal_nbp_runner_compute_module_state(nbp_module_t* module)
{
    unsigned int passedTasks  = 0;
    unsigned int skippedTasks = 0;

    nbp_test_case_instance_t* testCaseInstance = module->firstTestCaseInstance;
    nbp_test_suite_instance_t* testSuiteInstance =
        module->firstTestSuiteInstance;
    nbp_module_instance_t* moduleInstance = module->firstModuleInstance;

    while (testCaseInstance != NBP_NULLPTR) {
        nbp_test_case_instance_state_e state =
            NBP_TEST_CASE_INSTANCE_GET_STATE(testCaseInstance);

        if (state == tcis_passed) {
            passedTasks++;
        } else if (state == tcis_skipped) {
            skippedTasks++;
        }

        testCaseInstance = testCaseInstance->next;
    }

    while (testSuiteInstance != NBP_NULLPTR) {
        nbp_test_suite_instance_state_e state =
            NBP_TEST_SUITE_INSTANCE_GET_STATE(testSuiteInstance);

        if (state == tsis_passed) {
            passedTasks++;
        } else if (state == tsis_skipped) {
            skippedTasks++;
        }

        testSuiteInstance = testSuiteInstance->next;
    }

    while (moduleInstance != NBP_NULLPTR) {
        nbp_module_instance_state_e state =
            NBP_MODULE_INSTANCE_GET_STATE(moduleInstance);

        if (state == mis_passed) {
            passedTasks++;
        } else if (state == mis_skipped) {
            skippedTasks++;
        }

        moduleInstance = moduleInstance->next;
    }

    if (passedTasks == module->numberOfTasks) {
        return ms_passed;
    }

    if (skippedTasks == module->numberOfTasks) {
        return ms_skipped;
    }

    return ms_failed;
}

static void internal_nbp_runner_teardown_module(nbp_module_t* module)
{
    while (module != NBP_NULLPTR) {
        unsigned int num =
            NBP_ATOMIC_UINT_ADD_AND_FETCH(&module->numberOfCompletedTasks, 1U);
        if (num != module->numberOfTasks) {
            return;
        }

        int isSkipped = NBP_ATOMIC_INT_LOAD(&module->isSkipped);
        if (isSkipped == (int) sf_is_processed) {
            if (module->moduleInstance->teardownFunction != NBP_NULLPTR) {
                module->moduleInstance->teardownFunction->function(module);
            }
        }

        int newState = internal_nbp_runner_compute_module_state(module);

        int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
            &module->state,
            ms_running,
            newState);

        if (oldState != ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "module is not running");
            NBP_EXIT(ec_unexpected_state);
            return;
        }

        internal_nbp_module_update_state_stats(
            module,
            ms_running,
            (nbp_module_state_e) newState);

        internal_nbp_notify_reporter_module_completed(module);

        int isCompletedInstance = internal_nbp_runner_complete_module_instance(
            module->moduleInstance);
        if (isCompletedInstance == 0) {
            break;
        }

        module = module->moduleInstance->parent;
    }
}

static int internal_nbp_runner_setup_test_suite(nbp_test_suite_t* testSuite)
{
    nbp_error_code_e err;

    int oldTsiValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->testSuiteInstance->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldTsiValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    int oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    if (oldValue == (int) sf_is_processed) {
        err = NBP_SYNC_EVENT_WAIT(testSuite->setupEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to wait for test suite setupEvent");
            NBP_EXIT(ec_sync_error);
            return (int) sf_is_not_set;
        }

        oldValue = NBP_ATOMIC_INT_LOAD(&testSuite->isSkipped);
        if (oldValue == (int) sf_is_set || oldValue == (int) sf_is_processed) {
            return oldValue;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected test suite isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    if (oldValue == (int) sf_is_not_set) {
        int parentValue = internal_nbp_runner_setup_module(
            testSuite->testSuiteInstance->module);

        if (parentValue == (int) sf_is_processed) {
            if (testSuite->testSuiteInstance->setupFunction != NBP_NULLPTR) {
                testSuite->testSuiteInstance->setupFunction->function(
                    testSuite);
            }

            err = NBP_SYNC_EVENT_NOTIFY(testSuite->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify test suite setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_processed;
        }

        if (parentValue == (int) sf_is_set) {
            oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
                &testSuite->isSkipped,
                sf_is_processed,
                sf_is_set);

            if (oldValue != (int) sf_is_processed) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_unexpected_internal_data,
                    "unexpected test suite isSkipped flag value");
                NBP_EXIT(ec_unexpected_internal_data);
            }

            err = NBP_SYNC_EVENT_NOTIFY(testSuite->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify test suite setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_set;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected test suite isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_internal_data,
        "unexpected test suite isSkipped flag value");
    NBP_EXIT(ec_unexpected_internal_data);
    return (int) sf_is_not_set;
}

static int internal_nbp_runner_complete_test_suite_instance(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    unsigned int num = NBP_ATOMIC_UINT_ADD_AND_FETCH(
        &testSuiteInstance->numberOfCompletedRuns,
        1U);
    if (num != testSuiteInstance->numberOfRuns) {
        return 0;
    }

    int newState = tsis_passed;

    do {
        num = internal_nbp_get_number_of_test_suites(
            testSuiteInstance->numberOfTestSuites,
            tss_failed);
        if (num > 0) {
            newState = tsis_failed;
            break;
        }

        num = internal_nbp_get_number_of_test_suites(
            testSuiteInstance->numberOfTestSuites,
            tss_skipped);

        if (num == testSuiteInstance->numberOfRuns) {
            newState = tsis_skipped;
            break;
        }

        if (num > 0) {
            newState = tsis_failed;
            break;
        }
    } while (0);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuiteInstance->state,
        tsis_running,
        newState);

    if (oldState != tsis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test suite instance is not running");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    internal_nbp_test_suite_instance_update_state_stats(
        testSuiteInstance,
        tsis_running,
        (nbp_test_suite_instance_state_e) newState);

    internal_nbp_notify_reporter_test_suite_instance_completed(
        testSuiteInstance);

    return 1;
}

static void internal_nbp_runner_teardown_test_suite(nbp_test_suite_t* testSuite)
{
    unsigned int num =
        NBP_ATOMIC_UINT_ADD_AND_FETCH(&testSuite->numberOfCompletedTasks, 1U);
    if (num != testSuite->totalNumberOfTestCaseInstances) {
        return;
    }

    int isSkipped = NBP_ATOMIC_INT_LOAD(&testSuite->isSkipped);
    if (isSkipped == (int) sf_is_processed) {
        if (testSuite->testSuiteInstance->teardownFunction != NBP_NULLPTR) {
            testSuite->testSuiteInstance->teardownFunction->function(testSuite);
        }
    }

    int newState = tss_passed;

    do {
        num = internal_nbp_get_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            tcis_failed);
        if (num > 0) {
            newState = tss_failed;
            break;
        }

        num = internal_nbp_get_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            tcis_skipped);

        if (num == testSuite->totalNumberOfTestCaseInstances) {
            newState = tss_skipped;
            break;
        }

        if (num > 0) {
            newState = tss_failed;
            break;
        }
    } while (0);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->state,
        tss_running,
        newState);

    if (oldState != tss_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test suite is not running");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    internal_nbp_test_suite_update_state_stats(
        testSuite,
        tss_running,
        (nbp_test_suite_state_e) newState);

    internal_nbp_notify_reporter_test_suite_completed(testSuite);

    int isCompletedInstance = internal_nbp_runner_complete_test_suite_instance(
        testSuite->testSuiteInstance);
    if (isCompletedInstance == 1) {
        internal_nbp_runner_teardown_module(
            testSuite->testSuiteInstance->module);
    }
}

static int internal_nbp_runner_complete_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance)
{
    unsigned int num = NBP_ATOMIC_UINT_ADD_AND_FETCH(
        &testCaseInstance->numberOfCompletedRuns,
        1U);
    if (num != testCaseInstance->numberOfRuns) {
        return 0;
    }

    int newState = tcis_passed;

    do {
        num = internal_nbp_get_number_of_test_cases(
            testCaseInstance->numberOfTestCases,
            tcs_failed);
        if (num > 0) {
            newState = tcis_failed;
            break;
        }

        num = internal_nbp_get_number_of_test_cases(
            testCaseInstance->numberOfTestCases,
            tcs_skipped);

        if (num == testCaseInstance->numberOfRuns) {
            newState = tcis_skipped;
            break;
        }

        if (num > 0) {
            newState = tcis_failed;
            break;
        }
    } while (0);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCaseInstance->state,
        tcis_running,
        newState);

    if (oldState != tcis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case instance is not running");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    internal_nbp_test_case_instance_update_state_stats(
        testCaseInstance,
        tcis_running,
        (nbp_test_case_instance_state_e) newState);

    internal_nbp_notify_reporter_test_case_instance_completed(testCaseInstance);

    return 1;
}

static void internal_nbp_runner_run_skipped_test_case(nbp_test_case_t* testCase)
{
    ((void) testCase);
}

static void internal_nbp_runner_run_ready_test_case(nbp_test_case_t* testCase)
{
    internal_nbp_test_case_update_state_stats(testCase, tcs_ready, tcs_running);
    internal_nbp_notify_reporter_test_case_started(testCase);

    if (testCase->testCaseInstance->setupFunction != NBP_NULLPTR) {
        testCase->testCaseInstance->setupFunction->function(testCase);
    }

    testCase->testCaseInstance->testCaseFunction->function(testCase);

    if (testCase->testCaseInstance->teardownFunction != NBP_NULLPTR) {
        testCase->testCaseInstance->teardownFunction->function(testCase);
    }

    int newState = (int) tcs_passed;
    if (internal_nbp_is_failed_test_case(testCase) == 1) {
        newState = (int) tcs_failed;
    }

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->state,
        tcs_running,
        newState);
    if (oldState != (int) tcs_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case is not running");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    internal_nbp_test_case_update_state_stats(
        testCase,
        tcs_running,
        (nbp_test_case_state_e) newState);
    internal_nbp_notify_reporter_test_case_completed(testCase);
}

void internal_nbp_runner_run_test_case(nbp_test_case_t* testCase)
{
    if (gInternalNbpRunnerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_runner_run_is_disabled,
            "a test case can be run only from runner's run callback");
        NBP_EXIT(ec_runner_run_is_disabled);
        return;
    }

    int oldInstanceState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->testCaseInstance->state,
        tcis_ready,
        tcis_running);
    if (oldInstanceState != tcis_ready && oldInstanceState != tcis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case instance is not ready or running");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->state,
        (int) tcs_ready,
        (int) tcs_running);

    if (oldState != (int) tcs_ready) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case is not ready");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    if (testCase->testCaseInstance->module != NBP_NULLPTR) {
        int moduleState =
            internal_nbp_runner_run_module(testCase->testCaseInstance->module);
        if (moduleState != (int) ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "module is not running");
            NBP_EXIT(ec_unexpected_state);
            return;
        }
    } else if (testCase->testCaseInstance->testSuite != NBP_NULLPTR) {
        int testSuiteState = internal_nbp_runner_run_test_suite(
            testCase->testCaseInstance->testSuite);
        if (testSuiteState != (int) tss_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "test suite is not running");
            NBP_EXIT(ec_unexpected_state);
            return;
        }
    } else {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "test case has no parent");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    if (oldInstanceState == tcis_ready) {
        internal_nbp_test_case_instance_update_state_stats(
            testCase->testCaseInstance,
            tcis_ready,
            tcis_running);

        internal_nbp_notify_reporter_test_case_instance_started(
            testCase->testCaseInstance);
    }

    int tciIsSkipped = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->testCaseInstance->isSkipped,
        (int) sf_is_not_set,
        (int) sf_is_processed);

    if (tciIsSkipped == (int) sf_is_set) {
        internal_nbp_runner_run_skipped_test_case(testCase);
    } else {
        int isSkipped = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
            &testCase->isSkipped,
            (int) sf_is_not_set,
            (int) sf_is_processed);

        if (isSkipped == (int) sf_is_set) {
            internal_nbp_runner_run_skipped_test_case(testCase);
        } else if (isSkipped == (int) sf_is_not_set) {
            int parentIsSkipped;
            if (testCase->testCaseInstance->module != NBP_NULLPTR) {
                parentIsSkipped = internal_nbp_runner_setup_module(
                    testCase->testCaseInstance->module);
            } else {
                parentIsSkipped = internal_nbp_runner_setup_test_suite(
                    testCase->testCaseInstance->testSuite);
            }

            if (parentIsSkipped == (int) sf_is_processed) {
                internal_nbp_runner_run_ready_test_case(testCase);
            } else if (parentIsSkipped == (int) sf_is_set) {
                internal_nbp_runner_run_skipped_test_case(testCase);
            } else {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_unexpected_internal_data,
                    "unexpected value for parent isSkipped flag");
                NBP_EXIT(ec_unexpected_internal_data);
                return;
            }
        } else {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_internal_data,
                "unexpected value for isSkipped flag");
            NBP_EXIT(ec_unexpected_internal_data);
            return;
        }
    }

    int isCompletedInstance = internal_nbp_runner_complete_test_case_instance(
        testCase->testCaseInstance);

    if (isCompletedInstance == 1) {
        if (testCase->testCaseInstance->module != NBP_NULLPTR) {
            internal_nbp_runner_teardown_module(
                testCase->testCaseInstance->module);
        } else {
            internal_nbp_runner_teardown_test_suite(
                testCase->testCaseInstance->testSuite);
        }
    }

    NBP_ATOMIC_UINT_ADD_AND_FETCH(&gInternalNbpNumberOfRanTestCases, 1);
}

void internal_nbp_runner_run_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance)
{
    if (gInternalNbpRunnerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_runner_run_is_disabled,
            "a test case instance can be run only from runner's run "
            "callback");
        NBP_EXIT(ec_runner_run_is_disabled);
        return;
    }

    for (unsigned int i = 0; i < testCaseInstance->numberOfRuns; i++) {
        internal_nbp_runner_run_test_case(&testCaseInstance->runs[i]);
    }
}

extern nbp_runner_interface_t* gInternalNbpRunnerInterface;

extern int gInternalNbpRunnerRunEnabled;

#define INTERNAL_NBP_CALLBACK_IS_SET(cbk)                                      \
    gInternalNbpRunnerInterface->cbk != NBP_NULLPTR

void internal_nbp_notify_runner_init()
{
    gInternalNbpRunnerInterface->configFunction(gInternalNbpRunnerInterface);

    if (INTERNAL_NBP_CALLBACK_IS_SET(initCbk)) {
        gInternalNbpRunnerInterface->initCbk();
    }
}

void internal_nbp_notify_runner_uninit()
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(uninitCbk)) {
        gInternalNbpRunnerInterface->uninitCbk();
    }
}

void internal_nbp_notify_runner_run()
{
    gInternalNbpRunnerRunEnabled = 1;

    if (INTERNAL_NBP_CALLBACK_IS_SET(runCbk)) {
        gInternalNbpRunnerInterface->runCbk();
    }

    gInternalNbpRunnerRunEnabled = 0;
}

void internal_nbp_notify_runner_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance,
    void* context)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestCaseCbk)) {
        gInternalNbpRunnerInterface->instantiateTestCaseCbk(
            testCaseInstance,
            testCaseInstance->testSuite,
            testCaseInstance->module,
            context);
    }
}

void internal_nbp_notify_runner_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance,
    void* context)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteStartedCbk)) {
        gInternalNbpRunnerInterface->instantiateTestSuiteStartedCbk(
            testSuiteInstance,
            testSuiteInstance->module,
            context);
    }
}

void internal_nbp_notify_runner_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteCompletedCbk)) {
        gInternalNbpRunnerInterface->instantiateTestSuiteCompletedCbk(
            testSuiteInstance,
            testSuiteInstance->module);
    }
}

void internal_nbp_notify_runner_instantiate_module_started(
    nbp_module_instance_t* moduleInstance,
    void* context)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleStartedCbk)) {
        gInternalNbpRunnerInterface->instantiateModuleStartedCbk(
            moduleInstance,
            moduleInstance->parent,
            context);
    }
}

void internal_nbp_notify_runner_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance)
{
    if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleCompletedCbk)) {
        gInternalNbpRunnerInterface->instantiateModuleCompletedCbk(
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
    unsigned int pos = internal_nbp_get_test_case_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_test_case_state_position(state);
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
    unsigned int pos =
        internal_nbp_get_test_case_instance_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state,
    unsigned int value)
{
    unsigned int pos =
        internal_nbp_get_test_case_instance_state_position(state);
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

unsigned int internal_nbp_get_test_case_state_position(
    nbp_test_case_state_e state)
{
    if ((unsigned int) state < (unsigned int) tcs_ready
        || (unsigned int) state > (unsigned int) tcs_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test case state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tcs_ready);
}

unsigned int internal_nbp_get_test_case_instance_state_position(
    nbp_test_case_instance_state_e state)
{
    if ((unsigned int) state < (unsigned int) tcis_ready
        || (unsigned int) state > (unsigned int) tcis_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test case instance state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tcis_ready);
}

int internal_nbp_is_failed_test_case(nbp_test_case_t* testCase)
{
    ((void) testCase);
    return 0;
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
    unsigned int pos = internal_nbp_get_test_case_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state)
{
    unsigned int pos =
        internal_nbp_get_test_case_instance_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_test_case_t* internal_nbp_get_test_case_from_instance(
    nbp_test_case_instance_t* testCaseInstance,
    unsigned int runId)
{
    if (runId >= testCaseInstance->numberOfRuns) {
        return NBP_NULLPTR;
    }
    return &testCaseInstance->runs[runId];
}

nbp_test_case_instance_t* internal_nbp_instantiate_test_case(
    nbp_test_case_function_t* testCaseFunction,
    nbp_module_t* parentModule,
    nbp_test_suite_t* parentTestSuite,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    testCaseFunction->configFunction(testCaseFunction);

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

        NBP_ATOMIC_INT_STORE(&runs[i].state, (int) tcs_ready);
        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);
    }

    testCaseInstance->testCaseFunction  = testCaseFunction;
    testCaseInstance->module            = parentModule;
    testCaseInstance->testSuite         = parentTestSuite;
    testCaseInstance->depth             = 0;
    testCaseInstance->instantiationLine = instantiationLine;
    testCaseInstance->setupFunction     = testCaseFunction->setupFunction;
    testCaseInstance->teardownFunction  = testCaseFunction->teardownFunction;
    testCaseInstance->runs              = runs;
    testCaseInstance->numberOfRuns      = numberOfRuns;
    testCaseInstance->next              = NBP_NULLPTR;
    testCaseInstance->prev              = NBP_NULLPTR;

    NBP_ATOMIC_INT_STORE(&testCaseInstance->state, (int) tcis_ready);
    NBP_ATOMIC_INT_STORE(&testCaseInstance->isSkipped, (int) sf_is_not_set);
    NBP_ATOMIC_UINT_STORE(&testCaseInstance->numberOfCompletedRuns, 0U);

    internal_nbp_initialize_array_of_atomic_uint(
        testCaseInstance->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES,
        0U);

    if (parentModule != NBP_NULLPTR) {
        testCaseInstance->depth = parentModule->moduleInstance->depth + 1;

        parentModule->numberOfTasks += 1;

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

    internal_nbp_notify_reporter_instantiate_test_case(testCaseInstance);
    internal_nbp_notify_runner_instantiate_test_case(testCaseInstance, context);

    return testCaseInstance;
}

static void internal_nbp_increment_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_test_suite_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_test_suite_state_position(state);
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
    unsigned int pos =
        internal_nbp_get_test_suite_instance_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state,
    unsigned int value)
{
    unsigned int pos =
        internal_nbp_get_test_suite_instance_state_position(state);
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

unsigned int internal_nbp_get_test_suite_state_position(
    nbp_test_suite_state_e state)
{
    if ((unsigned int) state < (unsigned int) tss_ready
        || (unsigned int) state > (unsigned int) tss_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test suite state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tss_ready);
}

unsigned int internal_nbp_get_test_suite_instance_state_position(
    nbp_test_suite_instance_state_e state)
{
    if ((unsigned int) state < (unsigned int) tsis_ready
        || (unsigned int) state > (unsigned int) tsis_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test suite instance state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tsis_ready);
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
    unsigned int pos = internal_nbp_get_test_suite_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state)
{
    unsigned int pos =
        internal_nbp_get_test_suite_instance_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_test_suite_t* internal_nbp_get_test_suite_from_instance(
    nbp_test_suite_instance_t* testSuiteInstance,
    unsigned int runId)
{
    if (runId >= testSuiteInstance->numberOfRuns) {
        return NBP_NULLPTR;
    }
    return &testSuiteInstance->runs[runId];
}

nbp_test_suite_instance_t* internal_nbp_instantiate_test_suite(
    nbp_test_suite_function_t* testSuiteFunction,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    testSuiteFunction->configFunction(testSuiteFunction);

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
        numberOfRuns * sizeof(nbp_test_suite_t),
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
        runs[i].firstTestCaseInstance          = NBP_NULLPTR;
        runs[i].lastTestCaseInstance           = NBP_NULLPTR;
        runs[i].totalNumberOfTestCases         = 0;
        runs[i].totalNumberOfTestCaseInstances = 0;

        NBP_ATOMIC_INT_STORE(&runs[i].state, (int) tss_ready);
        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);
        NBP_ATOMIC_UINT_STORE(&runs[i].numberOfCompletedTasks, 0U);

        if (NBP_SYNC_EVENT_INIT(&runs[i].runEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init runEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        if (NBP_SYNC_EVENT_INIT(&runs[i].setupEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init setupEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCases,
            NBP_NUMBER_OF_TEST_CASE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCaseInstances,
            NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
            0U);
    }

    testSuiteInstance->testSuiteFunction = testSuiteFunction;
    testSuiteInstance->module            = parentModule;
    testSuiteInstance->instantiationLine = instantiationLine;
    testSuiteInstance->setupFunction     = testSuiteFunction->setupFunction;
    testSuiteInstance->teardownFunction  = testSuiteFunction->teardownFunction;
    testSuiteInstance->runs              = runs;
    testSuiteInstance->numberOfRuns      = numberOfRuns;
    testSuiteInstance->next              = NBP_NULLPTR;
    testSuiteInstance->prev              = NBP_NULLPTR;
    testSuiteInstance->depth = parentModule->moduleInstance->depth + 1;
    testSuiteInstance->totalNumberOfTestCases         = 0;
    testSuiteInstance->totalNumberOfTestCaseInstances = 0;

    NBP_ATOMIC_INT_STORE(&testSuiteInstance->state, (int) tsis_ready);
    NBP_ATOMIC_INT_STORE(&testSuiteInstance->isSkipped, (int) sf_is_not_set);
    NBP_ATOMIC_UINT_STORE(&testSuiteInstance->numberOfCompletedRuns, 0U);

    internal_nbp_initialize_array_of_atomic_uint(
        testSuiteInstance->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        testSuiteInstance->numberOfTestCaseInstances,
        NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        testSuiteInstance->numberOfTestSuites,
        NBP_NUMBER_OF_TEST_SUITE_STATES,
        0U);

    parentModule->numberOfTasks += 1;

    if (parentModule->firstTestSuiteInstance == NBP_NULLPTR) {
        parentModule->firstTestSuiteInstance = testSuiteInstance;
        parentModule->lastTestSuiteInstance  = testSuiteInstance;
    } else {
        testSuiteInstance->prev = parentModule->lastTestSuiteInstance;
        parentModule->lastTestSuiteInstance->next = testSuiteInstance;
        parentModule->lastTestSuiteInstance       = testSuiteInstance;
    }

    internal_nbp_test_suite_instance_update_stats(testSuiteInstance);

    internal_nbp_notify_reporter_instantiate_test_suite_started(
        testSuiteInstance);

    internal_nbp_notify_runner_instantiate_test_suite_started(
        testSuiteInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testSuiteInstance->testSuiteFunction->function(
            &testSuiteInstance->runs[i],
            &testSuiteInstance->runs[i],
            NBP_NULLPTR,
            1);

        if (testSuiteInstance->runs[i].totalNumberOfTestCaseInstances == 0) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_no_test_case_instantiated,
                "test suite has no test case");
            NBP_EXIT(ec_no_test_case_instantiated);
        }
    }

    internal_nbp_notify_reporter_instantiate_test_suite_completed(
        testSuiteInstance);

    internal_nbp_notify_runner_instantiate_test_suite_completed(
        testSuiteInstance);

    return testSuiteInstance;
}

void internal_nbp_initialize_array_of_atomic_uint(
    NBP_ATOMIC_UINT_TYPE* array,
    unsigned int size,
    unsigned int value)
{
    for (unsigned int i = 0; i < size; i++) {
        NBP_ATOMIC_UINT_STORE(&array[i], value);
    }
}

void internal_nbp_copy_array_of_atomic_uint(
    NBP_ATOMIC_UINT_TYPE* source,
    unsigned int* dest,
    unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
        dest[i] = NBP_ATOMIC_UINT_LOAD(&source[i]);
    }
}

#endif // end if NBP_LIBRARY_MAIN

#ifdef NBP_CONSOLE_REPORTER

#ifdef NBP_LIBRARY_MAIN

/*
 * Console reporter for Linux
 */
#ifdef NBP_OS_LINUX

#include <stdio.h>

#define NBP_CR_TEST_CASE_EMOJI  "\xF0\x9F\x93\x9D"
#define NBP_CR_TEST_SUITE_EMOJI "\xF0\x9F\x93\x9C"
#define NBP_CR_MODULE_EMOJI     "\xF0\x9F\x93\x81"

#define NBP_CR_COLOR_NORMAL "\x1B[0m"
#define NBP_CR_COLOR_RED    "\x1B[31m"
#define NBP_CR_COLOR_GREEN  "\x1B[32m"
#define NBP_CR_COLOR_YELLOW "\x1B[33m"

#define NBP_CR_CLEAR_LINE "\x1B[2K\r"

#ifdef NBP_MT_SUPPORT

#include <pthread.h>

static inline nbp_error_code_e internal_nbp_cr_mutex_init(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_init(mutex, NULL) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_cr_mutex_uninit(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_destroy(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_cr_mutex_lock(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_lock(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_cr_mutex_unlock(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_unlock(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

#define INTERNAL_NBP_CR_DECLARE_MUTEX(name)                                    \
    pthread_mutex_t name = PTHREAD_MUTEX_INITIALIZER;

#define INTERNAL_NBP_CR_MUTEX_INIT(name) internal_nbp_cr_mutex_init(&name)

#define INTERNAL_NBP_CR_MUTEX_UNINIT(name) internal_nbp_cr_mutex_uninit(&name)

#define INTERNAL_NBP_CR_MUTEX_LOCK(name) internal_nbp_cr_mutex_lock(&name)

#define INTERNAL_NBP_CR_MUTEX_UNLOCK(name) internal_nbp_cr_mutex_unlock(&name)

#else

static inline nbp_error_code_e internal_nbp_cr_mutex_init_dummy()
{
    return ec_success;
}

static inline nbp_error_code_e internal_nbp_cr_mutex_uninit_dummy()
{
    return ec_success;
}

static inline nbp_error_code_e internal_nbp_cr_mutex_lock_dummy()
{
    return ec_success;
}

static inline nbp_error_code_e internal_nbp_cr_mutex_unlock_dummy()
{
    return ec_success;
}

#define INTERNAL_NBP_CR_DECLARE_MUTEX(name)

#define INTERNAL_NBP_CR_MUTEX_INIT(name) internal_nbp_cr_mutex_init_dummy()

#define INTERNAL_NBP_CR_MUTEX_UNINIT(name) internal_nbp_cr_mutex_uninit_dummy()

#define INTERNAL_NBP_CR_MUTEX_LOCK(name) internal_nbp_cr_mutex_lock_dummy()

#define INTERNAL_NBP_CR_MUTEX_UNLOCK(name) internal_nbp_cr_mutex_unlock_dummy()

#endif // end if NBP_MT_SUPPORT

enum nbp_cr_task_type_e
{
    tt_unknown             = 0x60000000,
    tt_test_case_instance  = 0x60000001,
    tt_test_suite_instance = 0x60000002,
    tt_module_instance     = 0x60000003,
    tt_module              = 0x60000004,
};
typedef enum nbp_cr_task_type_e nbp_cr_task_type_e;

struct nbp_cr_test_case_instance_task_t;
struct nbp_cr_test_suite_instance_task_t;

struct nbp_cr_message_list_t
{
    char* message;
    struct nbp_cr_message_list_t* next;
};
typedef struct nbp_cr_message_list_t nbp_cr_message_list_t;

struct nbp_cr_test_case_task_t
{
    nbp_test_case_t* testCase;
    unsigned int runId;

    struct nbp_cr_test_case_instance_task_t* testCaseInstanceTask;

    nbp_cr_message_list_t* messageList;
    nbp_cr_message_list_t* messageListLast;
};
typedef struct nbp_cr_test_case_task_t nbp_cr_test_case_task_t;

struct nbp_cr_test_case_instance_task_t
{
    nbp_test_case_instance_t* testCaseInstance;
    nbp_cr_test_case_task_t* testCaseTasks;
    unsigned int depth;

    struct nbp_cr_test_case_instance_task_t* next;
};
typedef struct nbp_cr_test_case_instance_task_t
    nbp_cr_test_case_instance_task_t;

struct nbp_cr_test_suite_task_t
{
    nbp_test_suite_t* testSuite;
    unsigned int runId;

    struct nbp_cr_test_suite_instance_task_t* testSuiteInstanceTask;

    nbp_cr_test_case_instance_task_t* firstTestCaseInstance;
    nbp_cr_test_case_instance_task_t* lastTestCaseInstance;
};
typedef struct nbp_cr_test_suite_task_t nbp_cr_test_suite_task_t;

struct nbp_cr_test_suite_instance_task_t
{
    nbp_test_suite_instance_t* testSuiteInstance;
    nbp_cr_test_suite_task_t* testSuiteTasks;
    unsigned int depth;
};
typedef struct nbp_cr_test_suite_instance_task_t
    nbp_cr_test_suite_instance_task_t;

struct nbp_cr_module_task_t
{
    nbp_module_t* module;
    unsigned int depth;
    unsigned int runId;
};
typedef struct nbp_cr_module_task_t nbp_cr_module_task_t;

struct nbp_cr_module_instance_task_t
{
    nbp_module_instance_t* moduleInstance;
    unsigned int depth;
};
typedef struct nbp_cr_module_instance_task_t nbp_cr_module_instance_task_t;

struct nbp_cr_task_tree_t
{
    nbp_cr_task_type_e taskType;
    union
    {
        nbp_cr_test_case_instance_task_t testCaseInstance;
        nbp_cr_test_suite_instance_task_t testSuiteInstance;
        nbp_cr_module_task_t module;
        nbp_cr_module_instance_task_t moduleInstance;
    };

    struct nbp_cr_task_tree_t* next;

    struct nbp_cr_task_tree_t* firstChild;
    struct nbp_cr_task_tree_t* lastChild;
};
typedef struct nbp_cr_task_tree_t nbp_cr_task_tree_t;

static nbp_cr_task_tree_t* gInternalNbpCrTaskTreeRoot        = NBP_NULLPTR;
static unsigned int gInternalNbpCrNumberOfTestCases          = 0;
static unsigned int gInternalNbpCrNumberOfCompletedTestCases = 0;
static int gInternalNbpCrProgressMessagePrinted              = 0;

INTERNAL_NBP_CR_DECLARE_MUTEX(gInternalNbpCrMutex);

static nbp_cr_task_tree_t* internal_nbp_cr_find_module_task(
    nbp_cr_task_tree_t* root,
    nbp_module_t* module)
{
    if (root == NBP_NULLPTR) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_case_instance) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_suite_instance) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_module && root->module.module == module) {
        return root;
    }

    nbp_cr_task_tree_t* child = root->firstChild;
    nbp_cr_task_tree_t* task  = NBP_NULLPTR;

    while (child != NBP_NULLPTR) {
        task = internal_nbp_cr_find_module_task(child, module);
        if (task != NBP_NULLPTR) {
            return task;
        }

        child = child->next;
    }

    return NBP_NULLPTR;
}

static nbp_cr_task_tree_t* internal_nbp_cr_find_test_suite_instance_task(
    nbp_cr_task_tree_t* root,
    nbp_test_suite_instance_t* testSuiteInstance)
{
    if (root == NBP_NULLPTR) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_case_instance) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_suite_instance
        && root->testSuiteInstance.testSuiteInstance == testSuiteInstance) {
        return root;
    }

    nbp_cr_task_tree_t* child = root->firstChild;
    nbp_cr_task_tree_t* task  = NBP_NULLPTR;

    while (child != NBP_NULLPTR) {
        task = internal_nbp_cr_find_test_suite_instance_task(
            child,
            testSuiteInstance);
        if (task != NBP_NULLPTR) {
            return task;
        }

        child = child->next;
    }

    return NBP_NULLPTR;
}

static nbp_cr_test_suite_task_t* internal_nbp_cr_find_test_suite_task(
    nbp_test_suite_t* testSuite)
{
    nbp_cr_task_tree_t* testSuiteInstanceTask =
        internal_nbp_cr_find_test_suite_instance_task(
            gInternalNbpCrTaskTreeRoot,
            NBP_TEST_SUITE_GET_INSTANCE(testSuite));
    if (testSuiteInstanceTask == NBP_NULLPTR) {
        return NBP_NULLPTR;
    }

    nbp_cr_test_suite_task_t* tasks =
        testSuiteInstanceTask->testSuiteInstance.testSuiteTasks;
    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_SUITE_GET_INSTANCE(testSuite));

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        if (tasks[i].testSuite == testSuite) {
            return &tasks[i];
        }
    }

    return NBP_NULLPTR;
}

static void internal_nbp_cr_print_depth(
    unsigned int depth,
    unsigned int instantiationDepth)
{
    depth += (instantiationDepth / 2);

    if (instantiationDepth % 2 == 1) {
        printf("  ");
    }

    while (depth-- > 0) {
        printf("    ");
    }
}

static void internal_nbp_cr_print_test_case_task(
    nbp_cr_test_case_task_t* testCaseTask)
{
    unsigned int numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_CASE_GET_INSTANCE(testCaseTask->testCase));
    nbp_test_case_state_e state =
        NBP_TEST_CASE_GET_STATE(testCaseTask->testCase);
    const char* color = NBP_CR_COLOR_NORMAL;

    if (state == tcs_passed) {
        color = NBP_CR_COLOR_GREEN;
    } else if (state == tcs_failed) {
        color = NBP_CR_COLOR_RED;
    } else if (state == tcs_skipped) {
        color = NBP_CR_COLOR_YELLOW;
    }

    if (numberOfRuns > 1) {
        internal_nbp_cr_print_depth(
            NBP_TEST_CASE_GET_DEPTH(testCaseTask->testCase),
            testCaseTask->testCaseInstanceTask->depth + 1);
        printf(
            "%s %s%s%s#%u\n",
            NBP_CR_TEST_CASE_EMOJI,
            color,
            NBP_TEST_CASE_GET_NAME(testCaseTask->testCase),
            NBP_CR_COLOR_NORMAL,
            testCaseTask->runId);
    } else {
        internal_nbp_cr_print_depth(
            NBP_TEST_CASE_GET_DEPTH(testCaseTask->testCase),
            testCaseTask->testCaseInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_CR_TEST_CASE_EMOJI,
            color,
            NBP_TEST_CASE_GET_NAME(testCaseTask->testCase),
            NBP_CR_COLOR_NORMAL);
    }
}

static void internal_nbp_cr_print_test_case_instance_task(
    nbp_cr_test_case_instance_task_t* testCaseInstanceTask)
{
    unsigned int numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(
        testCaseInstanceTask->testCaseInstance);

    if (numberOfRuns > 1) {
        nbp_test_case_instance_state_e state = NBP_TEST_CASE_INSTANCE_GET_STATE(
            testCaseInstanceTask->testCaseInstance);
        const char* color = NBP_CR_COLOR_NORMAL;

        if (state == tcis_passed) {
            color = NBP_CR_COLOR_GREEN;
        } else if (state == tcis_failed) {
            color = NBP_CR_COLOR_RED;
        } else if (state == tcis_skipped) {
            color = NBP_CR_COLOR_YELLOW;
        }

        internal_nbp_cr_print_depth(
            NBP_TEST_CASE_INSTANCE_GET_DEPTH(
                testCaseInstanceTask->testCaseInstance),
            testCaseInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_CR_TEST_CASE_EMOJI,
            color,
            NBP_TEST_CASE_INSTANCE_GET_NAME(
                testCaseInstanceTask->testCaseInstance),
            NBP_CR_COLOR_NORMAL);
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        internal_nbp_cr_print_test_case_task(
            &testCaseInstanceTask->testCaseTasks[i]);
    }
}

static void internal_nbp_cr_print_test_suite_task(
    nbp_cr_test_suite_task_t* testSuiteTask)
{
    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_SUITE_GET_INSTANCE(testSuiteTask->testSuite));
    nbp_test_suite_state_e state =
        NBP_TEST_SUITE_GET_STATE(testSuiteTask->testSuite);
    const char* color = NBP_CR_COLOR_NORMAL;

    if (state == tss_passed) {
        color = NBP_CR_COLOR_GREEN;
    } else if (state == tss_failed) {
        color = NBP_CR_COLOR_RED;
    } else if (state == tss_skipped) {
        color = NBP_CR_COLOR_YELLOW;
    }

    if (numberOfRuns > 1) {
        internal_nbp_cr_print_depth(
            NBP_TEST_SUITE_GET_DEPTH(testSuiteTask->testSuite),
            testSuiteTask->testSuiteInstanceTask->depth + 1);
        printf(
            "%s %s%s%s#%u\n",
            NBP_CR_TEST_SUITE_EMOJI,
            color,
            NBP_TEST_SUITE_GET_NAME(testSuiteTask->testSuite),
            NBP_CR_COLOR_NORMAL,
            testSuiteTask->runId);
    } else {
        internal_nbp_cr_print_depth(
            NBP_TEST_SUITE_GET_DEPTH(testSuiteTask->testSuite),
            testSuiteTask->testSuiteInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_CR_TEST_SUITE_EMOJI,
            color,
            NBP_TEST_SUITE_GET_NAME(testSuiteTask->testSuite),
            NBP_CR_COLOR_NORMAL);
    }

    nbp_cr_test_case_instance_task_t* child =
        testSuiteTask->firstTestCaseInstance;

    while (child != NBP_NULLPTR) {
        internal_nbp_cr_print_test_case_instance_task(child);
        child = child->next;
    }
}

static void internal_nbp_cr_print_test_suite_instance_task(
    nbp_cr_test_suite_instance_task_t* testSuiteInstanceTask)
{
    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        testSuiteInstanceTask->testSuiteInstance);

    if (numberOfRuns > 1) {
        nbp_test_suite_instance_state_e state =
            NBP_TEST_SUITE_INSTANCE_GET_STATE(
                testSuiteInstanceTask->testSuiteInstance);
        const char* color = NBP_CR_COLOR_NORMAL;

        if (state == tsis_passed) {
            color = NBP_CR_COLOR_GREEN;
        } else if (state == tsis_failed) {
            color = NBP_CR_COLOR_RED;
        } else if (state == tsis_skipped) {
            color = NBP_CR_COLOR_YELLOW;
        }

        internal_nbp_cr_print_depth(
            NBP_TEST_SUITE_INSTANCE_GET_DEPTH(
                testSuiteInstanceTask->testSuiteInstance),
            testSuiteInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_CR_TEST_SUITE_EMOJI,
            color,
            NBP_TEST_SUITE_INSTANCE_GET_NAME(
                testSuiteInstanceTask->testSuiteInstance),
            NBP_CR_COLOR_NORMAL);
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        internal_nbp_cr_print_test_suite_task(
            &testSuiteInstanceTask->testSuiteTasks[i]);
    }
}

static void internal_nbp_cr_print_module_task(nbp_cr_module_task_t* moduleTask)
{
    unsigned int numberOfRuns = NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_MODULE_GET_INSTANCE(moduleTask->module));
    nbp_module_state_e state = NBP_MODULE_GET_STATE(moduleTask->module);
    const char* color        = NBP_CR_COLOR_NORMAL;

    if (state == ms_passed) {
        color = NBP_CR_COLOR_GREEN;
    } else if (state == ms_failed) {
        color = NBP_CR_COLOR_RED;
    } else if (state == ms_skipped) {
        color = NBP_CR_COLOR_YELLOW;
    }

    if (numberOfRuns > 1) {
        internal_nbp_cr_print_depth(
            NBP_MODULE_GET_DEPTH(moduleTask->module),
            moduleTask->depth);
        printf(
            "%s %s%s%s#%u\n",
            NBP_CR_MODULE_EMOJI,
            color,
            NBP_MODULE_GET_NAME(moduleTask->module),
            NBP_CR_COLOR_NORMAL,
            moduleTask->runId);
    } else {
        internal_nbp_cr_print_depth(
            NBP_MODULE_GET_DEPTH(moduleTask->module),
            moduleTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_CR_MODULE_EMOJI,
            color,
            NBP_MODULE_GET_NAME(moduleTask->module),
            NBP_CR_COLOR_NORMAL);
    }
}

static void internal_nbp_cr_print_module_instace_task(
    nbp_cr_module_instance_task_t* moduleInstanceTask)
{
    unsigned int numberOfRuns = NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(
        moduleInstanceTask->moduleInstance);

    if (numberOfRuns > 1) {
        nbp_module_instance_state_e state =
            NBP_MODULE_INSTANCE_GET_STATE(moduleInstanceTask->moduleInstance);
        const char* color = NBP_CR_COLOR_NORMAL;

        if (state == mis_passed) {
            color = NBP_CR_COLOR_GREEN;
        } else if (state == mis_failed) {
            color = NBP_CR_COLOR_RED;
        } else if (state == mis_skipped) {
            color = NBP_CR_COLOR_YELLOW;
        }

        internal_nbp_cr_print_depth(
            NBP_MODULE_INSTANCE_GET_DEPTH(moduleInstanceTask->moduleInstance),
            moduleInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_CR_MODULE_EMOJI,
            color,
            NBP_MODULE_INSTANCE_GET_NAME(moduleInstanceTask->moduleInstance),
            NBP_CR_COLOR_NORMAL);
    }
}

static void internal_nbp_cr_print_task_tree(nbp_cr_task_tree_t* root)
{
    if (root == NBP_NULLPTR) {
        return;
    }

    switch (root->taskType) {
    case tt_test_case_instance:
        internal_nbp_cr_print_test_case_instance_task(&root->testCaseInstance);
        break;
    case tt_test_suite_instance:
        internal_nbp_cr_print_test_suite_instance_task(
            &root->testSuiteInstance);
        break;
    case tt_module:
        internal_nbp_cr_print_module_task(&root->module);
        break;
    case tt_module_instance:
        internal_nbp_cr_print_module_instace_task(&root->moduleInstance);
        break;
    default:
        break;
    }

    nbp_cr_task_tree_t* child = root->firstChild;
    while (child != NBP_NULLPTR) {
        internal_nbp_cr_print_task_tree(child);
        child = child->next;
    }
}

static void internal_nbp_cr_add_test_case_instance_to_module(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_module_t* module)
{
    nbp_cr_task_tree_t* task               = NBP_NULLPTR;
    nbp_cr_task_tree_t* parent             = NBP_NULLPTR;
    nbp_cr_test_case_task_t* testCaseTasks = NBP_NULLPTR;
    unsigned int numberOfRuns              = 0;

    numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance);

    parent =
        internal_nbp_cr_find_module_task(gInternalNbpCrTaskTreeRoot, module);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_cr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_cr_task_tree_t),
        mt_console_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testCaseTasks = (nbp_cr_test_case_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_cr_test_case_task_t),
        mt_console_reporter);
    if (testCaseTasks == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case tasks");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->taskType   = tt_test_case_instance;
    task->next       = NBP_NULLPTR;
    task->firstChild = NBP_NULLPTR;
    task->lastChild  = NBP_NULLPTR;

    task->testCaseInstance.testCaseInstance = testCaseInstance;
    task->testCaseInstance.testCaseTasks    = testCaseTasks;
    task->testCaseInstance.next             = NBP_NULLPTR;
    task->testCaseInstance.depth            = parent->module.depth;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testCaseTasks[i].testCase =
            NBP_TEST_CASE_INSTANCE_GET_TEST_CASE(testCaseInstance, i);
        testCaseTasks[i].testCaseInstanceTask = &task->testCaseInstance;
        testCaseTasks[i].runId                = i;
        testCaseTasks[i].messageList          = NBP_NULLPTR;
        testCaseTasks[i].messageListLast      = NBP_NULLPTR;
    }

    if (parent->firstChild == NBP_NULLPTR) {
        parent->firstChild = task;
        parent->lastChild  = task;
    } else {
        parent->lastChild->next = task;
        parent->lastChild       = task;
    }
}

static void internal_nbp_cr_add_test_case_instance_to_test_suite(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_test_suite_t* testSuite)
{
    nbp_cr_test_case_instance_task_t* task = NBP_NULLPTR;
    nbp_cr_test_suite_task_t* parent       = NBP_NULLPTR;
    nbp_cr_test_case_task_t* testCaseTasks = NBP_NULLPTR;
    unsigned int numberOfRuns              = 0;

    numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance);

    parent = internal_nbp_cr_find_test_suite_task(testSuite);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_cr_test_case_instance_task_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_cr_test_case_instance_task_t),
        mt_console_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testCaseTasks = (nbp_cr_test_case_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_cr_test_case_task_t),
        mt_console_reporter);
    if (testCaseTasks == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case tasks");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->testCaseInstance = testCaseInstance;
    task->testCaseTasks    = testCaseTasks;
    task->next             = NBP_NULLPTR;
    task->depth            = parent->testSuiteInstanceTask->depth;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testCaseTasks[i].testCase =
            NBP_TEST_CASE_INSTANCE_GET_TEST_CASE(testCaseInstance, i);
        testCaseTasks[i].testCaseInstanceTask = task;
        testCaseTasks[i].runId                = i;
        testCaseTasks[i].messageList          = NBP_NULLPTR;
        testCaseTasks[i].messageListLast      = NBP_NULLPTR;
    }

    if (parent->firstTestCaseInstance == NBP_NULLPTR) {
        parent->firstTestCaseInstance = task;
        parent->lastTestCaseInstance  = task;
    } else {
        parent->lastTestCaseInstance->next = task;
        parent->lastTestCaseInstance       = task;
    }
}

NBP_REPORTER_CALLBACK_INIT(nbp_cr_init)
{
    INTERNAL_NBP_CR_MUTEX_INIT(gInternalNbpCrMutex);
}

NBP_REPORTER_CALLBACK_UNINIT(nbp_cr_uninit)
{
    gInternalNbpCrTaskTreeRoot = NBP_NULLPTR;
    INTERNAL_NBP_CR_MUTEX_UNINIT(gInternalNbpCrMutex);
}

NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(nbp_cr_handle_version_command)
{
    INTERNAL_NBP_CR_MUTEX_LOCK(gInternalNbpCrMutex);
    printf("nbp version: %s\n", NBP_VERSION_STR);
    INTERNAL_NBP_CR_MUTEX_UNLOCK(gInternalNbpCrMutex);
}

NBP_REPORTER_CALLBACK_ON_ERROR(nbp_cr_on_error)
{
    INTERNAL_NBP_CR_MUTEX_LOCK(gInternalNbpCrMutex);

    if (gInternalNbpCrProgressMessagePrinted == 1) {
        printf(NBP_CR_CLEAR_LINE);
    }

    switch (NBP_GET_ERROR_CONTEXT_TYPE(NBP_THIS_ERROR)) {
    case ect_string:
        printf(
            "[%serror%s] code = %d, line = %d, file = %s, message = %s\n",
            NBP_CR_COLOR_RED,
            NBP_CR_COLOR_NORMAL,
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR),
            NBP_GET_ERROR_STRING_CONTEXT(NBP_THIS_ERROR));
        break;
    default:
        printf(
            "[%serror%s] code = %d, line = %d, file = %s\n",
            NBP_CR_COLOR_RED,
            NBP_CR_COLOR_NORMAL,
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR));
        break;
    }

    if (gInternalNbpCrProgressMessagePrinted) {
        printf(
            NBP_CR_CLEAR_LINE "Running... %u/%u",
            gInternalNbpCrNumberOfCompletedTestCases,
            gInternalNbpCrNumberOfTestCases);
        fflush(stdout);
    }

    INTERNAL_NBP_CR_MUTEX_UNLOCK(gInternalNbpCrMutex);
}

NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_cr_instantiate_test_case)
{
    if (NBP_THIS_MODULE != NBP_NULLPTR) {
        internal_nbp_cr_add_test_case_instance_to_module(
            NBP_THIS_TEST_CASE_INSTANCE,
            NBP_THIS_MODULE);
        return;
    }

    if (NBP_THIS_TEST_SUITE != NBP_NULLPTR) {
        internal_nbp_cr_add_test_case_instance_to_test_suite(
            NBP_THIS_TEST_CASE_INSTANCE,
            NBP_THIS_TEST_SUITE);
        return;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_invalid_parent,
        "test case instance has no parent");
    NBP_EXIT(ec_invalid_parent);
}

NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(
    nbp_cr_instantiate_test_suite_started)
{
    nbp_cr_task_tree_t* task                 = NBP_NULLPTR;
    nbp_cr_task_tree_t* parent               = NBP_NULLPTR;
    nbp_cr_test_suite_task_t* testSuiteTasks = NBP_NULLPTR;
    unsigned int numberOfRuns                = 0;

    numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_THIS_TEST_SUITE_INSTANCE);

    parent = internal_nbp_cr_find_module_task(
        gInternalNbpCrTaskTreeRoot,
        NBP_THIS_MODULE);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_cr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_cr_task_tree_t),
        mt_console_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test suite instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testSuiteTasks = (nbp_cr_test_suite_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_cr_test_suite_task_t),
        mt_console_reporter);
    if (testSuiteTasks == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test suite tasks");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->taskType   = tt_test_suite_instance;
    task->next       = NBP_NULLPTR;
    task->firstChild = NBP_NULLPTR;
    task->lastChild  = NBP_NULLPTR;

    task->testSuiteInstance.testSuiteInstance = NBP_THIS_TEST_SUITE_INSTANCE;
    task->testSuiteInstance.testSuiteTasks    = testSuiteTasks;
    task->testSuiteInstance.depth             = parent->module.depth;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testSuiteTasks[i].testSuite = NBP_TEST_SUITE_INSTANCE_GET_TEST_SUITE(
            NBP_THIS_TEST_SUITE_INSTANCE,
            i);
        testSuiteTasks[i].runId                 = i;
        testSuiteTasks[i].testSuiteInstanceTask = &task->testSuiteInstance;
        testSuiteTasks[i].firstTestCaseInstance = NBP_NULLPTR;
        testSuiteTasks[i].lastTestCaseInstance  = NBP_NULLPTR;
    }

    if (parent->firstChild == NBP_NULLPTR) {
        parent->firstChild = task;
        parent->lastChild  = task;
    } else {
        parent->lastChild->next = task;
        parent->lastChild       = task;
    }
}

NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(
    nbp_cr_instantiate_module_started)
{
    nbp_cr_task_tree_t* task   = NBP_NULLPTR;
    nbp_cr_task_tree_t* child  = NBP_NULLPTR;
    nbp_cr_task_tree_t* parent = NBP_NULLPTR;
    unsigned int depth         = 0;
    unsigned int numberOfRuns  = 0;

    if (gInternalNbpCrTaskTreeRoot != NBP_NULLPTR) {
        parent = internal_nbp_cr_find_module_task(
            gInternalNbpCrTaskTreeRoot,
            NBP_THIS_MODULE);
        if (parent == NBP_NULLPTR) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_invalid_parent,
                "parent not found");
            NBP_EXIT(ec_invalid_parent);
            return;
        }

        depth = parent->module.depth;
    }

    task = (nbp_cr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_cr_task_tree_t),
        mt_console_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate module instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->taskType   = tt_module_instance;
    task->next       = NBP_NULLPTR;
    task->firstChild = NBP_NULLPTR;
    task->lastChild  = NBP_NULLPTR;

    task->moduleInstance.depth          = depth;
    task->moduleInstance.moduleInstance = NBP_THIS_MODULE_INSTANCE;

    numberOfRuns =
        NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(NBP_THIS_MODULE_INSTANCE);

    if (numberOfRuns > 1) {
        depth += 1;
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        child = (nbp_cr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
            sizeof(nbp_cr_task_tree_t),
            mt_console_reporter);
        if (child == NBP_NULLPTR) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_out_of_memory,
                "could not allocate module task");
            NBP_EXIT(ec_out_of_memory);
            return;
        }

        child->taskType   = tt_module;
        child->next       = NBP_NULLPTR;
        child->firstChild = NBP_NULLPTR;
        child->lastChild  = NBP_NULLPTR;

        child->module.module =
            NBP_MODULE_INSTANCE_GET_MODULE(NBP_THIS_MODULE_INSTANCE, i);
        child->module.depth = depth;
        child->module.runId = i;

        if (task->firstChild == NBP_NULLPTR) {
            task->firstChild = child;
            task->lastChild  = child;
        } else {
            task->lastChild->next = child;
            task->lastChild       = child;
        }
    }

    if (gInternalNbpCrTaskTreeRoot == NBP_NULLPTR) {
        gInternalNbpCrTaskTreeRoot = task;
        return;
    }

    if (parent->firstChild == NBP_NULLPTR) {
        parent->firstChild = task;
        parent->lastChild  = task;
    } else {
        parent->lastChild->next = task;
        parent->lastChild       = task;
    }
}

NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(nbp_cr_test_case_completed)
{
    INTERNAL_NBP_CR_MUTEX_LOCK(gInternalNbpCrMutex);

    gInternalNbpCrNumberOfCompletedTestCases++;

    printf(
        NBP_CR_CLEAR_LINE "Running... %u/%u",
        gInternalNbpCrNumberOfCompletedTestCases,
        gInternalNbpCrNumberOfTestCases);
    fflush(stdout);

    INTERNAL_NBP_CR_MUTEX_UNLOCK(gInternalNbpCrMutex);
}

NBP_REPORTER_CALLBACK_BEFORE_RUN(nbp_cr_before_run)
{
    INTERNAL_NBP_CR_MUTEX_LOCK(gInternalNbpCrMutex);

    gInternalNbpCrNumberOfTestCases =
        NBP_REPORTER_GET_STATISTICS(st_total_number_of_test_cases);

    printf(
        NBP_CR_CLEAR_LINE "Running... %u/%u",
        gInternalNbpCrNumberOfCompletedTestCases,
        gInternalNbpCrNumberOfTestCases);
    fflush(stdout);

    gInternalNbpCrProgressMessagePrinted = 1;

    INTERNAL_NBP_CR_MUTEX_UNLOCK(gInternalNbpCrMutex);
}

NBP_REPORTER_CALLBACK_AFTER_RUN(nbp_cr_after_run)
{
#define INTERNAL_NBP_CR_PRINT_STATS(                                           \
    name,                                                                      \
    totalType,                                                                 \
    type,                                                                      \
    passed,                                                                    \
    failed,                                                                    \
    skipped)                                                                   \
    numPassed  = NBP_REPORTER_GET_STATISTICS(type, passed);                    \
    numFailed  = NBP_REPORTER_GET_STATISTICS(type, failed);                    \
    numSkipped = NBP_REPORTER_GET_STATISTICS(type, skipped);                   \
    printf(                                                                    \
        "| %-22s | %5u | %s%5u%s %s | %s%5u%s %s | %s%5u%s %s |\n",            \
        name,                                                                  \
        NBP_REPORTER_GET_STATISTICS(totalType),                                \
        NBP_CR_COLOR_GREEN,                                                    \
        numPassed,                                                             \
        NBP_CR_COLOR_NORMAL,                                                   \
        "passed",                                                              \
        numFailed > 0 ? NBP_CR_COLOR_RED : NBP_CR_COLOR_GREEN,                 \
        numFailed,                                                             \
        NBP_CR_COLOR_NORMAL,                                                   \
        "failed",                                                              \
        numSkipped > 0 ? NBP_CR_COLOR_YELLOW : NBP_CR_COLOR_GREEN,             \
        numSkipped,                                                            \
        NBP_CR_COLOR_NORMAL,                                                   \
        "skipped");

    unsigned int numPassed  = 0;
    unsigned int numFailed  = 0;
    unsigned int numSkipped = 0;

    INTERNAL_NBP_CR_MUTEX_LOCK(gInternalNbpCrMutex);

    if (gInternalNbpCrProgressMessagePrinted == 1) {
        gInternalNbpCrProgressMessagePrinted = 0;
        printf(NBP_CR_CLEAR_LINE);
    }

    internal_nbp_cr_print_task_tree(gInternalNbpCrTaskTreeRoot);

    printf(
        "----------------------------------------------------------------------"
        "----------\n");

    INTERNAL_NBP_CR_PRINT_STATS(
        "Test cases",
        st_total_number_of_test_cases,
        st_number_of_test_cases,
        tcs_passed,
        tcs_failed,
        tcs_skipped);
    INTERNAL_NBP_CR_PRINT_STATS(
        "Test case instances",
        st_total_number_of_test_case_instances,
        st_number_of_test_case_instances,
        tcis_passed,
        tcis_failed,
        tcis_skipped);

    INTERNAL_NBP_CR_PRINT_STATS(
        "Test suites",
        st_total_number_of_test_suites,
        st_number_of_test_suites,
        tss_passed,
        tss_failed,
        tss_skipped);
    INTERNAL_NBP_CR_PRINT_STATS(
        "Test suite instances",
        st_total_number_of_test_suite_instances,
        st_number_of_test_suite_instances,
        tsis_passed,
        tsis_failed,
        tsis_skipped);

    INTERNAL_NBP_CR_PRINT_STATS(
        "Modules",
        st_total_number_of_modules,
        st_number_of_modules,
        ms_passed,
        ms_failed,
        ms_skipped);
    INTERNAL_NBP_CR_PRINT_STATS(
        "Module instances",
        st_total_number_of_module_instances,
        st_number_of_module_instances,
        mis_passed,
        mis_failed,
        mis_skipped);

    printf(
        "----------------------------------------------------------------------"
        "----------\n");

    INTERNAL_NBP_CR_MUTEX_UNLOCK(gInternalNbpCrMutex);

#undef INTERNAL_NBP_CR_PRINT_STATS
}

NBP_REPORTER(
    nbpConsoleReporter,
    NBP_REPORTER_CALLBACKS(
        NBP_REPORTER_CALLBACK_INIT(nbp_cr_init),
        NBP_REPORTER_CALLBACK_UNINIT(nbp_cr_uninit),
        NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(
            nbp_cr_handle_version_command),
        NBP_REPORTER_CALLBACK_ON_ERROR(nbp_cr_on_error),
        NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_cr_instantiate_test_case),
        NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(
            nbp_cr_instantiate_test_suite_started),
        NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(
            nbp_cr_instantiate_module_started),
        NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(nbp_cr_test_case_completed),
        NBP_REPORTER_CALLBACK_BEFORE_RUN(nbp_cr_before_run),
        NBP_REPORTER_CALLBACK_AFTER_RUN(nbp_cr_after_run)));

#undef NBP_CR_TEST_CASE_EMOJI
#undef NBP_CR_TEST_SUITE_EMOJI
#undef NBP_CR_MODULE_EMOJI

#undef NBP_CR_COLOR_NORMAL
#undef NBP_CR_COLOR_RED
#undef NBP_CR_COLOR_GREEN
#undef NBP_CR_COLOR_YELLOW

#undef NBP_CR_CLEAR_LINE

#endif // end if NBP_OS_LINUX

/*
 * Console reporter for Windows
 */
#ifdef NBP_OS_WINDOWS
#error "Not supported yet"
#endif // end if NBP_OS_WINDOWS

/*
 * Console reporter for Mac
 */
#ifdef NBP_OS_MAC
#error "Not supported yet"
#endif // end if NBP_OS_MAC

/*
 * We don't have console reporter for custom OS
 */
#ifdef NBP_OS_CUSTOM
#error "Console reporter is not supported on custom OS"
#endif // end if NBP_OS_CUSTOM

#endif // end if NBP_LIBRARY_MAIN

#endif // end if NBP_CONSOLE_REPORTER

/*
 * if custom runner is not used then use one of nbplib runners
 */
#ifndef NBP_CUSTOM_RUNNER

/**
 * TODO: add docs
 */
#ifdef NBP_MT_RUNNER
#error "Not supported yet"
#endif // end if NBP_MT_RUNNER

/**
 * TODO: add docs
 */
#ifdef NBP_BASIC_RUNNER
#ifdef NBP_LIBRARY_MAIN

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INIT(func) void nbp_runner_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_UNINIT(func) void nbp_runner_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_RUN(func) void nbp_runner_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(func)                        \
    void nbp_runner_callback_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)               \
    void nbp_runner_callback_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)             \
    void nbp_runner_callback_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                   \
    void nbp_runner_callback_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)                 \
    void nbp_runner_callback_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_RUNNER(name, ...)                                                  \
    void nbp_runner_interface_config_function_##name(                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_runner_interface_t* runnerInterface)    \
    {                                                                          \
        INTERNAL_NBP_GENERATE_RUNNER_CONFIG_FUNCTION(F_##__VA_ARGS__)          \
        return;                                                                \
    }                                                                          \
    nbp_runner_interface_t gInternalNbpRunnerInterface##name = {               \
        .runnerName             = #name,                                       \
        .configFunction         = nbp_runner_interface_config_function_##name, \
        .initCbk                = NBP_NULLPTR,                                 \
        .uninitCbk              = NBP_NULLPTR,                                 \
        .runCbk                 = NBP_NULLPTR,                                 \
        .instantiateTestCaseCbk = NBP_NULLPTR,                                 \
        .instantiateTestSuiteStartedCbk   = NBP_NULLPTR,                       \
        .instantiateTestSuiteCompletedCbk = NBP_NULLPTR,                       \
        .instantiateModuleStartedCbk      = NBP_NULLPTR,                       \
        .instantiateModuleCompletedCbk    = NBP_NULLPTR,                       \
    }

/**
 * TODO: add docs
 */
#define NBP_RUNNER_RUN_TEST_CASE_INSTANCE(testCaseInstance)                    \
    internal_nbp_runner_run_test_case_instance(testCaseInstance)

#define INTERNAL_NBP_GENERATE_RUNNER_CONFIG_FUNCTION(...)                      \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GRNC##__VA_ARGS__))    \
    (GRNCF_, GRNC##__VA_ARGS__)

#define INTERNAL_NBP_GRNCF_NBP_RUNNER_CALLBACKS(...)                           \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(RNC_##__VA_ARGS__))  \
    (RNC_, RNC_##__VA_ARGS__)

// This macro is generated when NBP_RUNNER macro is used without parameters
#define INTERNAL_NBP_GRNCF_

// This macro is generated when NBP_RUNNER_CALLBACKS macro is used without
// parameters
#define INTERNAL_NBP_RNC_

#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INIT(func)                        \
    NBP_RUNNER_CALLBACK_INIT(func);                                            \
    runnerInterface->initCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_UNINIT(func)                      \
    NBP_RUNNER_CALLBACK_UNINIT(func);                                          \
    runnerInterface->uninitCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_RUN(func)                         \
    NBP_RUNNER_CALLBACK_RUN(func);                                             \
    runnerInterface->runCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(func)       \
    NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(func);                           \
    runnerInterface->instantiateTestCaseCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(   \
    func)                                                                      \
    NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func);                  \
    runnerInterface->instantiateTestSuiteStartedCbk =                          \
        nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                      \
    NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func);                \
    runnerInterface->instantiateTestSuiteCompletedCbk =                        \
        nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)  \
    NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_STARTED(func);                      \
    runnerInterface->instantiateModuleStartedCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(     \
    func)                                                                      \
    NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func);                    \
    runnerInterface->instantiateModuleCompletedCbk = nbp_runner_callback_##func;

struct nbp_br_task_queue_t
{
    nbp_test_case_instance_t* testCaseInstance;
    struct nbp_br_task_queue_t* next;
};
typedef struct nbp_br_task_queue_t nbp_br_task_queue_t;

static nbp_br_task_queue_t* gInternalNbpBrFirstTask = NBP_NULLPTR;
static nbp_br_task_queue_t* gInternalNbpBrLastTask  = NBP_NULLPTR;

NBP_RUNNER_CALLBACK_UNINIT(nbp_br_uninit)
{
    nbp_br_task_queue_t* task = gInternalNbpBrFirstTask;
    nbp_br_task_queue_t* tmp  = NBP_NULLPTR;

    while (task != NBP_NULLPTR) {
        tmp  = task;
        task = task->next;

        NBP_MEMORY_FREE_TAG(tmp, mt_basic_runner);
    }
}

NBP_RUNNER_CALLBACK_RUN(nbp_br_run)
{
    nbp_br_task_queue_t* task = gInternalNbpBrFirstTask;
    while (task != NBP_NULLPTR) {
        NBP_RUNNER_RUN_TEST_CASE_INSTANCE(task->testCaseInstance);
        task = task->next;
    }
}

NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_br_instantiate_test_case)
{
    nbp_br_task_queue_t* task = (nbp_br_task_queue_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_br_task_queue_t),
        mt_basic_runner);

    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate basic runner task");
        NBP_EXIT(ec_out_of_memory);
    }

    task->testCaseInstance = NBP_THIS_TEST_CASE_INSTANCE;
    task->next             = NBP_NULLPTR;

    if (gInternalNbpBrFirstTask == NBP_NULLPTR) {
        gInternalNbpBrFirstTask = task;
        gInternalNbpBrLastTask  = task;
    } else {
        gInternalNbpBrLastTask->next = task;
        gInternalNbpBrLastTask       = task;
    }
}

NBP_RUNNER(
    nbpBasicRunner,
    NBP_RUNNER_CALLBACKS(
        NBP_RUNNER_CALLBACK_UNINIT(nbp_br_uninit),
        NBP_RUNNER_CALLBACK_RUN(nbp_br_run),
        NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_br_instantiate_test_case)));

#endif // end if NBP_LIBRARY_MAIN

#endif // end if NBP_BASIC_RUNNER

#endif // end if NBP_CUSTOM_RUNNER

#endif // end if _H_NBP_NBP

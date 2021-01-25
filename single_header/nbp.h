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

#define NBP_PP_PARSE_PARAMETER_1(parameter) NBP_PP_PARSE_##parameter
#define NBP_PP_PARSE_PARAMETER_2(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_1(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_3(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_2(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_4(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_3(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_5(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_4(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_6(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_5(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_7(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_6(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_8(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_7(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_9(parameter, ...)                               \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_8(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_10(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_9(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_11(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_10(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_12(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_11(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_13(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_12(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_14(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_13(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_15(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_14(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_16(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_15(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_17(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_16(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_18(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_17(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_19(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_18(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_20(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_19(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_21(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_20(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_22(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_21(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_23(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_22(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_24(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_23(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_25(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_24(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_26(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_25(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_27(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_26(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_28(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_27(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_29(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_28(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_30(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_29(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_31(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_30(PP_##__VA_ARGS__)
#define NBP_PP_PARSE_PARAMETER_32(parameter, ...)                              \
    NBP_PP_PARSE_##parameter NBP_PP_PARSE_PARAMETER_31(PP_##__VA_ARGS__)

#endif // end if _H_NBP_NBP

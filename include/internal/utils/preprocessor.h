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

#ifndef _H_NBP_INTERNAL_UTILS_PREPROCESSOR
#define _H_NBP_INTERNAL_UTILS_PREPROCESSOR

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

#endif // end if _H_NBP_INTERNAL_UTILS_PREPROCESSOR

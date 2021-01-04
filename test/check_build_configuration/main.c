/*
No Bugs in Production (NBP)
https://github.com/aenachescu/nbp

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

#include "nbp.h"

#include <stdio.h>

int main()
{
    // print operating system name
#ifdef NBP_OS_LINUX
    printf("linux ");
#elif defined NBP_OS_WINDOWS
    printf("windows ");
#elif defined NBP_OS_MAC
    printf("mac ");
#elif defined NBP_OS_CUSTOM
    printf("custom ");
#else
    printf("unknown ");
#endif // end if NBP_OS_LINUX

    // print compiler name and version
#ifdef NBP_COMPILER_GCC
    printf("gcc-");

#if NBP_COMPILER_VERSION == 5
    printf("5 ");
#elif NBP_COMPILER_VERSION == 6
    printf("6 ");
#elif NBP_COMPILER_VERSION == 7
    printf("7 ");
#elif NBP_COMPILER_VERSION == 8
    printf("8 ");
#elif NBP_COMPILER_VERSION == 9
    printf("9 ");
#else
    printf("unknown ");
#endif // end if NBP_COMPILER_VERSION

#elif defined NBP_COMPILER_GXX
    printf("g++-");

#if NBP_COMPILER_VERSION == 5
    printf("5 ");
#elif NBP_COMPILER_VERSION == 6
    printf("6 ");
#elif NBP_COMPILER_VERSION == 7
    printf("7 ");
#elif NBP_COMPILER_VERSION == 8
    printf("8 ");
#elif NBP_COMPILER_VERSION == 9
    printf("9 ");
#else
    printf("unknown ");
#endif // end if NBP_COMPILER_VERSION

#elif defined NBP_COMPILER_CLANG
    printf("clang-");
#elif defined NBP_COMPILER_CUSTOM
    printf("custom ");
#else
    printf("unknown ");
#endif // end if NBP_COMPILER_GCC

    // print standard
#ifdef NBP_LANGUAGE_STANDARD_C99
    printf("-std=c99 ");
#elif defined NBP_LANGUAGE_STANDARD_C11
    printf("-std=c11 ");
#elif defined NBP_LANGUAGE_STANDARD_CPP03
    printf("-std=c++03 ");
#elif defined NBP_LANGUAGE_STANDARD_CPP11
    printf("-std=c++11 ");
#elif defined NBP_LANGUAGE_STANDARD_CPP14
    printf("-std=c++14 ");
#elif defined NBP_LANGUAGE_STANDARD_CPP17
    printf("-std=c++17 ");
#else
    printf("unknown ");
#endif // end if NBP_LANGUAGE_STANDARD_C99

    // print platform
#ifdef NBP_PLATFORM_32BIT
    printf("-m32 ");
#elif defined NBP_PLATFORM_64BIT
    printf("-m64 ");
#else
    printf("unknown");
#endif // end if NBP_PLATFORM_32BIT

    // print sanitizer
#ifdef NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED
    printf("address ");
#elif defined NBP_TEST_MODE_THREAD_SANITIZER_ENABLED
    printf("thread ");
#elif defined NBP_TEST_MODE_LEAK_SANITIZER_ENABLED
    printf("leak ");
#elif defined NBP_TEST_MODE_UB_SANITIZER_ENABLED
    printf("ub ");
#endif // end if NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED

    printf("\n");

    return 0;
}

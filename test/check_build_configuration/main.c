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

#include "nbp.h"

#include <stdio.h>

int os              = 0;
int compiler        = 0;
int compilerVersion = 0;
int standard        = 0;
int platform        = 0;
int sanitizer       = 0;

void initialize_build_configuration()
{
#ifdef NBP_OS_LINUX
    os = 1;
#endif // end if NBP_OS_LINUX

#ifdef NBP_OS_WINDOWS
    os = 2;
#endif // end if NBP_OS_WINDOWS

#ifdef NBP_OS_MAC
    os = 3;
#endif // end if NBP_OS_MAC

#ifdef NBP_OS_CUSTOM
    os = 4;
#endif // end if NBP_OS_CUSTOM

#ifdef NBP_COMPILER_GCC
    compiler = 1;
#ifdef NBP_COMPILER_VERSION
    compilerVersion = NBP_COMPILER_VERSION;
#endif // end if NBP_COMPILER_VERSION
#endif // end if NBP_COMPILER_GCC

#ifdef NBP_COMPILER_GXX
    compiler = 2;
#ifdef NBP_COMPILER_VERSION
    compilerVersion = NBP_COMPILER_VERSION;
#endif // end if NBP_COMPILER_VERSION
#endif // end if NBP_COMPILER_GXX

#ifdef NBP_COMPILER_CLANG
    compiler = 3;
#endif // end if NBP_COMPILER_CLANG

#ifdef NBP_COMPILER_CUSTOM
    compiler = 4;
#endif // end if NBP_COMPILER_CUSTOM

#ifdef NBP_LANGUAGE_STANDARD_C99
    standard = 1;
#endif // end if NBP_LANGUAGE_STANDARD_C99

#ifdef NBP_LANGUAGE_STANDARD_C11
    standard = 2;
#endif // end if NBP_LANGUAGE_STANDARD_C11

#ifdef NBP_LANGUAGE_STANDARD_CPP03
    standard = 3;
#endif // end if NBP_LANGUAGE_STANDARD_CPP03

#ifdef NBP_LANGUAGE_STANDARD_CPP11
    standard = 4;
#endif // end if NBP_LANGUAGE_STANDARD_CPP11

#ifdef NBP_LANGUAGE_STANDARD_CPP14
    standard = 5;
#endif // end if NBP_LANGUAGE_STANDARD_CPP14

#ifdef NBP_LANGUAGE_STANDARD_CPP17
    standard = 6;
#endif // end if NBP_LANGUAGE_STANDARD_CPP17

#ifdef NBP_PLATFORM_32BIT
    platform = 1;
#endif // end if NBP_PLATFORM_32BIT

#ifdef NBP_PLATFORM_64BIT
    platform = 2;
#endif // end if NBP_PLATFORM_64BIT

#ifdef NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED
    sanitizer = 1;
#endif // end if NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_THREAD_SANITIZER_ENABLED
    sanitizer = 2;
#endif // end if NBP_TEST_MODE_THREAD_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_LEAK_SANITIZER_ENABLED
    sanitizer = 3;
#endif // end if NBP_TEST_MODE_LEAK_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_UB_SANITIZER_ENABLED
    sanitizer = 4;
#endif // end if NBP_TEST_MODE_UB_SANITIZER_ENABLED
}

int main()
{
    initialize_build_configuration();

    // print operating system name
    if (os == 1) {
        printf("linux ");
    } else if (os == 2) {
        printf("windows ");
    } else if (os == 3) {
        printf("mac ");
    } else if (os == 4) {
        printf("custom ");
    }

    // print compiler name and version
    if (compiler == 1) {
        printf("gcc-");
        if (compilerVersion == 5) {
            printf("5 ");
        } else if (compilerVersion == 6) {
            printf("6 ");
        } else if (compilerVersion == 7) {
            printf("7 ");
        } else if (compilerVersion == 8) {
            printf("8 ");
        } else if (compilerVersion == 9) {
            printf("9 ");
        }
    } else if (compiler == 2) {
        printf("g++-");
        if (compilerVersion == 5) {
            printf("5 ");
        } else if (compilerVersion == 6) {
            printf("6 ");
        } else if (compilerVersion == 7) {
            printf("7 ");
        } else if (compilerVersion == 8) {
            printf("8 ");
        } else if (compilerVersion == 9) {
            printf("9 ");
        }
    } else if (compiler == 3) {
        printf("clang-");
    } else if (compiler == 4) {
        printf("custom");
    }

    // print standard
    if (standard == 1) {
        printf("-std=c99 ");
    } else if (standard == 2) {
        printf("-std=c11 ");
    } else if (standard == 3) {
        printf("-std=c++03 ");
    } else if (standard == 4) {
        printf("-std=c++11 ");
    } else if (standard == 5) {
        printf("-std=c++14 ");
    } else if (standard == 6) {
        printf("-std=c++17 ");
    }

    // print platform
    if (platform == 1) {
        printf("-m32 ");
    } else if (platform == 2) {
        printf("-m64 ");
    }

    // print sanitizer
    if (sanitizer == 1) {
        printf("address ");
    } else if (sanitizer == 2) {
        printf("thread ");
    } else if (sanitizer == 3) {
        printf("leak ");
    } else if (sanitizer == 4) {
        printf("ub ");
    }

    printf("\n");

    return 0;
}

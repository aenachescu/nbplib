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

#define NBP_LIBRARY_MAIN
#include "nbp.h"

// test_utils.h must be included after nbp
#include "../test_utils.h"

#include <stdio.h>

int gOs              = 0;
int gCompiler        = 0;
int gCompilerVersion = 0;
int gStandard        = 0;
int gPlatform        = 0;
int gSanitizer       = 0;

void initialize_build_configuration()
{
#ifdef NBP_OS_LINUX
    gOs = 1;
#endif // end if NBP_OS_LINUX

#ifdef NBP_OS_WINDOWS
    gOs = 2;
#endif // end if NBP_OS_WINDOWS

#ifdef NBP_OS_MAC
    gOs = 3;
#endif // end if NBP_OS_MAC

#ifdef NBP_OS_CUSTOM
    gOs = 4;
#endif // end if NBP_OS_CUSTOM

#ifdef NBP_COMPILER_GCC
    gCompiler = 1;
#ifdef NBP_COMPILER_VERSION
    gCompilerVersion = NBP_COMPILER_VERSION;
#endif // end if NBP_COMPILER_VERSION
#endif // end if NBP_COMPILER_GCC

#ifdef NBP_COMPILER_GXX
    gCompiler = 2;
#ifdef NBP_COMPILER_VERSION
    gCompilerVersion = NBP_COMPILER_VERSION;
#endif // end if NBP_COMPILER_VERSION
#endif // end if NBP_COMPILER_GXX

#ifdef NBP_COMPILER_CLANG
    gCompiler = 3;
#endif // end if NBP_COMPILER_CLANG

#ifdef NBP_COMPILER_CUSTOM
    gCompiler = 4;
#endif // end if NBP_COMPILER_CUSTOM

#ifdef NBP_LANGUAGE_STANDARD_C99
    gStandard = 1;
#endif // end if NBP_LANGUAGE_STANDARD_C99

#ifdef NBP_LANGUAGE_STANDARD_C11
    gStandard = 2;
#endif // end if NBP_LANGUAGE_STANDARD_C11

#ifdef NBP_LANGUAGE_STANDARD_CPP03
    gStandard = 3;
#endif // end if NBP_LANGUAGE_STANDARD_CPP03

#ifdef NBP_LANGUAGE_STANDARD_CPP11
    gStandard = 4;
#endif // end if NBP_LANGUAGE_STANDARD_CPP11

#ifdef NBP_LANGUAGE_STANDARD_CPP14
    gStandard = 5;
#endif // end if NBP_LANGUAGE_STANDARD_CPP14

#ifdef NBP_LANGUAGE_STANDARD_CPP17
    gStandard = 6;
#endif // end if NBP_LANGUAGE_STANDARD_CPP17

#ifdef NBP_PLATFORM_32BIT
    gPlatform = 1;
#endif // end if NBP_PLATFORM_32BIT

#ifdef NBP_PLATFORM_64BIT
    gPlatform = 2;
#endif // end if NBP_PLATFORM_64BIT

#ifdef NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED
    gSanitizer = 1;
#endif // end if NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_THREAD_SANITIZER_ENABLED
    gSanitizer = 2;
#endif // end if NBP_TEST_MODE_THREAD_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_LEAK_SANITIZER_ENABLED
    gSanitizer = 3;
#endif // end if NBP_TEST_MODE_LEAK_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_UB_SANITIZER_ENABLED
    gSanitizer = 4;
#endif // end if NBP_TEST_MODE_UB_SANITIZER_ENABLED
}

int main()
{
    initialize_build_configuration();

    // print operating system name
    if (gOs == 1) {
        printf("linux ");
    } else if (gOs == 2) {
        printf("windows ");
    } else if (gOs == 3) {
        printf("mac ");
    } else if (gOs == 4) {
        printf("custom ");
    }

    // print gCompiler name and version
    if (gCompiler == 1) {
        printf("gcc-");
        if (gCompilerVersion == 5) {
            printf("5 ");
        } else if (gCompilerVersion == 6) {
            printf("6 ");
        } else if (gCompilerVersion == 7) {
            printf("7 ");
        } else if (gCompilerVersion == 8) {
            printf("8 ");
        } else if (gCompilerVersion == 9) {
            printf("9 ");
        }
    } else if (gCompiler == 2) {
        printf("g++-");
        if (gCompilerVersion == 5) {
            printf("5 ");
        } else if (gCompilerVersion == 6) {
            printf("6 ");
        } else if (gCompilerVersion == 7) {
            printf("7 ");
        } else if (gCompilerVersion == 8) {
            printf("8 ");
        } else if (gCompilerVersion == 9) {
            printf("9 ");
        }
    } else if (gCompiler == 3) {
        printf("clang-");
    } else if (gCompiler == 4) {
        printf("custom");
    }

    // print gStandard
    if (gStandard == 1) {
        printf("-std=c99 ");
    } else if (gStandard == 2) {
        printf("-std=c11 ");
    } else if (gStandard == 3) {
        printf("-std=c++03 ");
    } else if (gStandard == 4) {
        printf("-std=c++11 ");
    } else if (gStandard == 5) {
        printf("-std=c++14 ");
    } else if (gStandard == 6) {
        printf("-std=c++17 ");
    }

    // print gPlatform
    if (gPlatform == 1) {
        printf("-m32 ");
    } else if (gPlatform == 2) {
        printf("-m64 ");
    }

    // print gSanitizer
    if (gSanitizer == 1) {
        printf("address ");
    } else if (gSanitizer == 2) {
        printf("thread ");
    } else if (gSanitizer == 3) {
        printf("leak ");
    } else if (gSanitizer == 4) {
        printf("ub ");
    }

    printf("\n");

    return 0;
}

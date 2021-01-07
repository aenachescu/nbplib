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

#ifndef _H_TEST_ADDRESS_SANITIZER_OPTIONS
#define _H_TEST_ADDRESS_SANITIZER_OPTIONS

#ifdef NBP_LIBRARY_MAIN

#ifdef NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED

#ifdef NBP_LANGUAGE_CPP
extern "C" {
#endif // end if NBP_LANGUAGE_CPP

const char* __asan_default_options()
{
    return "detect_leaks=0";
}

#ifdef NBP_LANGUAGE_CPP
}
#endif // end if NBP_LANGUAGE_CPP

#endif // end if NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_THREAD_SANITIZER_ENABLED

#ifdef NBP_LANGUAGE_CPP
extern "C" {
#endif // end if NBP_LANGUAGE_CPP

const char* __tsan_default_options()
{
    return "halt_on_error=1";
}

#ifdef NBP_LANGUAGE_CPP
}
#endif // end if NBP_LANGUAGE_CPP

#endif // end if NBP_TEST_MODE_THREAD_SANITIZER_ENABLED

#endif // end if NBP_LIBRARY_MAIN

#endif // end if _H_TEST_ADDRESS_SANITIZER_OPTIONS

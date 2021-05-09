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

#ifndef _H_NBP_INTERNAL_REPORTERS_REPORTERS
#define _H_NBP_INTERNAL_REPORTERS_REPORTERS

#ifdef NBP_CONSOLE_REPORTER

#ifdef NBP_LIBRARY_MAIN

/*
 * Console reporter for Linux
 */
#ifdef NBP_OS_LINUX
#include "linux_console_reporter.h"
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

#endif // end if _H_NBP_INTERNAL_REPORTERS_REPORTERS

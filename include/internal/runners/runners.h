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

#ifndef _H_NBP_INTERNAL_RUNNERS_RUNNERS
#define _H_NBP_INTERNAL_RUNNERS_RUNNERS

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
#include "basic_runner.h"
#endif // end if NBP_BASIC_RUNNER

#endif // end if NBP_CUSTOM_RUNNER

#endif // end if _H_NBP_INTERNAL_RUNNERS_RUNNERS

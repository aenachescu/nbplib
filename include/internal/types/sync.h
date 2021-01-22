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

#ifndef _H_NBP_INTERNAL_TYPES_SYNC
#define _H_NBP_INTERNAL_TYPES_SYNC

#include "../build_configuration.h"
#include "../types/error.h"

#ifdef NBP_MT_SUPPORT

#ifdef NBP_OS_LINUX
#include "sync_linux.h"
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

#ifndef NBP_ATOMIC_UINT_ADD_AND_FETCH
#define NBP_ATOMIC_UINT_ADD_AND_FETCH(ptr, value) ((*(ptr)) += (value))
#endif // end if NBP_ATOMIC_UINT_ADD_AND_FETCH

#ifndef NBP_ATOMIC_UINT_CAS
#define NBP_ATOMIC_UINT_CAS(ptr, oldVal, newVal)                               \
    ((*(ptr)) == (oldVal) ? (*(ptr)) = (newVal), (oldVal) : (*(ptr)))
#endif // end if NBP_ATOMIC_UINT_CAS

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
 * Atomic unsigned int wrapper
 */

#define NBP_ATOMIC_UINT_TYPE unsigned int

#define NBP_ATOMIC_UINT_INIT(val) val

#define NBP_ATOMIC_UINT_LOAD(ptr) (*(ptr))

#define NBP_ATOMIC_UINT_ADD_AND_FETCH(ptr, value) ((*(ptr)) += (value))

#define NBP_ATOMIC_UINT_CAS(ptr, oldVal, newVal)                               \
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

#endif // end if _H_NBP_INTERNAL_TYPES_SYNC

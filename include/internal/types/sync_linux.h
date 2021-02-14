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

#ifndef _H_NBP_INTERNAL_TYPES_SYNC_LINUX
#define _H_NBP_INTERNAL_TYPES_SYNC_LINUX

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

#endif // end if _H_NBP_INTERNAL_TYPES_SYNC_LINUX

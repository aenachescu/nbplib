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

#ifndef _H_NBP_INTERNAL_IMPL_SYNC_LINUX
#define _H_NBP_INTERNAL_IMPL_SYNC_LINUX

#include "../details/sync_linux.h"

nbp_error_code_e internal_nbp_linux_sync_event_init(sem_t* event)
{
    if (sem_init(event, 0, 0) == 0) {
        return ec_success;
    }

    return ec_sync_error;
}

nbp_error_code_e internal_nbp_linux_sync_event_uninit(sem_t* event)
{
    if (sem_destroy(event) == 0) {
        return ec_success;
    }

    return ec_sync_error;
}

nbp_error_code_e internal_nbp_linux_sync_event_wait(sem_t* event)
{
    if (sem_wait(event) != 0) {
        return ec_sync_error;
    }
    if (sem_post(event) != 0) {
        return ec_sync_error;
    }

    return ec_success;
}

nbp_error_code_e internal_nbp_linux_sync_event_notify(sem_t* event)
{
    if (sem_post(event) == 0) {
        return ec_success;
    }

    return ec_sync_error;
}

#endif // end if _H_NBP_INTERNAL_IMPL_SYNC_LINUX

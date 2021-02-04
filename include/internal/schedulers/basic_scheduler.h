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

#ifndef _H_NBP_INTERNAL_SCHEDULERS_BASIC_SCHEDULER
#define _H_NBP_INTERNAL_SCHEDULERS_BASIC_SCHEDULER

#include "../api/scheduler.h"
#include "../api/test_case.h"

#include <stdio.h>

NBP_SCHEDULER_CALLBACK_INIT(nbp_bs_init)
{
    printf("basic scheduler init\n");
}

NBP_SCHEDULER_CALLBACK_UNINIT(nbp_bs_uninit)
{
    printf("basic scheduler uninit\n");
}

NBP_SCHEDULER_CALLBACK_RUN(nbp_bs_run)
{
    printf("basic scheduler run\n");
}

NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_bs_instantiate_test_case)
{
    printf(
        "instantiate test case [%s]\n",
        NBP_THIS_TEST_CASE_INSTANCE->testCaseDetails->name);
}

NBP_SCHEDULER(
    nbpBasicScheduler,
    NBP_SCHEDULER_CALLBACKS(
        NBP_SCHEDULER_CALLBACK_INIT(nbp_bs_init),
        NBP_SCHEDULER_CALLBACK_UNINIT(nbp_bs_uninit),
        NBP_SCHEDULER_CALLBACK_RUN(nbp_bs_run),
        NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_bs_instantiate_test_case)));

#endif // end if _H_NBP_INTERNAL_SCHEDULERS_BASIC_SCHEDULER
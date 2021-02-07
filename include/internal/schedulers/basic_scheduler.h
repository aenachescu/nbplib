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

#ifdef NBP_LIBRARY_MAIN

#include "../api/scheduler.h"
#include "../api/test_case.h"

struct nbp_bs_task_queue_t
{
    nbp_test_case_instance_t* testCaseInstance;
    struct nbp_bs_task_queue_t* next;
};
typedef struct nbp_bs_task_queue_t nbp_bs_task_queue_t;

static nbp_bs_task_queue_t* gInternalNbpBsFirstTask = NBP_NULLPTR;
static nbp_bs_task_queue_t* gInternalNbpBsLastTask  = NBP_NULLPTR;

NBP_SCHEDULER_CALLBACK_UNINIT(nbp_bs_uninit)
{
    nbp_bs_task_queue_t* task = gInternalNbpBsFirstTask;
    nbp_bs_task_queue_t* tmp  = NBP_NULLPTR;

    while (task != NBP_NULLPTR) {
        tmp  = task;
        task = task->next;

        NBP_MEMORY_FREE_TAG(tmp, mt_basic_scheduler);
    }
}

NBP_SCHEDULER_CALLBACK_RUN(nbp_bs_run)
{
    nbp_bs_task_queue_t* task = gInternalNbpBsFirstTask;
    while (task != NBP_NULLPTR) {
        NBP_SCHEDULER_RUN_TEST_CASE_INSTANCE(task->testCaseInstance);
        task = task->next;
    }
}

NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_bs_instantiate_test_case)
{
    nbp_bs_task_queue_t* task = (nbp_bs_task_queue_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_bs_task_queue_t),
        mt_basic_scheduler);

    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate basic scheduler task");
        NBP_EXIT(ec_out_of_memory);
    }

    task->testCaseInstance = NBP_THIS_TEST_CASE_INSTANCE;
    task->next             = NBP_NULLPTR;

    if (gInternalNbpBsFirstTask == NBP_NULLPTR) {
        gInternalNbpBsFirstTask = task;
        gInternalNbpBsLastTask  = task;
    } else {
        gInternalNbpBsLastTask->next = task;
        gInternalNbpBsLastTask       = task;
    }
}

NBP_SCHEDULER(
    nbpBasicScheduler,
    NBP_SCHEDULER_CALLBACKS(
        NBP_SCHEDULER_CALLBACK_UNINIT(nbp_bs_uninit),
        NBP_SCHEDULER_CALLBACK_RUN(nbp_bs_run),
        NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_bs_instantiate_test_case)));

#endif // end if NBP_LIBRARY_MAIN

#endif // end if _H_NBP_INTERNAL_SCHEDULERS_BASIC_SCHEDULER

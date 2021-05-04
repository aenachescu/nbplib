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

#ifndef _H_NBP_INTERNAL_RUNNERS_BASIC_RUNNER
#define _H_NBP_INTERNAL_RUNNERS_BASIC_RUNNER

#ifdef NBP_LIBRARY_MAIN

#include "../api/error.h"
#include "../api/exit.h"
#include "../api/runner.h"
#include "../api/test_case.h"

struct nbp_br_task_queue_t
{
    nbp_test_case_instance_t* testCaseInstance;
    struct nbp_br_task_queue_t* next;
};
typedef struct nbp_br_task_queue_t nbp_br_task_queue_t;

static nbp_br_task_queue_t* gInternalNbpBrFirstTask = NBP_NULLPTR;
static nbp_br_task_queue_t* gInternalNbpBrLastTask  = NBP_NULLPTR;

NBP_RUNNER_CALLBACK_UNINIT(nbp_br_uninit)
{
    nbp_br_task_queue_t* task = gInternalNbpBrFirstTask;
    nbp_br_task_queue_t* tmp  = NBP_NULLPTR;

    while (task != NBP_NULLPTR) {
        tmp  = task;
        task = task->next;

        NBP_MEMORY_FREE_TAG(tmp, mt_basic_runner);
    }
}

NBP_RUNNER_CALLBACK_RUN(nbp_br_run)
{
    nbp_br_task_queue_t* task = gInternalNbpBrFirstTask;
    while (task != NBP_NULLPTR) {
        NBP_RUNNER_RUN_TEST_CASE_INSTANCE(task->testCaseInstance);
        task = task->next;
    }
}

NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_br_instantiate_test_case)
{
    nbp_br_task_queue_t* task = (nbp_br_task_queue_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_br_task_queue_t),
        mt_basic_runner);

    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate basic runner task");
        NBP_EXIT(ec_out_of_memory);
    }

    task->testCaseInstance = NBP_THIS_TEST_CASE_INSTANCE;
    task->next             = NBP_NULLPTR;

    if (gInternalNbpBrFirstTask == NBP_NULLPTR) {
        gInternalNbpBrFirstTask = task;
        gInternalNbpBrLastTask  = task;
    } else {
        gInternalNbpBrLastTask->next = task;
        gInternalNbpBrLastTask       = task;
    }
}

NBP_RUNNER(
    nbpBasicRunner,
    NBP_RUNNER_CALLBACKS(
        NBP_RUNNER_CALLBACK_UNINIT(nbp_br_uninit),
        NBP_RUNNER_CALLBACK_RUN(nbp_br_run),
        NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_br_instantiate_test_case)));

#endif // end if NBP_LIBRARY_MAIN

#endif // end if _H_NBP_INTERNAL_RUNNERS_BASIC_RUNNER

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

#ifndef _H_NBP_INTERNAL_IMPL_SCHEDULER
#define _H_NBP_INTERNAL_IMPL_SCHEDULER

#include "../api/error.h"
#include "../api/exit.h"
#include "../details/scheduler.h"
#include "../types/sync.h"

extern int gInternalNbpSchedulerRunEnabled;

extern NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRanTestCases;

void internal_nbp_run_test_case(nbp_test_case_t* testCase)
{
    if (gInternalNbpSchedulerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_scheduler_run_is_disabled,
            "a test case can be run only from scheduler's run callback");
        NBP_EXIT(ec_scheduler_run_is_disabled);
        return;
    }

    testCase->testCaseInstance->testCaseDetails->function(testCase);

    NBP_ATOMIC_UINT_ADD_AND_FETCH(&gInternalNbpNumberOfRanTestCases, 1);
}

void internal_nbp_run_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance)
{
    if (gInternalNbpSchedulerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_scheduler_run_is_disabled,
            "a test case instance can be run only from scheduler's run "
            "callback");
        NBP_EXIT(ec_scheduler_run_is_disabled);
        return;
    }

    for (unsigned int i = 0; i < testCaseInstance->numberOfRuns; i++) {
        internal_nbp_run_test_case(&testCaseInstance->runs[i]);
    }
}

#endif // end if _H_NBP_INTERNAL_IMPL_SCHEDULER

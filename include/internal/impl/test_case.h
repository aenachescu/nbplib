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

#ifndef _H_NBP_INTERNAL_IMPL_TEST_CASE
#define _H_NBP_INTERNAL_IMPL_TEST_CASE

#include "../api/error.h"
#include "../api/exit.h"
#include "../api/memory.h"
#include "../details/printer_notifier.h"
#include "../details/scheduler_notifier.h"
#include "../details/test_case.h"

extern unsigned int gInternalNbpNumberOfTestCases;

nbp_test_case_instance_t* internal_nbp_instantiate_test_case(
    nbp_test_case_details_t* testCaseDetails,
    nbp_module_t* parentModule,
    nbp_test_suite_t* parentTestSuite,
    unsigned int numberOfRuns,
    void* context)
{
    if (numberOfRuns == 0) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_number_of_runs,
            "the number of runs must be greater than 0");
        NBP_EXIT(ec_invalid_number_of_runs);
        return NBP_NULLPTR;
    }

    if (parentModule != NBP_NULLPTR && parentTestSuite != NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "a test case instance must have one single parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    if (parentModule == NBP_NULLPTR && parentTestSuite == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "test case instance has no parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    nbp_test_case_instance_t* testCaseInstance =
        (nbp_test_case_instance_t*) NBP_MEMORY_ALLOC_TAG(
            sizeof(nbp_test_case_instance_t),
            mt_test_case_instance);

    if (testCaseInstance == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate test case instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    nbp_test_case_t* runs = (nbp_test_case_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_test_case_t),
        mt_test_case);

    if (runs == NBP_NULLPTR) {
        NBP_MEMORY_FREE_TAG(testCaseInstance, mt_test_case_instance);

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate the runs for test case instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    gInternalNbpNumberOfTestCases += numberOfRuns;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        runs[i].testCaseInstance = testCaseInstance;
        runs[i].state            = tcs_ready;
    }

    testCaseInstance->testCaseDetails = testCaseDetails;
    testCaseInstance->state           = tcis_ready;
    testCaseInstance->module          = parentModule;
    testCaseInstance->testSuite       = parentTestSuite;
    testCaseInstance->depth           = 0;
    testCaseInstance->setupDetails    = testCaseDetails->setupDetails;
    testCaseInstance->teardownDetails = testCaseDetails->teardownDetails;
    testCaseInstance->runs            = runs;
    testCaseInstance->numberOfRuns    = numberOfRuns;
    testCaseInstance->next            = NBP_NULLPTR;
    testCaseInstance->prev            = NBP_NULLPTR;

    if (parentModule != NBP_NULLPTR) {
        testCaseInstance->depth = parentModule->moduleInstance->depth + 1;

        if (parentModule->firstTestCaseInstance == NBP_NULLPTR) {
            parentModule->firstTestCaseInstance = testCaseInstance;
            parentModule->lastTestCaseInstance  = testCaseInstance;
        } else {
            testCaseInstance->prev = parentModule->lastTestCaseInstance;
            parentModule->lastTestCaseInstance->next = testCaseInstance;
            parentModule->lastTestCaseInstance       = testCaseInstance;
        }
    }

    if (parentTestSuite != NBP_NULLPTR) {
        testCaseInstance->depth = parentTestSuite->testSuiteInstance->depth + 1;

        if (parentTestSuite->firstTestCaseInstance == NBP_NULLPTR) {
            parentTestSuite->firstTestCaseInstance = testCaseInstance;
            parentTestSuite->lastTestCaseInstance  = testCaseInstance;
        } else {
            testCaseInstance->prev = parentTestSuite->lastTestCaseInstance;
            parentTestSuite->lastTestCaseInstance->next = testCaseInstance;
            parentTestSuite->lastTestCaseInstance       = testCaseInstance;
        }
    }

    internal_nbp_notify_printer_instantiate_test_case(testCaseInstance);
    internal_nbp_notify_scheduler_instantiate_test_case(
        testCaseInstance,
        context);

    return testCaseInstance;
}

#endif // end if _H_NBP_INTERNAL_IMPL_TEST_CASE

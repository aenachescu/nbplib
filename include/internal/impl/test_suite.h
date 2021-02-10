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

#ifndef _H_NBP_INTERNAL_IMPL_TEST_SUITE
#define _H_NBP_INTERNAL_IMPL_TEST_SUITE

#include "../api/error.h"
#include "../api/exit.h"
#include "../api/memory.h"
#include "../details/printer_notifier.h"
#include "../details/scheduler_notifier.h"
#include "../details/test_suite.h"

nbp_test_suite_instance_t* internal_nbp_instantiate_test_suite(
    nbp_test_suite_details_t* testSuiteDetails,
    nbp_module_t* parentModule,
    int instantiationLine,
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

    if (parentModule == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "test suite instance has no parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    nbp_test_suite_instance_t* testSuiteInstance =
        (nbp_test_suite_instance_t*) NBP_MEMORY_ALLOC_TAG(
            sizeof(nbp_test_suite_instance_t),
            mt_test_suite_instance);

    if (testSuiteInstance == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate test suite instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    nbp_test_suite_t* runs = (nbp_test_suite_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_test_suite_t),
        mt_test_suite);

    if (runs == NBP_NULLPTR) {
        NBP_MEMORY_FREE_TAG(testSuiteInstance, mt_test_suite);

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate the runs for test suite instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        runs[i].testSuiteInstance     = testSuiteInstance;
        runs[i].state                 = tss_ready;
        runs[i].firstTestCaseInstance = NBP_NULLPTR;
        runs[i].lastTestCaseInstance  = NBP_NULLPTR;
    }

    testSuiteInstance->testSuiteDetails  = testSuiteDetails;
    testSuiteInstance->state             = tsis_ready;
    testSuiteInstance->module            = parentModule;
    testSuiteInstance->instantiationLine = instantiationLine;
    testSuiteInstance->setupDetails      = testSuiteDetails->setupDetails;
    testSuiteInstance->teardownDetails   = testSuiteDetails->teardownDetails;
    testSuiteInstance->runs              = runs;
    testSuiteInstance->numberOfRuns      = numberOfRuns;
    testSuiteInstance->next              = NBP_NULLPTR;
    testSuiteInstance->prev              = NBP_NULLPTR;
    testSuiteInstance->depth = parentModule->moduleInstance->depth + 1;

    if (parentModule->firstTestSuiteInstance == NBP_NULLPTR) {
        parentModule->firstTestSuiteInstance = testSuiteInstance;
        parentModule->lastTestSuiteInstance  = testSuiteInstance;
    } else {
        testSuiteInstance->prev = parentModule->lastTestSuiteInstance;
        parentModule->lastTestSuiteInstance->next = testSuiteInstance;
        parentModule->lastTestSuiteInstance       = testSuiteInstance;
    }

    internal_nbp_notify_printer_instantiate_test_suite_started(
        testSuiteInstance);

    internal_nbp_notify_scheduler_instantiate_test_suite_started(
        testSuiteInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testSuiteInstance->testSuiteDetails->function(
            &testSuiteInstance->runs[i],
            &testSuiteInstance->runs[i],
            NBP_NULLPTR);
    }

    internal_nbp_notify_printer_instantiate_test_suite_completed(
        testSuiteInstance);

    internal_nbp_notify_scheduler_instantiate_test_suite_completed(
        testSuiteInstance);

    return testSuiteInstance;
}

#endif // end if _H_NBP_INTERNAL_IMPL_TEST_SUITE

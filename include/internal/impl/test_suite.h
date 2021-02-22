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
#include "../types/flags.h"

static void internal_nbp_increment_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tss_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tss_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e oldState,
    nbp_test_suite_state_e newState)
{
    internal_nbp_decrement_number_of_test_suites(statsArray, oldState, 1);
    internal_nbp_increment_number_of_test_suites(statsArray, newState, 1);
}

static void internal_nbp_increment_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tsis_ready);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state,
    unsigned int value)
{
    int pos = ((int) state) - ((int) tsis_ready);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e oldState,
    nbp_test_suite_instance_state_e newState)
{
    internal_nbp_decrement_number_of_test_suite_instances(
        statsArray,
        oldState,
        1);
    internal_nbp_increment_number_of_test_suite_instances(
        statsArray,
        newState,
        1);
}

static void internal_nbp_test_suite_instance_update_stats(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    nbp_module_t* parent            = testSuiteInstance->module;
    unsigned int numberOfTestSuites = testSuiteInstance->numberOfRuns;

    internal_nbp_increment_number_of_test_suites(
        testSuiteInstance->numberOfTestSuites,
        tss_ready,
        numberOfTestSuites);

    while (parent != NBP_NULLPTR) {
        parent->totalNumberOfTestSuiteInstances += 1;
        parent->totalNumberOfTestSuites += numberOfTestSuites;

        parent->moduleInstance->totalNumberOfTestSuiteInstances += 1;
        parent->moduleInstance->totalNumberOfTestSuites += numberOfTestSuites;

        internal_nbp_increment_number_of_test_suite_instances(
            parent->numberOfTestSuiteInstances,
            tsis_ready,
            1);
        internal_nbp_increment_number_of_test_suites(
            parent->numberOfTestSuites,
            tss_ready,
            numberOfTestSuites);

        internal_nbp_increment_number_of_test_suite_instances(
            parent->moduleInstance->numberOfTestSuiteInstances,
            tsis_ready,
            1);
        internal_nbp_increment_number_of_test_suites(
            parent->moduleInstance->numberOfTestSuites,
            tss_ready,
            numberOfTestSuites);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_test_suite_update_state_stats(
    nbp_test_suite_t* testSuite,
    nbp_test_suite_state_e oldState,
    nbp_test_suite_state_e newState)
{
    nbp_module_t* parent = testSuite->testSuiteInstance->module;

    internal_nbp_update_number_of_test_suites(
        testSuite->testSuiteInstance->numberOfTestSuites,
        oldState,
        newState);

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_suites(
            parent->numberOfTestSuites,
            oldState,
            newState);

        internal_nbp_update_number_of_test_suites(
            parent->moduleInstance->numberOfTestSuites,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_test_suite_instance_update_state_stats(
    nbp_test_suite_instance_t* testSuiteInstance,
    nbp_test_suite_instance_state_e oldState,
    nbp_test_suite_instance_state_e newState)
{
    nbp_module_t* parent = testSuiteInstance->module;

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_suite_instances(
            parent->numberOfTestSuiteInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_test_suite_instances(
            parent->moduleInstance->numberOfTestSuiteInstances,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state)
{
    int pos = ((int) state) - ((int) tss_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state)
{
    int pos = ((int) state) - ((int) tsis_ready);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

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
        runs[i].testSuiteInstance              = testSuiteInstance;
        runs[i].state                          = tss_ready;
        runs[i].firstTestCaseInstance          = NBP_NULLPTR;
        runs[i].lastTestCaseInstance           = NBP_NULLPTR;
        runs[i].totalNumberOfTestCases         = 0;
        runs[i].totalNumberOfTestCaseInstances = 0;

        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);

        unsigned int j;
        for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestCases[j], 0);
        }
        for (j = 0; j < NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES; j++) {
            NBP_ATOMIC_UINT_STORE(&runs[i].numberOfTestCaseInstances[j], 0);
        }
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
    testSuiteInstance->totalNumberOfTestCases         = 0;
    testSuiteInstance->totalNumberOfTestCaseInstances = 0;

    NBP_ATOMIC_INT_STORE(&testSuiteInstance->isSkipped, (int) sf_is_not_set);

    for (unsigned int i = 0; i < NBP_NUMBER_OF_TEST_CASE_STATES; i++) {
        NBP_ATOMIC_UINT_STORE(&testSuiteInstance->numberOfTestCases[i], 0U);
    }
    for (unsigned int i = 0; i < NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES; i++) {
        NBP_ATOMIC_UINT_STORE(
            &testSuiteInstance->numberOfTestCaseInstances[i],
            0U);
    }
    for (unsigned int i = 0; i < NBP_NUMBER_OF_TEST_SUITE_STATES; i++) {
        NBP_ATOMIC_UINT_STORE(&testSuiteInstance->numberOfTestSuites[i], 0U);
    }

    if (parentModule->firstTestSuiteInstance == NBP_NULLPTR) {
        parentModule->firstTestSuiteInstance = testSuiteInstance;
        parentModule->lastTestSuiteInstance  = testSuiteInstance;
    } else {
        testSuiteInstance->prev = parentModule->lastTestSuiteInstance;
        parentModule->lastTestSuiteInstance->next = testSuiteInstance;
        parentModule->lastTestSuiteInstance       = testSuiteInstance;
    }

    internal_nbp_test_suite_instance_update_stats(testSuiteInstance);

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

        if (testSuiteInstance->runs[i].totalNumberOfTestCaseInstances == 0) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_no_test_case_instantiated,
                "test suite has no test case");
            NBP_EXIT(ec_no_test_case_instantiated);
        }
    }

    internal_nbp_notify_printer_instantiate_test_suite_completed(
        testSuiteInstance);

    internal_nbp_notify_scheduler_instantiate_test_suite_completed(
        testSuiteInstance);

    return testSuiteInstance;
}

#endif // end if _H_NBP_INTERNAL_IMPL_TEST_SUITE

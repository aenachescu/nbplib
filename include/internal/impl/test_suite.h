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
#include "../details/runner_notifier.h"
#include "../details/test_suite.h"
#include "../details/utils.h"
#include "../types/flags.h"

static void internal_nbp_increment_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_test_suite_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suites(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_test_suite_state_position(state);
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
    unsigned int pos =
        internal_nbp_get_test_suite_instance_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state,
    unsigned int value)
{
    unsigned int pos =
        internal_nbp_get_test_suite_instance_state_position(state);
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

unsigned int internal_nbp_get_test_suite_state_position(
    nbp_test_suite_state_e state)
{
    if ((unsigned int) state < (unsigned int) tss_ready
        || (unsigned int) state > (unsigned int) tss_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test suite state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tss_ready);
}

unsigned int internal_nbp_get_test_suite_instance_state_position(
    nbp_test_suite_instance_state_e state)
{
    if ((unsigned int) state < (unsigned int) tsis_ready
        || (unsigned int) state > (unsigned int) tsis_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test suite instance state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tsis_ready);
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
    unsigned int pos = internal_nbp_get_test_suite_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_test_suite_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_suite_instance_state_e state)
{
    unsigned int pos =
        internal_nbp_get_test_suite_instance_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_test_suite_t* internal_nbp_get_test_suite_from_instance(
    nbp_test_suite_instance_t* testSuiteInstance,
    unsigned int runId)
{
    if (runId >= testSuiteInstance->numberOfRuns) {
        return NBP_NULLPTR;
    }
    return &testSuiteInstance->runs[runId];
}

nbp_test_suite_instance_t* internal_nbp_instantiate_test_suite(
    nbp_test_suite_details_t* testSuiteDetails,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    testSuiteDetails->configFunction(testSuiteDetails);

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
        numberOfRuns * sizeof(nbp_test_suite_t),
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
        runs[i].firstTestCaseInstance          = NBP_NULLPTR;
        runs[i].lastTestCaseInstance           = NBP_NULLPTR;
        runs[i].totalNumberOfTestCases         = 0;
        runs[i].totalNumberOfTestCaseInstances = 0;

        NBP_ATOMIC_INT_STORE(&runs[i].state, (int) tss_ready);
        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);
        NBP_ATOMIC_UINT_STORE(&runs[i].numberOfCompletedTasks, 0U);

        if (NBP_SYNC_EVENT_INIT(&runs[i].runEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init runEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        if (NBP_SYNC_EVENT_INIT(&runs[i].setupEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init setupEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCases,
            NBP_NUMBER_OF_TEST_CASE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCaseInstances,
            NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
            0U);
    }

    testSuiteInstance->testSuiteDetails  = testSuiteDetails;
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

    NBP_ATOMIC_INT_STORE(&testSuiteInstance->state, (int) tsis_ready);
    NBP_ATOMIC_INT_STORE(&testSuiteInstance->isSkipped, (int) sf_is_not_set);
    NBP_ATOMIC_UINT_STORE(&testSuiteInstance->numberOfCompletedRuns, 0U);

    internal_nbp_initialize_array_of_atomic_uint(
        testSuiteInstance->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        testSuiteInstance->numberOfTestCaseInstances,
        NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        testSuiteInstance->numberOfTestSuites,
        NBP_NUMBER_OF_TEST_SUITE_STATES,
        0U);

    parentModule->numberOfTasks += 1;

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

    internal_nbp_notify_runner_instantiate_test_suite_started(
        testSuiteInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testSuiteInstance->testSuiteDetails->function(
            &testSuiteInstance->runs[i],
            &testSuiteInstance->runs[i],
            NBP_NULLPTR,
            1);

        if (testSuiteInstance->runs[i].totalNumberOfTestCaseInstances == 0) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_no_test_case_instantiated,
                "test suite has no test case");
            NBP_EXIT(ec_no_test_case_instantiated);
        }
    }

    internal_nbp_notify_printer_instantiate_test_suite_completed(
        testSuiteInstance);

    internal_nbp_notify_runner_instantiate_test_suite_completed(
        testSuiteInstance);

    return testSuiteInstance;
}

#endif // end if _H_NBP_INTERNAL_IMPL_TEST_SUITE

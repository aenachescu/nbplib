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
#include "../details/runner_notifier.h"
#include "../details/test_case.h"
#include "../details/utils.h"
#include "../types/flags.h"

extern unsigned int gInternalNbpNumberOfTestCases;

static void internal_nbp_increment_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_test_case_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_test_case_state_position(state);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e oldState,
    nbp_test_case_state_e newState)
{
    internal_nbp_decrement_number_of_test_cases(statsArray, oldState, 1);
    internal_nbp_increment_number_of_test_cases(statsArray, newState, 1);
}

static void internal_nbp_increment_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state,
    unsigned int value)
{
    unsigned int pos =
        internal_nbp_get_test_case_instance_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state,
    unsigned int value)
{
    unsigned int pos =
        internal_nbp_get_test_case_instance_state_position(state);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e oldState,
    nbp_test_case_instance_state_e newState)
{
    internal_nbp_decrement_number_of_test_case_instances(
        statsArray,
        oldState,
        1);
    internal_nbp_increment_number_of_test_case_instances(
        statsArray,
        newState,
        1);
}

static void internal_nbp_test_case_instance_update_stats(
    nbp_test_case_instance_t* testCaseInstance)
{
    nbp_module_t* parent                         = testCaseInstance->module;
    nbp_test_suite_t* testSuite                  = testCaseInstance->testSuite;
    nbp_test_suite_instance_t* testSuiteInstance = NBP_NULLPTR;
    unsigned int numberOfTestCases = testCaseInstance->numberOfRuns;

    internal_nbp_increment_number_of_test_cases(
        testCaseInstance->numberOfTestCases,
        tcs_ready,
        numberOfTestCases);

    if (testSuite != NBP_NULLPTR) {
        testSuiteInstance = testSuite->testSuiteInstance;

        testSuite->totalNumberOfTestCaseInstances += 1;
        testSuite->totalNumberOfTestCases += numberOfTestCases;

        testSuiteInstance->totalNumberOfTestCaseInstances += 1;
        testSuiteInstance->totalNumberOfTestCases += numberOfTestCases;

        internal_nbp_increment_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            testSuite->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        internal_nbp_increment_number_of_test_case_instances(
            testSuiteInstance->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            testSuiteInstance->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        parent = testCaseInstance->testSuite->testSuiteInstance->module;
    }

    while (parent != NBP_NULLPTR) {
        parent->totalNumberOfTestCaseInstances += 1;
        parent->totalNumberOfTestCases += numberOfTestCases;

        parent->moduleInstance->totalNumberOfTestCaseInstances += 1;
        parent->moduleInstance->totalNumberOfTestCases += numberOfTestCases;

        internal_nbp_increment_number_of_test_case_instances(
            parent->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            parent->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        internal_nbp_increment_number_of_test_case_instances(
            parent->moduleInstance->numberOfTestCaseInstances,
            tcis_ready,
            1);
        internal_nbp_increment_number_of_test_cases(
            parent->moduleInstance->numberOfTestCases,
            tcs_ready,
            numberOfTestCases);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_test_case_state_position(
    nbp_test_case_state_e state)
{
    if ((unsigned int) state < (unsigned int) tcs_ready
        || (unsigned int) state > (unsigned int) tcs_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test case state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tcs_ready);
}

unsigned int internal_nbp_get_test_case_instance_state_position(
    nbp_test_case_instance_state_e state)
{
    if ((unsigned int) state < (unsigned int) tcis_ready
        || (unsigned int) state > (unsigned int) tcis_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid test case instance state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) tcis_ready);
}

int internal_nbp_is_failed_test_case(nbp_test_case_t* testCase)
{
    ((void) testCase);
    return 0;
}

void internal_nbp_test_case_update_state_stats(
    nbp_test_case_t* testCase,
    nbp_test_case_state_e oldState,
    nbp_test_case_state_e newState)
{
    nbp_module_t* parent        = testCase->testCaseInstance->module;
    nbp_test_suite_t* testSuite = testCase->testCaseInstance->testSuite;

    internal_nbp_update_number_of_test_cases(
        testCase->testCaseInstance->numberOfTestCases,
        oldState,
        newState);

    if (testSuite != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_cases(
            testSuite->numberOfTestCases,
            oldState,
            newState);

        internal_nbp_update_number_of_test_cases(
            testSuite->testSuiteInstance->numberOfTestCases,
            oldState,
            newState);

        parent = testSuite->testSuiteInstance->module;
    }

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_cases(
            parent->numberOfTestCases,
            oldState,
            newState);

        internal_nbp_update_number_of_test_cases(
            parent->moduleInstance->numberOfTestCases,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_test_case_instance_update_state_stats(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_test_case_instance_state_e oldState,
    nbp_test_case_instance_state_e newState)
{
    nbp_module_t* parent        = testCaseInstance->module;
    nbp_test_suite_t* testSuite = testCaseInstance->testSuite;

    if (testSuite != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_test_case_instances(
            testSuite->testSuiteInstance->numberOfTestCaseInstances,
            oldState,
            newState);

        parent = testSuite->testSuiteInstance->module;
    }

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_test_case_instances(
            parent->numberOfTestCaseInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_test_case_instances(
            parent->moduleInstance->numberOfTestCaseInstances,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state)
{
    unsigned int pos = internal_nbp_get_test_case_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state)
{
    unsigned int pos =
        internal_nbp_get_test_case_instance_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_test_case_t* internal_nbp_get_test_case_from_instance(
    nbp_test_case_instance_t* testCaseInstance,
    unsigned int runId)
{
    if (runId >= testCaseInstance->numberOfRuns) {
        return NBP_NULLPTR;
    }
    return &testCaseInstance->runs[runId];
}

nbp_test_case_instance_t* internal_nbp_instantiate_test_case(
    nbp_test_case_details_t* testCaseDetails,
    nbp_module_t* parentModule,
    nbp_test_suite_t* parentTestSuite,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    testCaseDetails->configFunction(testCaseDetails);

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

        NBP_ATOMIC_INT_STORE(&runs[i].state, (int) tcs_ready);
        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);
    }

    testCaseInstance->testCaseDetails   = testCaseDetails;
    testCaseInstance->module            = parentModule;
    testCaseInstance->testSuite         = parentTestSuite;
    testCaseInstance->depth             = 0;
    testCaseInstance->instantiationLine = instantiationLine;
    testCaseInstance->setupDetails      = testCaseDetails->setupDetails;
    testCaseInstance->teardownDetails   = testCaseDetails->teardownDetails;
    testCaseInstance->runs              = runs;
    testCaseInstance->numberOfRuns      = numberOfRuns;
    testCaseInstance->next              = NBP_NULLPTR;
    testCaseInstance->prev              = NBP_NULLPTR;

    NBP_ATOMIC_INT_STORE(&testCaseInstance->state, (int) tcis_ready);
    NBP_ATOMIC_INT_STORE(&testCaseInstance->isSkipped, (int) sf_is_not_set);
    NBP_ATOMIC_UINT_STORE(&testCaseInstance->numberOfCompletedRuns, 0U);

    internal_nbp_initialize_array_of_atomic_uint(
        testCaseInstance->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES,
        0U);

    if (parentModule != NBP_NULLPTR) {
        testCaseInstance->depth = parentModule->moduleInstance->depth + 1;

        parentModule->numberOfTasks += 1;

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

    internal_nbp_test_case_instance_update_stats(testCaseInstance);

    internal_nbp_notify_printer_instantiate_test_case(testCaseInstance);
    internal_nbp_notify_runner_instantiate_test_case(testCaseInstance, context);

    return testCaseInstance;
}

#endif // end if _H_NBP_INTERNAL_IMPL_TEST_CASE

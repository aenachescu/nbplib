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

#ifndef _H_NBP_INTERNAL_API_TEST_SUITE
#define _H_NBP_INTERNAL_API_TEST_SUITE

#include "../details/test_case.h"
#include "../details/test_suite.h"
#include "../types/test_suite.h"
#include "../utils/utils.h"
#include "memory.h"

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_SETUP(func)                                             \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_setup_details_t gInternalNbpTestSuiteSetupDetails##func = { \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_test_suite_setup_function_##func,                  \
    };                                                                         \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_TEARDOWN(func)                                          \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_teardown_details_t                                          \
        gInternalNbpTestSuiteTeardownDetails##func = {                         \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_suite_teardown_function_##func,           \
    };                                                                         \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE(func, ...)                                              \
    void nbp_test_suite_config_function_##func(                                \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_details_t* testSuiteDetails) \
    {                                                                          \
        if (testSuiteDetails->isConfigured == 1) {                             \
            return;                                                            \
        } else {                                                               \
            testSuiteDetails->isConfigured = 1;                                \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(F_##__VA_ARGS__)      \
    }                                                                          \
    void nbp_test_suite_function_##func(                                       \
        nbp_test_suite_t* nbpParamTestSuite,                                   \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        unsigned int nbpParamNumberOfRuns);                                    \
    nbp_test_suite_details_t gInternalNbpTestSuiteDetails##func = {            \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_test_suite_config_function_##func,              \
        .function        = nbp_test_suite_function_##func,                     \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    void nbp_test_suite_function_##func(                                       \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER unsigned int nbpParamNumberOfRuns)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_SETUP(func)                                     \
    extern nbp_test_suite_setup_details_t                                      \
        gInternalNbpTestSuiteSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_SETUP(func)                              \
    &gInternalNbpTestSuiteSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_TEARDOWN(func)                                  \
    extern nbp_test_suite_teardown_details_t                                   \
        gInternalNbpTestSuiteTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN(func)                           \
    &gInternalNbpTestSuiteTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE(func)                                           \
    extern nbp_test_suite_details_t gInternalNbpTestSuiteDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_DETAILS(func)                            \
    &gInternalNbpTestSuiteDetails##func

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_SUITE nbpParamTestSuite

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_SUITE_INSTANCE nbpParamTestSuiteInstance

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NAME(testSuiteInstance)                    \
    testSuiteInstance->testSuiteDetails->name

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_NAME(testSuite)                                     \
    NBP_TEST_SUITE_INSTANCE_GET_NAME(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_STATE(testSuiteInstance)                   \
    (nbp_test_suite_instance_state_e)                                          \
        NBP_ATOMIC_INT_LOAD(&(testSuiteInstance)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_STATE(testSuite)                                    \
    (nbp_test_suite_state_e) NBP_ATOMIC_INT_LOAD(&(testSuite)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(testSuiteInstance)          \
    testSuiteInstance->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TEST_SUITE(testSuiteInstance, runId)       \
    internal_nbp_get_test_suite_from_instance(testSuiteInstance, runId)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_DEPTH(testSuiteInstance)                   \
    testSuiteInstance->depth

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_DEPTH(testSuite)                                    \
    NBP_TEST_SUITE_INSTANCE_GET_DEPTH(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_INSTANCE(testSuite) testSuite->testSuiteInstance

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_MODULE(testSuiteInstance)                  \
    testSuiteInstance->module

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_MODULE(testSuite)                                   \
    NBP_TEST_SUITE_INSTANCE_GET_MODULE(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASES(                \
    testSuiteInstance)                                                         \
    testSuiteInstace->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_TEST_CASES(                      \
    testSuiteInstance,                                                         \
    state)                                                                     \
    internal_nbp_get_number_of_test_cases(                                     \
        testSuiteInstance->numberOfTestCases,                                  \
        state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(       \
    testSuiteInstance)                                                         \
    testSuiteInstace->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_TEST_CASE_INSTANCES(             \
    testSuiteInstance,                                                         \
    state)                                                                     \
    internal_nbp_get_number_of_test_case_instances(                            \
        testSuiteInstance->numberOfTestCaseInstances,                          \
        state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_SUITES(               \
    testSuiteInstance)                                                         \
    testSuiteInstace->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_TEST_SUITES(                     \
    testSuiteInstance,                                                         \
    state)                                                                     \
    internal_nbp_get_number_of_test_suites(                                    \
        testSuiteInstance->numberOfTestSuites,                                 \
        state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_TOTAL_NUMBER_OF_TEST_CASES(testSuite)               \
    testSuite->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_NUMBER_OF_TEST_CASES(testSuite, state)              \
    internal_nbp_get_number_of_test_cases(testSuite->numberOfTestCases, state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(testSuite)      \
    testSuite->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_NUMBER_OF_TEST_CASE_INSTANCES(testSuite, state)     \
    internal_nbp_get_number_of_test_case_instances(                            \
        testSuite->numberOfTestCaseInstances,                                  \
        state)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_TEST_SUITE(func, ...)                                  \
    NBP_INCLUDE_TEST_SUITE(func);                                              \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(TSPIO_##__VA_ARGS__))  \
    (TSPIO_, TSPIO_##__VA_ARGS__);                                             \
    internal_nbp_instantiate_test_suite(                                       \
        NBP_GET_POINTER_TO_TEST_SUITE_DETAILS(func),                           \
        nbpParamTsiParentModule,                                               \
        NBP_SOURCE_LINE,                                                       \
        nbpParamNumberOfRuns,                                                  \
        NBP_NULLPTR);                                                          \
    nbpParamNumberOfRuns = 1;

#define INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(...)                  \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GTSC##__VA_ARGS__))    \
    (GTSCF_, GTSC##__VA_ARGS__)

// This macro is generated when NBP_TEST_SUITE macro is used without parameters
#define INTERNAL_NBP_GTSCF_

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_NAME(newName)                        \
    testSuiteDetails->name = newName;

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(func)                          \
    NBP_INCLUDE_TEST_SUITE_SETUP(func);                                        \
    testSuiteDetails->setupDetails = NBP_GET_POINTER_TO_TEST_SUITE_SETUP(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(func)                       \
    NBP_INCLUDE_TEST_SUITE_TEARDOWN(func);                                     \
    testSuiteDetails->teardownDetails =                                        \
        NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_FIXTURES(setupFunc, teardownFunc)    \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(setupFunc)                         \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(teardownFunc)

// This macro is generated when NBP_INSTANTIATE_MODULE macro is used without
// parameters
#define INTERNAL_NBP_TSPIO_

#define INTERNAL_NBP_TSPIO_NBP_NUMBER_OF_RUNS(num) nbpParamNumberOfRuns = num;

#endif // end if _H_NBP_INTERNAL_API_TEST_SUITE

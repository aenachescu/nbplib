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

#ifndef _H_NBP_INTERNAL_API_TEST_CASE
#define _H_NBP_INTERNAL_API_TEST_CASE

#include "../details/test_case.h"
#include "../types/test_case.h"
#include "../utils/utils.h"
#include "memory.h"
#include "module.h"
#include "test_suite.h"

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_SETUP(func)                                              \
    void nbp_test_case_setup_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase);         \
    nbp_test_case_setup_function_t gInternalNbpTestCaseSetupFunction##func = { \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_test_case_setup_function_##func,                   \
    };                                                                         \
    void nbp_test_case_setup_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_TEARDOWN(func)                                           \
    void nbp_test_case_teardown_function_##func(                               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase);         \
    nbp_test_case_teardown_function_t                                          \
        gInternalNbpTestCaseTeardownFunction##func = {                         \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_case_teardown_function_##func,            \
    };                                                                         \
    void nbp_test_case_teardown_function_##func(                               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE(func, ...)                                               \
    void nbp_test_case_config_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_function_t* testCaseFunction) \
    {                                                                          \
        if (testCaseFunction->isConfigured == 1) {                             \
            return;                                                            \
        } else {                                                               \
            testCaseFunction->isConfigured = 1;                                \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(F_##__VA_ARGS__)       \
    }                                                                          \
    void nbp_test_case_function_##func(nbp_test_case_t* nbpParamTestCase);     \
    nbp_test_case_function_t gInternalNbpTestCaseFunction##func = {            \
        .name             = #func,                                             \
        .functionName     = #func,                                             \
        .file             = NBP_SOURCE_FILE,                                   \
        .line             = NBP_SOURCE_LINE,                                   \
        .isConfigured     = 0,                                                 \
        .configFunction   = nbp_test_case_config_function_##func,              \
        .function         = nbp_test_case_function_##func,                     \
        .setupFunction    = NBP_NULLPTR,                                       \
        .teardownFunction = NBP_NULLPTR,                                       \
    };                                                                         \
    void nbp_test_case_function_##func(                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_SETUP_FUNCTION(func)                             \
    extern nbp_test_case_setup_function_t                                      \
        gInternalNbpTestCaseSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_SETUP_FUNCTION(func)                      \
    &gInternalNbpTestCaseSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_TEARDOWN_FUNCTION(func)                          \
    extern nbp_test_case_teardown_function_t                                   \
        gInternalNbpTestCaseTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN_FUNCTION(func)                   \
    &gInternalNbpTestCaseTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_FUNCTION(func)                                   \
    extern nbp_test_case_function_t gInternalNbpTestCaseFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_FUNCTION(func)                            \
    &gInternalNbpTestCaseFunction##func

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_CASE nbpParamTestCase

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_CASE_INSTANCE nbpParamTestCaseInstance

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_NAME(testCase)                                       \
    NBP_TEST_CASE_INSTANCE_GET_NAME(testCase->testCaseInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_STATE(testCase)                                      \
    (nbp_test_case_state_e) NBP_ATOMIC_INT_LOAD(&(testCase)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_DEPTH(testCase)                                      \
    NBP_TEST_CASE_INSTANCE_GET_DEPTH(testCase->testCaseInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_STATISTICS(testCase, type, ...)                      \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TCGS_,                                                    \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testCase, INTERNAL_NBP_TCGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_GET_INSTANCE(testCase) testCase->testCaseInstance

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_NAME(testCaseInstance)                      \
    testCaseInstance->testCaseFunction->name

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_STATE(testCaseInstance)                     \
    (nbp_test_case_instance_state_e)                                           \
        NBP_ATOMIC_INT_LOAD(&(testCaseInstance)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_DEPTH(testCaseInstance)                     \
    testCaseInstance->depth

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_STATISTICS(testCaseInstance, type, ...)     \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TCIGS_,                                                   \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testCaseInstance, INTERNAL_NBP_TCIGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance)            \
    testCaseInstance->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_INSTANCE_GET_TEST_CASE(testCaseInstance, runId)          \
    internal_nbp_get_test_case_from_instance(testCaseInstance, runId)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_TEST_CASE(func, ...)                                   \
    NBP_INCLUDE_TEST_CASE_FUNCTION(func);                                      \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(TCPIO_##__VA_ARGS__))  \
    (TCPIO_, TCPIO_##__VA_ARGS__);                                             \
    internal_nbp_instantiate_test_case(                                        \
        NBP_GET_POINTER_TO_TEST_CASE_FUNCTION(func),                           \
        nbpParamTciParentModule,                                               \
        nbpParamTciParentTestSuite,                                            \
        NBP_SOURCE_LINE,                                                       \
        nbpParamNumberOfRuns,                                                  \
        NBP_NULLPTR);                                                          \
    nbpParamNumberOfRuns = 1;

#define INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(...)                   \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GTCC##__VA_ARGS__))    \
    (GTCCF_, GTCC##__VA_ARGS__)

// This macro is generated when NBP_TEST_CASE macro is used without
// parameters
#define INTERNAL_NBP_GTCCF_

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_NAME(newName)                         \
    testCaseFunction->name = newName;

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(func)                           \
    NBP_INCLUDE_TEST_CASE_SETUP_FUNCTION(func);                                \
    testCaseFunction->setupFunction =                                          \
        NBP_GET_POINTER_TO_TEST_CASE_SETUP_FUNCTION(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(func)                        \
    NBP_INCLUDE_TEST_CASE_TEARDOWN_FUNCTION(func);                             \
    testCaseFunction->teardownFunction =                                       \
        NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN_FUNCTION(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_FIXTURES(setupFunc, teardownFunc)     \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(setupFunc)                          \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(teardownFunc)

// This macro is generated when NBP_INSTANTIATE_TEST_CASE macro is used
// without parameters
#define INTERNAL_NBP_TCPIO_

#define INTERNAL_NBP_TCPIO_NBP_NUMBER_OF_RUNS(num) nbpParamNumberOfRuns = num;

// Helpers for NBP_TEST_CASE_GET_STATISTICS

#define INTERNAL_NBP_TCGS_PARAM_

// Helpers for NBP_TEST_CASE_INSTANCE_GET_STATISTICS

#define INTERNAL_NBP_TCIGS_PARAM_

#define INTERNAL_NBP_TCIGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_TCIGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_TCIGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_TCIGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_TCIGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_TCIGS_st_total_number_of_test_cases1(tci, unused)         \
    unused tci->numberOfRuns

#define INTERNAL_NBP_TCIGS_st_number_of_test_cases1(tci, state)                \
    internal_nbp_get_number_of_test_cases(tci->numberOfTestCases, state)

#endif // end if _H_NBP_INTERNAL_API_TEST_CASE

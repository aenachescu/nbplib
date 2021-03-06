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
    nbp_test_suite_setup_function_t gInternalNbpTestSuiteSetupFunction##func = \
        {                                                                      \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_suite_setup_function_##func,              \
    };                                                                         \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_TEARDOWN(func)                                          \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_teardown_function_t                                         \
        gInternalNbpTestSuiteTeardownFunction##func = {                        \
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
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_function_t*                  \
            testSuiteFunction)                                                 \
    {                                                                          \
        if (testSuiteFunction->isConfigured == 1) {                            \
            return;                                                            \
        } else {                                                               \
            testSuiteFunction->isConfigured = 1;                               \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(F_##__VA_ARGS__)      \
    }                                                                          \
    void nbp_test_suite_function_##func(                                       \
        nbp_test_suite_t* nbpParamTestSuite,                                   \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        unsigned int nbpParamNumberOfRuns);                                    \
    nbp_test_suite_function_t gInternalNbpTestSuiteFunction##func = {          \
        .name             = #func,                                             \
        .functionName     = #func,                                             \
        .file             = NBP_SOURCE_FILE,                                   \
        .line             = NBP_SOURCE_LINE,                                   \
        .isConfigured     = 0,                                                 \
        .configFunction   = nbp_test_suite_config_function_##func,             \
        .function         = nbp_test_suite_function_##func,                    \
        .setupFunction    = NBP_NULLPTR,                                       \
        .teardownFunction = NBP_NULLPTR,                                       \
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
#define NBP_INCLUDE_TEST_SUITE_SETUP_FUNCTION(func)                            \
    extern nbp_test_suite_setup_function_t                                     \
        gInternalNbpTestSuiteSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_SETUP_FUNCTION(func)                     \
    &gInternalNbpTestSuiteSetupFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_TEARDOWN_FUNCTION(func)                         \
    extern nbp_test_suite_teardown_function_t                                  \
        gInternalNbpTestSuiteTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN_FUNCTION(func)                  \
    &gInternalNbpTestSuiteTeardownFunction##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_FUNCTION(func)                                  \
    extern nbp_test_suite_function_t gInternalNbpTestSuiteFunction##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_FUNCTION(func)                           \
    &gInternalNbpTestSuiteFunction##func

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
#define NBP_TEST_SUITE_GET_NAME(testSuite)                                     \
    NBP_TEST_SUITE_INSTANCE_GET_NAME(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_STATE(testSuite)                                    \
    (nbp_test_suite_state_e) NBP_ATOMIC_INT_LOAD(&(testSuite)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_DEPTH(testSuite)                                    \
    NBP_TEST_SUITE_INSTANCE_GET_DEPTH(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_MODULE(testSuite)                                   \
    NBP_TEST_SUITE_INSTANCE_GET_MODULE(testSuite->testSuiteInstance)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_STATISTICS(testSuite, type, ...)                    \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TSGS_,                                                    \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testSuite, INTERNAL_NBP_TSGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_GET_INSTANCE(testSuite) testSuite->testSuiteInstance

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_NAME(testSuiteInstance)                    \
    testSuiteInstance->testSuiteFunction->name

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_STATE(testSuiteInstance)                   \
    (nbp_test_suite_instance_state_e)                                          \
        NBP_ATOMIC_INT_LOAD(&(testSuiteInstance)->state)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_DEPTH(testSuiteInstance)                   \
    testSuiteInstance->depth

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_MODULE(testSuiteInstance)                  \
    testSuiteInstance->module

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_INSTANCE_GET_STATISTICS(testSuiteInstance, type, ...)   \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_TSIGS_,                                                   \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (testSuiteInstance, INTERNAL_NBP_TSIGS_PARAM_##__VA_ARGS__)

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
#define NBP_INSTANTIATE_TEST_SUITE(func, ...)                                  \
    NBP_INCLUDE_TEST_SUITE_FUNCTION(func);                                     \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(TSPIO_##__VA_ARGS__))  \
    (TSPIO_, TSPIO_##__VA_ARGS__);                                             \
    internal_nbp_instantiate_test_suite(                                       \
        NBP_GET_POINTER_TO_TEST_SUITE_FUNCTION(func),                          \
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
    testSuiteFunction->name = newName;

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(func)                          \
    NBP_INCLUDE_TEST_SUITE_SETUP_FUNCTION(func);                               \
    testSuiteFunction->setupFunction =                                         \
        NBP_GET_POINTER_TO_TEST_SUITE_SETUP_FUNCTION(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(func)                       \
    NBP_INCLUDE_TEST_SUITE_TEARDOWN_FUNCTION(func);                            \
    testSuiteFunction->teardownFunction =                                      \
        NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN_FUNCTION(func);

#define INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_FIXTURES(setupFunc, teardownFunc)    \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_SETUP(setupFunc)                         \
    INTERNAL_NBP_GTSCF_NBP_TEST_SUITE_TEARDOWN(teardownFunc)

// This macro is generated when NBP_INSTANTIATE_MODULE macro is used without
// parameters
#define INTERNAL_NBP_TSPIO_

#define INTERNAL_NBP_TSPIO_NBP_NUMBER_OF_RUNS(num) nbpParamNumberOfRuns = num;

// Helpers for NBP_TEST_SUITE_GET_STATISTICS

#define INTERNAL_NBP_TSGS_PARAM_

#define INTERNAL_NBP_TSGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_TSGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_TSGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_TSGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_TSGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_TSGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_TSGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_TSGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_TSGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_TSGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_TSGS_st_total_number_of_test_cases1(ts, unused)           \
    unused ts->totalNumberOfTestCases
#define INTERNAL_NBP_TSGS_st_total_number_of_test_case_instances1(ts, unused)  \
    unused ts->totalNumberOfTestCaseInstances

#define INTERNAL_NBP_TSGS_st_number_of_test_cases1(ts, state)                  \
    internal_nbp_get_number_of_test_cases(ts->numberOfTestCases, state)
#define INTERNAL_NBP_TSGS_st_number_of_test_case_instances1(ts, state)         \
    internal_nbp_get_number_of_test_case_instances(                            \
        ts->numberOfTestCaseInstances,                                         \
        state)

// Helpers for NBP_TEST_SUITE_INSTANCE_GET_STATISTICS

#define INTERNAL_NBP_TSIGS_PARAM_

#define INTERNAL_NBP_TSIGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_TSIGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_TSIGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_TSIGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_TSIGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_TSIGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_TSIGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_TSIGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_TSIGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_TSIGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_TSIGS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_TSIGS_PARAM_tss_running tss_running
#define INTERNAL_NBP_TSIGS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_TSIGS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_TSIGS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_TSIGS_st_total_number_of_test_cases1(tsi, unused)         \
    unused tsi->totalNumberOfTestCases
#define INTERNAL_NBP_TSIGS_st_total_number_of_test_case_instances1(            \
    tsi,                                                                       \
    unused)                                                                    \
    unused tsi->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_TSIGS_st_total_number_of_test_suites1(tsi, unused)        \
    unused tsi->numberOfRuns

#define INTERNAL_NBP_TSIGS_st_number_of_test_cases1(tsi, state)                \
    internal_nbp_get_number_of_test_cases(tsi->numberOfTestCases, state)
#define INTERNAL_NBP_TSIGS_st_number_of_test_case_instances1(tsi, state)       \
    internal_nbp_get_number_of_test_case_instances(                            \
        tsi->numberOfTestCaseInstances,                                        \
        state)
#define INTERNAL_NBP_TSIGS_st_number_of_test_suites1(tsi, state)               \
    internal_nbp_get_number_of_test_suites(tsi->numberOfTestSuites, state)

#endif // end if _H_NBP_INTERNAL_API_TEST_SUITE

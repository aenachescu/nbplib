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

#ifndef _H_NBP_INTERNAL_API_REPORTER
#define _H_NBP_INTERNAL_API_REPORTER

#include "../types/reporter.h"
#include "../types/statistics.h"
#include "../utils/utils.h"
#include "memory.h"

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INIT(func)                                       \
    static void nbp_reporter_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_UNINIT(func)                                     \
    static void nbp_reporter_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(func)                     \
    static void nbp_reporter_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_ON_ERROR(func)                                   \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_t nbpParamError)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_ON_EXIT(func)                                    \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_code_e nbpParamErrorCode)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_BEFORE_RUN(func)                                 \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_reporter_statistics_t*                  \
            nbpParamStatistics)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_AFTER_RUN(func)                                  \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_reporter_statistics_t*                  \
            nbpParamStatistics)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(func)                      \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)             \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)           \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                 \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)               \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_STARTED(func)                          \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(func)                        \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)                 \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(func)               \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_STARTED(func)                         \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_COMPLETED(func)                       \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func)                \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(func)              \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_STARTED(func)                             \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_COMPLETED(func)                           \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_INSTANCE_STARTED(func)                    \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)                  \
    static void nbp_reporter_callback_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_REPORTER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_REPORTER(name, ...)                                                \
    void nbp_reporter_interface_config_function_##name(                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_reporter_interface_t*                   \
            reporterInterface)                                                 \
    {                                                                          \
        INTERNAL_NBP_GENERATE_REPORTER_CONFIG_FUNCTION(F_##__VA_ARGS__)        \
        return;                                                                \
    }                                                                          \
    nbp_reporter_interface_t gInternalNbpReporterInterface##name = {           \
        .reporterName   = #name,                                               \
        .configFunction = INTERNAL_NBP_GENERATE_REPORTER_INTERFACE_NAME(name), \
        .isInitialized  = 0,                                                   \
        .initCbk        = NBP_NULLPTR,                                         \
        .uninitCbk      = NBP_NULLPTR,                                         \
        .handleVersionCommandCbk          = NBP_NULLPTR,                       \
        .errorCbk                         = NBP_NULLPTR,                       \
        .exitCbk                          = NBP_NULLPTR,                       \
        .beforeRunCbk                     = NBP_NULLPTR,                       \
        .afterRunCbk                      = NBP_NULLPTR,                       \
        .instantiateTestCaseCbk           = NBP_NULLPTR,                       \
        .instantiateTestSuiteStartedCbk   = NBP_NULLPTR,                       \
        .instantiateTestSuiteCompletedCbk = NBP_NULLPTR,                       \
        .instantiateModuleStartedCbk      = NBP_NULLPTR,                       \
        .instantiateModuleCompletedCbk    = NBP_NULLPTR,                       \
        .testCaseStartedCbk               = NBP_NULLPTR,                       \
        .testCaseCompletedCbk             = NBP_NULLPTR,                       \
        .testCaseInstanceStartedCbk       = NBP_NULLPTR,                       \
        .testCaseInstanceCompletedCbk     = NBP_NULLPTR,                       \
        .testSuiteStartedCbk              = NBP_NULLPTR,                       \
        .testSuiteCompletedCbk            = NBP_NULLPTR,                       \
        .testSuiteInstanceStartedCbk      = NBP_NULLPTR,                       \
        .testSuiteInstanceCompletedCbk    = NBP_NULLPTR,                       \
        .moduleStartedCbk                 = NBP_NULLPTR,                       \
        .moduleCompletedCbk               = NBP_NULLPTR,                       \
        .moduleInstanceStartedCbk         = NBP_NULLPTR,                       \
        .moduleInstanceCompletedCbk       = NBP_NULLPTR,                       \
    }

/**
 * TODO: add docs
 */
#define NBP_THIS_ERROR nbpParamError

/**
 * TODO: add docs
 */
#define NBP_REPORTER_GET_STATISTICS(type, ...)                                 \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_RS_,                                                      \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (INTERNAL_NBP_RS_PARAM_##__VA_ARGS__)

#define INTERNAL_NBP_GENERATE_REPORTER_INTERFACE_NAME(name)                    \
    nbp_reporter_interface_config_function_##name

#define INTERNAL_NBP_GENERATE_REPORTER_CONFIG_FUNCTION(...)                    \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GRC##__VA_ARGS__))     \
    (GRCF_, GRC##__VA_ARGS__)

#define INTERNAL_NBP_GRCF_NBP_REPORTER_CALLBACKS(...)                          \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(R_##__VA_ARGS__))    \
    (R_, R_##__VA_ARGS__)

// This macro is generated when NBP_REPORTER macro is used without parameters
#define INTERNAL_NBP_GRCF_

// This macro is generated when NBP_REPORTER_CALLBACKS macro is used without
// parameters
#define INTERNAL_NBP_R_

#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INIT(func)                        \
    reporterInterface->initCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_UNINIT(func)                      \
    reporterInterface->uninitCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(func)      \
    reporterInterface->handleVersionCommandCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_ON_ERROR(func)                    \
    reporterInterface->errorCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_ON_EXIT(func)                     \
    reporterInterface->exitCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_BEFORE_RUN(func)                  \
    reporterInterface->beforeRunCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_AFTER_RUN(func)                   \
    reporterInterface->afterRunCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(func)       \
    reporterInterface->instantiateTestCaseCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(   \
    func)                                                                      \
    reporterInterface->instantiateTestSuiteStartedCbk =                        \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                      \
    reporterInterface->instantiateTestSuiteCompletedCbk =                      \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)  \
    reporterInterface->instantiateModuleStartedCbk =                           \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(     \
    func)                                                                      \
    reporterInterface->instantiateModuleCompletedCbk =                         \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_STARTED(func)           \
    reporterInterface->testCaseStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(func)         \
    reporterInterface->testCaseCompletedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)  \
    reporterInterface->testCaseInstanceStartedCbk =                            \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(     \
    func)                                                                      \
    reporterInterface->testCaseInstanceCompletedCbk =                          \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_STARTED(func)          \
    reporterInterface->testSuiteStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_COMPLETED(func)        \
    reporterInterface->testSuiteCompletedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func) \
    reporterInterface->testSuiteInstanceStartedCbk =                           \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(    \
    func)                                                                      \
    reporterInterface->testSuiteInstanceCompletedCbk =                         \
        nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_STARTED(func)              \
    reporterInterface->moduleStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_COMPLETED(func)            \
    reporterInterface->moduleCompletedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_INSTANCE_STARTED(func)     \
    reporterInterface->moduleInstanceStartedCbk = nbp_reporter_callback_##func;
#define INTERNAL_NBP_R_NBP_REPORTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)   \
    reporterInterface->moduleInstanceCompletedCbk =                            \
        nbp_reporter_callback_##func;

#define INTERNAL_NBP_RS_PARAM_

#define INTERNAL_NBP_RS_st_total_number_of_test_cases1(unused)                 \
    unused nbpParamStatistics->totalNumberOfTestCases
#define INTERNAL_NBP_RS_st_total_number_of_test_case_instances1(unused)        \
    unused nbpParamStatistics->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_RS_st_total_number_of_test_suites1(unused)                \
    unused nbpParamStatistics->totalNumberOfTestSuites
#define INTERNAL_NBP_RS_st_total_number_of_test_suite_instances1(unused)       \
    unused nbpParamStatistics->totalNumberOfTestSuiteInstances
#define INTERNAL_NBP_RS_st_total_number_of_modules1(unused)                    \
    unused nbpParamStatistics->totalNumberOfModules
#define INTERNAL_NBP_RS_st_total_number_of_module_instances1(unused)           \
    unused nbpParamStatistics->totalNumberOfModuleInstances

#define INTERNAL_NBP_RS_st_number_of_test_cases1(state)                        \
    nbpParamStatistics                                                         \
        ->numberOfTestCases[internal_nbp_get_test_case_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_test_case_instances1(state)               \
    nbpParamStatistics->numberOfTestCaseInstances                              \
        [internal_nbp_get_test_case_instance_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_test_suites1(state)                       \
    nbpParamStatistics                                                         \
        ->numberOfTestSuites[internal_nbp_get_test_suite_state_position(       \
            state)]
#define INTERNAL_NBP_RS_st_number_of_test_suite_instances1(state)              \
    nbpParamStatistics->numberOfTestSuiteInstances                             \
        [internal_nbp_get_test_suite_instance_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_modules1(state)                           \
    nbpParamStatistics                                                         \
        ->numberOfModules[internal_nbp_get_module_state_position(state)]
#define INTERNAL_NBP_RS_st_number_of_module_instances1(state)                  \
    nbpParamStatistics->numberOfModuleInstances                                \
        [internal_nbp_get_module_instance_state_position(state)]

#define INTERNAL_NBP_RS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_RS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_RS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_RS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_RS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_RS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_RS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_RS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_RS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_RS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_RS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_RS_PARAM_tss_running tss_running
#define INTERNAL_NBP_RS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_RS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_RS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_RS_PARAM_tsis_ready   tsis_ready
#define INTERNAL_NBP_RS_PARAM_tsis_running tsis_running
#define INTERNAL_NBP_RS_PARAM_tsis_passed  tsis_passed
#define INTERNAL_NBP_RS_PARAM_tsis_failed  tsis_failed
#define INTERNAL_NBP_RS_PARAM_tsis_skipped tsis_skipped

#define INTERNAL_NBP_RS_PARAM_ms_ready   ms_ready
#define INTERNAL_NBP_RS_PARAM_ms_running ms_running
#define INTERNAL_NBP_RS_PARAM_ms_passed  ms_passed
#define INTERNAL_NBP_RS_PARAM_ms_failed  ms_failed
#define INTERNAL_NBP_RS_PARAM_ms_skipped ms_skipped

#define INTERNAL_NBP_RS_PARAM_mis_ready   mis_ready
#define INTERNAL_NBP_RS_PARAM_mis_running mis_running
#define INTERNAL_NBP_RS_PARAM_mis_passed  mis_passed
#define INTERNAL_NBP_RS_PARAM_mis_failed  mis_failed
#define INTERNAL_NBP_RS_PARAM_mis_skipped mis_skipped

#endif // end if _H_NBP_INTERNAL_API_REPORTER

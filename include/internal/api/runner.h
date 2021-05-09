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

#ifndef _H_NBP_INTERNAL_API_RUNNER
#define _H_NBP_INTERNAL_API_RUNNER

#include "../details/runner.h"
#include "../types/runner.h"
#include "../utils/utils.h"
#include "memory.h"

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INIT(func) static void nbp_runner_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_UNINIT(func)                                       \
    static void nbp_runner_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_RUN(func) static void nbp_runner_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(func)                        \
    static void nbp_runner_callback_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)               \
    static void nbp_runner_callback_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)             \
    static void nbp_runner_callback_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                   \
    static void nbp_runner_callback_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)                 \
    static void nbp_runner_callback_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_RUNNER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_RUNNER(name, ...)                                                  \
    void nbp_runner_interface_config_function_##name(                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_runner_interface_t* runnerInterface)    \
    {                                                                          \
        INTERNAL_NBP_GENERATE_RUNNER_CONFIG_FUNCTION(F_##__VA_ARGS__)          \
        return;                                                                \
    }                                                                          \
    nbp_runner_interface_t gInternalNbpRunnerInterface##name = {               \
        .runnerName             = #name,                                       \
        .configFunction         = nbp_runner_interface_config_function_##name, \
        .initCbk                = NBP_NULLPTR,                                 \
        .uninitCbk              = NBP_NULLPTR,                                 \
        .runCbk                 = NBP_NULLPTR,                                 \
        .instantiateTestCaseCbk = NBP_NULLPTR,                                 \
        .instantiateTestSuiteStartedCbk   = NBP_NULLPTR,                       \
        .instantiateTestSuiteCompletedCbk = NBP_NULLPTR,                       \
        .instantiateModuleStartedCbk      = NBP_NULLPTR,                       \
        .instantiateModuleCompletedCbk    = NBP_NULLPTR,                       \
    }

/**
 * TODO: add docs
 */
#define NBP_RUNNER_RUN_TEST_CASE_INSTANCE(testCaseInstance)                    \
    internal_nbp_runner_run_test_case_instance(testCaseInstance)

#define INTERNAL_NBP_GENERATE_RUNNER_CONFIG_FUNCTION(...)                      \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GRNC##__VA_ARGS__))    \
    (GRNCF_, GRNC##__VA_ARGS__)

#define INTERNAL_NBP_GRNCF_NBP_RUNNER_CALLBACKS(...)                           \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(RNC_##__VA_ARGS__))  \
    (RNC_, RNC_##__VA_ARGS__)

// This macro is generated when NBP_RUNNER macro is used without parameters
#define INTERNAL_NBP_GRNCF_

// This macro is generated when NBP_RUNNER_CALLBACKS macro is used without
// parameters
#define INTERNAL_NBP_RNC_

#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INIT(func)                        \
    runnerInterface->initCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_UNINIT(func)                      \
    runnerInterface->uninitCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_RUN(func)                         \
    runnerInterface->runCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_CASE(func)       \
    runnerInterface->instantiateTestCaseCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(   \
    func)                                                                      \
    runnerInterface->instantiateTestSuiteStartedCbk =                          \
        nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                      \
    runnerInterface->instantiateTestSuiteCompletedCbk =                        \
        nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)  \
    runnerInterface->instantiateModuleStartedCbk = nbp_runner_callback_##func;
#define INTERNAL_NBP_RNC_NBP_RUNNER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(     \
    func)                                                                      \
    runnerInterface->instantiateModuleCompletedCbk = nbp_runner_callback_##func;

#endif // end if _H_NBP_INTERNAL_API_RUNNER

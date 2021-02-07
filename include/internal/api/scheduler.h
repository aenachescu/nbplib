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

#ifndef _H_NBP_INTERNAL_API_SCHEDULER
#define _H_NBP_INTERNAL_API_SCHEDULER

#include "../details/scheduler.h"
#include "../types/scheduler.h"
#include "../utils/utils.h"
#include "memory.h"

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INIT(func)                                      \
    static void nbp_scheduler_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_UNINIT(func)                                    \
    static void nbp_scheduler_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_RUN(func)                                       \
    static void nbp_scheduler_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(func)                     \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)            \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)          \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER void* nbpParamContext)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)              \
    static void nbp_scheduler_callback_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER(name, ...)                                               \
    void nbp_scheduler_interface_config_function_##name(                       \
        NBP_MAYBE_UNUSED_PARAMETER nbp_scheduler_interface_t*                  \
            schedulerInterface)                                                \
    {                                                                          \
        INTERNAL_NBP_GENERATE_SCHEDULER_CONFIG_FUNCTION(F_##__VA_ARGS__)       \
        return;                                                                \
    }                                                                          \
    nbp_scheduler_interface_t gInternalNbpSchedulerInterface##name = {         \
        .schedulerName  = #name,                                               \
        .configFunction = nbp_scheduler_interface_config_function_##name,      \
        .initCbk        = NBP_NULLPTR,                                         \
        .uninitCbk      = NBP_NULLPTR,                                         \
        .runCbk         = NBP_NULLPTR,                                         \
        .instantiateTestCaseCbk           = NBP_NULLPTR,                       \
        .instantiateTestSuiteStartedCbk   = NBP_NULLPTR,                       \
        .instantiateTestSuiteCompletedCbk = NBP_NULLPTR,                       \
        .instantiateModuleStartedCbk      = NBP_NULLPTR,                       \
        .instantiateModuleCompletedCbk    = NBP_NULLPTR,                       \
    }

/**
 * TODO: add docs
 */
#define NBP_SCHEDULER_RUN_TEST_CASE_INSTANCE(testCaseInstance)                 \
    internal_nbp_run_test_case_instance(testCaseInstance)

#define INTERNAL_NBP_GENERATE_SCHEDULER_CONFIG_FUNCTION(...)                   \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GSC##__VA_ARGS__))     \
    (GSCF_, GSC##__VA_ARGS__)

#define INTERNAL_NBP_GSCF_NBP_SCHEDULER_CALLBACKS(...)                         \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(SC_##__VA_ARGS__))   \
    (SC_, SC_##__VA_ARGS__)

// This macro is generated when NBP_SCHEDULER macro is used without parameters
#define INTERNAL_NBP_GSCF_

// This macro is generated when NBP_SCHEDULER_CALLBACKS macro is used without
// parameters
#define INTERNAL_NBP_SC_

#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INIT(func)                      \
    schedulerInterface->initCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_UNINIT(func)                    \
    schedulerInterface->uninitCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_RUN(func)                       \
    schedulerInterface->runCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_CASE(func)     \
    schedulerInterface->instantiateTestCaseCbk = nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED( \
    func)                                                                      \
    schedulerInterface->instantiateTestSuiteStartedCbk =                       \
        nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                        \
    schedulerInterface->instantiateTestSuiteCompletedCbk =                       \
        nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_STARTED(     \
    func)                                                                      \
    schedulerInterface->instantiateModuleStartedCbk =                          \
        nbp_scheduler_callback_##func;
#define INTERNAL_NBP_SC_NBP_SCHEDULER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(   \
    func)                                                                      \
    schedulerInterface->instantiateModuleCompletedCbk =                        \
        nbp_scheduler_callback_##func;

#endif // end if _H_NBP_INTERNAL_API_SCHEDULER

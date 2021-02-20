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

#ifndef _H_NBP_INTERNAL_API_MODULE
#define _H_NBP_INTERNAL_API_MODULE

#include "../details/module.h"
#include "../details/test_case.h"
#include "../details/test_suite.h"
#include "../types/module.h"
#include "../utils/utils.h"
#include "memory.h"

/**
 * TODO: add docs
 */
#define NBP_MODULE_SETUP(func)                                                 \
    void nbp_module_setup_function_##func(                                     \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule);              \
    nbp_module_setup_details_t gInternalNbpModuleSetupDetails##func = {        \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_module_setup_function_##func,                      \
    };                                                                         \
    void nbp_module_setup_function_##func(                                     \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_MODULE_TEARDOWN(func)                                              \
    void nbp_module_teardown_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule);              \
    nbp_module_teardown_details_t gInternalNbpModuleTeardownDetails##func = {  \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_module_teardown_function_##func,                   \
    };                                                                         \
    void nbp_module_teardown_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_MODULE(func, ...)                                                  \
    void nbp_module_config_function_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_details_t* moduleDetails)        \
    {                                                                          \
        if (moduleDetails->isConfigured == 1) {                                \
            return;                                                            \
        } else {                                                               \
            moduleDetails->isConfigured = 1;                                   \
        }                                                                      \
        INTERNAL_NBP_GENERATE_MODULE_CONFIG_FUNCTION(F_##__VA_ARGS__)          \
    }                                                                          \
    void nbp_module_function_##func(                                           \
        nbp_module_t* nbpParamModule,                                          \
        nbp_test_suite_t* nbpParamTciParentTestSuite,                          \
        nbp_module_t* nbpParamTciParentModule,                                 \
        nbp_module_t* nbpParamTsiParentModule,                                 \
        nbp_module_t* nbpParamMiParentModule);                                 \
    nbp_module_details_t gInternalNbpModuleDetails##func = {                   \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_module_config_function_##func,                  \
        .function        = nbp_module_function_##func,                         \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    void nbp_module_function_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t*                           \
            nbpParamTciParentTestSuite,                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTciParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamTsiParentModule,      \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamMiParentModule)

/**
 * TODO: add docs
 */
#define NBP_MODULE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_MODULE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE_SETUP(func)                                         \
    extern nbp_module_setup_details_t gInternalNbpModuleSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_SETUP(func)                                  \
    &gInternalNbpModuleSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE_TEARDOWN(func)                                      \
    extern nbp_module_teardown_details_t gInternalNbpModuleTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_TEARDOWN(func)                               \
    &gInternalNbpModuleTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_MODULE(func)                                               \
    extern nbp_module_details_t gInternalNbpModuleDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_MODULE_DETAILS(func) &gInternalNbpModuleDetails##func

/**
 * TODO: add docs
 */
#define NBP_THIS_MODULE nbpParamModule

/**
 * TODO: add docs
 */
#define NBP_THIS_MODULE_INSTANCE nbpParamModuleInstance

/**
 * TODO: add docs
 */
#define NBP_GET_MODULE_INSTANCE_NAME(moduleInstance)                           \
    moduleInstance->moduleDetails->name

/**
 * TODO: add docs
 */
#define NBP_GET_MODULE_NAME(module)                                            \
    NBP_GET_MODULE_INSTANCE_NAME(module->moduleInstance)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASES(moduleInstance)     \
    moduleInstance->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_CASES(moduleInstance, state)    \
    internal_nbp_get_number_of_test_cases(                                     \
        moduleInstance->numberOfTestCases,                                     \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(           \
    moduleInstance)                                                            \
    moduleInstance->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_CASE_INSTANCES(                 \
    moduleInstance,                                                            \
    state)                                                                     \
    internal_nbp_get_number_of_test_case_instances(                            \
        moduleInstance->numberOfTestCaseInstances,                             \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_SUITES(moduleInstance)    \
    moduleInstance->totalNumberOfTestSuites

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_SUITES(moduleInstance, state)   \
    internal_nbp_get_number_of_test_suites(                                    \
        moduleInstance->numberOfTestSuites,                                    \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_TEST_SUITE_INSTANCES(          \
    moduleInstance)                                                            \
    moduleInstance->totalNumberOfTestSuiteInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_TEST_SUITE_INSTANCES(                \
    moduleInstance,                                                            \
    state)                                                                     \
    internal_nbp_get_number_of_test_suite_instances(                           \
        moduleInstance->numberOfTestSuiteInstances,                            \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_MODULES(moduleInstance)        \
    moduleInstance->totalNumberOfModules

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_MODULES(moduleInstance, state)       \
    internal_nbp_get_number_of_modules(moduleInstance->numberOfModules, state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_TOTAL_NUMBER_OF_MODULE_INSTANCES(              \
    moduleInstance)                                                            \
    moduleInstance->totalNumberOfModuleInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_MODULE_INSTANCES(                    \
    moduleInstance,                                                            \
    state)                                                                     \
    internal_nbp_get_number_of_module_instances(                               \
        moduleInstance->numberOfModuleInstances,                               \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_CASES(module)                      \
    module->totalNumberOfTestCases

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_CASES(module, state)                     \
    internal_nbp_get_number_of_test_cases(module->numberOfTestCases, state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_CASE_INSTANCES(module)             \
    module->totalNumberOfTestCaseInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_CASE_INSTANCES(module, state)            \
    internal_nbp_get_number_of_test_case_instances(                            \
        module->numberOfTestCaseInstances,                                     \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_SUITES(module)                     \
    module->totalNumberOfTestSuites

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_SUITES(module, state)                    \
    internal_nbp_get_number_of_test_suites(                                    \
        moduleInstance->numberOfTestSuites,                                    \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_TEST_SUITE_INSTANCES(module)            \
    module->totalNumberOfTestSuiteInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_TEST_SUITE_INSTANCES(module, state)           \
    internal_nbp_get_number_of_test_suite_instances(                           \
        module->numberOfTestSuiteInstances,                                    \
        state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_MODULES(module)                         \
    module->totalNumberOfModules

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_MODULES(module, state)                        \
    internal_nbp_get_number_of_modules(module->numberOfModules, state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_TOTAL_NUMBER_OF_MODULE_INSTANCES(module)                \
    module->totalNumberOfModuleInstances

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_NUMBER_OF_MODULE_INSTANCES(module, state)               \
    internal_nbp_get_number_of_module_instances(                               \
        module->numberOfModuleInstances,                                       \
        state)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_MODULE(func, ...)                                      \
    NBP_INCLUDE_MODULE(func);                                                  \
    internal_nbp_instantiate_module(                                           \
        NBP_GET_POINTER_TO_MODULE_DETAILS(func),                               \
        nbpParamMiParentModule,                                                \
        NBP_SOURCE_LINE,                                                       \
        1,                                                                     \
        NBP_NULLPTR)

#define INTERNAL_NBP_GENERATE_MODULE_CONFIG_FUNCTION(...)                      \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GMC##__VA_ARGS__))     \
    (GMCF_, GMC##__VA_ARGS__)

// This macro is generated when NBP_MODULE macro is used without parameters
#define INTERNAL_NBP_GMCF_

#define INTERNAL_NBP_GMCF_NBP_MODULE_NAME(newName)                             \
    moduleDetails->name = newName;

#define INTERNAL_NBP_GMCF_NBP_MODULE_SETUP(func)                               \
    NBP_INCLUDE_MODULE_SETUP(func);                                            \
    moduleDetails->setupDetails = NBP_GET_POINTER_TO_MODULE_SETUP(func);

#define INTERNAL_NBP_GMCF_NBP_MODULE_TEARDOWN(func)                            \
    NBP_INCLUDE_MODULE_TEARDOWN(func);                                         \
    moduleDetails->teardownDetails = NBP_GET_POINTER_TO_MODULE_TEARDOWN(func);

#define INTERNAL_NBP_GMCF_NBP_MODULE_FIXTURES(setupFunc, teardownFunc)         \
    INTERNAL_NBP_GMCF_NBP_MODULE_SETUP(setupFunc)                              \
    INTERNAL_NBP_GMCF_NBP_MODULE_TEARDOWN(teardownFunc)

#endif // end if _H_NBP_INTERNAL_API_MODULE

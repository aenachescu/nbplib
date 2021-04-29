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
        nbp_module_t* nbpParamMiParentModule,                                  \
        unsigned int nbpParamNumberOfRuns);                                    \
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
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamMiParentModule,       \
        NBP_MAYBE_UNUSED_PARAMETER unsigned int nbpParamNumberOfRuns)

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
#define NBP_MODULE_GET_NAME(module)                                            \
    NBP_MODULE_INSTANCE_GET_NAME(module->moduleInstance)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_STATE(module)                                           \
    (nbp_module_state_e) NBP_ATOMIC_INT_LOAD(&(module)->state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_DEPTH(module)                                           \
    NBP_MODULE_INSTANCE_GET_DEPTH(module->moduleInstance)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_STATISTICS(module, type, ...)                           \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_MGS_,                                                     \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (module, INTERNAL_NBP_MGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_MODULE_GET_INSTANCE(module) module->moduleInstance

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NAME(moduleInstance)                           \
    moduleInstance->moduleDetails->name

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_STATE(moduleInstance)                          \
    (nbp_module_instance_state_e) NBP_ATOMIC_INT_LOAD(&(moduleInstance)->state)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_DEPTH(moduleInstance) moduleInstance->depth

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_STATISTICS(moduleInstance, type, ...)          \
    NBP_PP_CONCAT(                                                             \
        INTERNAL_NBP_MIGS_,                                                    \
        NBP_PP_CONCAT(type, NBP_PP_COUNT(P##__VA_ARGS__)))                     \
    (moduleInstance, INTERNAL_NBP_MIGS_PARAM_##__VA_ARGS__)

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(moduleInstance)                 \
    moduleInstance->numberOfRuns

/**
 * TODO: add docs
 */
#define NBP_MODULE_INSTANCE_GET_MODULE(moduleInstance, runId)                  \
    internal_nbp_get_module_from_instance(moduleInstance, runId)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_MODULE(func, ...)                                      \
    NBP_INCLUDE_MODULE(func);                                                  \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(MPIO_##__VA_ARGS__))   \
    (MPIO_, MPIO_##__VA_ARGS__);                                               \
    internal_nbp_instantiate_module(                                           \
        NBP_GET_POINTER_TO_MODULE_DETAILS(func),                               \
        nbpParamMiParentModule,                                                \
        NBP_SOURCE_LINE,                                                       \
        nbpParamNumberOfRuns,                                                  \
        NBP_NULLPTR);                                                          \
    nbpParamNumberOfRuns = 1;

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

// This macro is generated when NBP_INSTANTIATE_MODULE macro is used without
// parameters
#define INTERNAL_NBP_MPIO_

#define INTERNAL_NBP_MPIO_NBP_NUMBER_OF_RUNS(num) nbpParamNumberOfRuns = num;

// Helpers for NBP_MODULE_GET_STATISTICS

#define INTERNAL_NBP_MGS_PARAM_

#define INTERNAL_NBP_MGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_MGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_MGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_MGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_MGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_MGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_MGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_MGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_MGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_MGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_MGS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_MGS_PARAM_tss_running tss_running
#define INTERNAL_NBP_MGS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_MGS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_MGS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_MGS_PARAM_tsis_ready   tsis_ready
#define INTERNAL_NBP_MGS_PARAM_tsis_running tsis_running
#define INTERNAL_NBP_MGS_PARAM_tsis_passed  tsis_passed
#define INTERNAL_NBP_MGS_PARAM_tsis_failed  tsis_failed
#define INTERNAL_NBP_MGS_PARAM_tsis_skipped tsis_skipped

#define INTERNAL_NBP_MGS_PARAM_ms_ready   ms_ready
#define INTERNAL_NBP_MGS_PARAM_ms_running ms_running
#define INTERNAL_NBP_MGS_PARAM_ms_passed  ms_passed
#define INTERNAL_NBP_MGS_PARAM_ms_failed  ms_failed
#define INTERNAL_NBP_MGS_PARAM_ms_skipped ms_skipped

#define INTERNAL_NBP_MGS_PARAM_mis_ready   mis_ready
#define INTERNAL_NBP_MGS_PARAM_mis_running mis_running
#define INTERNAL_NBP_MGS_PARAM_mis_passed  mis_passed
#define INTERNAL_NBP_MGS_PARAM_mis_failed  mis_failed
#define INTERNAL_NBP_MGS_PARAM_mis_skipped mis_skipped

#define INTERNAL_NBP_MGS_st_total_number_of_test_cases1(m, unused)             \
    unused m->totalNumberOfTestCases
#define INTERNAL_NBP_MGS_st_total_number_of_test_case_instances1(m, unused)    \
    unused m->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_MGS_st_total_number_of_test_suites1(m, unused)            \
    unused m->totalNumberOfTestSuites
#define INTERNAL_NBP_MGS_st_total_number_of_test_suite_instances1(m, unused)   \
    unused m->totalNumberOfTestSuiteInstances
#define INTERNAL_NBP_MGS_st_total_number_of_modules1(m, unused)                \
    unused m->totalNumberOfModules
#define INTERNAL_NBP_MGS_st_total_number_of_module_instances1(m, unused)       \
    unused m->totalNumberOfModuleInstances

#define INTERNAL_NBP_MGS_st_number_of_test_cases1(m, state)                    \
    internal_nbp_get_number_of_test_cases(m->numberOfTestCases, state)
#define INTERNAL_NBP_MGS_st_number_of_test_case_instances1(m, state)           \
    internal_nbp_get_number_of_test_case_instances(                            \
        m->numberOfTestCaseInstances,                                          \
        state)
#define INTERNAL_NBP_MGS_st_number_of_test_suites1(m, state)                   \
    internal_nbp_get_number_of_test_suites(m->numberOfTestSuites, state)
#define INTERNAL_NBP_MGS_st_number_of_test_suite_instances1(m, state)          \
    internal_nbp_get_number_of_test_suite_instances(                           \
        m->numberOfTestSuiteInstances,                                         \
        state)
#define INTERNAL_NBP_MGS_st_number_of_modules1(m, state)                       \
    internal_nbp_get_number_of_modules(m->numberOfModules, state)
#define INTERNAL_NBP_MGS_st_number_of_module_instances1(m, state)              \
    internal_nbp_get_number_of_module_instances(                               \
        m->numberOfModuleInstances,                                            \
        state)

// Helpers for NBP_MODULE_INSTANCE_GET_STATISTICS

#define INTERNAL_NBP_MIGS_PARAM_

#define INTERNAL_NBP_MIGS_PARAM_tcs_ready   tcs_ready
#define INTERNAL_NBP_MIGS_PARAM_tcs_running tcs_running
#define INTERNAL_NBP_MIGS_PARAM_tcs_passed  tcs_passed
#define INTERNAL_NBP_MIGS_PARAM_tcs_failed  tcs_failed
#define INTERNAL_NBP_MIGS_PARAM_tcs_skipped tcs_skipped

#define INTERNAL_NBP_MIGS_PARAM_tcis_ready   tcis_ready
#define INTERNAL_NBP_MIGS_PARAM_tcis_running tcis_running
#define INTERNAL_NBP_MIGS_PARAM_tcis_passed  tcis_passed
#define INTERNAL_NBP_MIGS_PARAM_tcis_failed  tcis_failed
#define INTERNAL_NBP_MIGS_PARAM_tcis_skipped tcis_skipped

#define INTERNAL_NBP_MIGS_PARAM_tss_ready   tss_ready
#define INTERNAL_NBP_MIGS_PARAM_tss_running tss_running
#define INTERNAL_NBP_MIGS_PARAM_tss_passed  tss_passed
#define INTERNAL_NBP_MIGS_PARAM_tss_failed  tss_failed
#define INTERNAL_NBP_MIGS_PARAM_tss_skipped tss_skipped

#define INTERNAL_NBP_MIGS_PARAM_tsis_ready   tsis_ready
#define INTERNAL_NBP_MIGS_PARAM_tsis_running tsis_running
#define INTERNAL_NBP_MIGS_PARAM_tsis_passed  tsis_passed
#define INTERNAL_NBP_MIGS_PARAM_tsis_failed  tsis_failed
#define INTERNAL_NBP_MIGS_PARAM_tsis_skipped tsis_skipped

#define INTERNAL_NBP_MIGS_PARAM_ms_ready   ms_ready
#define INTERNAL_NBP_MIGS_PARAM_ms_running ms_running
#define INTERNAL_NBP_MIGS_PARAM_ms_passed  ms_passed
#define INTERNAL_NBP_MIGS_PARAM_ms_failed  ms_failed
#define INTERNAL_NBP_MIGS_PARAM_ms_skipped ms_skipped

#define INTERNAL_NBP_MIGS_PARAM_mis_ready   mis_ready
#define INTERNAL_NBP_MIGS_PARAM_mis_running mis_running
#define INTERNAL_NBP_MIGS_PARAM_mis_passed  mis_passed
#define INTERNAL_NBP_MIGS_PARAM_mis_failed  mis_failed
#define INTERNAL_NBP_MIGS_PARAM_mis_skipped mis_skipped

#define INTERNAL_NBP_MIGS_st_total_number_of_test_cases1(mi, unused)           \
    unused mi->totalNumberOfTestCases
#define INTERNAL_NBP_MIGS_st_total_number_of_test_case_instances1(mi, unused)  \
    unused mi->totalNumberOfTestCaseInstances
#define INTERNAL_NBP_MIGS_st_total_number_of_test_suites1(mi, unused)          \
    unused mi->totalNumberOfTestSuites
#define INTERNAL_NBP_MIGS_st_total_number_of_test_suite_instances1(mi, unused) \
    unused mi->totalNumberOfTestSuiteInstances
#define INTERNAL_NBP_MIGS_st_total_number_of_modules1(mi, unused)              \
    unused mi->totalNumberOfModules
#define INTERNAL_NBP_MIGS_st_total_number_of_module_instances1(mi, unused)     \
    unused mi->totalNumberOfModuleInstances

#define INTERNAL_NBP_MIGS_st_number_of_test_cases1(mi, state)                  \
    internal_nbp_get_number_of_test_cases(mi->numberOfTestCases, state)
#define INTERNAL_NBP_MIGS_st_number_of_test_case_instances1(mi, state)         \
    internal_nbp_get_number_of_test_case_instances(                            \
        mi->numberOfTestCaseInstances,                                         \
        state)
#define INTERNAL_NBP_MIGS_st_number_of_test_suites1(mi, state)                 \
    internal_nbp_get_number_of_test_suites(mi->numberOfTestSuites, state)
#define INTERNAL_NBP_MIGS_st_number_of_test_suite_instances1(mi, state)        \
    internal_nbp_get_number_of_test_suite_instances(                           \
        mi->numberOfTestSuiteInstances,                                        \
        state)
#define INTERNAL_NBP_MIGS_st_number_of_modules1(mi, state)                     \
    internal_nbp_get_number_of_modules(mi->numberOfModules, state)
#define INTERNAL_NBP_MIGS_st_number_of_module_instances1(mi, state)            \
    internal_nbp_get_number_of_module_instances(                               \
        mi->numberOfModuleInstances,                                           \
        state)

#endif // end if _H_NBP_INTERNAL_API_MODULE

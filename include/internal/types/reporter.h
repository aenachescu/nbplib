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

#ifndef _H_NBP_INTERNAL_TYPES_REPORTER
#define _H_NBP_INTERNAL_TYPES_REPORTER

#include "error.h"
#include "module.h"
#include "test_case.h"
#include "test_suite.h"

struct nbp_reporter_interface_t;

struct nbp_reporter_statistics_t
{
    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    unsigned int totalNumberOfTestSuites;
    unsigned int totalNumberOfTestSuiteInstances;
    unsigned int totalNumberOfModules;
    unsigned int totalNumberOfModuleInstances;

    unsigned int numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    unsigned int
        numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    unsigned int numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];
    unsigned int
        numberOfTestSuiteInstances[NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES];
    unsigned int numberOfModules[NBP_NUMBER_OF_MODULE_STATES];
    unsigned int numberOfModuleInstances[NBP_NUMBER_OF_MODULE_INSTANCE_STATES];
};
typedef struct nbp_reporter_statistics_t nbp_reporter_statistics_t;

typedef void (*nbp_reporter_config_pfn_t)(
    struct nbp_reporter_interface_t* /* reporterInterface */
);

typedef void (*nbp_reporter_callback_init_pfn_t)(void);

typedef void (*nbp_reporter_callback_uninit_pfn_t)(void);

typedef void (*nbp_reporter_callback_handle_version_command_pfn_t)(void);

typedef void (*nbp_reporter_callback_on_error_pfn_t)(
    nbp_error_t /* nbpParamError */
);

typedef void (*nbp_reporter_callback_on_exit_pfn_t)(
    nbp_error_code_e /* nbpParamErrorCode */
);

typedef void (*nbp_reporter_callback_before_run_pfn_t)(
    nbp_reporter_statistics_t* /* nbpParamStatistics */
);

typedef void (*nbp_reporter_callback_after_run_pfn_t)(
    nbp_reporter_statistics_t* /* nbpParamStatistics */
);

typedef void (*nbp_reporter_callback_on_instantiate_test_case_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_test_suite_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_test_suite_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_module_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_instantiate_module_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_started_pfn_t)(
    nbp_test_case_t* /* nbpParamTestCase */,
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_completed_pfn_t)(
    nbp_test_case_t* /* nbpParamTestCase */,
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_instance_started_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_case_instance_completed_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_started_pfn_t)(
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_completed_pfn_t)(
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_instance_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_test_suite_instance_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_reporter_callback_on_module_started_pfn_t)(
    nbp_module_t* /* nbpParamModule */,
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_reporter_callback_on_module_completed_pfn_t)(
    nbp_module_t* /* nbpParamModule */,
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_reporter_callback_on_module_instance_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

typedef void (*nbp_reporter_callback_on_module_instance_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */
);

struct nbp_reporter_interface_t
{
    const char* reporterName;
    nbp_reporter_config_pfn_t configFunction;

    int isInitialized;

    nbp_reporter_callback_init_pfn_t initCbk;
    nbp_reporter_callback_uninit_pfn_t uninitCbk;

    nbp_reporter_callback_handle_version_command_pfn_t handleVersionCommandCbk;

    nbp_reporter_callback_on_error_pfn_t errorCbk;
    nbp_reporter_callback_on_exit_pfn_t exitCbk;

    nbp_reporter_callback_before_run_pfn_t beforeRunCbk;
    nbp_reporter_callback_after_run_pfn_t afterRunCbk;

    nbp_reporter_callback_on_instantiate_test_case_pfn_t instantiateTestCaseCbk;

    nbp_reporter_callback_on_instantiate_test_suite_started_pfn_t
        instantiateTestSuiteStartedCbk;
    nbp_reporter_callback_on_instantiate_test_suite_completed_pfn_t
        instantiateTestSuiteCompletedCbk;

    nbp_reporter_callback_on_instantiate_module_started_pfn_t
        instantiateModuleStartedCbk;
    nbp_reporter_callback_on_instantiate_module_completed_pfn_t
        instantiateModuleCompletedCbk;

    nbp_reporter_callback_on_test_case_started_pfn_t testCaseStartedCbk;
    nbp_reporter_callback_on_test_case_completed_pfn_t testCaseCompletedCbk;
    nbp_reporter_callback_on_test_case_instance_started_pfn_t
        testCaseInstanceStartedCbk;
    nbp_reporter_callback_on_test_case_instance_completed_pfn_t
        testCaseInstanceCompletedCbk;

    nbp_reporter_callback_on_test_suite_started_pfn_t testSuiteStartedCbk;
    nbp_reporter_callback_on_test_suite_completed_pfn_t testSuiteCompletedCbk;
    nbp_reporter_callback_on_test_suite_instance_started_pfn_t
        testSuiteInstanceStartedCbk;
    nbp_reporter_callback_on_test_suite_instance_completed_pfn_t
        testSuiteInstanceCompletedCbk;

    nbp_reporter_callback_on_module_started_pfn_t moduleStartedCbk;
    nbp_reporter_callback_on_module_completed_pfn_t moduleCompletedCbk;
    nbp_reporter_callback_on_module_instance_started_pfn_t
        moduleInstanceStartedCbk;
    nbp_reporter_callback_on_module_instance_completed_pfn_t
        moduleInstanceCompletedCbk;
};
typedef struct nbp_reporter_interface_t nbp_reporter_interface_t;

#endif // end if _H_NBP_INTERNAL_TYPES_REPORTER

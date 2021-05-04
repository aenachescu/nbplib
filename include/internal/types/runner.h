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

#ifndef _H_NBP_INTERNAL_TYPES_RUNNER
#define _H_NBP_INTERNAL_TYPES_RUNNER

#include "module.h"
#include "test_case.h"
#include "test_suite.h"

struct nbp_runner_interface_t;

typedef void (*nbp_runner_config_pfn_t)(
    struct nbp_runner_interface_t* /* runnerInterface */
);

typedef void (*nbp_runner_callback_init_pfn_t)(void);

typedef void (*nbp_runner_callback_uninit_pfn_t)(void);

typedef void (*nbp_runner_callback_run_pfn_t)(void);

typedef void (*nbp_runner_callback_on_instantiate_test_case_pfn_t)(
    nbp_test_case_instance_t* /* nbpParamTestCaseInstance */,
    nbp_test_suite_t* /* nbpParamTestSuite */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);
typedef void (*nbp_runner_callback_on_instantiate_test_suite_started_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);

typedef void (*nbp_runner_callback_on_instantiate_test_suite_completed_pfn_t)(
    nbp_test_suite_instance_t* /* nbpParamTestSuiteInstance */,
    nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_runner_callback_on_instantiate_module_started_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */,
    void* /* nbpParamContext */
);

typedef void (*nbp_runner_callback_on_instantiate_module_completed_pfn_t)(
    nbp_module_instance_t* /* nbpParamModuleInstance */,
    nbp_module_t* /* nbpParamModule */
);

struct nbp_runner_interface_t
{
    const char* runnerName;
    nbp_runner_config_pfn_t configFunction;

    nbp_runner_callback_init_pfn_t initCbk;
    nbp_runner_callback_uninit_pfn_t uninitCbk;
    nbp_runner_callback_run_pfn_t runCbk;
    nbp_runner_callback_on_instantiate_test_case_pfn_t instantiateTestCaseCbk;
    nbp_runner_callback_on_instantiate_test_suite_started_pfn_t
        instantiateTestSuiteStartedCbk;
    nbp_runner_callback_on_instantiate_test_suite_completed_pfn_t
        instantiateTestSuiteCompletedCbk;
    nbp_runner_callback_on_instantiate_module_started_pfn_t
        instantiateModuleStartedCbk;
    nbp_runner_callback_on_instantiate_module_completed_pfn_t
        instantiateModuleCompletedCbk;
};
typedef struct nbp_runner_interface_t nbp_runner_interface_t;

#endif // end if _H_NBP_INTERNAL_TYPES_RUNNER

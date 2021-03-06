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

#ifndef _H_NBP_INTERNAL_TYPES_MODULE
#define _H_NBP_INTERNAL_TYPES_MODULE

#include "test_case.h"
#include "test_suite.h"

#define NBP_NUMBER_OF_MODULE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_MODULE_STATES          ((unsigned int) 5)

struct nbp_module_function_t;
struct nbp_module_instance_t;
struct nbp_module_t;

typedef void (*nbp_module_setup_pfn_t)(
    struct nbp_module_t* /* nbpParamModule */);

typedef void (*nbp_module_teardown_pfn_t)(
    struct nbp_module_t* /* nbpParamModule */
);

typedef void (*nbp_module_config_pfn_t)(
    struct nbp_module_function_t* /* moduleFunction */
);

typedef void (*nbp_module_pfn_t)(
    struct nbp_module_t* /* nbpParamModule*/,
    struct nbp_test_suite_t* /* nbpParamTciParentTestSuite */,
    struct nbp_module_t* /* nbpParamTciParentModule */,
    struct nbp_module_t* /* nbpParamTsiParentModule */,
    struct nbp_module_t* /* nbpParamMiParentModule */,
    unsigned int /* nbpParamNumberOfRuns */
);

enum nbp_module_instance_state_e
{
    mis_ready   = 0x40000000,
    mis_running = 0x40000001,
    mis_passed  = 0x40000002,
    mis_failed  = 0x40000003,
    mis_skipped = 0x40000004,
};
typedef enum nbp_module_instance_state_e nbp_module_instance_state_e;

enum nbp_module_state_e
{
    ms_ready   = 0x41000000,
    ms_running = 0x41000001,
    ms_passed  = 0x41000002,
    ms_failed  = 0x41000003,
    ms_skipped = 0x41000004,
};
typedef enum nbp_module_state_e nbp_module_state_e;

struct nbp_module_setup_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_module_setup_pfn_t function;
};
typedef struct nbp_module_setup_function_t nbp_module_setup_function_t;

struct nbp_module_teardown_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_module_teardown_pfn_t function;
};
typedef struct nbp_module_teardown_function_t nbp_module_teardown_function_t;

struct nbp_module_function_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_module_config_pfn_t configFunction;
    nbp_module_pfn_t function;

    nbp_module_setup_function_t* setupFunction;
    nbp_module_teardown_function_t* teardownFunction;
};
typedef struct nbp_module_function_t nbp_module_function_t;

struct nbp_module_instance_t
{
    nbp_module_function_t* moduleFunction;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* parent;
    unsigned int depth;

    int instantiationLine;

    nbp_module_setup_function_t* setupFunction;
    nbp_module_teardown_function_t* teardownFunction;

    struct nbp_module_t* runs;
    unsigned int numberOfRuns;
    NBP_ATOMIC_UINT_TYPE numberOfCompletedRuns;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    unsigned int totalNumberOfTestSuites;
    unsigned int totalNumberOfTestSuiteInstances;
    unsigned int totalNumberOfModules;
    unsigned int totalNumberOfModuleInstances;

    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestSuiteInstances[NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfModules[NBP_NUMBER_OF_MODULE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfModuleInstances[NBP_NUMBER_OF_MODULE_INSTANCE_STATES];

    struct nbp_module_instance_t* next;
    struct nbp_module_instance_t* prev;
};
typedef struct nbp_module_instance_t nbp_module_instance_t;

struct nbp_module_t
{
    nbp_module_instance_t* moduleInstance;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    NBP_SYNC_EVENT_TYPE runEvent;
    NBP_SYNC_EVENT_TYPE setupEvent;

    nbp_test_case_instance_t* firstTestCaseInstance;
    nbp_test_case_instance_t* lastTestCaseInstance;

    nbp_test_suite_instance_t* firstTestSuiteInstance;
    nbp_test_suite_instance_t* lastTestSuiteInstance;

    nbp_module_instance_t* firstModuleInstance;
    nbp_module_instance_t* lastModuleInstance;

    unsigned int numberOfTasks;
    NBP_ATOMIC_UINT_TYPE numberOfCompletedTasks;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    unsigned int totalNumberOfTestSuites;
    unsigned int totalNumberOfTestSuiteInstances;
    unsigned int totalNumberOfModules;
    unsigned int totalNumberOfModuleInstances;

    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestSuiteInstances[NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfModules[NBP_NUMBER_OF_MODULE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfModuleInstances[NBP_NUMBER_OF_MODULE_INSTANCE_STATES];
};
typedef struct nbp_module_t nbp_module_t;

#endif // end if _H_NBP_INTERNAL_TYPES_MODULE

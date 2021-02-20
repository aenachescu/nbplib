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

#ifndef _H_NBP_INTERNAL_TYPES_TEST_SUITE
#define _H_NBP_INTERNAL_TYPES_TEST_SUITE

#include "sync.h"
#include "test_case.h"

#define NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_TEST_SUITE_STATES          ((unsigned int) 5)

struct nbp_module_t;

struct nbp_test_suite_details_t;
struct nbp_test_suite_instance_t;
struct nbp_test_suite_t;

typedef void (*nbp_test_suite_setup_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */
);

typedef void (*nbp_test_suite_teardown_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */
);

typedef void (*nbp_test_suite_config_pfn_t)(
    struct nbp_test_suite_details_t* /* testSuiteDetails */
);

typedef void (*nbp_test_suite_pfn_t)(
    struct nbp_test_suite_t* /* nbpParamTestSuite */,
    struct nbp_test_suite_t* /* nbpParamTciParentTestSuite */,
    struct nbp_module_t* /*nbpParamTciParentModule */
);

enum nbp_test_suite_instance_state_e
{
    tsis_ready   = 0x30000000,
    tsis_running = 0x30000001,
    tsis_passed  = 0x30000002,
    tsis_failed  = 0x30000003,
    tsis_skipped = 0x30000004,
};
typedef enum nbp_test_suite_instance_state_e nbp_test_suite_instance_state_e;

enum nbp_test_suite_state_e
{
    tss_ready   = 0x31000000,
    tss_running = 0x31000001,
    tss_passed  = 0x31000002,
    tss_failed  = 0x31000003,
    tss_skipped = 0x31000004,
};
typedef enum nbp_test_suite_state_e nbp_test_suite_state_e;

struct nbp_test_suite_setup_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_suite_setup_pfn_t function;
};
typedef struct nbp_test_suite_setup_details_t nbp_test_suite_setup_details_t;

struct nbp_test_suite_teardown_details_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_suite_teardown_pfn_t function;
};
typedef struct nbp_test_suite_teardown_details_t
    nbp_test_suite_teardown_details_t;

struct nbp_test_suite_details_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_test_suite_config_pfn_t configFunction;
    nbp_test_suite_pfn_t function;

    nbp_test_suite_setup_details_t* setupDetails;
    nbp_test_suite_teardown_details_t* teardownDetails;
};
typedef struct nbp_test_suite_details_t nbp_test_suite_details_t;

struct nbp_test_suite_instance_t
{
    nbp_test_suite_details_t* testSuiteDetails;

    nbp_test_suite_instance_state_e state;

    struct nbp_module_t* module;
    unsigned int depth;

    int instantiationLine;

    nbp_test_suite_setup_details_t* setupDetails;
    nbp_test_suite_teardown_details_t* teardownDetails;

    struct nbp_test_suite_t* runs;
    unsigned int numberOfRuns;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
    NBP_ATOMIC_UINT_TYPE numberOfTestSuites[NBP_NUMBER_OF_TEST_SUITE_STATES];

    struct nbp_test_suite_instance_t* next;
    struct nbp_test_suite_instance_t* prev;
};
typedef struct nbp_test_suite_instance_t nbp_test_suite_instance_t;

struct nbp_test_suite_t
{
    nbp_test_suite_instance_t* testSuiteInstance;

    nbp_test_suite_state_e state;

    nbp_test_case_instance_t* firstTestCaseInstance;
    nbp_test_case_instance_t* lastTestCaseInstance;

    unsigned int totalNumberOfTestCases;
    unsigned int totalNumberOfTestCaseInstances;
    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];
    NBP_ATOMIC_UINT_TYPE
    numberOfTestCaseInstances[NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES];
};
typedef struct nbp_test_suite_t nbp_test_suite_t;

#endif // end if _H_NBP_INTERNAL_TYPES_TEST_SUITE

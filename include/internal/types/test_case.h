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

#ifndef _H_NBP_INTERNAL_TYPES_TEST_CASE
#define _H_NBP_INTERNAL_TYPES_TEST_CASE

#include "sync.h"

#define NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES ((unsigned int) 5)
#define NBP_NUMBER_OF_TEST_CASE_STATES          ((unsigned int) 5)

struct nbp_module_t;

struct nbp_test_suite_t;

struct nbp_test_case_function_t;
struct nbp_test_case_instance_t;
struct nbp_test_case_t;

typedef void (*nbp_test_case_setup_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

typedef void (*nbp_test_case_teardown_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

typedef void (*nbp_test_case_config_pfn_t)(
    struct nbp_test_case_function_t* /* testCaseFunction */
);

typedef void (*nbp_test_case_pfn_t)(
    struct nbp_test_case_t* /* nbpParamTestCase */
);

enum nbp_test_case_instance_state_e
{
    tcis_ready   = 0x20000000,
    tcis_running = 0x20000001,
    tcis_passed  = 0x20000002,
    tcis_failed  = 0x20000003,
    tcis_skipped = 0x20000004,
};
typedef enum nbp_test_case_instance_state_e nbp_test_case_instance_state_e;

enum nbp_test_case_state_e
{
    tcs_ready   = 0x21000000,
    tcs_running = 0x21000001,
    tcs_passed  = 0x21000002,
    tcs_failed  = 0x21000003,
    tcs_skipped = 0x21000004,
};
typedef enum nbp_test_case_state_e nbp_test_case_state_e;

struct nbp_test_case_setup_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_case_setup_pfn_t function;
};
typedef struct nbp_test_case_setup_function_t nbp_test_case_setup_function_t;

struct nbp_test_case_teardown_function_t
{
    const char* functionName;

    const char* file;
    int line;

    nbp_test_case_teardown_pfn_t function;
};
typedef struct nbp_test_case_teardown_function_t
    nbp_test_case_teardown_function_t;

struct nbp_test_case_function_t
{
    const char* name;
    const char* functionName;

    const char* file;
    int line;

    int isConfigured;

    nbp_test_case_config_pfn_t configFunction;
    nbp_test_case_pfn_t function;

    nbp_test_case_setup_function_t* setupFunction;
    nbp_test_case_teardown_function_t* teardownFunction;
};
typedef struct nbp_test_case_function_t nbp_test_case_function_t;

struct nbp_test_case_instance_t
{
    nbp_test_case_function_t* testCaseFunction;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;

    struct nbp_module_t* module;
    struct nbp_test_suite_t* testSuite;
    unsigned int depth;

    int instantiationLine;

    nbp_test_case_setup_function_t* setupFunction;
    nbp_test_case_teardown_function_t* teardownFunction;

    struct nbp_test_case_t* runs;
    unsigned int numberOfRuns;
    NBP_ATOMIC_UINT_TYPE numberOfCompletedRuns;

    NBP_ATOMIC_UINT_TYPE numberOfTestCases[NBP_NUMBER_OF_TEST_CASE_STATES];

    struct nbp_test_case_instance_t* next;
    struct nbp_test_case_instance_t* prev;
};
typedef struct nbp_test_case_instance_t nbp_test_case_instance_t;

struct nbp_test_case_t
{
    nbp_test_case_instance_t* testCaseInstance;

    NBP_ATOMIC_INT_TYPE state;

    NBP_ATOMIC_INT_TYPE isSkipped;
};
typedef struct nbp_test_case_t nbp_test_case_t;

#endif // end if _H_NBP_INTERNAL_TYPES_TEST_CASE

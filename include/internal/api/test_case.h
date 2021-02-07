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

#ifndef _H_NBP_INTERNAL_API_TEST_CASE
#define _H_NBP_INTERNAL_API_TEST_CASE

#include "../details/test_case.h"
#include "../types/test_case.h"
#include "../utils/utils.h"
#include "memory.h"
#include "module.h"
#include "test_suite.h"

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_SETUP(func)                                              \
    void nbp_test_case_setup_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase);         \
    nbp_test_case_setup_details_t gInternalNbpTestCaseSetupDetails##func = {   \
        .functionName = #func,                                                 \
        .file         = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_test_case_setup_function_##func,                   \
    };                                                                         \
    void nbp_test_case_setup_function_##func(                                  \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_TEARDOWN(func)                                           \
    void nbp_test_case_teardown_function_##func(                               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase);         \
    nbp_test_case_teardown_details_t                                           \
        gInternalNbpTestCaseTeardownDetails##func = {                          \
            .functionName = #func,                                             \
            .file         = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_case_teardown_function_##func,            \
    };                                                                         \
    void nbp_test_case_teardown_function_##func(                               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE(func, ...)                                               \
    void nbp_test_case_config_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_details_t* testCaseDetails)   \
    {                                                                          \
        if (testCaseDetails->isConfigured == 1) {                              \
            return;                                                            \
        } else {                                                               \
            testCaseDetails->isConfigured = 1;                                 \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(F_##__VA_ARGS__)       \
    }                                                                          \
    void nbp_test_case_function_##func(nbp_test_case_t* nbpParamTestCase);     \
    nbp_test_case_details_t gInternalNbpTestCaseDetails##func = {              \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_test_case_config_function_##func,               \
        .function        = nbp_test_case_function_##func,                      \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    void nbp_test_case_function_##func(                                        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_TEST_CASE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_SETUP(func)                                      \
    extern nbp_test_case_setup_details_t gInternalNbpTestCaseSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_SETUP(func)                               \
    &gInternalNbpTestCaseSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE_TEARDOWN(func)                                   \
    extern nbp_test_case_teardown_details_t                                    \
        gInternalNbpTestCaseTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN(func)                            \
    &gInternalNbpTestCaseTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_CASE(func)                                            \
    extern nbp_test_case_details_t gInternalNbpTestCaseDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_CASE_DETAILS(func)                             \
    &gInternalNbpTestCaseDetails##func

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_CASE nbpParamTestCase

/**
 * TODO: add docs
 */
#define NBP_THIS_TEST_CASE_INSTANCE nbpParamTestCaseInstance

/**
 * TODO: add docs
 */
#define NBP_GET_TEST_CASE_INSTANCE_NAME(testCaseInstance)                      \
    testCaseInstance->testCaseDetails->name

/**
 * TODO: add docs
 */
#define NBP_GET_TEST_CASE_NAME(testCase)                                       \
    NBP_GET_TEST_CASE_INSTANCE_NAME(testCase->testCaseInstance)

/**
 * TODO: add docs
 */
#define NBP_INSTANTIATE_TEST_CASE(func, ...)                                   \
    NBP_INCLUDE_TEST_CASE(func);                                               \
    internal_nbp_instantiate_test_case(                                        \
        NBP_GET_POINTER_TO_TEST_CASE_DETAILS(func),                            \
        nbpParamTciParentModule,                                               \
        nbpParamTciParentTestSuite,                                            \
        1,                                                                     \
        NBP_NULLPTR)

#define INTERNAL_NBP_GENERATE_TEST_CASE_CONFIG_FUNCTION(...)                   \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GTCC##__VA_ARGS__))    \
    (GTCCF_, GTCC##__VA_ARGS__)

// This macro is generated when NBP_TEST_CASE macro is used without parameters
#define INTERNAL_NBP_GTCCF_

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_NAME(newName)                         \
    testCaseDetails->name = newName;

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(func)                           \
    NBP_INCLUDE_TEST_CASE_SETUP(func);                                         \
    testCaseDetails->setupDetails = NBP_GET_POINTER_TO_TEST_CASE_SETUP(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(func)                        \
    NBP_INCLUDE_TEST_CASE_TEARDOWN(func);                                      \
    testCaseDetails->teardownDetails =                                         \
        NBP_GET_POINTER_TO_TEST_CASE_TEARDOWN(func);

#define INTERNAL_NBP_GTCCF_NBP_TEST_CASE_FIXTURES(setupFunc, teardownFunc)     \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_SETUP(setupFunc)                          \
    INTERNAL_NBP_GTCCF_NBP_TEST_CASE_TEARDOWN(teardownFunc)

#endif // end if _H_NBP_INTERNAL_API_TEST_CASE

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

#ifndef _H_NBP_INTERNAL_API_TEST_SUITE
#define _H_NBP_INTERNAL_API_TEST_SUITE

#include "../types/test_suite.h"
#include "../utils/utils.h"
#include "memory.h"

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_SETUP(func)                                             \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_setup_details_t gInternalNbpTestSuiteSetupDetails##func = { \
        .functionName = #func,                                                 \
        .fileName     = NBP_SOURCE_FILE,                                       \
        .line         = NBP_SOURCE_LINE,                                       \
        .function     = nbp_test_suite_setup_function_##func,                  \
    };                                                                         \
    void nbp_test_suite_setup_function_##func(                                 \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_TEARDOWN(func)                                          \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite);       \
    nbp_test_suite_teardown_details_t                                          \
        gInternalNbpTestSuiteTeardownDetails##func = {                         \
            .functionName = #func,                                             \
            .fileName     = NBP_SOURCE_FILE,                                   \
            .line         = NBP_SOURCE_LINE,                                   \
            .function     = nbp_test_suite_teardown_function_##func,           \
    };                                                                         \
    void nbp_test_suite_teardown_function_##func(                              \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE(func, ...)                                              \
    void nbp_test_suite_config_function_##func(                                \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_details_t* testSuiteDetails) \
    {                                                                          \
        if (testSuiteDetails->isConfigured == 1) {                             \
            return;                                                            \
        } else {                                                               \
            testSuiteDetails->isConfigured = 1;                                \
        }                                                                      \
        INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(P_##__VA_ARGS__)      \
    }                                                                          \
    void nbp_test_suite_function_##func(nbp_test_suite_t* nbpParamTestSuite);  \
    nbp_test_suite_details_t gInternalNbpTestSuiteDetails##func = {            \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .fileName        = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_test_suite_config_function_##func,              \
        .function        = nbp_test_suite_function_##func,                     \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    void nbp_test_suite_function_##func(                                       \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_NAME(name)

/**
 * TODO: add docs
 */
#define NBP_TEST_SUITE_FIXTURES(setup, teardown)

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_SETUP(func)                                     \
    extern nbp_test_suite_setup_details_t                                      \
        gInternalNbpTestSuiteSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_SETUP(func)                              \
    &gInternalNbpTestSuiteSetupDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE_TEARDOWN(func)                                  \
    extern nbp_test_suite_teardown_details_t                                   \
        gInternalNbpTestSuiteTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN(func)                           \
    &gInternalNbpTestSuiteTeardownDetails##func

/**
 * TODO: add docs
 */
#define NBP_INCLUDE_TEST_SUITE(func)                                           \
    extern nbp_test_suite_details_t gInternalNbpTestSuiteDetails##func

/**
 * TODO: add docs
 */
#define NBP_GET_POINTER_TO_TEST_SUITE_DETAILS(func)                            \
    &gInternalNbpTestSuiteDetails##func

#define INTERNAL_NBP_GENERATE_TEST_SUITE_CONFIG_FUNCTION(...)                  \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(P##__VA_ARGS__))       \
    (P##__VA_ARGS__)

#define NBP_PP_PARSE_PP_NBP_TEST_SUITE_NAME(newName)                           \
    testSuiteDetails->name = newName;

#define NBP_PP_PARSE_PP_NBP_TEST_SUITE_SETUP(func)                             \
    NBP_INCLUDE_TEST_SUITE_SETUP(func);                                        \
    testSuiteDetails->setupDetails = NBP_GET_POINTER_TO_TEST_SUITE_SETUP(func);

#define NBP_PP_PARSE_PP_NBP_TEST_SUITE_TEARDOWN(func)                          \
    NBP_INCLUDE_TEST_SUITE_TEARDOWN(func);                                     \
    testSuiteDetails->teardownDetails =                                        \
        NBP_GET_POINTER_TO_TEST_SUITE_TEARDOWN(func);

#define NBP_PP_PARSE_PP_NBP_TEST_SUITE_FIXTURES(setupFunc, teardownFunc)       \
    NBP_PP_PARSE_PP_NBP_TEST_SUITE_SETUP(setupFunc)                            \
    NBP_PP_PARSE_PP_NBP_TEST_SUITE_TEARDOWN(teardownFunc)

#endif // end if _H_NBP_INTERNAL_API_TEST_SUITE

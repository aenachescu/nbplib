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

#ifndef _H_NBP_INTERNAL_API_PRINTER
#define _H_NBP_INTERNAL_API_PRINTER

#include "../types/printer.h"
#include "../utils/utils.h"
#include "memory.h"

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INIT(func)                                        \
    static void nbp_printer_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_UNINIT(func)                                      \
    static void nbp_printer_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(func)                      \
    static void nbp_printer_callback_##func()

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_ON_ERROR(func)                                    \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_t nbpParamError)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_ON_EXIT(func)                                     \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_error_code_e nbpParamErrorCode)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_CASE(func)                       \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(func)              \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED(func)            \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)                  \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(func)                \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance,                                            \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_STARTED(func)                           \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_COMPLETED(func)                         \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_t* nbpParamTestCase,          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)                  \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(func)                \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_case_instance_t*                   \
            nbpParamTestCaseInstance,                                          \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_STARTED(func)                          \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_COMPLETED(func)                        \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_t* nbpParamTestSuite,        \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func)                 \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(func)               \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_test_suite_instance_t*                  \
            nbpParamTestSuiteInstance,                                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_STARTED(func)                              \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_COMPLETED(func)                            \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule,               \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_INSTANCE_STARTED(func)                     \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)                   \
    static void nbp_printer_callback_##func(                                   \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_instance_t*                      \
            nbpParamModuleInstance)

/**
 * TODO: add docs
 */
#define NBP_PRINTER_CALLBACKS(...)

/**
 * TODO: add docs
 */
#define NBP_PRINTER(name, ...)                                                 \
    void nbp_printer_interface_config_function_##name(                         \
        NBP_MAYBE_UNUSED_PARAMETER nbp_printer_interface_t* printerInterface)  \
    {                                                                          \
        INTERNAL_NBP_GENERATE_PRINTER_CONFIG_FUNCTION(P_##__VA_ARGS__)         \
        return;                                                                \
    }                                                                          \
    nbp_printer_interface_t gInternalNbpPrinterInterface##name = {             \
        .printerName    = #name,                                               \
        .configFunction = INTERNAL_NBP_GENERATE_PRINTER_INTERFACE_NAME(name),  \
        .isInitialized  = 0,                                                   \
        .initCbk        = NBP_NULLPTR,                                         \
        .uninitCbk      = NBP_NULLPTR,                                         \
        .handleVersionCommandCbk          = NBP_NULLPTR,                       \
        .errorCbk                         = NBP_NULLPTR,                       \
        .exitCbk                          = NBP_NULLPTR,                       \
        .instantiateTestCaseCbk           = NBP_NULLPTR,                       \
        .instantiateTestSuiteStartedCbk   = NBP_NULLPTR,                       \
        .instantiateTestSuiteCompletedCbk = NBP_NULLPTR,                       \
        .instantiateModuleStartedCbk      = NBP_NULLPTR,                       \
        .instantiateModuleCompletedCbk    = NBP_NULLPTR,                       \
        .testCaseStartedCbk               = NBP_NULLPTR,                       \
        .testCaseCompletedCbk             = NBP_NULLPTR,                       \
        .testCaseInstanceStartedCbk       = NBP_NULLPTR,                       \
        .testCaseInstanceCompletedCbk     = NBP_NULLPTR,                       \
        .testSuiteStartedCbk              = NBP_NULLPTR,                       \
        .testSuiteCompletedCbk            = NBP_NULLPTR,                       \
        .testSuiteInstanceStartedCbk      = NBP_NULLPTR,                       \
        .testSuiteInstanceCompletedCbk    = NBP_NULLPTR,                       \
        .moduleStartedCbk                 = NBP_NULLPTR,                       \
        .moduleCompletedCbk               = NBP_NULLPTR,                       \
        .moduleInstanceStartedCbk         = NBP_NULLPTR,                       \
        .moduleInstanceCompletedCbk       = NBP_NULLPTR,                       \
    }

#define INTERNAL_NBP_GENERATE_PRINTER_INTERFACE_NAME(name)                     \
    nbp_printer_interface_config_function_##name

#define INTERNAL_NBP_GENERATE_PRINTER_CONFIG_FUNCTION(...)                     \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(P##__VA_ARGS__))       \
    (P##__VA_ARGS__)

#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACKS(...)                             \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_2_, NBP_PP_COUNT(PP_##__VA_ARGS__))   \
    (PP_##__VA_ARGS__)

#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_INIT(func)                        \
    printerInterface->initCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_UNINIT(func)                      \
    printerInterface->uninitCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(func)      \
    printerInterface->handleVersionCommandCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_ON_ERROR(func)                    \
    printerInterface->errorCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_ON_EXIT(func)                     \
    printerInterface->exitCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_CASE(func)       \
    printerInterface->instantiateTestCaseCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(   \
    func)                                                                      \
    printerInterface->instantiateTestSuiteStartedCbk =                         \
        nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_COMPLETED( \
    func)                                                                      \
    printerInterface->instantiateTestSuiteCompletedCbk =                       \
        nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_STARTED(func)  \
    printerInterface->instantiateModuleStartedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_COMPLETED(     \
    func)                                                                      \
    printerInterface->instantiateModuleCompletedCbk =                          \
        nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_CASE_STARTED(func)           \
    printerInterface->testCaseStartedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_CASE_COMPLETED(func)         \
    printerInterface->testCaseCompletedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_STARTED(func)  \
    printerInterface->testCaseInstanceStartedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_CASE_INSTANCE_COMPLETED(     \
    func)                                                                      \
    printerInterface->testCaseInstanceCompletedCbk =                           \
        nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_SUITE_STARTED(func)          \
    printerInterface->testSuiteStartedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_SUITE_COMPLETED(func)        \
    printerInterface->testSuiteCompletedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_STARTED(func) \
    printerInterface->testSuiteInstanceStartedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_TEST_SUITE_INSTANCE_COMPLETED(    \
    func)                                                                      \
    printerInterface->testSuiteInstanceCompletedCbk =                          \
        nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_MODULE_STARTED(func)              \
    printerInterface->moduleStartedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_MODULE_COMPLETED(func)            \
    printerInterface->moduleCompletedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_MODULE_INSTANCE_STARTED(func)     \
    printerInterface->moduleInstanceStartedCbk = nbp_printer_callback_##func;
#define NBP_PP_PARSE_PP_NBP_PRINTER_CALLBACK_MODULE_INSTANCE_COMPLETED(func)   \
    printerInterface->moduleInstanceCompletedCbk = nbp_printer_callback_##func;

#endif // end if _H_NBP_INTERNAL_API_PRINTER

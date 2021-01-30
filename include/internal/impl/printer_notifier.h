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

#ifndef _H_NBP_INTERNAL_IMPL_PRINTER_NOTIFIER
#define _H_NBP_INTERNAL_IMPL_PRINTER_NOTIFIER

#include "../api/memory.h"
#include "../details/printer_notifier.h"

extern nbp_printer_interface_t** gInternalNbpPrinterInterfaces;
extern unsigned int gInternalNbpPrinterInterfacesSize;

#define INTERNAL_NBP_CALLBACK_IS_SET(cbk)                                      \
    gInternalNbpPrinterInterfaces[i]->cbk != NBP_NULLPTR

void internal_nbp_notify_printer_init()
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        gInternalNbpPrinterInterfaces[i]->configFunction(
            gInternalNbpPrinterInterfaces[i]);
        if (INTERNAL_NBP_CALLBACK_IS_SET(initCbk)) {
            gInternalNbpPrinterInterfaces[i]->initCbk();
        }
        gInternalNbpPrinterInterfaces[i]->isInitialized = 1;
    }
}

void internal_nbp_notify_printer_uninit()
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(uninitCbk)) {
            gInternalNbpPrinterInterfaces[i]->uninitCbk();
        }
        gInternalNbpPrinterInterfaces[i]->isInitialized = 0;
    }
}

void internal_nbp_notify_printer_handle_version_command()
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(handleVersionCommandCbk)) {
            gInternalNbpPrinterInterfaces[i]->handleVersionCommandCbk();
        }
    }
}

void internal_nbp_notify_printer_on_error(
    nbp_error_code_e errorCode,
    int line,
    const char* file)
{
    nbp_error_t error;

    error.errorCode   = errorCode;
    error.line        = line;
    error.file        = file;
    error.contextType = ect_empty;

    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpPrinterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_printer_on_error_string_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    const char* context)
{
    nbp_error_t error;

    error.errorCode     = errorCode;
    error.line          = line;
    error.file          = file;
    error.contextType   = ect_string;
    error.stringContext = context;

    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpPrinterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_printer_on_error_custom_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    void* context)
{
    nbp_error_t error;

    error.errorCode     = errorCode;
    error.line          = line;
    error.file          = file;
    error.contextType   = ect_custom;
    error.customContext = context;

    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpPrinterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_printer_on_exit(nbp_error_code_e errorCode)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(exitCbk)) {
            gInternalNbpPrinterInterfaces[i]->exitCbk(errorCode);
        }
    }
}

void internal_nbp_notify_printer_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestCaseCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateTestCaseCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateTestSuiteStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateTestSuiteCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_instantiate_module_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateModuleStartedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_printer_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->instantiateModuleCompletedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_printer_test_case_started(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseStartedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_case_completed(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseCompletedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_case_instance_started(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseInstanceStartedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_case_instance_completed(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testCaseInstanceCompletedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_started(nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteStartedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_completed(
    nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteCompletedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_instance_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteInstanceStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_test_suite_instance_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->testSuiteInstanceCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_printer_module_started(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleStartedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_printer_module_completed(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleCompletedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_printer_module_instance_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceStartedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleInstanceStartedCbk(
                moduleInstance);
        }
    }
}

void internal_nbp_notify_printer_module_instance_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpPrinterInterfacesSize; i++) {
        if (gInternalNbpPrinterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceCompletedCbk)) {
            gInternalNbpPrinterInterfaces[i]->moduleInstanceCompletedCbk(
                moduleInstance);
        }
    }
}

#undef INTERNAL_NBP_CALLBACK_IS_SET

#endif // end if _H_NBP_INTERNAL_IMPL_PRINTER_NOTIFIER

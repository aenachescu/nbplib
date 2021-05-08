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

#ifndef _H_NBP_INTERNAL_IMPL_REPORTER_NOTIFIER
#define _H_NBP_INTERNAL_IMPL_REPORTER_NOTIFIER

#include "../api/memory.h"
#include "../api/module.h"
#include "../details/reporter_notifier.h"
#include "../details/utils.h"

extern nbp_module_instance_t* gInternalNbpMainModuleInstance;
extern nbp_reporter_interface_t** gInternalNbpReporterInterfaces;
extern unsigned int gInternalNbpReporterInterfacesSize;

#define INTERNAL_NBP_CALLBACK_IS_SET(cbk)                                      \
    gInternalNbpReporterInterfaces[i]->cbk != NBP_NULLPTR

static void internal_nbp_initialize_reporter_statistics(
    nbp_reporter_statistics_t* statistics)
{
    statistics->totalNumberOfTestCases =
        gInternalNbpMainModuleInstance->totalNumberOfTestCases;
    statistics->totalNumberOfTestCaseInstances =
        gInternalNbpMainModuleInstance->totalNumberOfTestCaseInstances;
    statistics->totalNumberOfTestSuites =
        gInternalNbpMainModuleInstance->totalNumberOfTestSuites;
    statistics->totalNumberOfTestSuiteInstances =
        gInternalNbpMainModuleInstance->totalNumberOfTestSuiteInstances;
    statistics->totalNumberOfModules =
        gInternalNbpMainModuleInstance->totalNumberOfModules;
    statistics->totalNumberOfModuleInstances =
        gInternalNbpMainModuleInstance->totalNumberOfModuleInstances;

    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestCases,
        statistics->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestCaseInstances,
        statistics->numberOfTestCaseInstances,
        NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestSuites,
        statistics->numberOfTestSuites,
        NBP_NUMBER_OF_TEST_SUITE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfTestSuiteInstances,
        statistics->numberOfTestSuiteInstances,
        NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfModules,
        statistics->numberOfModules,
        NBP_NUMBER_OF_MODULE_STATES);
    internal_nbp_copy_array_of_atomic_uint(
        gInternalNbpMainModuleInstance->numberOfModuleInstances,
        statistics->numberOfModuleInstances,
        NBP_NUMBER_OF_MODULE_INSTANCE_STATES);

    statistics->totalNumberOfModuleInstances += 1;
    statistics->totalNumberOfModules +=
        gInternalNbpMainModuleInstance->numberOfRuns;

    unsigned int pos = internal_nbp_get_module_instance_state_position(
        NBP_MODULE_INSTANCE_GET_STATE(gInternalNbpMainModuleInstance));
    statistics->numberOfModuleInstances[pos] += 1;
}

void internal_nbp_notify_reporter_init()
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        gInternalNbpReporterInterfaces[i]->configFunction(
            gInternalNbpReporterInterfaces[i]);
        if (INTERNAL_NBP_CALLBACK_IS_SET(initCbk)) {
            gInternalNbpReporterInterfaces[i]->initCbk();
        }
        gInternalNbpReporterInterfaces[i]->isInitialized = 1;
    }
}

void internal_nbp_notify_reporter_uninit()
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(uninitCbk)) {
            gInternalNbpReporterInterfaces[i]->uninitCbk();
        }
        gInternalNbpReporterInterfaces[i]->isInitialized = 0;
    }
}

void internal_nbp_notify_reporter_handle_version_command()
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(handleVersionCommandCbk)) {
            gInternalNbpReporterInterfaces[i]->handleVersionCommandCbk();
        }
    }
}

void internal_nbp_notify_reporter_on_error(
    nbp_error_code_e errorCode,
    int line,
    const char* file)
{
    nbp_error_t error;

    error.errorCode   = errorCode;
    error.line        = line;
    error.file        = file;
    error.contextType = ect_empty;

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpReporterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_reporter_on_error_string_context(
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

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpReporterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_reporter_on_error_custom_context(
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

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(errorCbk)) {
            gInternalNbpReporterInterfaces[i]->errorCbk(error);
        }
    }
}

void internal_nbp_notify_reporter_on_exit(nbp_error_code_e errorCode)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(exitCbk)) {
            gInternalNbpReporterInterfaces[i]->exitCbk(errorCode);
        }
    }
}

void internal_nbp_notify_reporter_before_run()
{
    nbp_reporter_statistics_t statistics;

    internal_nbp_initialize_reporter_statistics(&statistics);

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(beforeRunCbk)) {
            gInternalNbpReporterInterfaces[i]->beforeRunCbk(&statistics);
        }
    }
}

void internal_nbp_notify_reporter_after_run()
{
    nbp_reporter_statistics_t statistics;

    internal_nbp_initialize_reporter_statistics(&statistics);

    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(afterRunCbk)) {
            gInternalNbpReporterInterfaces[i]->afterRunCbk(&statistics);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestCaseCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateTestCaseCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateTestSuiteStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateTestSuiteCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateTestSuiteCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_module_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateModuleStartedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_reporter_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(instantiateModuleCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->instantiateModuleCompletedCbk(
                moduleInstance,
                moduleInstance->parent);
        }
    }
}

void internal_nbp_notify_reporter_test_case_started(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseStartedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_case_completed(nbp_test_case_t* testCase)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseCompletedCbk(
                testCase,
                testCase->testCaseInstance,
                testCase->testCaseInstance->testSuite,
                testCase->testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_case_instance_started(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseInstanceStartedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_case_instance_completed(
    nbp_test_case_instance_t* testCaseInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testCaseInstanceCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testCaseInstanceCompletedCbk(
                testCaseInstance,
                testCaseInstance->testSuite,
                testCaseInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_started(
    nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteStartedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_completed(
    nbp_test_suite_t* testSuite)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteCompletedCbk(
                testSuite,
                testSuite->testSuiteInstance,
                testSuite->testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_instance_started(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteInstanceStartedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_test_suite_instance_completed(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(testSuiteInstanceCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->testSuiteInstanceCompletedCbk(
                testSuiteInstance,
                testSuiteInstance->module);
        }
    }
}

void internal_nbp_notify_reporter_module_started(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleStartedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_reporter_module_completed(nbp_module_t* module)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleCompletedCbk(
                module,
                module->moduleInstance);
        }
    }
}

void internal_nbp_notify_reporter_module_instance_started(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceStartedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleInstanceStartedCbk(
                moduleInstance);
        }
    }
}

void internal_nbp_notify_reporter_module_instance_completed(
    nbp_module_instance_t* moduleInstance)
{
    for (unsigned int i = 0; i < gInternalNbpReporterInterfacesSize; i++) {
        if (gInternalNbpReporterInterfaces[i]->isInitialized == 0) {
            continue;
        }
        if (INTERNAL_NBP_CALLBACK_IS_SET(moduleInstanceCompletedCbk)) {
            gInternalNbpReporterInterfaces[i]->moduleInstanceCompletedCbk(
                moduleInstance);
        }
    }
}

#undef INTERNAL_NBP_CALLBACK_IS_SET

#endif // end if _H_NBP_INTERNAL_IMPL_REPORTER_NOTIFIER

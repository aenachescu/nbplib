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

#ifndef _H_NBP_INTERNAL_IMPL_SCHEDULER
#define _H_NBP_INTERNAL_IMPL_SCHEDULER

#include "../api/error.h"
#include "../api/exit.h"
#include "../details/printer_notifier.h"
#include "../details/scheduler.h"
#include "../types/sync.h"

extern int gInternalNbpSchedulerRunEnabled;

extern NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRanTestCases;

static int internal_nbp_scheduler_run_module(nbp_module_t* module)
{
    if (module == NBP_NULLPTR) {
        return (int) ms_running;
    }

    int oldModuleInstanceState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &module->moduleInstance->state,
        mis_ready,
        mis_running);
    if (oldModuleInstanceState != mis_ready
        && oldModuleInstanceState != mis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "module instance is not ready or running");
        NBP_EXIT(ec_unexpected_state);
        return ms_failed;
    }

    int oldModuleState =
        NBP_ATOMIC_INT_COMPARE_AND_SWAP(&module->state, ms_ready, ms_running);
    if (oldModuleState == ms_running) {
        nbp_error_code_e err = NBP_SYNC_EVENT_WAIT(module->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "wait for module runEvent failed");
            NBP_EXIT(ec_sync_error);
            return ms_failed;
        }

        return ms_running;
    }

    if (oldModuleState == ms_ready) {
        int parentModuleState =
            internal_nbp_scheduler_run_module(module->moduleInstance->parent);
        if (parentModuleState != ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "parent module is not running");
            NBP_EXIT(ec_unexpected_state);
            return ms_failed;
        }

        if (oldModuleInstanceState == mis_ready) {
            internal_nbp_module_instance_update_state_stats(
                module->moduleInstance,
                mis_ready,
                mis_running);

            internal_nbp_notify_printer_module_instance_started(
                module->moduleInstance);
        }

        internal_nbp_module_update_state_stats(module, ms_ready, ms_running);

        internal_nbp_notify_printer_module_started(module);

        nbp_error_code_e err = NBP_SYNC_EVENT_NOTIFY(module->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to notify module runEvent");
            NBP_EXIT(ec_sync_error);
            return ms_failed;
        }

        return ms_running;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_state,
        "module is not ready or running");
    NBP_EXIT(ec_unexpected_state);
    return ms_failed;
}

static int internal_nbp_scheduler_run_test_suite(nbp_test_suite_t* testSuite)
{
    int oldTestSuiteInstanceState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->testSuiteInstance->state,
        tsis_ready,
        tsis_running);
    if (oldTestSuiteInstanceState != tsis_ready
        && oldTestSuiteInstanceState != tsis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test suite instance is not ready or running");
        NBP_EXIT(ec_unexpected_state);
        return tss_failed;
    }

    int oldTestSuiteState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->state,
        tss_ready,
        tss_running);

    if (oldTestSuiteState == tss_running) {
        nbp_error_code_e err = NBP_SYNC_EVENT_WAIT(testSuite->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "wait for test suite runEvent failed");
            NBP_EXIT(ec_sync_error);
            return tss_failed;
        }

        return tss_running;
    }

    if (oldTestSuiteState == tss_ready) {
        int moduleState = internal_nbp_scheduler_run_module(
            testSuite->testSuiteInstance->module);
        if (moduleState != ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "parent module is not running");
            NBP_EXIT(ec_unexpected_state);
            return tss_failed;
        }

        if (oldTestSuiteInstanceState == tsis_ready) {
            internal_nbp_test_suite_instance_update_state_stats(
                testSuite->testSuiteInstance,
                tsis_ready,
                tsis_running);

            internal_nbp_notify_printer_test_suite_instance_started(
                testSuite->testSuiteInstance);
        }

        internal_nbp_test_suite_update_state_stats(
            testSuite,
            tss_ready,
            tss_running);

        internal_nbp_notify_printer_test_suite_started(testSuite);

        nbp_error_code_e err = NBP_SYNC_EVENT_NOTIFY(testSuite->runEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to notify test suite runEvent");
            NBP_EXIT(ec_sync_error);
            return tss_failed;
        }

        return tss_running;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_state,
        "test suite is not ready or running");
    NBP_EXIT(ec_unexpected_state);
    return tss_failed;
}

static int internal_nbp_scheduler_setup_module(nbp_module_t* module)
{
    if (module == NBP_NULLPTR) {
        return (int) sf_is_processed;
    }

    nbp_error_code_e err;

    int oldModuleInstanceValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &module->moduleInstance->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldModuleInstanceValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    int oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &module->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    if (oldValue == (int) sf_is_processed) {
        err = NBP_SYNC_EVENT_WAIT(module->setupEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to wait for module setupEvent");
            NBP_EXIT(ec_sync_error);
            return (int) sf_is_not_set;
        }

        oldValue = NBP_ATOMIC_INT_LOAD(&module->isSkipped);
        if (oldValue == (int) sf_is_set || oldValue == (int) sf_is_processed) {
            return oldValue;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected module isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    if (oldValue == (int) sf_is_not_set) {
        int parentValue =
            internal_nbp_scheduler_setup_module(module->moduleInstance->parent);

        if (parentValue == (int) sf_is_processed) {
            if (module->moduleInstance->setupDetails != NBP_NULLPTR) {
                module->moduleInstance->setupDetails->function(module);
            }

            err = NBP_SYNC_EVENT_NOTIFY(module->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify module setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_processed;
        }

        if (parentValue == (int) sf_is_set) {
            oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
                &module->isSkipped,
                sf_is_processed,
                sf_is_set);

            if (oldValue != (int) sf_is_processed) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_unexpected_internal_data,
                    "unexpected module isSkipped flag value");
                NBP_EXIT(ec_unexpected_internal_data);
            }

            err = NBP_SYNC_EVENT_NOTIFY(module->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify module setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_set;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected module isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_internal_data,
        "unexpected module isSkipped flag value");
    NBP_EXIT(ec_unexpected_internal_data);
    return (int) sf_is_not_set;
}

static int internal_nbp_scheduler_compute_module_instance_state(
    nbp_module_instance_t* moduleInstance)
{
    unsigned int numberOfPassedModules  = 0;
    unsigned int numberOfSkippedModules = 0;

    for (unsigned int i = 0; i < moduleInstance->numberOfRuns; i++) {
        nbp_module_state_e state =
            NBP_MODULE_GET_STATE(&moduleInstance->runs[i]);
        if (state == ms_passed) {
            numberOfPassedModules++;
        } else if (state == ms_skipped) {
            numberOfSkippedModules++;
        }
    }

    if (numberOfPassedModules == moduleInstance->numberOfRuns) {
        return mis_passed;
    }

    if (numberOfSkippedModules == moduleInstance->numberOfRuns) {
        return mis_skipped;
    }

    return mis_failed;
}

static int internal_nbp_scheduler_complete_module_instance(
    nbp_module_instance_t* moduleInstance)
{
    unsigned int num = NBP_ATOMIC_UINT_ADD_AND_FETCH(
        &moduleInstance->numberOfCompletedRuns,
        1U);
    if (num != moduleInstance->numberOfRuns) {
        return 0;
    }

    int newState =
        internal_nbp_scheduler_compute_module_instance_state(moduleInstance);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &moduleInstance->state,
        mis_running,
        newState);

    if (oldState != mis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "module instance is not running");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    internal_nbp_module_instance_update_state_stats(
        moduleInstance,
        mis_running,
        (nbp_module_instance_state_e) newState);

    internal_nbp_notify_printer_module_instance_completed(moduleInstance);

    return 1;
}

static int internal_nbp_scheduler_compute_module_state(nbp_module_t* module)
{
    unsigned int passedTasks  = 0;
    unsigned int skippedTasks = 0;

    nbp_test_case_instance_t* testCaseInstance = module->firstTestCaseInstance;
    nbp_test_suite_instance_t* testSuiteInstance =
        module->firstTestSuiteInstance;
    nbp_module_instance_t* moduleInstance = module->firstModuleInstance;

    while (testCaseInstance != NBP_NULLPTR) {
        nbp_test_case_instance_state_e state =
            NBP_TEST_CASE_INSTANCE_GET_STATE(testCaseInstance);

        if (state == tcis_passed) {
            passedTasks++;
        } else if (state == tcis_skipped) {
            skippedTasks++;
        }

        testCaseInstance = testCaseInstance->next;
    }

    while (testSuiteInstance != NBP_NULLPTR) {
        nbp_test_suite_instance_state_e state =
            NBP_TEST_SUITE_INSTANCE_GET_STATE(testSuiteInstance);

        if (state == tsis_passed) {
            passedTasks++;
        } else if (state == tsis_skipped) {
            skippedTasks++;
        }

        testSuiteInstance = testSuiteInstance->next;
    }

    while (moduleInstance != NBP_NULLPTR) {
        nbp_module_instance_state_e state =
            NBP_MODULE_INSTANCE_GET_STATE(moduleInstance);

        if (state == mis_passed) {
            passedTasks++;
        } else if (state == mis_skipped) {
            skippedTasks++;
        }

        moduleInstance = moduleInstance->next;
    }

    if (passedTasks == module->numberOfTasks) {
        return ms_passed;
    }

    if (skippedTasks == module->numberOfTasks) {
        return ms_skipped;
    }

    return ms_failed;
}

static void internal_nbp_scheduler_teardown_module(nbp_module_t* module)
{
    while (module != NBP_NULLPTR) {
        unsigned int num =
            NBP_ATOMIC_UINT_ADD_AND_FETCH(&module->numberOfCompletedTasks, 1U);
        if (num != module->numberOfTasks) {
            return;
        }

        int isSkipped = NBP_ATOMIC_INT_LOAD(&module->isSkipped);
        if (isSkipped == (int) sf_is_processed) {
            if (module->moduleInstance->teardownDetails != NBP_NULLPTR) {
                module->moduleInstance->teardownDetails->function(module);
            }
        }

        int newState = internal_nbp_scheduler_compute_module_state(module);

        int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
            &module->state,
            ms_running,
            newState);

        if (oldState != ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "module is not running");
            NBP_EXIT(ec_unexpected_state);
            return;
        }

        internal_nbp_module_update_state_stats(
            module,
            ms_running,
            (nbp_module_state_e) newState);

        internal_nbp_notify_printer_module_completed(module);

        int isCompletedInstance =
            internal_nbp_scheduler_complete_module_instance(
                module->moduleInstance);
        if (isCompletedInstance == 0) {
            break;
        }

        module = module->moduleInstance->parent;
    }
}

static int internal_nbp_scheduler_setup_test_suite(nbp_test_suite_t* testSuite)
{
    nbp_error_code_e err;

    int oldTsiValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->testSuiteInstance->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldTsiValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    int oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->isSkipped,
        sf_is_not_set,
        sf_is_processed);

    if (oldValue == (int) sf_is_set) {
        return (int) sf_is_set;
    }

    if (oldValue == (int) sf_is_processed) {
        err = NBP_SYNC_EVENT_WAIT(testSuite->setupEvent);
        if (err != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to wait for test suite setupEvent");
            NBP_EXIT(ec_sync_error);
            return (int) sf_is_not_set;
        }

        oldValue = NBP_ATOMIC_INT_LOAD(&testSuite->isSkipped);
        if (oldValue == (int) sf_is_set || oldValue == (int) sf_is_processed) {
            return oldValue;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected test suite isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    if (oldValue == (int) sf_is_not_set) {
        int parentValue = internal_nbp_scheduler_setup_module(
            testSuite->testSuiteInstance->module);

        if (parentValue == (int) sf_is_processed) {
            if (testSuite->testSuiteInstance->setupDetails != NBP_NULLPTR) {
                testSuite->testSuiteInstance->setupDetails->function(testSuite);
            }

            err = NBP_SYNC_EVENT_NOTIFY(testSuite->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify test suite setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_processed;
        }

        if (parentValue == (int) sf_is_set) {
            oldValue = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
                &testSuite->isSkipped,
                sf_is_processed,
                sf_is_set);

            if (oldValue != (int) sf_is_processed) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_unexpected_internal_data,
                    "unexpected test suite isSkipped flag value");
                NBP_EXIT(ec_unexpected_internal_data);
            }

            err = NBP_SYNC_EVENT_NOTIFY(testSuite->setupEvent);
            if (err != ec_success) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_sync_error,
                    "failed to notify test suite setupEvent");
                NBP_EXIT(ec_sync_error);
                return (int) sf_is_not_set;
            }

            return (int) sf_is_set;
        }

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_internal_data,
            "unexpected test suite isSkipped flag value");
        NBP_EXIT(ec_unexpected_internal_data);
        return (int) sf_is_not_set;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_unexpected_internal_data,
        "unexpected test suite isSkipped flag value");
    NBP_EXIT(ec_unexpected_internal_data);
    return (int) sf_is_not_set;
}

static int internal_nbp_scheduler_complete_test_suite_instance(
    nbp_test_suite_instance_t* testSuiteInstance)
{
    unsigned int num = NBP_ATOMIC_UINT_ADD_AND_FETCH(
        &testSuiteInstance->numberOfCompletedRuns,
        1U);
    if (num != testSuiteInstance->numberOfRuns) {
        return 0;
    }

    int newState = tsis_passed;

    do {
        num = internal_nbp_get_number_of_test_suites(
            testSuiteInstance->numberOfTestSuites,
            tss_failed);
        if (num > 0) {
            newState = tsis_failed;
            break;
        }

        num = internal_nbp_get_number_of_test_suites(
            testSuiteInstance->numberOfTestSuites,
            tss_skipped);

        if (num == testSuiteInstance->numberOfRuns) {
            newState = tsis_skipped;
            break;
        }

        if (num > 0) {
            newState = tsis_failed;
            break;
        }
    } while (0);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuiteInstance->state,
        tsis_running,
        newState);

    if (oldState != tsis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test suite instance is not running");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    internal_nbp_test_suite_instance_update_state_stats(
        testSuiteInstance,
        tsis_running,
        (nbp_test_suite_instance_state_e) newState);

    internal_nbp_notify_printer_test_suite_instance_completed(
        testSuiteInstance);

    return 1;
}

static void internal_nbp_scheduler_teardown_test_suite(
    nbp_test_suite_t* testSuite)
{
    unsigned int num =
        NBP_ATOMIC_UINT_ADD_AND_FETCH(&testSuite->numberOfCompletedTasks, 1U);
    if (num != testSuite->totalNumberOfTestCaseInstances) {
        return;
    }

    int isSkipped = NBP_ATOMIC_INT_LOAD(&testSuite->isSkipped);
    if (isSkipped == (int) sf_is_processed) {
        if (testSuite->testSuiteInstance->teardownDetails != NBP_NULLPTR) {
            testSuite->testSuiteInstance->teardownDetails->function(testSuite);
        }
    }

    int newState = tss_passed;

    do {
        num = internal_nbp_get_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            tcis_failed);
        if (num > 0) {
            newState = tss_failed;
            break;
        }

        num = internal_nbp_get_number_of_test_case_instances(
            testSuite->numberOfTestCaseInstances,
            tcis_skipped);

        if (num == testSuite->totalNumberOfTestCaseInstances) {
            newState = tss_skipped;
            break;
        }

        if (num > 0) {
            newState = tss_failed;
            break;
        }
    } while (0);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testSuite->state,
        tss_running,
        newState);

    if (oldState != tss_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test suite is not running");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    internal_nbp_test_suite_update_state_stats(
        testSuite,
        tss_running,
        (nbp_test_suite_state_e) newState);

    internal_nbp_notify_printer_test_suite_completed(testSuite);

    int isCompletedInstance =
        internal_nbp_scheduler_complete_test_suite_instance(
            testSuite->testSuiteInstance);
    if (isCompletedInstance == 1) {
        internal_nbp_scheduler_teardown_module(
            testSuite->testSuiteInstance->module);
    }
}

static int internal_nbp_scheduler_complete_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance)
{
    unsigned int num = NBP_ATOMIC_UINT_ADD_AND_FETCH(
        &testCaseInstance->numberOfCompletedRuns,
        1U);
    if (num != testCaseInstance->numberOfRuns) {
        return 0;
    }

    int newState = tcis_passed;

    do {
        num = internal_nbp_get_number_of_test_cases(
            testCaseInstance->numberOfTestCases,
            tcs_failed);
        if (num > 0) {
            newState = tcis_failed;
            break;
        }

        num = internal_nbp_get_number_of_test_cases(
            testCaseInstance->numberOfTestCases,
            tcs_skipped);

        if (num == testCaseInstance->numberOfRuns) {
            newState = tcis_skipped;
            break;
        }

        if (num > 0) {
            newState = tcis_failed;
            break;
        }
    } while (0);

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCaseInstance->state,
        tcis_running,
        newState);

    if (oldState != tcis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case instance is not running");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    internal_nbp_test_case_instance_update_state_stats(
        testCaseInstance,
        tcis_running,
        (nbp_test_case_instance_state_e) newState);

    internal_nbp_notify_printer_test_case_instance_completed(testCaseInstance);

    return 1;
}

static void internal_nbp_scheduler_run_skipped_test_case(
    nbp_test_case_t* testCase)
{
    ((void) testCase);
}

static void internal_nbp_scheduler_run_ready_test_case(
    nbp_test_case_t* testCase)
{
    internal_nbp_test_case_update_state_stats(testCase, tcs_ready, tcs_running);
    internal_nbp_notify_printer_test_case_started(testCase);

    if (testCase->testCaseInstance->setupDetails != NBP_NULLPTR) {
        testCase->testCaseInstance->setupDetails->function(testCase);
    }

    testCase->testCaseInstance->testCaseDetails->function(testCase);

    if (testCase->testCaseInstance->teardownDetails != NBP_NULLPTR) {
        testCase->testCaseInstance->teardownDetails->function(testCase);
    }

    int newState = (int) tcs_passed;
    if (internal_nbp_is_failed_test_case(testCase) == 1) {
        newState = (int) tcs_failed;
    }

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->state,
        tcs_running,
        newState);
    if (oldState != (int) tcs_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case is not running");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    internal_nbp_test_case_update_state_stats(
        testCase,
        tcs_running,
        (nbp_test_case_state_e) newState);
    internal_nbp_notify_printer_test_case_completed(testCase);
}

void internal_nbp_scheduler_run_test_case(nbp_test_case_t* testCase)
{
    if (gInternalNbpSchedulerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_scheduler_run_is_disabled,
            "a test case can be run only from scheduler's run callback");
        NBP_EXIT(ec_scheduler_run_is_disabled);
        return;
    }

    int oldInstanceState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->testCaseInstance->state,
        tcis_ready,
        tcis_running);
    if (oldInstanceState != tcis_ready && oldInstanceState != tcis_running) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case instance is not ready or running");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    int oldState = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->state,
        (int) tcs_ready,
        (int) tcs_running);

    if (oldState != (int) tcs_ready) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "test case is not ready");
        NBP_EXIT(ec_unexpected_state);
        return;
    }

    if (testCase->testCaseInstance->module != NBP_NULLPTR) {
        int moduleState = internal_nbp_scheduler_run_module(
            testCase->testCaseInstance->module);
        if (moduleState != (int) ms_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "module is not running");
            NBP_EXIT(ec_unexpected_state);
            return;
        }
    } else if (testCase->testCaseInstance->testSuite != NBP_NULLPTR) {
        int testSuiteState = internal_nbp_scheduler_run_test_suite(
            testCase->testCaseInstance->testSuite);
        if (testSuiteState != (int) tss_running) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_state,
                "test suite is not running");
            NBP_EXIT(ec_unexpected_state);
            return;
        }
    } else {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "test case has no parent");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    if (oldInstanceState == tcis_ready) {
        internal_nbp_test_case_instance_update_state_stats(
            testCase->testCaseInstance,
            tcis_ready,
            tcis_running);

        internal_nbp_notify_printer_test_case_instance_started(
            testCase->testCaseInstance);
    }

    int tciIsSkipped = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
        &testCase->testCaseInstance->isSkipped,
        (int) sf_is_not_set,
        (int) sf_is_processed);

    if (tciIsSkipped == (int) sf_is_set) {
        internal_nbp_scheduler_run_skipped_test_case(testCase);
    } else {
        int isSkipped = NBP_ATOMIC_INT_COMPARE_AND_SWAP(
            &testCase->isSkipped,
            (int) sf_is_not_set,
            (int) sf_is_processed);

        if (isSkipped == (int) sf_is_set) {
            internal_nbp_scheduler_run_skipped_test_case(testCase);
        } else if (isSkipped == (int) sf_is_not_set) {
            int parentIsSkipped;
            if (testCase->testCaseInstance->module != NBP_NULLPTR) {
                parentIsSkipped = internal_nbp_scheduler_setup_module(
                    testCase->testCaseInstance->module);
            } else {
                parentIsSkipped = internal_nbp_scheduler_setup_test_suite(
                    testCase->testCaseInstance->testSuite);
            }

            if (parentIsSkipped == (int) sf_is_processed) {
                internal_nbp_scheduler_run_ready_test_case(testCase);
            } else if (parentIsSkipped == (int) sf_is_set) {
                internal_nbp_scheduler_run_skipped_test_case(testCase);
            } else {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_unexpected_internal_data,
                    "unexpected value for parent isSkipped flag");
                NBP_EXIT(ec_unexpected_internal_data);
                return;
            }
        } else {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_unexpected_internal_data,
                "unexpected value for isSkipped flag");
            NBP_EXIT(ec_unexpected_internal_data);
            return;
        }
    }

    int isCompletedInstance =
        internal_nbp_scheduler_complete_test_case_instance(
            testCase->testCaseInstance);

    if (isCompletedInstance == 1) {
        if (testCase->testCaseInstance->module != NBP_NULLPTR) {
            internal_nbp_scheduler_teardown_module(
                testCase->testCaseInstance->module);
        } else {
            internal_nbp_scheduler_teardown_test_suite(
                testCase->testCaseInstance->testSuite);
        }
    }

    NBP_ATOMIC_UINT_ADD_AND_FETCH(&gInternalNbpNumberOfRanTestCases, 1);
}

void internal_nbp_scheduler_run_test_case_instance(
    nbp_test_case_instance_t* testCaseInstance)
{
    if (gInternalNbpSchedulerRunEnabled != 1) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_scheduler_run_is_disabled,
            "a test case instance can be run only from scheduler's run "
            "callback");
        NBP_EXIT(ec_scheduler_run_is_disabled);
        return;
    }

    for (unsigned int i = 0; i < testCaseInstance->numberOfRuns; i++) {
        internal_nbp_scheduler_run_test_case(&testCaseInstance->runs[i]);
    }
}

#endif // end if _H_NBP_INTERNAL_IMPL_SCHEDULER

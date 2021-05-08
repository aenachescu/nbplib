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

#ifndef _H_NBP_INTERNAL_REPORTERS_LINUX_DEFAULT_REPORTER
#define _H_NBP_INTERNAL_REPORTERS_LINUX_DEFAULT_REPORTER

#include "../api/error.h"
#include "../api/exit.h"
#include "../api/module.h"
#include "../api/reporter.h"
#include "../api/test_case.h"
#include "../api/test_suite.h"
#include "../api/version.h"
#include "../build_configuration.h"
#include "../types/error.h"

#include <stdio.h>

#define NBP_DR_TEST_CASE_EMOJI  "\xF0\x9F\x93\x9D"
#define NBP_DR_TEST_SUITE_EMOJI "\xF0\x9F\x93\x9C"
#define NBP_DR_MODULE_EMOJI     "\xF0\x9F\x93\x81"

#define NBP_DR_COLOR_NORMAL "\x1B[0m"
#define NBP_DR_COLOR_RED    "\x1B[31m"
#define NBP_DR_COLOR_GREEN  "\x1B[32m"
#define NBP_DR_COLOR_YELLOW "\x1B[33m"

#define NBP_DR_CLEAR_LINE "\x1B[2K\r"

#ifdef NBP_MT_SUPPORT

#include <pthread.h>

static inline nbp_error_code_e internal_nbp_dr_mutex_init(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_init(mutex, NULL) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_dr_mutex_uninit(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_destroy(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_dr_mutex_lock(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_lock(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_dr_mutex_unlock(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_unlock(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

#define INTERNAL_NBP_DR_DECLARE_MUTEX(name)                                    \
    pthread_mutex_t name = PTHREAD_MUTEX_INITIALIZER;

#define INTERNAL_NBP_DR_MUTEX_INIT(name) internal_nbp_dr_mutex_init(&name)

#define INTERNAL_NBP_DR_MUTEX_UNINIT(name) internal_nbp_dr_mutex_uninit(&name)

#define INTERNAL_NBP_DR_MUTEX_LOCK(name) internal_nbp_dr_mutex_lock(&name)

#define INTERNAL_NBP_DR_MUTEX_UNLOCK(name) internal_nbp_dr_mutex_unlock(&name)

#else

static inline nbp_error_code_e internal_nbp_dr_mutex_init_dummy()
{
    return ec_success;
}

static inline nbp_error_code_e internal_nbp_dr_mutex_uninit_dummy()
{
    return ec_success;
}

static inline nbp_error_code_e internal_nbp_dr_mutex_lock_dummy()
{
    return ec_success;
}

static inline nbp_error_code_e internal_nbp_dr_mutex_unlock_dummy()
{
    return ec_success;
}

#define INTERNAL_NBP_DR_DECLARE_MUTEX(name)

#define INTERNAL_NBP_DR_MUTEX_INIT(name) internal_nbp_dr_mutex_init_dummy()

#define INTERNAL_NBP_DR_MUTEX_UNINIT(name) internal_nbp_dr_mutex_uninit_dummy()

#define INTERNAL_NBP_DR_MUTEX_LOCK(name) internal_nbp_dr_mutex_lock_dummy()

#define INTERNAL_NBP_DR_MUTEX_UNLOCK(name) internal_nbp_dr_mutex_unlock_dummy()

#endif // end if NBP_MT_SUPPORT

enum nbp_dr_task_type_e
{
    tt_unknown             = 0x60000000,
    tt_test_case_instance  = 0x60000001,
    tt_test_suite_instance = 0x60000002,
    tt_module_instance     = 0x60000003,
    tt_module              = 0x60000004,
};
typedef enum nbp_dr_task_type_e nbp_dr_task_type_e;

struct nbp_dr_test_case_instance_task_t;
struct nbp_dr_test_suite_instance_task_t;

struct nbp_dr_message_list_t
{
    char* message;
    struct nbp_dr_message_list_t* next;
};
typedef struct nbp_dr_message_list_t nbp_dr_message_list_t;

struct nbp_dr_test_case_task_t
{
    nbp_test_case_t* testCase;
    unsigned int runId;

    struct nbp_dr_test_case_instance_task_t* testCaseInstanceTask;

    nbp_dr_message_list_t* messageList;
    nbp_dr_message_list_t* messageListLast;
};
typedef struct nbp_dr_test_case_task_t nbp_dr_test_case_task_t;

struct nbp_dr_test_case_instance_task_t
{
    nbp_test_case_instance_t* testCaseInstance;
    nbp_dr_test_case_task_t* testCaseTasks;
    unsigned int depth;

    struct nbp_dr_test_case_instance_task_t* next;
};
typedef struct nbp_dr_test_case_instance_task_t
    nbp_dr_test_case_instance_task_t;

struct nbp_dr_test_suite_task_t
{
    nbp_test_suite_t* testSuite;
    unsigned int runId;

    struct nbp_dr_test_suite_instance_task_t* testSuiteInstanceTask;

    nbp_dr_test_case_instance_task_t* firstTestCaseInstance;
    nbp_dr_test_case_instance_task_t* lastTestCaseInstance;
};
typedef struct nbp_dr_test_suite_task_t nbp_dr_test_suite_task_t;

struct nbp_dr_test_suite_instance_task_t
{
    nbp_test_suite_instance_t* testSuiteInstance;
    nbp_dr_test_suite_task_t* testSuiteTasks;
    unsigned int depth;
};
typedef struct nbp_dr_test_suite_instance_task_t
    nbp_dr_test_suite_instance_task_t;

struct nbp_dr_module_task_t
{
    nbp_module_t* module;
    unsigned int depth;
    unsigned int runId;
};
typedef struct nbp_dr_module_task_t nbp_dr_module_task_t;

struct nbp_dr_module_instance_task_t
{
    nbp_module_instance_t* moduleInstance;
    unsigned int depth;
};
typedef struct nbp_dr_module_instance_task_t nbp_dr_module_instance_task_t;

struct nbp_dr_task_tree_t
{
    nbp_dr_task_type_e taskType;
    union
    {
        nbp_dr_test_case_instance_task_t testCaseInstance;
        nbp_dr_test_suite_instance_task_t testSuiteInstance;
        nbp_dr_module_task_t module;
        nbp_dr_module_instance_task_t moduleInstance;
    };

    struct nbp_dr_task_tree_t* next;

    struct nbp_dr_task_tree_t* firstChild;
    struct nbp_dr_task_tree_t* lastChild;
};
typedef struct nbp_dr_task_tree_t nbp_dr_task_tree_t;

static nbp_dr_task_tree_t* gInternalNbpDrTaskTreeRoot        = NBP_NULLPTR;
static unsigned int gInternalNbpDrNumberOfTestCases          = 0;
static unsigned int gInternalNbpDrNumberOfCompletedTestCases = 0;
static int gInternalNbpDrProgressMessagePrinted              = 0;

INTERNAL_NBP_DR_DECLARE_MUTEX(gInternalNbpDrMutex);

static nbp_dr_task_tree_t* internal_nbp_dr_find_module_task(
    nbp_dr_task_tree_t* root,
    nbp_module_t* module)
{
    if (root == NBP_NULLPTR) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_case_instance) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_suite_instance) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_module && root->module.module == module) {
        return root;
    }

    nbp_dr_task_tree_t* child = root->firstChild;
    nbp_dr_task_tree_t* task  = NBP_NULLPTR;

    while (child != NBP_NULLPTR) {
        task = internal_nbp_dr_find_module_task(child, module);
        if (task != NBP_NULLPTR) {
            return task;
        }

        child = child->next;
    }

    return NBP_NULLPTR;
}

static nbp_dr_task_tree_t* internal_nbp_dr_find_test_suite_instance_task(
    nbp_dr_task_tree_t* root,
    nbp_test_suite_instance_t* testSuiteInstance)
{
    if (root == NBP_NULLPTR) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_case_instance) {
        return NBP_NULLPTR;
    }

    if (root->taskType == tt_test_suite_instance
        && root->testSuiteInstance.testSuiteInstance == testSuiteInstance) {
        return root;
    }

    nbp_dr_task_tree_t* child = root->firstChild;
    nbp_dr_task_tree_t* task  = NBP_NULLPTR;

    while (child != NBP_NULLPTR) {
        task = internal_nbp_dr_find_test_suite_instance_task(
            child,
            testSuiteInstance);
        if (task != NBP_NULLPTR) {
            return task;
        }

        child = child->next;
    }

    return NBP_NULLPTR;
}

static nbp_dr_test_suite_task_t* internal_nbp_dr_find_test_suite_task(
    nbp_test_suite_t* testSuite)
{
    nbp_dr_task_tree_t* testSuiteInstanceTask =
        internal_nbp_dr_find_test_suite_instance_task(
            gInternalNbpDrTaskTreeRoot,
            NBP_TEST_SUITE_GET_INSTANCE(testSuite));
    if (testSuiteInstanceTask == NBP_NULLPTR) {
        return NBP_NULLPTR;
    }

    nbp_dr_test_suite_task_t* tasks =
        testSuiteInstanceTask->testSuiteInstance.testSuiteTasks;
    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_SUITE_GET_INSTANCE(testSuite));

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        if (tasks[i].testSuite == testSuite) {
            return &tasks[i];
        }
    }

    return NBP_NULLPTR;
}

static void internal_nbp_dr_print_depth(
    unsigned int depth,
    unsigned int instantiationDepth)
{
    depth += (instantiationDepth / 2);

    if (instantiationDepth % 2 == 1) {
        printf("  ");
    }

    while (depth-- > 0) {
        printf("    ");
    }
}

static void internal_nbp_dr_print_test_case_task(
    nbp_dr_test_case_task_t* testCaseTask)
{
    unsigned int numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_CASE_GET_INSTANCE(testCaseTask->testCase));
    nbp_test_case_state_e state =
        NBP_TEST_CASE_GET_STATE(testCaseTask->testCase);
    const char* color = NBP_DR_COLOR_NORMAL;

    if (state == tcs_passed) {
        color = NBP_DR_COLOR_GREEN;
    } else if (state == tcs_failed) {
        color = NBP_DR_COLOR_RED;
    } else if (state == tcs_skipped) {
        color = NBP_DR_COLOR_YELLOW;
    }

    if (numberOfRuns > 1) {
        internal_nbp_dr_print_depth(
            NBP_TEST_CASE_GET_DEPTH(testCaseTask->testCase),
            testCaseTask->testCaseInstanceTask->depth + 1);
        printf(
            "%s %s%s%s#%u\n",
            NBP_DR_TEST_CASE_EMOJI,
            color,
            NBP_TEST_CASE_GET_NAME(testCaseTask->testCase),
            NBP_DR_COLOR_NORMAL,
            testCaseTask->runId);
    } else {
        internal_nbp_dr_print_depth(
            NBP_TEST_CASE_GET_DEPTH(testCaseTask->testCase),
            testCaseTask->testCaseInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_DR_TEST_CASE_EMOJI,
            color,
            NBP_TEST_CASE_GET_NAME(testCaseTask->testCase),
            NBP_DR_COLOR_NORMAL);
    }
}

static void internal_nbp_dr_print_test_case_instance_task(
    nbp_dr_test_case_instance_task_t* testCaseInstanceTask)
{
    unsigned int numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(
        testCaseInstanceTask->testCaseInstance);

    if (numberOfRuns > 1) {
        nbp_test_case_instance_state_e state = NBP_TEST_CASE_INSTANCE_GET_STATE(
            testCaseInstanceTask->testCaseInstance);
        const char* color = NBP_DR_COLOR_NORMAL;

        if (state == tcis_passed) {
            color = NBP_DR_COLOR_GREEN;
        } else if (state == tcis_failed) {
            color = NBP_DR_COLOR_RED;
        } else if (state == tcis_skipped) {
            color = NBP_DR_COLOR_YELLOW;
        }

        internal_nbp_dr_print_depth(
            NBP_TEST_CASE_INSTANCE_GET_DEPTH(
                testCaseInstanceTask->testCaseInstance),
            testCaseInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_DR_TEST_CASE_EMOJI,
            color,
            NBP_TEST_CASE_INSTANCE_GET_NAME(
                testCaseInstanceTask->testCaseInstance),
            NBP_DR_COLOR_NORMAL);
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        internal_nbp_dr_print_test_case_task(
            &testCaseInstanceTask->testCaseTasks[i]);
    }
}

static void internal_nbp_dr_print_test_suite_task(
    nbp_dr_test_suite_task_t* testSuiteTask)
{
    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_SUITE_GET_INSTANCE(testSuiteTask->testSuite));
    nbp_test_suite_state_e state =
        NBP_TEST_SUITE_GET_STATE(testSuiteTask->testSuite);
    const char* color = NBP_DR_COLOR_NORMAL;

    if (state == tss_passed) {
        color = NBP_DR_COLOR_GREEN;
    } else if (state == tss_failed) {
        color = NBP_DR_COLOR_RED;
    } else if (state == tss_skipped) {
        color = NBP_DR_COLOR_YELLOW;
    }

    if (numberOfRuns > 1) {
        internal_nbp_dr_print_depth(
            NBP_TEST_SUITE_GET_DEPTH(testSuiteTask->testSuite),
            testSuiteTask->testSuiteInstanceTask->depth + 1);
        printf(
            "%s %s%s%s#%u\n",
            NBP_DR_TEST_SUITE_EMOJI,
            color,
            NBP_TEST_SUITE_GET_NAME(testSuiteTask->testSuite),
            NBP_DR_COLOR_NORMAL,
            testSuiteTask->runId);
    } else {
        internal_nbp_dr_print_depth(
            NBP_TEST_SUITE_GET_DEPTH(testSuiteTask->testSuite),
            testSuiteTask->testSuiteInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_DR_TEST_SUITE_EMOJI,
            color,
            NBP_TEST_SUITE_GET_NAME(testSuiteTask->testSuite),
            NBP_DR_COLOR_NORMAL);
    }

    nbp_dr_test_case_instance_task_t* child =
        testSuiteTask->firstTestCaseInstance;

    while (child != NBP_NULLPTR) {
        internal_nbp_dr_print_test_case_instance_task(child);
        child = child->next;
    }
}

static void internal_nbp_dr_print_test_suite_instance_task(
    nbp_dr_test_suite_instance_task_t* testSuiteInstanceTask)
{
    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        testSuiteInstanceTask->testSuiteInstance);

    if (numberOfRuns > 1) {
        nbp_test_suite_instance_state_e state =
            NBP_TEST_SUITE_INSTANCE_GET_STATE(
                testSuiteInstanceTask->testSuiteInstance);
        const char* color = NBP_DR_COLOR_NORMAL;

        if (state == tsis_passed) {
            color = NBP_DR_COLOR_GREEN;
        } else if (state == tsis_failed) {
            color = NBP_DR_COLOR_RED;
        } else if (state == tsis_skipped) {
            color = NBP_DR_COLOR_YELLOW;
        }

        internal_nbp_dr_print_depth(
            NBP_TEST_SUITE_INSTANCE_GET_DEPTH(
                testSuiteInstanceTask->testSuiteInstance),
            testSuiteInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_DR_TEST_SUITE_EMOJI,
            color,
            NBP_TEST_SUITE_INSTANCE_GET_NAME(
                testSuiteInstanceTask->testSuiteInstance),
            NBP_DR_COLOR_NORMAL);
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        internal_nbp_dr_print_test_suite_task(
            &testSuiteInstanceTask->testSuiteTasks[i]);
    }
}

static void internal_nbp_dr_print_module_task(nbp_dr_module_task_t* moduleTask)
{
    unsigned int numberOfRuns = NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_MODULE_GET_INSTANCE(moduleTask->module));
    nbp_module_state_e state = NBP_MODULE_GET_STATE(moduleTask->module);
    const char* color        = NBP_DR_COLOR_NORMAL;

    if (state == ms_passed) {
        color = NBP_DR_COLOR_GREEN;
    } else if (state == ms_failed) {
        color = NBP_DR_COLOR_RED;
    } else if (state == ms_skipped) {
        color = NBP_DR_COLOR_YELLOW;
    }

    if (numberOfRuns > 1) {
        internal_nbp_dr_print_depth(
            NBP_MODULE_GET_DEPTH(moduleTask->module),
            moduleTask->depth);
        printf(
            "%s %s%s%s#%u\n",
            NBP_DR_MODULE_EMOJI,
            color,
            NBP_MODULE_GET_NAME(moduleTask->module),
            NBP_DR_COLOR_NORMAL,
            moduleTask->runId);
    } else {
        internal_nbp_dr_print_depth(
            NBP_MODULE_GET_DEPTH(moduleTask->module),
            moduleTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_DR_MODULE_EMOJI,
            color,
            NBP_MODULE_GET_NAME(moduleTask->module),
            NBP_DR_COLOR_NORMAL);
    }
}

static void internal_nbp_dr_print_module_instace_task(
    nbp_dr_module_instance_task_t* moduleInstanceTask)
{
    unsigned int numberOfRuns = NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(
        moduleInstanceTask->moduleInstance);

    if (numberOfRuns > 1) {
        nbp_module_instance_state_e state =
            NBP_MODULE_INSTANCE_GET_STATE(moduleInstanceTask->moduleInstance);
        const char* color = NBP_DR_COLOR_NORMAL;

        if (state == mis_passed) {
            color = NBP_DR_COLOR_GREEN;
        } else if (state == mis_failed) {
            color = NBP_DR_COLOR_RED;
        } else if (state == mis_skipped) {
            color = NBP_DR_COLOR_YELLOW;
        }

        internal_nbp_dr_print_depth(
            NBP_MODULE_INSTANCE_GET_DEPTH(moduleInstanceTask->moduleInstance),
            moduleInstanceTask->depth);
        printf(
            "%s %s%s%s\n",
            NBP_DR_MODULE_EMOJI,
            color,
            NBP_MODULE_INSTANCE_GET_NAME(moduleInstanceTask->moduleInstance),
            NBP_DR_COLOR_NORMAL);
    }
}

static void internal_nbp_dr_print_task_tree(nbp_dr_task_tree_t* root)
{
    if (root == NBP_NULLPTR) {
        return;
    }

    switch (root->taskType) {
    case tt_test_case_instance:
        internal_nbp_dr_print_test_case_instance_task(&root->testCaseInstance);
        break;
    case tt_test_suite_instance:
        internal_nbp_dr_print_test_suite_instance_task(
            &root->testSuiteInstance);
        break;
    case tt_module:
        internal_nbp_dr_print_module_task(&root->module);
        break;
    case tt_module_instance:
        internal_nbp_dr_print_module_instace_task(&root->moduleInstance);
        break;
    default:
        break;
    }

    nbp_dr_task_tree_t* child = root->firstChild;
    while (child != NBP_NULLPTR) {
        internal_nbp_dr_print_task_tree(child);
        child = child->next;
    }
}

static void internal_nbp_dr_add_test_case_instance_to_module(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_module_t* module)
{
    nbp_dr_task_tree_t* task               = NBP_NULLPTR;
    nbp_dr_task_tree_t* parent             = NBP_NULLPTR;
    nbp_dr_test_case_task_t* testCaseTasks = NBP_NULLPTR;
    unsigned int numberOfRuns              = 0;

    numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance);

    parent =
        internal_nbp_dr_find_module_task(gInternalNbpDrTaskTreeRoot, module);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_dr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dr_task_tree_t),
        mt_default_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testCaseTasks = (nbp_dr_test_case_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_dr_test_case_task_t),
        mt_default_reporter);
    if (testCaseTasks == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case tasks");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->taskType   = tt_test_case_instance;
    task->next       = NBP_NULLPTR;
    task->firstChild = NBP_NULLPTR;
    task->lastChild  = NBP_NULLPTR;

    task->testCaseInstance.testCaseInstance = testCaseInstance;
    task->testCaseInstance.testCaseTasks    = testCaseTasks;
    task->testCaseInstance.next             = NBP_NULLPTR;
    task->testCaseInstance.depth            = parent->module.depth;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testCaseTasks[i].testCase =
            NBP_TEST_CASE_INSTANCE_GET_TEST_CASE(testCaseInstance, i);
        testCaseTasks[i].testCaseInstanceTask = &task->testCaseInstance;
        testCaseTasks[i].runId                = i;
        testCaseTasks[i].messageList          = NBP_NULLPTR;
        testCaseTasks[i].messageListLast      = NBP_NULLPTR;
    }

    if (parent->firstChild == NBP_NULLPTR) {
        parent->firstChild = task;
        parent->lastChild  = task;
    } else {
        parent->lastChild->next = task;
        parent->lastChild       = task;
    }
}

static void internal_nbp_dr_add_test_case_instance_to_test_suite(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_test_suite_t* testSuite)
{
    nbp_dr_test_case_instance_task_t* task = NBP_NULLPTR;
    nbp_dr_test_suite_task_t* parent       = NBP_NULLPTR;
    nbp_dr_test_case_task_t* testCaseTasks = NBP_NULLPTR;
    unsigned int numberOfRuns              = 0;

    numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance);

    parent = internal_nbp_dr_find_test_suite_task(testSuite);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_dr_test_case_instance_task_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dr_test_case_instance_task_t),
        mt_default_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testCaseTasks = (nbp_dr_test_case_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_dr_test_case_task_t),
        mt_default_reporter);
    if (testCaseTasks == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case tasks");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->testCaseInstance = testCaseInstance;
    task->testCaseTasks    = testCaseTasks;
    task->next             = NBP_NULLPTR;
    task->depth            = parent->testSuiteInstanceTask->depth;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testCaseTasks[i].testCase =
            NBP_TEST_CASE_INSTANCE_GET_TEST_CASE(testCaseInstance, i);
        testCaseTasks[i].testCaseInstanceTask = task;
        testCaseTasks[i].runId                = i;
        testCaseTasks[i].messageList          = NBP_NULLPTR;
        testCaseTasks[i].messageListLast      = NBP_NULLPTR;
    }

    if (parent->firstTestCaseInstance == NBP_NULLPTR) {
        parent->firstTestCaseInstance = task;
        parent->lastTestCaseInstance  = task;
    } else {
        parent->lastTestCaseInstance->next = task;
        parent->lastTestCaseInstance       = task;
    }
}

NBP_REPORTER_CALLBACK_INIT(nbp_dr_init)
{
    INTERNAL_NBP_DR_MUTEX_INIT(gInternalNbpDrMutex);
}

NBP_REPORTER_CALLBACK_UNINIT(nbp_dr_uninit)
{
    gInternalNbpDrTaskTreeRoot = NBP_NULLPTR;
    INTERNAL_NBP_DR_MUTEX_UNINIT(gInternalNbpDrMutex);
}

NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(nbp_dr_handle_version_command)
{
    INTERNAL_NBP_DR_MUTEX_LOCK(gInternalNbpDrMutex);
    printf("nbp version: %s\n", NBP_VERSION_STR);
    INTERNAL_NBP_DR_MUTEX_UNLOCK(gInternalNbpDrMutex);
}

NBP_REPORTER_CALLBACK_ON_ERROR(nbp_dr_on_error)
{
    INTERNAL_NBP_DR_MUTEX_LOCK(gInternalNbpDrMutex);

    if (gInternalNbpDrProgressMessagePrinted == 1) {
        printf(NBP_DR_CLEAR_LINE);
    }

    switch (NBP_GET_ERROR_CONTEXT_TYPE(NBP_THIS_ERROR)) {
    case ect_string:
        printf(
            "[%serror%s] code = %d, line = %d, file = %s, message = %s\n",
            NBP_DR_COLOR_RED,
            NBP_DR_COLOR_NORMAL,
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR),
            NBP_GET_ERROR_STRING_CONTEXT(NBP_THIS_ERROR));
        break;
    default:
        printf(
            "[%serror%s] code = %d, line = %d, file = %s\n",
            NBP_DR_COLOR_RED,
            NBP_DR_COLOR_NORMAL,
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR));
        break;
    }

    if (gInternalNbpDrProgressMessagePrinted) {
        printf(
            NBP_DR_CLEAR_LINE "Running... %u/%u",
            gInternalNbpDrNumberOfCompletedTestCases,
            gInternalNbpDrNumberOfTestCases);
        fflush(stdout);
    }

    INTERNAL_NBP_DR_MUTEX_UNLOCK(gInternalNbpDrMutex);
}

NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_dr_instantiate_test_case)
{
    if (NBP_THIS_MODULE != NBP_NULLPTR) {
        internal_nbp_dr_add_test_case_instance_to_module(
            NBP_THIS_TEST_CASE_INSTANCE,
            NBP_THIS_MODULE);
        return;
    }

    if (NBP_THIS_TEST_SUITE != NBP_NULLPTR) {
        internal_nbp_dr_add_test_case_instance_to_test_suite(
            NBP_THIS_TEST_CASE_INSTANCE,
            NBP_THIS_TEST_SUITE);
        return;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_invalid_parent,
        "test case instance has no parent");
    NBP_EXIT(ec_invalid_parent);
}

NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(
    nbp_dr_instantiate_test_suite_started)
{
    nbp_dr_task_tree_t* task                 = NBP_NULLPTR;
    nbp_dr_task_tree_t* parent               = NBP_NULLPTR;
    nbp_dr_test_suite_task_t* testSuiteTasks = NBP_NULLPTR;
    unsigned int numberOfRuns                = 0;

    numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_THIS_TEST_SUITE_INSTANCE);

    parent = internal_nbp_dr_find_module_task(
        gInternalNbpDrTaskTreeRoot,
        NBP_THIS_MODULE);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_dr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dr_task_tree_t),
        mt_default_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test suite instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testSuiteTasks = (nbp_dr_test_suite_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_dr_test_suite_task_t),
        mt_default_reporter);
    if (testSuiteTasks == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test suite tasks");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->taskType   = tt_test_suite_instance;
    task->next       = NBP_NULLPTR;
    task->firstChild = NBP_NULLPTR;
    task->lastChild  = NBP_NULLPTR;

    task->testSuiteInstance.testSuiteInstance = NBP_THIS_TEST_SUITE_INSTANCE;
    task->testSuiteInstance.testSuiteTasks    = testSuiteTasks;
    task->testSuiteInstance.depth             = parent->module.depth;

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        testSuiteTasks[i].testSuite = NBP_TEST_SUITE_INSTANCE_GET_TEST_SUITE(
            NBP_THIS_TEST_SUITE_INSTANCE,
            i);
        testSuiteTasks[i].runId                 = i;
        testSuiteTasks[i].testSuiteInstanceTask = &task->testSuiteInstance;
        testSuiteTasks[i].firstTestCaseInstance = NBP_NULLPTR;
        testSuiteTasks[i].lastTestCaseInstance  = NBP_NULLPTR;
    }

    if (parent->firstChild == NBP_NULLPTR) {
        parent->firstChild = task;
        parent->lastChild  = task;
    } else {
        parent->lastChild->next = task;
        parent->lastChild       = task;
    }
}

NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(
    nbp_dr_instantiate_module_started)
{
    nbp_dr_task_tree_t* task   = NBP_NULLPTR;
    nbp_dr_task_tree_t* child  = NBP_NULLPTR;
    nbp_dr_task_tree_t* parent = NBP_NULLPTR;
    unsigned int depth         = 0;
    unsigned int numberOfRuns  = 0;

    if (gInternalNbpDrTaskTreeRoot != NBP_NULLPTR) {
        parent = internal_nbp_dr_find_module_task(
            gInternalNbpDrTaskTreeRoot,
            NBP_THIS_MODULE);
        if (parent == NBP_NULLPTR) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_invalid_parent,
                "parent not found");
            NBP_EXIT(ec_invalid_parent);
            return;
        }

        depth = parent->module.depth;
    }

    task = (nbp_dr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dr_task_tree_t),
        mt_default_reporter);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate module instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    task->taskType   = tt_module_instance;
    task->next       = NBP_NULLPTR;
    task->firstChild = NBP_NULLPTR;
    task->lastChild  = NBP_NULLPTR;

    task->moduleInstance.depth          = depth;
    task->moduleInstance.moduleInstance = NBP_THIS_MODULE_INSTANCE;

    numberOfRuns =
        NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(NBP_THIS_MODULE_INSTANCE);

    if (numberOfRuns > 1) {
        depth += 1;
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        child = (nbp_dr_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
            sizeof(nbp_dr_task_tree_t),
            mt_default_reporter);
        if (child == NBP_NULLPTR) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_out_of_memory,
                "could not allocate module task");
            NBP_EXIT(ec_out_of_memory);
            return;
        }

        child->taskType   = tt_module;
        child->next       = NBP_NULLPTR;
        child->firstChild = NBP_NULLPTR;
        child->lastChild  = NBP_NULLPTR;

        child->module.module =
            NBP_MODULE_INSTANCE_GET_MODULE(NBP_THIS_MODULE_INSTANCE, i);
        child->module.depth = depth;
        child->module.runId = i;

        if (task->firstChild == NBP_NULLPTR) {
            task->firstChild = child;
            task->lastChild  = child;
        } else {
            task->lastChild->next = child;
            task->lastChild       = child;
        }
    }

    if (gInternalNbpDrTaskTreeRoot == NBP_NULLPTR) {
        gInternalNbpDrTaskTreeRoot = task;
        return;
    }

    if (parent->firstChild == NBP_NULLPTR) {
        parent->firstChild = task;
        parent->lastChild  = task;
    } else {
        parent->lastChild->next = task;
        parent->lastChild       = task;
    }
}

NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(nbp_dr_test_case_completed)
{
    INTERNAL_NBP_DR_MUTEX_LOCK(gInternalNbpDrMutex);

    gInternalNbpDrNumberOfCompletedTestCases++;

    printf(
        NBP_DR_CLEAR_LINE "Running... %u/%u",
        gInternalNbpDrNumberOfCompletedTestCases,
        gInternalNbpDrNumberOfTestCases);
    fflush(stdout);

    INTERNAL_NBP_DR_MUTEX_UNLOCK(gInternalNbpDrMutex);
}

NBP_REPORTER_CALLBACK_BEFORE_RUN(nbp_dr_before_run)
{
    INTERNAL_NBP_DR_MUTEX_LOCK(gInternalNbpDrMutex);

    gInternalNbpDrNumberOfTestCases =
        NBP_REPORTER_GET_STATISTICS(st_total_number_of_test_cases);

    printf(
        NBP_DR_CLEAR_LINE "Running... %u/%u",
        gInternalNbpDrNumberOfCompletedTestCases,
        gInternalNbpDrNumberOfTestCases);
    fflush(stdout);

    gInternalNbpDrProgressMessagePrinted = 1;

    INTERNAL_NBP_DR_MUTEX_UNLOCK(gInternalNbpDrMutex);
}

NBP_REPORTER_CALLBACK_AFTER_RUN(nbp_dr_after_run)
{
#define INTERNAL_NBP_DR_PRINT_STATS(                                           \
    name,                                                                      \
    totalType,                                                                 \
    type,                                                                      \
    passed,                                                                    \
    failed,                                                                    \
    skipped)                                                                   \
    numPassed  = NBP_REPORTER_GET_STATISTICS(type, passed);                    \
    numFailed  = NBP_REPORTER_GET_STATISTICS(type, failed);                    \
    numSkipped = NBP_REPORTER_GET_STATISTICS(type, skipped);                   \
    printf(                                                                    \
        "| %-22s | %5u | %s%5u%s %s | %s%5u%s %s | %s%5u%s %s |\n",            \
        name,                                                                  \
        NBP_REPORTER_GET_STATISTICS(totalType),                                \
        NBP_DR_COLOR_GREEN,                                                    \
        numPassed,                                                             \
        NBP_DR_COLOR_NORMAL,                                                   \
        "passed",                                                              \
        numFailed > 0 ? NBP_DR_COLOR_RED : NBP_DR_COLOR_GREEN,                 \
        numFailed,                                                             \
        NBP_DR_COLOR_NORMAL,                                                   \
        "failed",                                                              \
        numSkipped > 0 ? NBP_DR_COLOR_YELLOW : NBP_DR_COLOR_GREEN,             \
        numSkipped,                                                            \
        NBP_DR_COLOR_NORMAL,                                                   \
        "skipped");

    unsigned int numPassed  = 0;
    unsigned int numFailed  = 0;
    unsigned int numSkipped = 0;

    INTERNAL_NBP_DR_MUTEX_LOCK(gInternalNbpDrMutex);

    if (gInternalNbpDrProgressMessagePrinted == 1) {
        gInternalNbpDrProgressMessagePrinted = 0;
        printf(NBP_DR_CLEAR_LINE);
    }

    internal_nbp_dr_print_task_tree(gInternalNbpDrTaskTreeRoot);

    printf(
        "----------------------------------------------------------------------"
        "----------\n");

    INTERNAL_NBP_DR_PRINT_STATS(
        "Test cases",
        st_total_number_of_test_cases,
        st_number_of_test_cases,
        tcs_passed,
        tcs_failed,
        tcs_skipped);
    INTERNAL_NBP_DR_PRINT_STATS(
        "Test case instances",
        st_total_number_of_test_case_instances,
        st_number_of_test_case_instances,
        tcis_passed,
        tcis_failed,
        tcis_skipped);

    INTERNAL_NBP_DR_PRINT_STATS(
        "Test suites",
        st_total_number_of_test_suites,
        st_number_of_test_suites,
        tss_passed,
        tss_failed,
        tss_skipped);
    INTERNAL_NBP_DR_PRINT_STATS(
        "Test suite instances",
        st_total_number_of_test_suite_instances,
        st_number_of_test_suite_instances,
        tsis_passed,
        tsis_failed,
        tsis_skipped);

    INTERNAL_NBP_DR_PRINT_STATS(
        "Modules",
        st_total_number_of_modules,
        st_number_of_modules,
        ms_passed,
        ms_failed,
        ms_skipped);
    INTERNAL_NBP_DR_PRINT_STATS(
        "Module instances",
        st_total_number_of_module_instances,
        st_number_of_module_instances,
        mis_passed,
        mis_failed,
        mis_skipped);

    printf(
        "----------------------------------------------------------------------"
        "----------\n");

    INTERNAL_NBP_DR_MUTEX_UNLOCK(gInternalNbpDrMutex);

#undef INTERNAL_NBP_DR_PRINT_STATS
}

NBP_REPORTER(
    nbpDefaultReporter,
    NBP_REPORTER_CALLBACKS(
        NBP_REPORTER_CALLBACK_INIT(nbp_dr_init),
        NBP_REPORTER_CALLBACK_UNINIT(nbp_dr_uninit),
        NBP_REPORTER_CALLBACK_HANDLE_VERSION_COMMAND(
            nbp_dr_handle_version_command),
        NBP_REPORTER_CALLBACK_ON_ERROR(nbp_dr_on_error),
        NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_dr_instantiate_test_case),
        NBP_REPORTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(
            nbp_dr_instantiate_test_suite_started),
        NBP_REPORTER_CALLBACK_INSTANTIATE_MODULE_STARTED(
            nbp_dr_instantiate_module_started),
        NBP_REPORTER_CALLBACK_TEST_CASE_COMPLETED(nbp_dr_test_case_completed),
        NBP_REPORTER_CALLBACK_BEFORE_RUN(nbp_dr_before_run),
        NBP_REPORTER_CALLBACK_AFTER_RUN(nbp_dr_after_run)));

#undef NBP_DR_TEST_CASE_EMOJI
#undef NBP_DR_TEST_SUITE_EMOJI
#undef NBP_DR_MODULE_EMOJI

#undef NBP_DR_COLOR_NORMAL
#undef NBP_DR_COLOR_RED
#undef NBP_DR_COLOR_GREEN
#undef NBP_DR_COLOR_YELLOW

#undef NBP_DR_CLEAR_LINE

#endif // end if _H_NBP_INTERNAL_REPORTERS_LINUX_DEFAULT_REPORTER

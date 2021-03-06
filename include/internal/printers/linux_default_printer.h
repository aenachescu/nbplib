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

#ifndef _H_NBP_INTERNAL_PRINTERS_LINUX_DEFAULT_PRINTER
#define _H_NBP_INTERNAL_PRINTERS_LINUX_DEFAULT_PRINTER

#include "../api/printer.h"
#include "../api/version.h"
#include "../build_configuration.h"
#include "../types/error.h"

#include <stdio.h>

#define NBP_DP_TEST_CASE_EMOJI  "\xF0\x9F\x93\x9D"
#define NBP_DP_TEST_SUITE_EMOJI "\xF0\x9F\x93\x9C"
#define NBP_DP_MODULE_EMOJI     "\xF0\x9F\x93\x81"

#ifdef NBP_MT_SUPPORT

#include <pthread.h>

static inline nbp_error_code_e internal_nbp_dp_mutex_init(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_init(mutex, NULL) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_dp_mutex_uninit(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_destroy(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_dp_mutex_lock(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_lock(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

static inline nbp_error_code_e internal_nbp_dp_mutex_unlock(
    pthread_mutex_t* mutex)
{
    if (pthread_mutex_unlock(mutex) == 0) {
        return ec_success;
    }
    return ec_sync_error;
}

#define INTERNAL_NBP_DP_DECLARE_MUTEX(name)                                    \
    pthread_mutex_t name = PTHREAD_MUTEX_INITIALIZER;

#define INTERNAL_NBP_DP_MUTEX_INIT(name) internal_nbp_dp_mutex_init(&name)

#define INTERNAL_NBP_DP_MUTEX_UNINIT(name) internal_nbp_dp_mutex_uninit(&name)

#define INTERNAL_NBP_DP_MUTEX_LOCK(name) internal_nbp_dp_mutex_lock(&name)

#define INTERNAL_NBP_DP_MUTEX_UNLOCK(name) internal_nbp_dp_mutex_unlock(&name)

#else

#define INTERNAL_NBP_DP_DECLARE_MUTEX(name)

#define INTERNAL_NBP_DP_MUTEX_INIT(name) ec_success

#define INTERNAL_NBP_DP_MUTEX_UNINIT(name) ec_success

#define INTERNAL_NBP_DP_MUTEX_LOCK(name) ec_success

#define INTERNAL_NBP_DP_MUTEX_UNLOCK(name) ec_success

#endif // end if NBP_MT_SUPPORT

enum nbp_dp_task_type_e
{
    tt_unknown             = 0x60000000,
    tt_test_case_instance  = 0x60000001,
    tt_test_suite_instance = 0x60000002,
    tt_module_instance     = 0x60000003,
    tt_module              = 0x60000004,
};
typedef enum nbp_dp_task_type_e nbp_dp_task_type_e;

struct nbp_dp_test_case_instance_task_t;
struct nbp_dp_test_suite_instance_task_t;

struct nbp_dp_message_list_t
{
    char* message;
    struct nbp_dp_message_list_t* next;
};
typedef struct nbp_dp_message_list_t nbp_dp_message_list_t;

struct nbp_dp_test_case_task_t
{
    nbp_test_case_t* testCase;
    unsigned int runId;

    struct nbp_dp_test_case_instance_task_t* testCaseInstanceTask;

    nbp_dp_message_list_t* messageList;
    nbp_dp_message_list_t* messageListLast;
};
typedef struct nbp_dp_test_case_task_t nbp_dp_test_case_task_t;

struct nbp_dp_test_case_instance_task_t
{
    nbp_test_case_instance_t* testCaseInstance;
    nbp_dp_test_case_task_t* testCaseTasks;
    unsigned int depth;

    struct nbp_dp_test_case_instance_task_t* next;
};
typedef struct nbp_dp_test_case_instance_task_t
    nbp_dp_test_case_instance_task_t;

struct nbp_dp_test_suite_task_t
{
    nbp_test_suite_t* testSuite;
    unsigned int runId;

    struct nbp_dp_test_suite_instance_task_t* testSuiteInstanceTask;

    nbp_dp_test_case_instance_task_t* firstTestCaseInstance;
    nbp_dp_test_case_instance_task_t* lastTestCaseInstance;
};
typedef struct nbp_dp_test_suite_task_t nbp_dp_test_suite_task_t;

struct nbp_dp_test_suite_instance_task_t
{
    nbp_test_suite_instance_t* testSuiteInstance;
    nbp_dp_test_suite_task_t* testSuiteTasks;
    unsigned int depth;
};
typedef struct nbp_dp_test_suite_instance_task_t
    nbp_dp_test_suite_instance_task_t;

struct nbp_dp_module_task_t
{
    nbp_module_t* module;
    unsigned int depth;
    unsigned int runId;
};
typedef struct nbp_dp_module_task_t nbp_dp_module_task_t;

struct nbp_dp_module_instance_task_t
{
    nbp_module_instance_t* moduleInstance;
    unsigned int depth;
};
typedef struct nbp_dp_module_instance_task_t nbp_dp_module_instance_task_t;

struct nbp_dp_task_tree_t
{
    nbp_dp_task_type_e taskType;
    union
    {
        nbp_dp_test_case_instance_task_t testCaseInstance;
        nbp_dp_test_suite_instance_task_t testSuiteInstance;
        nbp_dp_module_task_t module;
        nbp_dp_module_instance_task_t moduleInstance;
    };

    struct nbp_dp_task_tree_t* next;

    struct nbp_dp_task_tree_t* firstChild;
    struct nbp_dp_task_tree_t* lastChild;
};
typedef struct nbp_dp_task_tree_t nbp_dp_task_tree_t;

static nbp_dp_task_tree_t* gInternalNbpDpTaskTreeRoot = NBP_NULLPTR;

static nbp_dp_task_tree_t* internal_nbp_dp_find_module_task(
    nbp_dp_task_tree_t* root,
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

    nbp_dp_task_tree_t* child = root->firstChild;
    nbp_dp_task_tree_t* task  = NBP_NULLPTR;

    while (child != NBP_NULLPTR) {
        task = internal_nbp_dp_find_module_task(child, module);
        if (task != NBP_NULLPTR) {
            return task;
        }

        child = child->next;
    }

    return NBP_NULLPTR;
}

static nbp_dp_task_tree_t* internal_nbp_dp_find_test_suite_instance_task(
    nbp_dp_task_tree_t* root,
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

    nbp_dp_task_tree_t* child = root->firstChild;
    nbp_dp_task_tree_t* task  = NBP_NULLPTR;

    while (child != NBP_NULLPTR) {
        task = internal_nbp_dp_find_test_suite_instance_task(
            child,
            testSuiteInstance);
        if (task != NBP_NULLPTR) {
            return task;
        }

        child = child->next;
    }

    return NBP_NULLPTR;
}

static nbp_dp_test_suite_task_t* internal_nbp_dp_find_test_suite_task(
    nbp_test_suite_t* testSuite)
{
    nbp_dp_task_tree_t* testSuiteInstanceTask =
        internal_nbp_dp_find_test_suite_instance_task(
            gInternalNbpDpTaskTreeRoot,
            NBP_TEST_SUITE_GET_INSTANCE(testSuite));
    if (testSuiteInstanceTask == NBP_NULLPTR) {
        return NBP_NULLPTR;
    }

    nbp_dp_test_suite_task_t* tasks =
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

static void internal_nbp_dp_print_depth(
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

static void internal_nbp_dp_print_test_case_task(
    nbp_dp_test_case_task_t* testCaseTask)
{
    unsigned int numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_CASE_GET_INSTANCE(testCaseTask->testCase));

    if (numberOfRuns > 1) {
        internal_nbp_dp_print_depth(
            NBP_TEST_CASE_GET_DEPTH(testCaseTask->testCase),
            testCaseTask->testCaseInstanceTask->depth + 1);
        printf(
            "%s %s#%u\n",
            NBP_DP_TEST_CASE_EMOJI,
            NBP_TEST_CASE_GET_NAME(testCaseTask->testCase),
            testCaseTask->runId);
    }
}

static void internal_nbp_dp_print_test_case_instance_task(
    nbp_dp_test_case_instance_task_t* testCaseInstanceTask)
{
    internal_nbp_dp_print_depth(
        NBP_TEST_CASE_INSTANCE_GET_DEPTH(
            testCaseInstanceTask->testCaseInstance),
        testCaseInstanceTask->depth);
    printf(
        "%s %s\n",
        NBP_DP_TEST_CASE_EMOJI,
        NBP_TEST_CASE_INSTANCE_GET_NAME(
            testCaseInstanceTask->testCaseInstance));

    unsigned int numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(
        testCaseInstanceTask->testCaseInstance);
    for (unsigned int i = 0; i < numberOfRuns; i++) {
        internal_nbp_dp_print_test_case_task(
            &testCaseInstanceTask->testCaseTasks[i]);
    }
}

static void internal_nbp_dp_print_test_suite_task(
    nbp_dp_test_suite_task_t* testSuiteTask)
{
    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_TEST_SUITE_GET_INSTANCE(testSuiteTask->testSuite));

    if (numberOfRuns > 1) {
        internal_nbp_dp_print_depth(
            NBP_TEST_SUITE_GET_DEPTH(testSuiteTask->testSuite),
            testSuiteTask->testSuiteInstanceTask->depth + 1);
        printf(
            "%s %s#%u\n",
            NBP_DP_TEST_SUITE_EMOJI,
            NBP_TEST_SUITE_GET_NAME(testSuiteTask->testSuite),
            testSuiteTask->runId);
    }

    nbp_dp_test_case_instance_task_t* child =
        testSuiteTask->firstTestCaseInstance;

    while (child != NBP_NULLPTR) {
        internal_nbp_dp_print_test_case_instance_task(child);
        child = child->next;
    }
}

static void internal_nbp_dp_print_test_suite_instance_task(
    nbp_dp_test_suite_instance_task_t* testSuiteInstanceTask)
{
    internal_nbp_dp_print_depth(
        NBP_TEST_SUITE_INSTANCE_GET_DEPTH(
            testSuiteInstanceTask->testSuiteInstance),
        testSuiteInstanceTask->depth);
    printf(
        "%s %s\n",
        NBP_DP_TEST_SUITE_EMOJI,
        NBP_TEST_SUITE_INSTANCE_GET_NAME(
            testSuiteInstanceTask->testSuiteInstance));

    unsigned int numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        testSuiteInstanceTask->testSuiteInstance);
    for (unsigned int i = 0; i < numberOfRuns; i++) {
        internal_nbp_dp_print_test_suite_task(
            &testSuiteInstanceTask->testSuiteTasks[i]);
    }
}

static void internal_nbp_dp_print_module_task(nbp_dp_module_task_t* moduleTask)
{
    unsigned int numberOfRuns = NBP_MODULE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_MODULE_GET_INSTANCE(moduleTask->module));
    if (numberOfRuns < 2) {
        return;
    }

    internal_nbp_dp_print_depth(
        NBP_MODULE_GET_DEPTH(moduleTask->module),
        moduleTask->depth);
    printf(
        "%s %s#%u\n",
        NBP_DP_MODULE_EMOJI,
        NBP_MODULE_GET_NAME(moduleTask->module),
        moduleTask->runId);
}

static void internal_nbp_dp_print_module_instace_task(
    nbp_dp_module_instance_task_t* moduleInstanceTask)
{
    internal_nbp_dp_print_depth(
        NBP_MODULE_INSTANCE_GET_DEPTH(moduleInstanceTask->moduleInstance),
        moduleInstanceTask->depth);
    printf(
        "%s %s\n",
        NBP_DP_MODULE_EMOJI,
        NBP_MODULE_INSTANCE_GET_NAME(moduleInstanceTask->moduleInstance));
}

static void internal_nbp_dp_print_task_tree(nbp_dp_task_tree_t* root)
{
    if (root == NBP_NULLPTR) {
        return;
    }

    switch (root->taskType) {
    case tt_test_case_instance:
        internal_nbp_dp_print_test_case_instance_task(&root->testCaseInstance);
        break;
    case tt_test_suite_instance:
        internal_nbp_dp_print_test_suite_instance_task(
            &root->testSuiteInstance);
        break;
    case tt_module:
        internal_nbp_dp_print_module_task(&root->module);
        break;
    case tt_module_instance:
        internal_nbp_dp_print_module_instace_task(&root->moduleInstance);
        break;
    default:
        break;
    }

    nbp_dp_task_tree_t* child = root->firstChild;
    while (child != NBP_NULLPTR) {
        internal_nbp_dp_print_task_tree(child);
        child = child->next;
    }
}

static void internal_nbp_dp_add_test_case_instance_to_module(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_module_t* module)
{
    nbp_dp_task_tree_t* task               = NBP_NULLPTR;
    nbp_dp_task_tree_t* parent             = NBP_NULLPTR;
    nbp_dp_test_case_task_t* testCaseTasks = NBP_NULLPTR;
    unsigned int numberOfRuns              = 0;

    numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance);

    parent =
        internal_nbp_dp_find_module_task(gInternalNbpDpTaskTreeRoot, module);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_dp_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dp_task_tree_t),
        mt_default_printer);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testCaseTasks = (nbp_dp_test_case_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_dp_test_case_task_t),
        mt_default_printer);
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

static void internal_nbp_dp_add_test_case_instance_to_test_suite(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_test_suite_t* testSuite)
{
    nbp_dp_test_case_instance_task_t* task = NBP_NULLPTR;
    nbp_dp_test_suite_task_t* parent       = NBP_NULLPTR;
    nbp_dp_test_case_task_t* testCaseTasks = NBP_NULLPTR;
    unsigned int numberOfRuns              = 0;

    numberOfRuns = NBP_TEST_CASE_INSTANCE_GET_NUMBER_OF_RUNS(testCaseInstance);

    parent = internal_nbp_dp_find_test_suite_task(testSuite);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_dp_test_case_instance_task_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dp_test_case_instance_task_t),
        mt_default_printer);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test case instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testCaseTasks = (nbp_dp_test_case_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_dp_test_case_task_t),
        mt_default_printer);
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

NBP_PRINTER_CALLBACK_INIT(nbp_dp_init)
{
}

NBP_PRINTER_CALLBACK_UNINIT(nbp_dp_uninit)
{
    internal_nbp_dp_print_task_tree(gInternalNbpDpTaskTreeRoot);
    gInternalNbpDpTaskTreeRoot = NBP_NULLPTR;
}

NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(nbp_dp_handle_version_command)
{
    printf("nbp version: %s\n", NBP_VERSION_STR);
}

NBP_PRINTER_CALLBACK_ON_ERROR(nbp_dp_on_error)
{
    switch (NBP_GET_ERROR_CONTEXT_TYPE(NBP_THIS_ERROR)) {
    case ect_string:
        printf(
            "[error] code = %d, line = %d, file = %s, message = %s\n",
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR),
            NBP_GET_ERROR_STRING_CONTEXT(NBP_THIS_ERROR));
        break;
    default:
        printf(
            "[error] code = %d, line = %d, file = %s\n",
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR));
        break;
    }
}

NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_CASE(nbp_dp_instantiate_test_case)
{
    if (NBP_THIS_MODULE != NBP_NULLPTR) {
        internal_nbp_dp_add_test_case_instance_to_module(
            NBP_THIS_TEST_CASE_INSTANCE,
            NBP_THIS_MODULE);
        return;
    }

    if (NBP_THIS_TEST_SUITE != NBP_NULLPTR) {
        internal_nbp_dp_add_test_case_instance_to_test_suite(
            NBP_THIS_TEST_CASE_INSTANCE,
            NBP_THIS_TEST_SUITE);
        return;
    }

    NBP_REPORT_ERROR_STRING_CONTEXT(
        ec_invalid_parent,
        "test case instance has no parent");
    NBP_EXIT(ec_invalid_parent);
}

NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(
    nbp_dp_instantiate_test_suite_started)
{
    nbp_dp_task_tree_t* task                 = NBP_NULLPTR;
    nbp_dp_task_tree_t* parent               = NBP_NULLPTR;
    nbp_dp_test_suite_task_t* testSuiteTasks = NBP_NULLPTR;
    unsigned int numberOfRuns                = 0;

    numberOfRuns = NBP_TEST_SUITE_INSTANCE_GET_NUMBER_OF_RUNS(
        NBP_THIS_TEST_SUITE_INSTANCE);

    parent = internal_nbp_dp_find_module_task(
        gInternalNbpDpTaskTreeRoot,
        NBP_THIS_MODULE);
    if (parent == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(ec_invalid_parent, "parent not found");
        NBP_EXIT(ec_invalid_parent);
        return;
    }

    task = (nbp_dp_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dp_task_tree_t),
        mt_default_printer);
    if (task == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "could not allocate test suite instance task");
        NBP_EXIT(ec_out_of_memory);
        return;
    }

    testSuiteTasks = (nbp_dp_test_suite_task_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_dp_test_suite_task_t),
        mt_default_printer);
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

NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_STARTED(
    nbp_dp_instantiate_module_started)
{
    nbp_dp_task_tree_t* task   = NBP_NULLPTR;
    nbp_dp_task_tree_t* child  = NBP_NULLPTR;
    nbp_dp_task_tree_t* parent = NBP_NULLPTR;
    unsigned int depth         = 0;
    unsigned int numberOfRuns  = 0;

    if (gInternalNbpDpTaskTreeRoot != NBP_NULLPTR) {
        parent = internal_nbp_dp_find_module_task(
            gInternalNbpDpTaskTreeRoot,
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

    task = (nbp_dp_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
        sizeof(nbp_dp_task_tree_t),
        mt_default_printer);
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
        child = (nbp_dp_task_tree_t*) NBP_MEMORY_ALLOC_TAG(
            sizeof(nbp_dp_task_tree_t),
            mt_default_printer);
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

    if (gInternalNbpDpTaskTreeRoot == NBP_NULLPTR) {
        gInternalNbpDpTaskTreeRoot = task;
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

NBP_PRINTER(
    nbpDefaultPrinter,
    NBP_PRINTER_CALLBACKS(
        NBP_PRINTER_CALLBACK_INIT(nbp_dp_init),
        NBP_PRINTER_CALLBACK_UNINIT(nbp_dp_uninit),
        NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(
            nbp_dp_handle_version_command),
        NBP_PRINTER_CALLBACK_ON_ERROR(nbp_dp_on_error),
        NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_CASE(
            nbp_dp_instantiate_test_case),
        NBP_PRINTER_CALLBACK_INSTANTIATE_TEST_SUITE_STARTED(
            nbp_dp_instantiate_test_suite_started),
        NBP_PRINTER_CALLBACK_INSTANTIATE_MODULE_STARTED(
            nbp_dp_instantiate_module_started)));

#endif // end if _H_NBP_INTERNAL_PRINTERS_LINUX_DEFAULT_PRINTER

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

#ifndef _H_NBP_INTERNAL_IMPL_MODULE
#define _H_NBP_INTERNAL_IMPL_MODULE

#include "../api/error.h"
#include "../api/exit.h"
#include "../api/memory.h"
#include "../details/module.h"
#include "../details/printer_notifier.h"
#include "../details/runner_notifier.h"
#include "../details/utils.h"
#include "../types/flags.h"

extern nbp_module_details_t* gInternalNbpMainModuleDetails;

static void internal_nbp_increment_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_module_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_module_state_position(state);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e oldState,
    nbp_module_state_e newState)
{
    internal_nbp_decrement_number_of_modules(statsArray, oldState, 1);
    internal_nbp_increment_number_of_modules(statsArray, newState, 1);
}

static void internal_nbp_increment_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_module_instance_state_position(state);
    NBP_ATOMIC_UINT_ADD_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_decrement_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state,
    unsigned int value)
{
    unsigned int pos = internal_nbp_get_module_instance_state_position(state);
    NBP_ATOMIC_UINT_SUB_AND_FETCH(&statsArray[pos], value);
}

static void internal_nbp_update_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e oldState,
    nbp_module_instance_state_e newState)
{
    internal_nbp_decrement_number_of_module_instances(statsArray, oldState, 1);
    internal_nbp_increment_number_of_module_instances(statsArray, newState, 1);
}

static void internal_nbp_module_instance_update_stats(
    nbp_module_instance_t* moduleInstance)
{
    nbp_module_t* parent         = moduleInstance->parent;
    unsigned int numberOfModules = moduleInstance->numberOfRuns;

    internal_nbp_increment_number_of_modules(
        moduleInstance->numberOfModules,
        ms_ready,
        numberOfModules);

    while (parent != NBP_NULLPTR) {
        parent->totalNumberOfModuleInstances += 1;
        parent->totalNumberOfModules += numberOfModules;

        parent->moduleInstance->totalNumberOfModuleInstances += 1;
        parent->moduleInstance->totalNumberOfModules += numberOfModules;

        internal_nbp_increment_number_of_module_instances(
            parent->numberOfModuleInstances,
            mis_ready,
            1);
        internal_nbp_increment_number_of_modules(
            parent->numberOfModules,
            ms_ready,
            numberOfModules);

        internal_nbp_increment_number_of_module_instances(
            parent->moduleInstance->numberOfModuleInstances,
            mis_ready,
            1);
        internal_nbp_increment_number_of_modules(
            parent->moduleInstance->numberOfModules,
            ms_ready,
            numberOfModules);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_module_state_position(nbp_module_state_e state)
{
    if ((unsigned int) state < (unsigned int) ms_ready
        || (unsigned int) state > (unsigned int) ms_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid module state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) ms_ready);
}

unsigned int internal_nbp_get_module_instance_state_position(
    nbp_module_instance_state_e state)
{
    if ((unsigned int) state < (unsigned int) mis_ready
        || (unsigned int) state > (unsigned int) mis_skipped) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_unexpected_state,
            "invalid module instance state");
        NBP_EXIT(ec_unexpected_state);
        return 0;
    }

    return ((unsigned int) state) - ((unsigned int) mis_ready);
}

void internal_nbp_module_update_state_stats(
    nbp_module_t* module,
    nbp_module_state_e oldState,
    nbp_module_state_e newState)
{
    nbp_module_t* parent = module->moduleInstance->parent;

    internal_nbp_update_number_of_modules(
        module->moduleInstance->numberOfModules,
        oldState,
        newState);

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_modules(
            parent->numberOfModules,
            oldState,
            newState);

        internal_nbp_update_number_of_modules(
            parent->moduleInstance->numberOfModules,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

void internal_nbp_module_instance_update_state_stats(
    nbp_module_instance_t* moduleInstance,
    nbp_module_instance_state_e oldState,
    nbp_module_instance_state_e newState)
{
    nbp_module_t* parent = moduleInstance->parent;

    while (parent != NBP_NULLPTR) {
        internal_nbp_update_number_of_module_instances(
            parent->numberOfModuleInstances,
            oldState,
            newState);

        internal_nbp_update_number_of_module_instances(
            parent->moduleInstance->numberOfModuleInstances,
            oldState,
            newState);

        parent = parent->moduleInstance->parent;
    }
}

unsigned int internal_nbp_get_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state)
{
    unsigned int pos = internal_nbp_get_module_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

unsigned int internal_nbp_get_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state)
{
    unsigned int pos = internal_nbp_get_module_instance_state_position(state);
    return NBP_ATOMIC_UINT_LOAD(&statsArray[pos]);
}

nbp_module_t* internal_nbp_get_module_from_instance(
    nbp_module_instance_t* moduleInstance,
    unsigned int runId)
{
    if (runId >= moduleInstance->numberOfRuns) {
        return NBP_NULLPTR;
    }
    return &moduleInstance->runs[runId];
}

nbp_module_instance_t* internal_nbp_instantiate_module(
    nbp_module_details_t* moduleDetails,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context)
{
    moduleDetails->configFunction(moduleDetails);

    if (numberOfRuns == 0) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_number_of_runs,
            "the number of runs must be greater than 0");
        NBP_EXIT(ec_invalid_number_of_runs);
        return NBP_NULLPTR;
    }

    if (parentModule == NBP_NULLPTR
        && moduleDetails != gInternalNbpMainModuleDetails) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_invalid_parent,
            "module instance has no parent");
        NBP_EXIT(ec_invalid_parent);
        return NBP_NULLPTR;
    }

    if (parentModule != NBP_NULLPTR) {
        if (parentModule->moduleInstance->moduleDetails == moduleDetails) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_invalid_parent,
                "a module cannot self instantiate");
            NBP_EXIT(ec_invalid_parent);
            return NBP_NULLPTR;
        }

        nbp_module_t* p = parentModule->moduleInstance->parent;
        while (p != NBP_NULLPTR) {
            if (p->moduleInstance->moduleDetails == moduleDetails) {
                NBP_REPORT_ERROR_STRING_CONTEXT(
                    ec_invalid_parent,
                    "a module cannot instantiate a parent module");
                NBP_EXIT(ec_invalid_parent);
                return NBP_NULLPTR;
            }
            p = p->moduleInstance->parent;
        }
    }

    nbp_module_instance_t* moduleInstance = (nbp_module_instance_t*)
        NBP_MEMORY_ALLOC_TAG(sizeof(nbp_module_instance_t), mt_module_instance);

    if (moduleInstance == NBP_NULLPTR) {
        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate module instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    nbp_module_t* runs = (nbp_module_t*) NBP_MEMORY_ALLOC_TAG(
        numberOfRuns * sizeof(nbp_module_t),
        mt_module);

    if (runs == NBP_NULLPTR) {
        NBP_MEMORY_FREE_TAG(moduleInstance, mt_module_instance);

        NBP_REPORT_ERROR_STRING_CONTEXT(
            ec_out_of_memory,
            "failed to allocate the runs for module instance");
        NBP_EXIT(ec_out_of_memory);
        return NBP_NULLPTR;
    }

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        runs[i].moduleInstance                  = moduleInstance;
        runs[i].firstTestCaseInstance           = NBP_NULLPTR;
        runs[i].lastTestCaseInstance            = NBP_NULLPTR;
        runs[i].firstTestSuiteInstance          = NBP_NULLPTR;
        runs[i].lastTestSuiteInstance           = NBP_NULLPTR;
        runs[i].firstModuleInstance             = NBP_NULLPTR;
        runs[i].lastModuleInstance              = NBP_NULLPTR;
        runs[i].numberOfTasks                   = 0;
        runs[i].totalNumberOfTestCases          = 0;
        runs[i].totalNumberOfTestCaseInstances  = 0;
        runs[i].totalNumberOfTestSuites         = 0;
        runs[i].totalNumberOfTestSuiteInstances = 0;
        runs[i].totalNumberOfModules            = 0;
        runs[i].totalNumberOfModuleInstances    = 0;

        NBP_ATOMIC_INT_STORE(&runs[i].state, (int) ms_ready);
        NBP_ATOMIC_INT_STORE(&runs[i].isSkipped, (int) sf_is_not_set);
        NBP_ATOMIC_UINT_STORE(&runs[i].numberOfCompletedTasks, 0U);

        if (NBP_SYNC_EVENT_INIT(&runs[i].runEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init runEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        if (NBP_SYNC_EVENT_INIT(&runs[i].setupEvent) != ec_success) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_sync_error,
                "failed to init setupEvent");
            NBP_EXIT(ec_sync_error);
            return NBP_NULLPTR;
        }

        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCases,
            NBP_NUMBER_OF_TEST_CASE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestCaseInstances,
            NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestSuites,
            NBP_NUMBER_OF_TEST_SUITE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfTestSuiteInstances,
            NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfModules,
            NBP_NUMBER_OF_MODULE_STATES,
            0U);
        internal_nbp_initialize_array_of_atomic_uint(
            runs[i].numberOfModuleInstances,
            NBP_NUMBER_OF_MODULE_INSTANCE_STATES,
            0U);
    }

    moduleInstance->moduleDetails     = moduleDetails;
    moduleInstance->parent            = parentModule;
    moduleInstance->depth             = 0;
    moduleInstance->instantiationLine = instantiationLine;
    moduleInstance->setupDetails      = moduleDetails->setupDetails;
    moduleInstance->teardownDetails   = moduleDetails->teardownDetails;
    moduleInstance->runs              = runs;
    moduleInstance->numberOfRuns      = numberOfRuns;
    moduleInstance->next              = NBP_NULLPTR;
    moduleInstance->prev              = NBP_NULLPTR;

    moduleInstance->totalNumberOfTestCases          = 0;
    moduleInstance->totalNumberOfTestCaseInstances  = 0;
    moduleInstance->totalNumberOfTestSuites         = 0;
    moduleInstance->totalNumberOfTestSuiteInstances = 0;
    moduleInstance->totalNumberOfModules            = 0;
    moduleInstance->totalNumberOfModuleInstances    = 0;

    NBP_ATOMIC_INT_STORE(&moduleInstance->state, (int) mis_ready);
    NBP_ATOMIC_INT_STORE(&moduleInstance->isSkipped, (int) sf_is_not_set);
    NBP_ATOMIC_UINT_STORE(&moduleInstance->numberOfCompletedRuns, 0U);

    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestCases,
        NBP_NUMBER_OF_TEST_CASE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestCaseInstances,
        NBP_NUMBER_OF_TEST_CASE_INSTANCE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestSuites,
        NBP_NUMBER_OF_TEST_SUITE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfTestSuiteInstances,
        NBP_NUMBER_OF_TEST_SUITE_INSTANCE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfModules,
        NBP_NUMBER_OF_MODULE_STATES,
        0U);
    internal_nbp_initialize_array_of_atomic_uint(
        moduleInstance->numberOfModuleInstances,
        NBP_NUMBER_OF_MODULE_INSTANCE_STATES,
        0U);

    if (parentModule != NBP_NULLPTR) {
        moduleInstance->depth = parentModule->moduleInstance->depth + 1;

        parentModule->numberOfTasks += 1;

        if (parentModule->firstModuleInstance == NBP_NULLPTR) {
            parentModule->firstModuleInstance = moduleInstance;
            parentModule->lastModuleInstance  = moduleInstance;
        } else {
            moduleInstance->prev = parentModule->lastModuleInstance;
            parentModule->lastModuleInstance->next = moduleInstance;
            parentModule->lastModuleInstance       = moduleInstance;
        }
    }

    internal_nbp_module_instance_update_stats(moduleInstance);

    internal_nbp_notify_printer_instantiate_module_started(moduleInstance);

    internal_nbp_notify_runner_instantiate_module_started(
        moduleInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        moduleInstance->moduleDetails->function(
            &moduleInstance->runs[i],
            NBP_NULLPTR,
            &moduleInstance->runs[i],
            &moduleInstance->runs[i],
            &moduleInstance->runs[i],
            1);

        if (moduleInstance->runs[i].totalNumberOfTestCaseInstances == 0) {
            NBP_REPORT_ERROR_STRING_CONTEXT(
                ec_no_test_case_instantiated,
                "module has no test case");
            NBP_EXIT(ec_no_test_case_instantiated);
        }
    }

    internal_nbp_notify_runner_instantiate_module_completed(moduleInstance);

    internal_nbp_notify_printer_instantiate_module_completed(moduleInstance);

    return moduleInstance;
}

#endif // end if _H_NBP_INTERNAL_IMPL_MODULE

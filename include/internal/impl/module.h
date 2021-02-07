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
#include "../details/scheduler_notifier.h"

extern nbp_module_details_t* gInternalNbpMainModuleDetails;

nbp_module_instance_t* internal_nbp_instantiate_module(
    nbp_module_details_t* moduleDetails,
    nbp_module_t* parentModule,
    unsigned int numberOfRuns,
    void* context)
{
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
        runs[i].moduleInstance         = moduleInstance;
        runs[i].state                  = ms_ready;
        runs[i].firstTestCaseInstance  = NBP_NULLPTR;
        runs[i].lastTestCaseInstance   = NBP_NULLPTR;
        runs[i].firstTestSuiteInstance = NBP_NULLPTR;
        runs[i].lastTestSuiteInstance  = NBP_NULLPTR;
        runs[i].firstModuleInstance    = NBP_NULLPTR;
        runs[i].lastModuleInstance     = NBP_NULLPTR;
    }

    moduleInstance->moduleDetails   = moduleDetails;
    moduleInstance->state           = mis_ready;
    moduleInstance->parent          = parentModule;
    moduleInstance->depth           = 0;
    moduleInstance->setupDetails    = moduleDetails->setupDetails;
    moduleInstance->teardownDetails = moduleDetails->teardownDetails;
    moduleInstance->runs            = runs;
    moduleInstance->numberOfRuns    = numberOfRuns;
    moduleInstance->next            = NBP_NULLPTR;
    moduleInstance->prev            = NBP_NULLPTR;

    if (parentModule != NBP_NULLPTR) {
        moduleInstance->depth = parentModule->moduleInstance->depth + 1;

        if (parentModule->firstModuleInstance == NBP_NULLPTR) {
            parentModule->firstModuleInstance = moduleInstance;
            parentModule->lastModuleInstance  = moduleInstance;
        } else {
            moduleInstance->prev = parentModule->lastModuleInstance;
            parentModule->lastModuleInstance->next = moduleInstance;
            parentModule->lastModuleInstance       = moduleInstance;
        }
    }

    internal_nbp_notify_printer_instantiate_module_started(moduleInstance);

    internal_nbp_notify_scheduler_instantiate_module_started(
        moduleInstance,
        context);

    for (unsigned int i = 0; i < numberOfRuns; i++) {
        moduleInstance->moduleDetails->function(&moduleInstance->runs[i]);
    }

    internal_nbp_notify_scheduler_instantiate_module_completed(moduleInstance);

    internal_nbp_notify_printer_instantiate_module_completed(moduleInstance);

    return moduleInstance;
}

#endif // end if _H_NBP_INTERNAL_IMPL_MODULE

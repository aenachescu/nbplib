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

#ifndef _H_NBP_INTERNAL_IMPL_MAIN
#define _H_NBP_INTERNAL_IMPL_MAIN

#include "../api/error.h"
#include "../api/exit.h"
#include "../api/memory.h"
#include "../build_configuration.h"
#include "../details/printer_notifier.h"
#include "../details/scheduler.h"
#include "../details/scheduler_notifier.h"
#include "../types/error.h"
#include "../types/module.h"
#include "../types/printer.h"
#include "../types/scheduler.h"
#include "../types/sync.h"

extern nbp_module_t* gInternalNbpMainModule;

extern nbp_printer_interface_t gInternalNbpPrinterInterfacenbpDefaultPrinter;

nbp_printer_interface_t* gInternalNbpDefaultPrinterInterfaces[] = {
    &gInternalNbpPrinterInterfacenbpDefaultPrinter};

nbp_printer_interface_t** gInternalNbpPrinterInterfaces = NBP_NULLPTR;
unsigned int gInternalNbpPrinterInterfacesSize          = 0;

unsigned int gInternalNbpNumberOfTestCases            = 0;
NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRunTestCases = NBP_ATOMIC_UINT_INIT(0);

int gInternalNbpSchedulerRunEnabled = 0;

#ifdef NBP_BASIC_SCHEDULER
INTERNAL_NBP_INCLUDE_SCHEDULER(nbpBasicScheduler);
nbp_scheduler_interface_t* gInternalNbpSchedulerInterface =
    INTERNAL_NBP_GET_POINTER_TO_SCHEDULER(nbpBasicScheduler);
#endif // end if NBP_BASIC_SCHEDULER

#ifdef NBP_MT_SCHEDULER
nbp_scheduler_interface_t* gInternalNbpSchedulerInterface = NBP_NULLPTR;
#endif // end if NBP_MT_SCHEDULER

static int internal_nbp_string_equal(const char* a, const char* b)
{
    while (*a == *b && *a != '\0') {
        a++;
        b++;
    }

    return *a != *b ? 0 : 1;
}

static int internal_nbp_command_run_all()
{
    internal_nbp_notify_printer_init();
    internal_nbp_notify_scheduler_init();

    if (gInternalNbpSchedulerInterface->instantiateTestCaseCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_scheduler_interface);
        NBP_EXIT(ec_invalid_scheduler_interface);
    }
    if (gInternalNbpSchedulerInterface->runCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_scheduler_interface);
        NBP_EXIT(ec_invalid_scheduler_interface);
    }

    // TODO: instantiate the main module

    // TODO: send some stats to printers about instances

    internal_nbp_notify_scheduler_run();

    unsigned int numberOfRunTestsCases =
        NBP_ATOMIC_UINT_LOAD(&gInternalNbpNumberOfRunTestCases);
    if (numberOfRunTestsCases != gInternalNbpNumberOfTestCases) {
        NBP_REPORT_ERROR(ec_not_all_tests_were_run);
        NBP_EXIT(ec_not_all_tests_were_run);
    }

    // TODO: send some stats to printers about asserts, test cases etc

    internal_nbp_notify_scheduler_uninit();
    internal_nbp_notify_printer_uninit();

    // TODO: return error if main module state is not passed

    return (int) ec_success;
}

static int internal_nbp_command_version()
{
    internal_nbp_notify_printer_init();
    internal_nbp_notify_printer_handle_version_command();
    internal_nbp_notify_printer_uninit();

    return (int) ec_success;
}

int main(int argc, const char** argv)
{
    if (argc < 1) {
        return (int) ec_invalid_command_line;
    }

    gInternalNbpPrinterInterfaces     = gInternalNbpDefaultPrinterInterfaces;
    gInternalNbpPrinterInterfacesSize = 1;

    if (argc == 1) {
        return internal_nbp_command_run_all();
    }

    if (internal_nbp_string_equal(argv[1], "--version") == 1) {
        return internal_nbp_command_version();
    }

    return (int) ec_invalid_command_line;
}

#endif // end if _H_NBP_INTERNAL_IMPL_MAIN

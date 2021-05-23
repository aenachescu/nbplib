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
#include "../details/module.h"
#include "../details/reporter.h"
#include "../details/reporter_notifier.h"
#include "../details/runner.h"
#include "../details/runner_notifier.h"
#include "../types/error.h"
#include "../types/module.h"
#include "../types/reporter.h"
#include "../types/runner.h"
#include "../types/sync.h"

extern nbp_module_function_t* gInternalNbpMainModuleFunction;

nbp_module_instance_t* gInternalNbpMainModuleInstance = NBP_NULLPTR;

INTERNAL_NBP_INCLUDE_REPORTER(nbpConsoleReporter);

nbp_reporter_interface_t* gInternalNbpDefaultReporterInterfaces[] = {
    INTERNAL_NBP_GET_POINTER_TO_REPORTER(nbpConsoleReporter)};

nbp_reporter_interface_t** gInternalNbpReporterInterfaces = NBP_NULLPTR;
unsigned int gInternalNbpReporterInterfacesSize           = 0;

unsigned int gInternalNbpNumberOfTestCases            = 0;
NBP_ATOMIC_UINT_TYPE gInternalNbpNumberOfRanTestCases = NBP_ATOMIC_UINT_INIT(0);

int gInternalNbpRunnerRunEnabled = 0;

#ifdef NBP_BASIC_RUNNER
INTERNAL_NBP_INCLUDE_RUNNER(nbpBasicRunner);
nbp_runner_interface_t* gInternalNbpRunnerInterface =
    INTERNAL_NBP_GET_POINTER_TO_RUNNER(nbpBasicRunner);
#endif // end if NBP_BASIC_RUNNER

#ifdef NBP_MT_RUNNER
nbp_runner_interface_t* gInternalNbpRunnerInterface = NBP_NULLPTR;
#endif // end if NBP_MT_RUNNER

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
    internal_nbp_notify_reporter_init();
    internal_nbp_notify_runner_init();

    if (gInternalNbpRunnerInterface->instantiateTestCaseCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_runner_interface);
        NBP_EXIT(ec_invalid_runner_interface);
        return ec_invalid_runner_interface;
    }
    if (gInternalNbpRunnerInterface->runCbk == NBP_NULLPTR) {
        NBP_REPORT_ERROR(ec_invalid_runner_interface);
        NBP_EXIT(ec_invalid_runner_interface);
        return ec_invalid_runner_interface;
    }

    gInternalNbpMainModuleInstance = internal_nbp_instantiate_module(
        gInternalNbpMainModuleFunction,
        NBP_NULLPTR,
        0,
        1,
        NBP_NULLPTR);

    if (gInternalNbpMainModuleInstance == NBP_NULLPTR) {
        return ec_out_of_memory;
    }

    // TODO: send some stats to reporters about instances

    internal_nbp_notify_reporter_before_run();

    internal_nbp_notify_runner_run();

    internal_nbp_notify_reporter_after_run();

    unsigned int numberOfRunTestsCases =
        NBP_ATOMIC_UINT_LOAD(&gInternalNbpNumberOfRanTestCases);
    if (numberOfRunTestsCases != gInternalNbpNumberOfTestCases) {
        NBP_REPORT_ERROR(ec_not_all_tests_were_run);
        NBP_EXIT(ec_not_all_tests_were_run);
        return ec_not_all_tests_were_run;
    }

    // TODO: send some stats to reporters about asserts, test cases etc

    internal_nbp_notify_runner_uninit();
    internal_nbp_notify_reporter_uninit();

    // TODO: return error if main module state is not passed

    // TODO: free data!!!

    return (int) ec_success;
}

static int internal_nbp_command_version()
{
    internal_nbp_notify_reporter_init();
    internal_nbp_notify_reporter_handle_version_command();
    internal_nbp_notify_reporter_uninit();

    return (int) ec_success;
}

int main(int argc, const char** argv)
{
    if (argc < 1) {
        return (int) ec_invalid_command_line;
    }

    gInternalNbpReporterInterfaces     = gInternalNbpDefaultReporterInterfaces;
    gInternalNbpReporterInterfacesSize = 1;

    if (argc == 1) {
        return internal_nbp_command_run_all();
    }

    if (internal_nbp_string_equal(argv[1], "--version") == 1) {
        return internal_nbp_command_version();
    }

    return (int) ec_invalid_command_line;
}

#endif // end if _H_NBP_INTERNAL_IMPL_MAIN

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

#ifndef _H_NBP_INTERNAL_DETAILS_RUNNER_NOTIFIER
#define _H_NBP_INTERNAL_DETAILS_RUNNER_NOTIFIER

#include "../types/runner.h"

void internal_nbp_notify_runner_init();

void internal_nbp_notify_runner_uninit();

void internal_nbp_notify_runner_run();

void internal_nbp_notify_runner_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance,
    void* context);

void internal_nbp_notify_runner_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance,
    void* context);

void internal_nbp_notify_runner_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_runner_instantiate_module_started(
    nbp_module_instance_t* moduleInstance,
    void* context);

void internal_nbp_notify_runner_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance);

#endif // end if _H_NBP_INTERNAL_DETAILS_RUNNER_NOTIFIER

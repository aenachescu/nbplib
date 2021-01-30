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

#ifndef _H_NBP_INTERNAL_DETAILS_PRINTER_NOTIFIER
#define _H_NBP_INTERNAL_DETAILS_PRINTER_NOTIFIER

#include "../types/printer.h"

void internal_nbp_notify_printer_init();

void internal_nbp_notify_printer_uninit();

void internal_nbp_notify_printer_handle_version_command();

void internal_nbp_notify_printer_on_error(
    nbp_error_code_e errorCode,
    int line,
    const char* file);

void internal_nbp_notify_printer_on_error_string_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    const char* context);

void internal_nbp_notify_printer_on_error_custom_context(
    nbp_error_code_e errorCode,
    int line,
    const char* file,
    void* context);

void internal_nbp_notify_printer_on_exit(nbp_error_code_e errorCode);

void internal_nbp_notify_printer_instantiate_test_case(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_printer_instantiate_test_suite_started(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_instantiate_test_suite_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_instantiate_module_started(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_printer_instantiate_module_completed(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_printer_test_case_started(nbp_test_case_t* testCase);

void internal_nbp_notify_printer_test_case_completed(nbp_test_case_t* testCase);

void internal_nbp_notify_printer_test_case_instance_started(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_printer_test_case_instance_completed(
    nbp_test_case_instance_t* testCaseInstance);

void internal_nbp_notify_printer_test_suite_started(
    nbp_test_suite_t* testSuite);

void internal_nbp_notify_printer_test_suite_completed(
    nbp_test_suite_t* testSuite);

void internal_nbp_notify_printer_test_suite_instance_started(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_test_suite_instance_completed(
    nbp_test_suite_instance_t* testSuiteInstance);

void internal_nbp_notify_printer_module_started(nbp_module_t* module);

void internal_nbp_notify_printer_module_completed(nbp_module_t* module);

void internal_nbp_notify_printer_module_instance_started(
    nbp_module_instance_t* moduleInstance);

void internal_nbp_notify_printer_module_instance_completed(
    nbp_module_instance_t* moduleInstance);

#endif // end if _H_NBP_INTERNAL_DETAILS_PRINTER_NOTIFIER

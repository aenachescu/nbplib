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

#ifndef _H_NBP_INTERNAL_DETAILS_TEST_CASE
#define _H_NBP_INTERNAL_DETAILS_TEST_CASE

#include "../types/module.h"
#include "../types/test_case.h"
#include "../types/test_suite.h"

unsigned int internal_nbp_get_test_case_state_position(
    nbp_test_case_state_e state);

unsigned int internal_nbp_get_test_case_instance_state_position(
    nbp_test_case_instance_state_e state);

int internal_nbp_is_failed_test_case(nbp_test_case_t* testCase);

void internal_nbp_test_case_update_state_stats(
    nbp_test_case_t* testCase,
    nbp_test_case_state_e oldState,
    nbp_test_case_state_e newState);

void internal_nbp_test_case_instance_update_state_stats(
    nbp_test_case_instance_t* testCaseInstance,
    nbp_test_case_instance_state_e oldState,
    nbp_test_case_instance_state_e newState);

unsigned int internal_nbp_get_number_of_test_cases(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_state_e state);

unsigned int internal_nbp_get_number_of_test_case_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_test_case_instance_state_e state);

nbp_test_case_t* internal_nbp_get_test_case_from_instance(
    nbp_test_case_instance_t* testCaseInstance,
    unsigned int runId);

nbp_test_case_instance_t* internal_nbp_instantiate_test_case(
    nbp_test_case_details_t* testCaseDetails,
    nbp_module_t* parentModule,
    nbp_test_suite_t* parentTestSuite,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

#endif // end if _H_NBP_INTERNAL_DETAILS_TEST_CASE

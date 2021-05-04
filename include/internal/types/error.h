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

#ifndef _H_NBP_INTERNAL_TYPES_ERROR
#define _H_NBP_INTERNAL_TYPES_ERROR

/**
 * TODO: add docs
 */
enum nbp_error_context_type_e
{
    ect_empty  = 0x10000000,
    ect_string = 0x10000001,
    ect_custom = 0x10000002
};
typedef enum nbp_error_context_type_e nbp_error_context_type_e;

/**
 * TODO: add docs
 */
enum nbp_error_code_e
{
    ec_success                   = 0,
    ec_tests_failed              = 1,
    ec_out_of_memory             = 2,
    ec_sync_error                = 3,
    ec_invalid_command_line      = 4,
    ec_not_all_tests_were_run    = 5,
    ec_invalid_runner_interface  = 6,
    ec_invalid_number_of_runs    = 7,
    ec_runner_run_is_disabled    = 8,
    ec_unexpected_state          = 9,
    ec_invalid_parent            = 10,
    ec_no_test_case_instantiated = 11,
    ec_unexpected_internal_data  = 12,
};
typedef enum nbp_error_code_e nbp_error_code_e;

struct nbp_error_t
{
    nbp_error_code_e errorCode;
    int line;
    const char* file;

    nbp_error_context_type_e contextType;
    union
    {
        const char* stringContext;
        void* customContext;
    };
};
typedef struct nbp_error_t nbp_error_t;

#endif // end if _H_NBP_INTERNAL_TYPES_ERROR

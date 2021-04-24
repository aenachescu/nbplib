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

#ifndef _H_NBP_INTERNAL_TYPES_STATISTICS
#define _H_NBP_INTERNAL_TYPES_STATISTICS

enum nbp_statistics_type_e
{
    st_total_number_of_test_cases           = 0x70000000,
    st_total_number_of_test_case_instances  = 0x70000001,
    st_total_number_of_test_suites          = 0x70000002,
    st_total_number_of_test_suite_instances = 0x70000003,
    st_total_number_of_modules              = 0x70000004,
    st_total_number_of_module_instances     = 0x70000005,
    st_number_of_test_cases                 = 0x70000006,
    st_number_of_test_case_instances        = 0x70000007,
    st_number_of_test_suites                = 0x70000008,
    st_number_of_test_suite_instances       = 0x70000009,
    st_number_of_modules                    = 0x7000000A,
    st_number_of_module_instances           = 0x7000000B,
};
typedef enum nbp_statistics_type_e nbp_statistics_type_e;

#endif // end if _H_NBP_INTERNAL_TYPES_STATISTICS

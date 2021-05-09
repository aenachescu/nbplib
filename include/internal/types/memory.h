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

#ifndef _H_NBP_INTERNAL_TYPES_MEMORY
#define _H_NBP_INTERNAL_TYPES_MEMORY

enum nbp_memory_tag_e
{
    mt_test_case_instance  = 0x4E425000,
    mt_test_case           = 0x4E425001,
    mt_test_suite_instance = 0x4E425002,
    mt_test_suite          = 0x4E425003,
    mt_module_instance     = 0x4E425004,
    mt_module              = 0x4E425005,
    mt_console_reporter    = 0x4E425006,
    mt_basic_runner        = 0x4E425007,
};
typedef enum nbp_memory_tag_e nbp_memory_tag_e;

#endif // end if _H_NBP_INTERNAL_TYPES_MEMORY

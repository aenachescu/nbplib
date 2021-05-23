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

#ifndef _H_NBP_INTERNAL_DETAILS_MODULE
#define _H_NBP_INTERNAL_DETAILS_MODULE

#include "../types/module.h"

unsigned int internal_nbp_get_module_state_position(nbp_module_state_e state);

unsigned int internal_nbp_get_module_instance_state_position(
    nbp_module_instance_state_e state);

void internal_nbp_module_update_state_stats(
    nbp_module_t* module,
    nbp_module_state_e oldState,
    nbp_module_state_e newState);

void internal_nbp_module_instance_update_state_stats(
    nbp_module_instance_t* moduleInstance,
    nbp_module_instance_state_e oldState,
    nbp_module_instance_state_e newState);

unsigned int internal_nbp_get_number_of_modules(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_state_e state);

unsigned int internal_nbp_get_number_of_module_instances(
    NBP_ATOMIC_UINT_TYPE* statsArray,
    nbp_module_instance_state_e state);

nbp_module_t* internal_nbp_get_module_from_instance(
    nbp_module_instance_t* moduleInstance,
    unsigned int runId);

nbp_module_instance_t* internal_nbp_instantiate_module(
    nbp_module_function_t* moduleFunction,
    nbp_module_t* parentModule,
    int instantiationLine,
    unsigned int numberOfRuns,
    void* context);

#endif // end if _H_NBP_INTERNAL_DETAILS_MODULE

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

#ifndef _H_NBP_INTERNAL_API_MAIN
#define _H_NBP_INTERNAL_API_MAIN

#include "../types/module.h"
#include "../utils/utils.h"
#include "memory.h"
#include "module.h"

/**
 * TODO: add docs
 */
#define NBP_MAIN_MODULE(func, ...)                                             \
    void nbp_module_config_function_##func(                                    \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_details_t* moduleDetails)        \
    {                                                                          \
        if (moduleDetails->isConfigured == 1) {                                \
            return;                                                            \
        } else {                                                               \
            moduleDetails->isConfigured = 1;                                   \
        }                                                                      \
        INTERNAL_NBP_GENERATE_MAIN_MODULE_CONFIG_FUNCTION(F_##__VA_ARGS__)     \
    }                                                                          \
    void nbp_module_function_##func(nbp_module_t* nbpParamModule);             \
    nbp_module_details_t gInternalNbpModuleDetails##func = {                   \
        .name            = #func,                                              \
        .functionName    = #func,                                              \
        .file            = NBP_SOURCE_FILE,                                    \
        .line            = NBP_SOURCE_LINE,                                    \
        .isConfigured    = 0,                                                  \
        .configFunction  = nbp_module_config_function_##func,                  \
        .function        = nbp_module_function_##func,                         \
        .setupDetails    = NBP_NULLPTR,                                        \
        .teardownDetails = NBP_NULLPTR,                                        \
    };                                                                         \
    nbp_module_details_t* gInternalNbpMainModuleDetails =                      \
        &gInternalNbpModuleDetails##func;                                      \
    void nbp_module_function_##func(                                           \
        NBP_MAYBE_UNUSED_PARAMETER nbp_module_t* nbpParamModule)

#define INTERNAL_NBP_GENERATE_MAIN_MODULE_CONFIG_FUNCTION(...)                 \
    NBP_PP_CONCAT(NBP_PP_PARSE_PARAMETER_, NBP_PP_COUNT(GMMC##__VA_ARGS__))    \
    (GMMCF_, GMMC##__VA_ARGS__)

// This macro is generated when NBP_MAIN_MODULE macro is used without parameters
#define INTERNAL_NBP_GMMCF_

#define INTERNAL_NBP_GMMCF_NBP_MODULE_NAME(newName)                            \
    moduleDetails->name = newName;

#define INTERNAL_NBP_GMMCF_NBP_MODULE_SETUP(func)                              \
    NBP_INCLUDE_MODULE_SETUP(func);                                            \
    moduleDetails->setupDetails = NBP_GET_POINTER_TO_MODULE_SETUP(func);

#define INTERNAL_NBP_GMMCF_NBP_MODULE_TEARDOWN(func)                           \
    NBP_INCLUDE_MODULE_TEARDOWN(func);                                         \
    moduleDetails->teardownDetails = NBP_GET_POINTER_TO_MODULE_TEARDOWN(func);

#define INTERNAL_NBP_GMMCF_NBP_MODULE_FIXTURES(setupFunc, teardownFunc)        \
    INTERNAL_NBP_GMMCF_NBP_MODULE_SETUP(setupFunc)                             \
    INTERNAL_NBP_GMMCF_NBP_MODULE_TEARDOWN(teardownFunc)

#endif // end if _H_NBP_INTERNAL_API_MAIN

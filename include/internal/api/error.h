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

#ifndef _H_NBP_INTERNAL_API_ERROR
#define _H_NBP_INTERNAL_API_ERROR

#include "../details/printer_notifier.h"
#include "../utils/compiler.h"

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR(errCode)                                              \
    internal_nbp_notify_printer_on_error(                                      \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE)

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR_CTX_STRING(errCode, str)                              \
    internal_nbp_notify_printer_on_error_ctx_string(                           \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE,                                                       \
        str)

/**
 * TODO: add docs
 */
#define NBP_REPORT_ERROR_CTX_CUSTOM(errCode, ctx)                              \
    internal_nbp_notify_printer_on_error_ctx_custom(                           \
        errCode,                                                               \
        NBP_SOURCE_LINE,                                                       \
        NBP_SOURCE_FILE,                                                       \
        ctx)

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_CODE(err) err.errorCode

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_LINE(err) err.line

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_FILE(err) err.file

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_CONTEXT_TYPE(err) err.contextType

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_CONTEXT_STRING(err) err.contextString

/**
 * TODO: add docs
 */
#define NBP_GET_ERROR_CONTEXT_CUSTOM(err) err.contextCustom

#endif // end if _H_NBP_INTERNAL_API_ERROR

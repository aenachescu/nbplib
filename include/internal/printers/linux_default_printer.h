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

#ifndef _H_NBP_INTERNAL_PRINTERS_LINUX_DEFAULT_PRINTER
#define _H_NBP_INTERNAL_PRINTERS_LINUX_DEFAULT_PRINTER

#include "../api/printer.h"
#include "../api/version.h"

#include <stdio.h>

NBP_PRINTER_CALLBACK_INIT(nbp_dp_init)
{
    printf("init\n");
}

NBP_PRINTER_CALLBACK_UNINIT(nbp_dp_uninit)
{
    printf("uninit\n");
}

NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(nbp_dp_handle_version_command)
{
    printf("nbp version: %s\n", NBP_VERSION_STR);
}

NBP_PRINTER_CALLBACK_ON_ERROR(nbp_dp_on_error)
{
    switch (NBP_GET_ERROR_CONTEXT_TYPE(NBP_THIS_ERROR)) {
    case ect_string:
        printf(
            "[error] code = %d, line = %d, file = %s, message = %s\n",
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR),
            NBP_GET_ERROR_STRING_CONTEXT(NBP_THIS_ERROR));
        break;
    default:
        printf(
            "[error] code = %d, line = %d, file = %s\n",
            NBP_GET_ERROR_CODE(NBP_THIS_ERROR),
            NBP_GET_ERROR_LINE(NBP_THIS_ERROR),
            NBP_GET_ERROR_FILE(NBP_THIS_ERROR));
        break;
    }
}

NBP_PRINTER(
    nbpDefaultPrinter,
    NBP_PRINTER_CALLBACKS(
        NBP_PRINTER_CALLBACK_INIT(nbp_dp_init),
        NBP_PRINTER_CALLBACK_UNINIT(nbp_dp_uninit),
        NBP_PRINTER_CALLBACK_HANDLE_VERSION_COMMAND(
            nbp_dp_handle_version_command),
        NBP_PRINTER_CALLBACK_ON_ERROR(nbp_dp_on_error)));

#endif // end if _H_NBP_INTERNAL_PRINTERS_LINUX_DEFAULT_PRINTER

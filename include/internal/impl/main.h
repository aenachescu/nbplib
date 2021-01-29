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

#ifndef _H_NBP_INTERNAL_IMPL_MAIN
#define _H_NBP_INTERNAL_IMPL_MAIN

#include "../api/memory.h"
#include "../details/printer_notifier.h"
#include "../types/error.h"
#include "../types/module.h"
#include "../types/printer.h"

extern nbp_module_t* gInternalNbpMainModule;

extern nbp_printer_interface_t gInternalNbpPrinterInterfacenbpDefaultPrinter;

nbp_printer_interface_t* gInternalNbpDefaultPrinterInterfaces[] = {
    &gInternalNbpPrinterInterfacenbpDefaultPrinter};

nbp_printer_interface_t** gInternalNbpPrinterInterfaces = NBP_NULLPTR;
unsigned int gInternalNbpPrinterInterfacesSize          = 0;

int gInternalNbpSchedulerRunEnabled = 0;

static int internal_nbp_string_equal(const char* a, const char* b)
{
    while (*a == *b && *a != '\0') {
        a++;
        b++;
    }

    return *a != *b ? 0 : 1;
}

static int internal_nbp_command_run_all()
{
    return (int) ec_success;
}

static int internal_nbp_command_version()
{
    internal_nbp_notify_printer_init();
    internal_nbp_notify_printer_handle_version_command();
    internal_nbp_notify_printer_uninit();

    return (int) ec_success;
}

int main(int argc, const char** argv)
{
    if (argc < 1) {
        return (int) ec_invalid_command_line;
    }

    gInternalNbpPrinterInterfaces     = gInternalNbpDefaultPrinterInterfaces;
    gInternalNbpPrinterInterfacesSize = 1;

    if (argc == 1) {
        return internal_nbp_command_run_all();
    }

    if (internal_nbp_string_equal(argv[1], "--version") == 1) {
        return internal_nbp_command_version();
    }

    return (int) ec_invalid_command_line;
}

#endif // end if _H_NBP_INTERNAL_IMPL_MAIN

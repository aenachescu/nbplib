/*
No Bugs in Production (NBP)
https://github.com/aenachescu/nbp

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

#include "nbp.h"

#include <stdio.h>
#include <stdlib.h>

#if NBP_VERSION > NBP_MAKE_VERSION(1, 0, 0)
const char* msg1 = "greater than 1.0.0";
#else
const char* msg1 = "not greater than 1.0.0";
#endif

#if NBP_VERSION >= NBP_MAKE_VERSION(1, 0, 0)
const char* msg2 = "greater than or equal to 1.0.0";
#else
const char* msg2 = "less than 1.0.0";
#endif

#if NBP_VERSION > NBP_MAKE_VERSION(0, 9, 9)
const char* msg3 = "greater than 0.9.9";
#else
const char* msg3 = "not greater than 0.9.9";
#endif

int main(int argc, const char** argv)
{
    if (argc != 2) {
        return 0;
    }

    printf(
        "nbp version = %s\n"
        "nbp version = %x\n",
        NBP_VERSION_STR,
        NBP_VERSION);

    printf("message#1 = %s\n", msg1);
    printf("message#2 = %s\n", msg2);
    printf("message#3 = %s\n", msg3);

    printf("%s", argv[1]);

    return 1;
}

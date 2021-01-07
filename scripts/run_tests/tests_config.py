# No Bugs in Production (NBP) Library
# https://github.com/aenachescu/nbplib
#
# Licensed under the MIT License <http://opensource.org/licenses/MIT>.
# SPDX-License-Identifier: MIT
# Copyright (c) 2019-2020 Alin Enachescu <https://github.com/aenachescu>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

testsConfig = [
    {
        "name": "tmp2",
        "cmdline": "--version",
        "returnCode": 1
    },
    {
        "name": "check_build_configuration",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<any>",
                "outputContains": "linux ${compiler} ${standard} ${platform} ${sanitizer}"
            }
        ]
    },
    {
        "name": "check_leak_sanitizer",
        "outputContains": "check_leak_sanitizer completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<-m64>:<leak>",
                "returnCode": 23,
                "outputContains": "detected memory leaks"
            }
        ]
    },
    {
        "name": "check_thread_sanitizer",
        "outputContains": "check_thread_sanitizer completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<thread>",
                "returnCode": 66,
                "outputContains": "ThreadSanitizer: data race"
            }
        ]
    },
    {
        "name": "check_ub_sanitizer",
        "outputContains": "check_ub_sanitizer completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<ub>",
                "outputContains": "signed integer overflow"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_heap_use_after_free",
        "outputContains": "check_address_sanitizer(heap use after free) completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "outputContains": "AddressSanitizer: heap-use-after-free on address"
            }
        ]
    }
]

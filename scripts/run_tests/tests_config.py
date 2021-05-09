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
        "name": "check_build_configuration",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<any>",
                "consoleOutputContains": "linux ${compiler} ${standard} "
                    "${platform} ${sanitizer}"
            }
        ]
    },
    {
        "name": "check_leak_sanitizer",
        "consoleOutputContains": "check_leak_sanitizer completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<-m64>:<leak>",
                "returnCode": 23,
                "consoleOutputContains": "detected memory leaks"
            }
        ]
    },
    {
        "name": "check_thread_sanitizer",
        "consoleOutputContains":
            "check_thread_sanitizer completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<thread>",
                "returnCode": 66,
                "consoleOutputContains": "ThreadSanitizer: data race"
            }
        ]
    },
    {
        "name": "check_ub_sanitizer",
        "consoleOutputContains": "check_ub_sanitizer completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<ub>",
                "returnCode": 1,
                "consoleOutputContains": "signed integer overflow"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_heap_use_after_free",
        "consoleOutputContains": "check_address_sanitizer(heap use after free) "
            "completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "consoleOutputContains":
                    "AddressSanitizer: heap-use-after-free on address"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_heap_buffer_overflow",
        "consoleOutputContains": "check_address_sanitizer(heap buffer "
            "overflow) completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "consoleOutputContains":
                    "AddressSanitizer: heap-buffer-overflow on address"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_stack_buffer_overflow",
        "consoleOutputContains":
            "check_address_sanitizer_stack_buffer_overflow "
            "completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "consoleOutputContains":
                    "AddressSanitizer: stack-buffer-overflow on address"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_global_buffer_overflow",
        "consoleOutputContains":
            "check_address_sanitizer_global_buffer_overflow "
            "completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "consoleOutputContains":
                    "AddressSanitizer: global-buffer-overflow on address"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_stack_use_after_return",
        "consoleOutputContains":
            "check_address_sanitizer_stack_use_after_return "
            "completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "consoleOutputContains":
                    "AddressSanitizer: stack-use-after-return on address"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_pointer_comparison",
        "consoleOutputContains":
            "check_address_sanitizer_pointer_comparison completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "consoleOutputContains":
                    "AddressSanitizer: invalid-pointer-pair:"
            }
        ]
    },
    {
        "name": "check_address_sanitizer_pointer_subtraction",
        "consoleOutputContains":"check_address_sanitizer_pointer_subtraction "
            "completed successfully",
        "buildConfig": [
            {
                "config": "<any>:<any>:<any>:<address>",
                "returnCode": 1,
                "consoleOutputContains":
                    "AddressSanitizer: invalid-pointer-pair:"
            }
        ]
    }
]

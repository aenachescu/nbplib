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

#ifndef _H_TEST_ADDRESS_SANITIZER_OPTIONS
#define _H_TEST_ADDRESS_SANITIZER_OPTIONS

#ifdef NBP_LIBRARY_MAIN

#ifdef NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED

#ifdef NBP_LANGUAGE_CPP
extern "C" {
#endif // end if NBP_LANGUAGE_CPP

const char* __asan_default_options()
{
    const char* options =
        "report_globals=1"
        ":check_initialization_order=true"
        ":replace_str=true"
        ":replace_intrin=true"
        ":detect_stack_use_after_return=true"
        ":alloc_dealloc_mismatch=true"
        ":new_delete_type_mismatch=true"
        ":strict_init_order=true"
        ":detect_invalid_pointer_pairs=100"
        ":detect_container_overflow=true"
        ":detect_odr_violation=2"
        ":halt_on_error=true"
        ":detect_leaks=false"
        ":leak_check_at_exit=false"
        ":detect_deadlocks=false"
        ":strict_string_checks=true"
        ":intercept_strstr=true"
        ":intercept_strspn=true"
        ":intercept_strtok=true"
        ":intercept_strpbrk=true"
        ":intercept_strlen=true"
        ":intercept_strndup=true"
        ":intercept_strchr=true"
        ":intercept_memcmp=true"
        ":strict_memcmp=true"
        ":intercept_memmem=true"
        ":intercept_intrin=true"
        ":intercept_stat=true"
        ":intercept_send=true";

    return options;
}

#ifdef NBP_LANGUAGE_CPP
}
#endif // end if NBP_LANGUAGE_CPP

#endif // end if NBP_TEST_MODE_ADDRESS_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_THREAD_SANITIZER_ENABLED

#ifdef NBP_LANGUAGE_CPP
extern "C" {
#endif // end if NBP_LANGUAGE_CPP

const char* __tsan_default_options()
{
    const char* options =
        "report_bugs=1"
        ":report_thread_leaks=1"
        ":report_destroy_locked=1"
        ":report_mutex_bugs=1"
        ":report_signal_unsafe=1"
        ":report_atomic_races=1"
        ":halt_on_error=true"
        ":detect_deadlocks=1";

    return options;
}

#ifdef NBP_LANGUAGE_CPP
}
#endif // end if NBP_LANGUAGE_CPP

#endif // end if NBP_TEST_MODE_THREAD_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_LEAK_SANITIZER_ENABLED

#ifdef NBP_LANGUAGE_CPP
extern "C" {
#endif // end if NBP_LANGUAGE_CPP

const char* __lsan_default_options()
{
    const char* options =
        "use_globals=true"
        ":use_stacks=true"
        ":use_registers=true"
        ":use_tls=true"
        ":use_root_sections=true"
        ":detect_leaks=true"
        ":leak_check_at_exit=true"
        ":check_printf=true";

    return options;
}

#ifdef NBP_LANGUAGE_CPP
}
#endif // end if NBP_LANGUAGE_CPP

#endif // end if NBP_TEST_MODE_LEAK_SANITIZER_ENABLED

#ifdef NBP_TEST_MODE_UB_SANITIZER_ENABLED

#ifdef NBP_LANGUAGE_CPP
extern "C" {
#endif // end if NBP_LANGUAGE_CPP

const char* __ubsan_default_options()
{
    const char* options = "halt_on_error=true";

    return options;
}

#ifdef NBP_LANGUAGE_CPP
}
#endif // end if NBP_LANGUAGE_CPP

#endif // end if NBP_TEST_MODE_UB_SANITIZER_ENABLED

#endif // end if NBP_LIBRARY_MAIN

#endif // end if _H_TEST_ADDRESS_SANITIZER_OPTIONS

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

#ifndef _H_NBP_INTERNAL_API_MEMORY
#define _H_NBP_INTERNAL_API_MEMORY

/**
 * TODO: add docs
 */
#ifndef NBP_CUSTOM_MEMORY_ALLOCATOR

#include <stdlib.h>

/**
 * TODO: add docs
 */
#define NBP_NULLPTR NULL

/**
 * TODO: add docs
 */
#define NBP_MEMORY_ALLOC(size) malloc(size)

/**
 * TODO: add docs
 */
#define NBP_MEMORY_FREE(ptr) free(ptr)

/**
 * TODO: add docs
 */
#define NBP_MEMORY_ALLOC_TAG(size, tag) malloc(size)

/**
 * TODO: add docs
 */
#define NBP_MEMORY_FREE_TAG(ptr, tag) free(ptr)

#else // if custom memory allocator is enabled

#ifndef NBP_NULLPTR
#error "Custom memory allocator is enabled but NBP_NULLPTR is undefined"
#endif // end if NBP_NULLPTR

#ifndef NBP_MEMORY_ALLOC
#error "Custom memory allocator is enabled but NBP_MEMORY_ALLOC is undefined"
#endif // end if NBP_MEMORY_ALLOC

#ifndef NBP_MEMORY_FREE
#error "Custom memory allocator is enabled but NBP_MEMORY_FREE is undefined"
#endif // end if NBP_MEMORY_FREE

#ifndef NBP_MEMORY_ALLOC_TAG
#error                                                                         \
    "Custom memory allocator is enabled but NBP_MEMORY_ALLOC_TAG is undefined"
#endif // end if NBP_MEMORY_ALLOC_TAG

#ifndef NBP_MEMORY_FREE_TAG
#error "Custom memory allocator is enabled but NBP_MEMORY_FREE_TAG is undefined"
#endif // end if NBP_MEMORY_FREE_TAG

#endif // end if NBP_CUSTOM_MEMORY_ALLOCATOR

#endif // end if _H_NBP_INTERNAL_API_MEMORY

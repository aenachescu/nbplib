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

#include "nbp.h"

#include <pthread.h>
#include <stdio.h>

int gValue = 0;

#define NUMBER_OF_THREADS 4

void* thread_func(void* param)
{
    int numberOfIterations = *((int*) param);

    for (int i = 0; i < numberOfIterations; i++) {
        gValue++;
    }

    return NULL;
}

int main()
{
    pthread_t threads[NUMBER_OF_THREADS];
    int       numberOfIterations[NUMBER_OF_THREADS];
    int       err;

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        numberOfIterations[i] = 1000;

        err = pthread_create(
            &threads[i],
            NULL,
            thread_func,
            (void*) &numberOfIterations[i]);
        if (err != 0) {
            printf("failed to create thread\n");
            return 1;
        }
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        err = pthread_join(threads[i], NULL);
        if (err != 0) {
            printf("failed to join thread\n");
            return 1;
        }
    }

    printf("check_thread_sanitizer completed successfully\n");

    return 0;
}

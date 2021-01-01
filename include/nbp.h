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

#ifndef _H_NBP_LIBRARY
#define _H_NBP_LIBRARY

#define NBP_MAKE_VERSION(major, minor, rev)                                    \
    (((major & 0xFFFF) << 16) | ((minor & 0xFF) << 8) | ((rev & 0xFF) << 8))

#define NBP_VERSION_MAJOR    1
#define NBP_VERSION_MINOR    0
#define NBP_VERSION_REVISION 0

#define NBP_VERSION_STR "1.0.0"

#define NBP_VERSION                                                            \
    NBP_MAKE_VERSION(NBP_VERSION_MAJOR, NBP_VERSION_MINOR, NBP_VERSION_REVISION)

#endif // end if _H_NBP_LIBRARY

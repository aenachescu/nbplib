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

supportedCompilersDict = {
    "gcc-5": {
        "standards": [ "-std=c99", "-std=c11" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-5"
    },
    "gcc-6": {
        "standards": [ "-std=c99", "-std=c11" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-6"
    },
    "gcc-7": {
        "standards": [ "-std=c99", "-std=c11" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-7"
    },
    "gcc-8": {
        "standards": [ "-std=c99", "-std=c11" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-8"
    },
    "gcc-9": {
        "standards": [ "-std=c99", "-std=c11" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-9"
    },
    "g++-5": {
        "standards": [ "-std=c++03", "-std=c++11", "-std=c++14", "-std=c++17" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-5"
    },
    "g++-6": {
        "standards": [ "-std=c++03", "-std=c++11", "-std=c++14", "-std=c++17" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-6"
    },
    "g++-7": {
        "standards": [ "-std=c++03", "-std=c++11", "-std=c++14", "-std=c++17" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-7"
    },
    "g++-8": {
        "standards": [ "-std=c++03", "-std=c++11", "-std=c++14", "-std=c++17" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-8"
    },
    "g++-9": {
        "standards": [ "-std=c++03", "-std=c++11", "-std=c++14", "-std=c++17" ],
        "platforms": [ "-m32", "-m64"],
        "gcov_tool": "gcov-9"
    },
}

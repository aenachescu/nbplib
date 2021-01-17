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

import difflib
import logging
import os
import subprocess
import sys

supportedExtensions = [ ".h", ".c", ".cpp" ]

COLOR_RED   = '\033[91m'
COLOR_GREEN = '\033[92m'
COLOR_CYAN  = '\033[96m'
COLOR_RESET = '\033[0m'

def check_file_formatting(log, filePath):
    log.info("Checking file formatting... [%s]", filePath)

    hasSupportedExtension = False

    for ext in supportedExtensions:
        if filePath.endswith(ext):
            hasSupportedExtension = True
            break

    if not hasSupportedExtension:
        log.info("Unsupported extension for file [%s]", filePath)
        return True

    if not os.path.exists(filePath):
        log.info("File does not exists [%s]", filePath)
        return False

    with open(filePath, 'r') as file:
        data = file.read()

        # clang-format-10 --style=file ../../include/nbp.h
        proc = subprocess.Popen(
            [ 'clang-format-10', '--style=file', filePath ],
            stdout=subprocess.PIPE
        )

        output = proc.communicate()[0]
        if proc.returncode != 0:
            log.error(
                "Unexpected return code for clang-format: %d",
                proc.returncode
            )
            return False

        output = output.decode('utf-8')

        if output != data:
            log.error("File is not formatted correctly: [%s]", filePath)

            dataLines = data.splitlines(keepends=True)
            outputLines = output.splitlines(keepends=True)

            diff = difflib.unified_diff(
                dataLines,
                outputLines,
                'original',
                'formatted'
            )

            for line in diff:
                if (line.startswith("+++") or line.startswith("---")
                    or line.startswith("@@")):
                    print(
                        "{}{}{}".format(COLOR_CYAN, line, COLOR_RESET),
                        end=""
                    )
                elif line.startswith("-"):
                    print(
                        "{}{}{}".format(COLOR_RED, line, COLOR_RESET),
                        end=""
                    )
                elif line.startswith("+"):
                    print(
                        "{}{}{}".format(COLOR_GREEN, line, COLOR_RESET),
                        end=""
                    )
                else:
                    print(line, end="")

            return False

    log.info("File is formatted correctly: [%s]", filePath)

    return True

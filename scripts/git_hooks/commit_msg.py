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

import logging
import os
import subprocess
import sys

from colorlog import ColoredFormatter

scriptPath = os.path.dirname(os.path.realpath(__file__))
rootPath = os.path.abspath(os.path.join(scriptPath, '../../'))

def check_commit_message(commitFilePath):
    status = True
    f = open(commitFilePath)
    commitMsg = f.readline()
    f.close()

    if commitMsg.endswith("\n"):
        commitMsg = commitMsg[:-1]

    params = [
        "python3.6",
        os.path.join(rootPath, "scripts/coding_standard_checks/run_checks.py"),
        "-v",
        "-ccm",
        commitMsg
    ]

    proc = subprocess.Popen(
        params,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )
    output = proc.communicate()[0]

    if proc.returncode != 0:
        log.error("Invalid commit message")
        status = False

    print()
    print(output.decode("utf-8"))

    if status:
        log.info("Valid commit message")

    return status

if __name__ == '__main__':
    logLevel = logging.DEBUG
    LOGFORMAT = "  %(log_color)s%(levelname)-8s%(reset)s | %(message)s"
    logging.root.setLevel(logLevel)
    formatter = ColoredFormatter(LOGFORMAT)
    stream = logging.StreamHandler()
    stream.setLevel(logLevel)
    stream.setFormatter(formatter)
    log = logging.getLogger('pythonConfig')
    log.setLevel(logLevel)
    log.addHandler(stream)

    log.info("Checking commit message...")

    if len(sys.argv) != 2:
        log.error("Invalid number of arguments")
        sys.exit(1)

    if not check_commit_message(sys.argv[1]):
        sys.exit(1)

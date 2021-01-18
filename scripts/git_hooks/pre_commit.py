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

def get_changed_files():
    log.info("Getting changed files...")

    files = []

    proc = subprocess.Popen(
        ['git', 'diff', '--cached', '--name-only'],
        stdout=subprocess.PIPE
    )
    output = proc.communicate()[0]

    if proc.returncode != 0:
        log.fatal("git diff failed: %d", proc.returncode)
        sys.exit(1)

    output = output.decode("utf-8")

    for line in output.split('\n'):
        if line == "":
            continue

        log.info("Found changed file: [%s]", line)
        files.append(line)

    return files

def reset_file(filePath):
    proc = subprocess.Popen(
        [
            'git',
            'reset',
            filePath
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )

    output = proc.communicate()[0]
    if proc.returncode != 0:
        log.error("Failed to reset file [%s]: %d", filePath, proc.returncode)
        print(output.decode("utf-8"))

def restore_file(filePath):
    proc = subprocess.Popen(
        [
            'git',
            'checkout',
            filePath
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )

    output = proc.communicate()[0]
    if proc.returncode != 0:
        log.error("Failed to restore file [%s]: %d", filePath, proc.returncode)
        print(output.decode("utf-8"))

def generate_single_header():
    log.info("Generating single header...")

    toolPath = os.path.join(
        rootPath,
        "scripts/generate_single_header/generate_single_header.py"
    )

    sourceFilePath = os.path.join(
        rootPath,
        "include/nbp.h"
    )

    destFilePath = os.path.join(
        rootPath,
        "single_header/nbp.h"
    )

    proc = subprocess.Popen(
        [
            'python3.6',
            toolPath,
            sourceFilePath,
            '-o',
            destFilePath,
            '-rl',
            '-rig',
            '-ric'
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )

    output = proc.communicate()[0]
    if proc.returncode != 0:
        log.error("Failed to generate single header: %d", proc.returncode)
        print()
        print(output.decode("utf-8"))

        restore_file(destFilePath)

        return False

    log.info("Single header generated successfully")

    return True

def add_single_header():
    proc = subprocess.Popen(
        ['git', 'add', 'single_header/nbp.h'],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )
    output = proc.communicate()[0]

    if proc.returncode != 0:
        log.error("Failed to add single header: %d", proc.returncode)
        print(output.decode("utf-8"))
        return False

    log.info("Single header has been added to commit")

    return True

def stash_unstaged_changes():
    proc = subprocess.Popen(
        ['git', 'stash', '--keep-index', '--include-untracked'],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )
    output = proc.communicate()[0]

    if proc.returncode != 0:
        log.error("git stash failed: %d", proc.returncode)
        print(output.decode("utf-8"))
        return False

    log.info("git stash succeeded")

    return True

def stash_pop():
    proc = subprocess.Popen(
        ['git', 'stash', 'pop'],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )
    output = proc.communicate()[0]

    if proc.returncode != 0:
        log.error("git stash pop failed: %d", proc.returncode)
        print(output.decode("utf-8"))
        return False

    log.info("git stash pop succeeded")

    return True

def check_coding_standard(files):
    params = [
        "python3.6",
        os.path.join(rootPath, "scripts/coding_standard_checks/run_checks.py"),
        "-ca"
    ]

    for f in files:
        params.append(f)

    message = ""
    for p in params:
        tmp = "{} {}".format(message, p)
        message = tmp

    log.info("Running: %s", message)

    proc = subprocess.Popen(
        params,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )
    output = proc.communicate()[0]

    if proc.returncode != 0:
        log.error("Checking coding standard failed: %d", proc.returncode)
        print()
        print(output.decode("utf-8"))
        return False

    log.info("Checking coding standard succeeded")

    return True

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

    generateSingleHeader = False

    files = get_changed_files()
    for filepath in files:
        if filepath.startswith("include/"):
            generateSingleHeader = True
            break

    if generateSingleHeader:
        if not stash_unstaged_changes():
            sys.exit(1)
        if not generate_single_header():
            stash_pop()
            sys.exit(1)
        if not add_single_header():
            stash_pop()
            sys.exit(1)
        if not stash_pop():
            sys.exit(1)

        if not "single_header/nbp.h" in files:
            files.append("single_header/nbp.h")

    if not check_coding_standard(files):
        if generateSingleHeader:
            filePath = os.path.join(rootPath, "single_header/nbp.h")
            reset_file(filePath)
            restore_file(filePath)
        sys.exit(1)

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

import argparse
import logging
import os
import sys

from colorlog import ColoredFormatter

sys.dont_write_bytecode = True

from check_commit_message import check_commit_message
from check_file_formatting import check_file_formatting
from check_file_rules import check_file_rules, init_globals
from check_naming import check_naming

scriptPath = os.path.dirname(os.path.realpath(__file__))
rootPath = os.path.abspath(os.path.join(scriptPath, '../../'))

excludedDirs = [ ".git", "bin", "coverage", "build/cmake_files", ".vscode" ]
excludedDirsAbsPath = []

stopOnError = False
success = True

totalNumberOfWarnings = 0

def check_file_formatting_for_directory(directory):
    formattingSuccess = True

    for current, subdirs, files in os.walk(directory):
        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if current.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        for f in files:
            filePath = os.path.join(current, f)
            if not check_file_formatting(log, filePath):
                formattingSuccess = False
                if stopOnError:
                    break

        if not formattingSuccess and stopOnError:
            break

    return formattingSuccess

def processing_check_file_formatting(files):
    formattingSuccess = True

    for file in files:
        if file == "<all>":
            if not check_file_formatting_for_directory(rootPath):
                formattingSuccess = False
                if stopOnError:
                    break
            continue

        filePath = file
        if not os.path.isabs(file):
            filePath = os.path.join(rootPath, file)

        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if filePath.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        if not check_file_formatting(log, filePath):
            formattingSuccess = False
            if stopOnError:
                break

    return formattingSuccess

def check_file_rules_for_directory(directory):
    status = True

    for current, subdirs, files in os.walk(directory):
        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if current.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        for f in files:
            filePath = os.path.join(current, f)
            if not check_file_rules(log, filePath):
                status = False
                if stopOnError:
                    break

        if not status and stopOnError:
            break

    return status

def processing_check_file_rules(files):
    status = True

    for file in files:
        if file == "<all>":
            if not check_file_rules_for_directory(rootPath):
                status = False
                if stopOnError:
                    break
            continue

        filePath = file
        if not os.path.isabs(file):
            filePath = os.path.join(rootPath, file)

        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if filePath.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        if not check_file_rules(log, filePath):
            status = False
            if stopOnError:
                break

    return status

def check_naming_for_directory(directory):
    global totalNumberOfWarnings
    status = True

    for current, subdirs, files in os.walk(directory):
        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if current.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        for f in files:
            filePath = os.path.join(current, f)

            st, n = check_naming(log, filePath)
            totalNumberOfWarnings += n

            if not st:
                status = False
                if stopOnError:
                    break

        if not status and stopOnError:
            break

    return status

def processing_check_naming(files):
    global totalNumberOfWarnings
    status = True

    for file in files:
        if file == "<all>":
            if not check_naming_for_directory(rootPath):
                status = False
                if stopOnError:
                    break
            continue

        filePath = file
        if not os.path.isabs(file):
            filePath = os.path.join(rootPath, file)

        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if filePath.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        st, n = check_naming(log, filePath)
        totalNumberOfWarnings += n

        if not st:
            status = False
            if stopOnError:
                break

    return status

def check_all_for_directory(directory):
    global totalNumberOfWarnings
    status = True

    for current, subdirs, files in os.walk(directory):
        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if current.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        for f in files:
            filePath = os.path.join(current, f)
            if not check_file_formatting(log, filePath):
                status = False
                if stopOnError:
                    break

            if not check_file_rules(log, filePath):
                status = False
                if stopOnError:
                    break

            st, n = check_naming(log, filePath)
            totalNumberOfWarnings += n

            if not st:
                status = False
                if stopOnError:
                    break

        if not status and stopOnError:
            break

    return status

def processing_check_all(files):
    global totalNumberOfWarnings
    status = True

    for file in files:
        if file == "<all>":
            if not check_file_formatting_for_directory(rootPath):
                status = False
                if stopOnError:
                    break
            if not check_file_rules_for_directory(rootPath):
                status = False
                if stopOnError:
                    break
            if not check_naming_for_directory(rootPath):
                status = False
                if stopOnError:
                    break
            continue

        filePath = file
        if not os.path.isabs(file):
            filePath = os.path.join(rootPath, file)

        isExcludedDir = False

        for d in excludedDirsAbsPath:
            if filePath.startswith(d):
                isExcludedDir = True
                break

        if isExcludedDir:
            continue

        if not check_file_formatting(log, filePath):
            status = False
            if stopOnError:
                break

        if not check_file_rules(log, filePath):
            status = False
            if stopOnError:
                break

        st, n = check_naming(log, filePath)
        totalNumberOfWarnings += n

        if not st:
            status = False
            if stopOnError:
                break

    return status

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description=r"Runs coding standard checks for nbp project."
    )

    parser.add_argument(
        '-v',
        '--verbose',
        help='verbose console output.',
        action='store_true'
    )

    parser.add_argument(
        '-soe',
        '--stop-on-error',
        help='if it is set then the script will stop if a check fails',
        action='store_true'
    )

    parser.add_argument(
        '-ccm',
        '--check-commit-message',
        help='if it is set then the script check if the commit message is\
            valid'
    )

    parser.add_argument(
        '-cff',
        '--check-file-formatting',
        help='if it is set then the script check if the file is formatted\
            correctly',
        nargs='+'
    )

    parser.add_argument(
        '-cfr',
        '--check-file-rules',
        help='if it is set then the script check if the file follow some rules',
        nargs='+'
    )

    parser.add_argument(
        '-cn',
        '--check-naming',
        help='if it is set then the script check C/C++ naming',
        nargs='+'
    )

    parser.add_argument(
        '-ca',
        '--check-all',
        help='Activate -cff -cfr and -cn',
        nargs='+'
    )

    args = parser.parse_args()

    #
    # initialize logger
    #

    logLevel = logging.ERROR
    if args.verbose:
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

    rootPath = os.path.join(rootPath, '')

    log.info("script path = %s", scriptPath)
    log.info("root   path = %s", rootPath)

    init_globals(rootPath)

    for d in excludedDirs:
        excludedDirsAbsPath.append(os.path.join(rootPath, d))

    if args.stop_on_error:
        stopOnError = True

    while True:
        if args.check_commit_message != None:
            if not check_commit_message(log, args.check_commit_message):
                success = False
                if stopOnError:
                    log.fatal("Exiting because stop on error is set")
                    break

        if args.check_file_formatting != None:
            if not processing_check_file_formatting(args.check_file_formatting):
                success = False
                if stopOnError:
                    log.fatal("Exiting because stop on error is set")
                    break

        if args.check_file_rules != None:
            if not processing_check_file_rules(args.check_file_rules):
                success = False
                if stopOnError:
                    log.fatal("Exiting because stop on error is set")
                    break

        if args.check_naming != None:
            if not processing_check_naming(args.check_naming):
                success = False
                if stopOnError:
                    log.fatal("Exiting because stop on error is set")
                    break

        if args.check_all != None:
            if not processing_check_all(args.check_all):
                success = False
                if stopOnError:
                    log.fatal("Exiting because stop on error is set 1")
                    break

        break

    log.info("Number of warnings = %d", totalNumberOfWarnings)

    if not success:
        sys.exit(1)

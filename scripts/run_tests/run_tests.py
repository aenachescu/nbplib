# https://github.com/aenachescu/nbp
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
import concurrent.futures
import logging
import multiprocessing
import os
import shutil
import subprocess
import sys
import time
from threading import Lock

import pexpect
from colorlog import ColoredFormatter

sys.dont_write_bytecode = True

from compilers_config import *
from tests_config import *

testsArray = []
requestedTests = []

scriptPath = os.path.dirname(os.path.realpath(__file__))
rootPath = os.path.abspath(os.path.join(scriptPath, '../../'))
buildPath = os.path.abspath(os.path.join(rootPath, 'build'))
cmakeFilesPath = os.path.abspath(os.path.join(rootPath, 'build/cmake_files'))
binPath = os.path.abspath(os.path.join(rootPath, 'bin'))
testPath = os.path.abspath(os.path.join(rootPath, 'test'))
numberOfCpus = multiprocessing.cpu_count()

printCmakeOutput    = False
printMakeOutput     = False
printTestOutput     = False
stopOnBuildError    = False
stopOnTestError     = False
stopOnTestCaseError = False
runTestsMt          = False

runTestsMtStop      = False
runTestsMtLogMutex  = Lock()

statistics = {
    "numberOfFailedBuilds" : 0,
    "numberOfPassedBuilds" : 0,
    "numberOfFailedTests"  : 0,
    "numberOfPassedTests"  : 0,
    "buildDuration"        : 0.0,
    "testsDuration"        : 0.0
}

COLOR_RED   = '\033[91m'
COLOR_GREEN = '\033[92m'
COLOR_RESET = '\033[0m'

def update_build_statistics(passed):
    if passed:
        statistics["numberOfPassedBuilds"] += 1
    else:
        statistics["numberOfFailedBuilds"] += 1

def update_test_statistics(passed):
    if passed:
        statistics["numberOfPassedTests"] += 1
    else:
        statistics["numberOfFailedTests"] += 1

def increment_build_time(duration):
    statistics["buildDuration"] += duration

def increment_tests_time(duration):
    statistics["testsDuration"] += duration

def print_statistics():
    log.info("General statistics:")

    log.info(
        "Passed builds: %s%d%s",
        COLOR_GREEN,
        statistics["numberOfPassedBuilds"],
        COLOR_RESET
    )

    color = COLOR_RED
    if statistics["numberOfFailedBuilds"] == 0:
        color = COLOR_GREEN

    log.info(
        "Failed builds: %s%d%s",
        color,
        statistics["numberOfFailedBuilds"],
        COLOR_RESET
    )

    log.info(
        "Passed tests: %s%d%s",
        COLOR_GREEN,
        statistics["numberOfPassedTests"],
        COLOR_RESET
    )

    color = COLOR_RED
    if statistics["numberOfFailedTests"] == 0:
        color = COLOR_GREEN

    log.info(
        "Failed tests: %s%d%s",
        color,
        statistics["numberOfFailedTests"],
        COLOR_RESET
    )

    log.info("Build duration: %6fs", statistics["buildDuration"])
    log.info("Tests duration: %6fs", statistics["testsDuration"])

def parse_tests_list(tests):
    global requestedTests

    if len(tests) == 0:
        return

    tmp = tests.split(';')

    for t in tmp:
        if not t in requestedTests:
            requestedTests.append(t)
        else:
            log.warning("Test %s is duplicated", t)

def print_process_output(output, error, source):
    if error:
        print(output)
        return

    if source == "cmake" and printCmakeOutput:
        print(output)
    elif source == "make" and printMakeOutput:
        print(output)
    elif source == "test" and printTestOutput:
        runTestsMtLogMutex.acquire()
        print(output)
        runTestsMtLogMutex.release()

def build_tests(compiler = "", standard = "", platform = ""):
    log.info(
        "Building tests: compiler = %s, standard = %s, platform = %s",
        compiler, standard, platform,
    )

    startTime = time.time()

    success = True

    while True:
        shutil.rmtree(binPath, ignore_errors=True)

        if os.path.exists(binPath):
            log.error("bin folder exists")
            success = False
            break

        shutil.rmtree(cmakeFilesPath, ignore_errors=True)

        if os.path.exists(cmakeFilesPath):
            log.error("cmake_files folder exists")
            success = False
            break

        os.mkdir(cmakeFilesPath)

        config = ""

        if len(compiler):
            config = "{} -DCOMPILER={}".format(config, compiler)
        if len(standard):
            config = "{} -DSTANDARD={}".format(config, standard)
        if len(platform):
            config = "{} -DPLATFORM={}".format(config, platform)

        # run cmake
        cmakeCmdline = "cmake -S {} -B {} {}".format(buildPath, cmakeFilesPath, config)
        output, rc = pexpect.runu(cmakeCmdline, withexitstatus=1, timeout=-1)

        if rc != 0:
            log.error("cmake failed: rc = %d, cmdline = %s", rc, cmakeCmdline)
            print_process_output(output, True, "cmake")
            success = False
            break

        print_process_output(output, False, "cmake")

        # run make
        makeCmdline = "make -C {} -j{}".format(cmakeFilesPath, numberOfCpus)
        output, rc = pexpect.runu(makeCmdline, withexitstatus=1, timeout=-1)

        if rc != 0:
            log.error("make failed: rc = %d, cmdline = %s", rc, makeCmdline)
            print_process_output(output, True, "make")
            success = False
            break

        print_process_output(output, False, "make")

        break

    endTime = time.time()
    duration = endTime - startTime

    update_build_statistics(success)
    increment_build_time(duration)

    if success:
        log.info(
            "%sBuild completed successfully%s (%.6fs)",
            COLOR_GREEN,
            COLOR_RESET,
            duration
        )
    else:
        log.error(
            "%sBuild tests failed%s (%.6fs)",
            COLOR_RED,
            COLOR_RESET,
            duration
        )

    return success

def get_test_config(testName):
    testConfig = {
        "returnCode": 0,
        "cmdline": "",
    }

    for test in testsConfig:
        if test["name"] != testName:
            continue

        if "returnCode" in test:
            testConfig["returnCode"] = test["returnCode"]
        if "cmdline" in test:
            testConfig["cmdline"] = test["cmdline"]

    return testConfig

def load_expected_printer_output(filePath):
    file = open(filePath, mode='r')
    output = file.read()
    file.close()

    return output

def run_test(testName):
    log.info("Running test %s...", testName)
    success = False

    startTime = time.time()

    while True:
        testConfig = get_test_config(testName)
        testFolder = os.path.join(testPath, testName)
        testBinFolder = os.path.join(binPath, testName)
        testExe = os.path.join(testBinFolder, testName)
        printerOutputPath = os.path.join(testFolder, "expected_linux_printer_output.txt")

        if not os.path.exists(testFolder):
            log.error("Test folder does not exists [%s]", testFolder)
            break

        if not os.path.exists(testBinFolder):
            log.error("Test bin folder does not exists [%s]", testBinFolder)
            break

        if not os.path.exists(testExe):
            log.error("Test exe does not exists [%s]", testExe)
            break

        if not os.path.exists(printerOutputPath):
            log.error("Expected printer output does not exists [%s]", printerOutputPath)
            break

        expectedOutput = load_expected_printer_output(printerOutputPath)

        testCmd = "{} {}".format(testExe, testConfig["cmdline"])
        testOutput, testRc = pexpect.runu(
            testCmd,
            withexitstatus=True,
            timeout=-1,
            cwd=testBinFolder
        )

        testOutput = testOutput.replace("\r\n", "\n")

        if testRc != testConfig["returnCode"]:
            log.error(
                "Unexpected return code. Test = %s, Expected = %d, Actual = %d",
                testName,
                testConfig["returnCode"],
                testRc
            )
            break

        if testOutput != expectedOutput:
            runTestsMtLogMutex.acquire()
            log.error("Unexpected output for test %s", testName)
            print("{}Expected printer output:{}".format(COLOR_GREEN, COLOR_RESET))
            print(expectedOutput)
            print("{}Actual printer output:{}".format(COLOR_RED, COLOR_RESET))
            print(testOutput)
            runTestsMtLogMutex.release()
            break
        else:
            print_process_output(testOutput, False, "test")

        success = True
        break

    endTime = time.time()
    duration = endTime - startTime

    if success:
        log.info(
            "Test %s%s%s passed (%.6fs)",
            COLOR_GREEN,
            testName,
            COLOR_RESET,
            duration
        )
    else:
        log.error(
            "Test %s%s%s failed (%.6fs)",
            COLOR_RED,
            testName,
            COLOR_RESET,
            duration
        )

    return success

def run_test_mt(testName):
    global runTestsMtStop
    global stopOnTestCaseError

    if runTestsMtStop:
        return 0

    testPassed = run_test(testName)

    update_test_statistics(testPassed)

    if testPassed:
        return 1

    if stopOnTestCaseError:
        runTestsMtStop = True

    return 2

def run_tests():
    log.info("Running tests...")

    startTime = time.time()

    numberOfPassedTests = 0
    numberOfFailedTests = 0
    success = True

    if runTestsMt:
        with concurrent.futures.ThreadPoolExecutor(max_workers=numberOfCpus) as executor:
            futureTests = {
                executor.submit(run_test_mt, testName ) : testName
                    for testName in testsArray
            }
            for future in concurrent.futures.as_completed(futureTests):
                status = future.result()
                if status == 1:
                    numberOfPassedTests += 1
                elif status == 2:
                    numberOfFailedTests += 1
                    success = False
                    if stopOnTestCaseError:
                        log.fatal("Exiting because stop on test case error is set")
                elif status == 0:
                    continue
                else:
                    log.error("Unknown status = %d", status)
    else:
        for testName in testsArray:
            testPassed = run_test(testName)

            update_test_statistics(testPassed)
            if testPassed:
                numberOfPassedTests += 1
            else:
                numberOfFailedTests += 1
                success = False
                if stopOnTestCaseError:
                    log.fatal("Exiting because stop on test case error is set")
                    break

    endTime = time.time()
    duration = endTime - startTime
    increment_tests_time(duration)

    color = COLOR_RED
    if numberOfFailedTests == 0:
        color = COLOR_GREEN

    if success:
        log.info("%sRun tests completed successfully%s", COLOR_GREEN, COLOR_RESET)
    else:
        log.error("%sRun tests failed%s", COLOR_RED, COLOR_RESET)

    log.info("Run tests statistics:")

    log.info(
        "Tests passed: %s%d%s/%d",
        COLOR_GREEN,
        numberOfPassedTests,
        COLOR_RESET,
        len(testsArray)
    )
    log.info(
        "Tests failed: %s%d%s/%d",
        color,
        numberOfFailedTests,
        COLOR_RESET,
        len(testsArray)
    )
    log.info("Tests duration: %6fs", duration)

    return success

def load_tests():
    log.info("Loading tests...")

    for filename in os.listdir(testPath):
        if os.path.isdir(os.path.join(testPath, filename)):
            log.info("Found test = %s", filename)
            testsArray.append(filename)

    log.info("Found %d tests", len(testsArray))

    return True

def is_supported_compiler(compiler):
    value = supportedCompilersDict.get(compiler)
    if value == None:
        return False

    return True

def is_supported_standard(compiler, standard):
    compDict = supportedCompilersDict.get(compiler)
    if compDict == None:
        return False

    standards = compDict.get("standards")
    if standards == None:
        return False

    if standard in standards:
        return True

    return False

def is_supported_platform(compiler, platform):
    compDict = supportedCompilersDict.get(compiler)
    if compDict == None:
        return False

    platforms = compDict.get("platforms")
    if platforms == None:
        return False

    if platform in platforms:
        return True

    return False

def is_list_of_compilers(compilers):
    if compilers.find(';') != -1:
        return True
    return False

def unwrap_value(value):
    tmp = value

    if tmp.startswith('<'):
        tmp = tmp[1:]

    if tmp.endswith('>'):
        tmp = tmp[:-1]

    return tmp

def build_and_run_tests_by_compiler(compiler, standard, platform,
    ignoreUnsupportedStandard = False, ignoreUnsupportedPlatform = False,
    runTests = True):
    standards = []
    platforms = []

    if len(standard) == 0:
        standards.append("")
    elif standard == "<all>":
        compDict = supportedCompilersDict.get(compiler)
        compStandards = compDict.get("standards")
        for std in compStandards:
            standards.append(std)
    else:
        std = unwrap_value(standard)
        if is_supported_standard(compiler, std):
            standards.append(std)
        elif not ignoreUnsupportedStandard:
            log.fatal("Unsupported standard %s for compiler %s", std, compiler)
            return True, False, False

    if len(platform) == 0:
        platforms.append("")
    elif platform == "<all>":
        compDict = supportedCompilersDict.get(compiler)
        compPlatforms = compDict.get("platforms")
        for p in compPlatforms:
            platforms.append(p)
    else:
        p = unwrap_value(platform)
        if is_supported_platform(compiler, p):
            platforms.append(p)
        elif not ignoreUnsupportedPlatform:
            log.fatal("Unsupported platform %s for compiler %s", p, compiler)
            return True, False, False

    buildError = False
    testError  = False

    for std in standards:
        for p in platforms:
            if not build_tests(compiler, std, p):
                buildError = True
                if stopOnBuildError:
                    log.fatal("Exiting because stop on build error is set")
                    return False, True, False
                else:
                    continue
            if runTests:
                if not run_tests():
                    testError = True
                    if stopOnTestCaseError:
                        return False, False, True
                    elif stopOnTestError:
                        log.fatal("Exiting because stop on test error is set")
                        return False, False, True
                    else:
                        continue

    return False, buildError, testError

def build_and_run_tests(compiler, standard, platform, runTests):
    if len(compiler) == 0:
        if not build_tests():
            return False

        if not run_tests():
            return False
    elif compiler == "<all>":
        fail = False
        for comp in supportedCompilersDict:
            error, buildError, testError = build_and_run_tests_by_compiler(
                comp,
                standard,
                platform,
                True,
                True,
                runTests
            )
            if error or buildError or testError:
                fail = True
            if stopOnBuildError and buildError:
                break
            if (stopOnTestError or stopOnTestCaseError) and testError:
                break
        if fail:
            return False
    elif is_list_of_compilers(compiler):
        compilers = compiler.split(';')
        for comp in compilers:
            if not is_supported_compiler(comp):
                log.fatal("Unsupported compiler = %s", comp)

        fail = False
        for comp in compilers:
            error, buildError, testError = build_and_run_tests_by_compiler(
                comp,
                standard,
                platform,
                True,
                True,
                runTests
            )
            if error or buildError or testError:
                fail = True
            if stopOnBuildError and buildError:
                break
            if (stopOnTestError or stopOnTestCaseError) and testError:
                break

        if fail:
            return False
    else:
        if is_supported_compiler(compiler):
            error, buildError, testError = build_and_run_tests_by_compiler(
                compiler,
                standard,
                platform,
                runTests=runTests
            )
            if error or buildError or testError:
                return False
        else:
            log.fatal("Unsupported compiler = %s", compiler)
            return False

    return True

def run_tests_mode():
    global testsArray

    log.info("Run tests mode")

    startTime = time.time()

    error = False

    while True:
        if not load_tests():
            log.fatal("Failed to load tests")
            error = True
            break

        if len(requestedTests) > 0:
            for t in requestedTests:
                if not t in testsArray:
                    log.critical("Unknown test [%s]", t)
                    error = True
                    break

            if error:
                break

            testsArray = requestedTests

        if not run_tests():
            error = True
            break

        break

    print_statistics()

    endTime = time.time()
    duration = endTime - startTime

    log.info("Total duration: %.6fs", duration)

    if error:
        log.error("%sScript failed%s", COLOR_RED, COLOR_RESET)
        sys.exit(1)

def build_tests_mode(compiler, standard, platform):
    log.info("Build tests mode")

    startTime = time.time()

    error = False

    while True:
        if not build_and_run_tests(compiler, standard, platform, False):
            error = True
            break

        break

    print_statistics()

    endTime = time.time()
    duration = endTime - startTime

    log.info("Total duration: %.6fs", duration)

    if error:
        log.error("%sScript failed%s", COLOR_RED, COLOR_RESET)
        sys.exit(1)

def build_and_run_tests_mode(compiler, standard, platform):
    global testsArray

    log.info("Build and run tests mode")

    startTime = time.time()

    error = False

    while True:
        if not load_tests():
            log.fatal("Failed to load tests")
            error = True
            break

        if len(requestedTests) > 0:
            for t in requestedTests:
                if not t in testsArray:
                    log.critical("Unknown test %s", t)
                    error = True
                    break

            if error:
                break

            testsArray = requestedTests

        if not build_and_run_tests(compiler, standard, platform, True):
            error = True
            break

        break

    print_statistics()

    endTime = time.time()
    duration = endTime - startTime

    log.info("Total duration: %.6fs", duration)

    if error:
        log.error("%sScript failed%s", COLOR_RED, COLOR_RESET)
        sys.exit(1)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description=r"Builds and runs the tests for nbp project."
    )

    parser.add_argument(
        '-v',
        '--verbose',
        help='verbose console output.',
        action='store_true'
    )

    parser.add_argument(
        '-rt',
        '--run-tests',
        help='if it is set then the tests will be run without build.',
        action='store_true'
    )

    parser.add_argument(
        '-bt',
        '--build-tests',
        help='if it is set then the tests will be built but not run.',
        action='store_true'
    )

    parser.add_argument(
        '-comp',
        '--compiler',
        help='set the compiler used for build. If value is <all> then the build\
        will run for all compilers. If it is not set then the default compiler\
        from cmake will be used.',
        default=''
    )

    parser.add_argument(
        '-std',
        '--standard',
        help='set the language standard used for build. If value is <all> then\
        the build will run for all standards. If it is not set then the default\
        standard from cmake will be used. This argument is ignored if the\
        default compiler is used. The value must be wrapped in <>.',
        default=''
    )

    parser.add_argument(
        '-p',
        '--platform',
        help='set the platform used for build. If value is <all> then the build\
        will run for all platforms. If it is not set then the default platform\
        will be used. This argument is ignored if the default compiler is used.\
        The value must be wrapped in <>.',
        default=''
    )

    parser.add_argument(
        '-t',
        '--tests',
        help='a list of tests that will be run. If this parameter is set then\
        only these tests will be run. The tests name should be separated by \';\'',
        default=''
    )

    parser.add_argument(
        '-pcmo',
        '--print-cmake-output',
        help='if it is set then the cmake output will be printed even if cmake\
        does not fail',
        action='store_true'
    )

    parser.add_argument(
        '-pmo',
        '--print-make-output',
        help='if it is set then the make output will be printed even if make\
        does not fail',
        action='store_true'
    )

    parser.add_argument(
        '-pto',
        '--print-test-output',
        help='if it is set then the test output will be printed even if test\
        does not fail',
        action='store_true'
    )

    parser.add_argument(
        '-sobe',
        '--stop-on-build-error',
        help='if it is set then the script will stop if build fails for a\
        configuration',
        action='store_true'
    )

    parser.add_argument(
        '-sote',
        '--stop-on-test-error',
        help='if it is set then the script will stop if a test fails but not\
        before all tests are run for the current build',
        action='store_true'
    )

    parser.add_argument(
        '-sotce',
        '--stop-on-test-case-error',
        help='if it is set then the script will stop immediately after a test\
        fails',
        action='store_true'
    )

    parser.add_argument(
        '-rtmt',
        '--run-tests-multithreading',
        help='if it is set then the tests will be run in parallel',
        action='store_true'
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

    compiler = args.compiler
    standard = args.standard
    platform = args.platform

    log.info("script      path = %s", scriptPath)
    log.info("root        path = %s", rootPath)
    log.info("build       path = %s", buildPath)
    log.info("cmake files path = %s", cmakeFilesPath)
    log.info("bin         path = %s", binPath)
    log.info("test        path = %s", testPath)
    log.info("number of cpus = %d", numberOfCpus)
    log.info("compiler = %s", compiler)
    log.info("standard = %s", standard)
    log.info("platform = %s", platform)

    if args.print_cmake_output:
        printCmakeOutput = True
    if args.print_make_output:
        printMakeOutput = True
    if args.print_test_output:
        printTestOutput = True
    if args.stop_on_build_error:
        stopOnBuildError = True
    if args.stop_on_test_error:
        stopOnTestError = True
    if args.stop_on_test_case_error:
        stopOnTestCaseError = True
    if args.run_tests_multithreading:
        runTestsMt = True

    parse_tests_list(args.tests)

    if args.run_tests:
        run_tests_mode()
    elif args.build_tests:
        build_tests_mode(compiler, standard, platform)
    else:
        build_and_run_tests_mode(compiler, standard, platform)

    log.info("%sEverything is ok%s", COLOR_GREEN, COLOR_RESET)

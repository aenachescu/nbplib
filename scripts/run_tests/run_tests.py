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
import concurrent.futures
import glob
import logging
import multiprocessing
import os
import shutil
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

sanitizers = []

coverageFileId = 0

scriptPath = os.path.dirname(os.path.realpath(__file__))
rootPath = os.path.abspath(os.path.join(scriptPath, '../../'))
buildPath = os.path.abspath(os.path.join(rootPath, 'build'))
cmakeFilesPath = os.path.abspath(os.path.join(rootPath, 'build/cmake_files'))
binPath = os.path.abspath(os.path.join(rootPath, 'bin'))
testPath = os.path.abspath(os.path.join(rootPath, 'test'))
coveragePath = os.path.abspath(os.path.join(rootPath, "coverage"))
numberOfCpus = multiprocessing.cpu_count()

printCmakeOutput        = False
printMakeOutput         = False
printTestOutput         = False
printLCovOutput         = False
printCoverallsOutput    = False
stopOnBuildError        = False
stopOnTestError         = False
stopOnTestCaseError     = False
runTestsMt              = False
enableCoverage          = False
reportCoverage          = False

runTestsMtStop          = False
runTestsMtLogMutex      = Lock()

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
    elif source == "lcov" and printLCovOutput:
        print(output)
    elif source == "coveralls" and printCoverallsOutput:
        print(output)

def build_tests(compiler = "", standard = "", platform = "", sanitizer=""):
    log.info(
        "Building tests: compiler = %s, standard = %s, platform = %s, "
        "sanitizer = %s",
        compiler, standard, platform, sanitizer
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

        if sanitizer == "address":
            config += " -DADDRESS_SANITIZER=ON"
        elif sanitizer == "thread":
            config += " -DTHREAD_SANITIZER=ON"
        elif sanitizer == "leak":
            config += " -DLEAK_SANITIZER=ON"
        elif sanitizer == "ub":
            config += " -DUNDEFINED_BEHAVIOR_SANITIZER=ON"
        elif sanitizer != "":
            log.error("Unknown sanitizer %s", sanitizer)
            success = False
            break

        if enableCoverage:
            config += " -DCODE_COVERAGE=ON"

        # run cmake
        cmakeCmdline = "cmake -S {} -B {} {}".format(
            buildPath, cmakeFilesPath, config
        )
        output, rc = pexpect.runu(cmakeCmdline, withexitstatus=1, timeout=-1)

        if rc != 0:
            log.error("cmake failed: rc = %d, cmdline = %s", rc, cmakeCmdline)
            print_process_output(output, True, "cmake")
            success = False
            break

        print_process_output(output, False, "cmake")

        # run make
        tests = ""
        for t in testsArray:
            tests += " " + t
        makeCmdline = "make -C {} -j{} {}".format(
            cmakeFilesPath,
            numberOfCpus,
            tests
        )
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

def remove_abs_path_from_coverage_report(coverageReportPath):
    f = open(coverageReportPath, mode='r')
    data = f.read()
    f.close()

    absPath = rootPath
    if not absPath.endswith("/"):
        absPath += "/"

    data = data.replace(absPath, "")

    f = open(coverageReportPath, mode='w')
    f.write(data)
    f.close()

    return True

def get_gcov_tool(compiler):
    gcovTool = ""
    if "gcov_tool" in supportedCompilersDict[compiler]:
        gcovTool = "--gcov-tool "
        if ("gcov_tool_absolute_path" in supportedCompilersDict[compiler] and
            supportedCompilersDict[compiler]["gcov_tool_absolute_path"]):
            gcovTool += os.path.join(
                rootPath,
                supportedCompilersDict[compiler]["gcov_tool"]
            )
        else:
            gcovTool += supportedCompilersDict[compiler]["gcov_tool"]

    return gcovTool

def generate_coverage_report(compiler):
    global coverageFileId

    log.info("Generating coverage report...")

    coverageFiles = ""
    success = True
    gcovTool = ""

    if compiler != "":
        if compiler in supportedCompilersDict:
            gcovTool = get_gcov_tool(compiler)
        else:
            log.error("Unknown compiler %s", compiler)
            return False

    for testName in testsArray:
        log.info("Generating coverage report for test %s", testName)

        testBinPath = os.path.join(binPath, testName)
        coverageFile = os.path.join(testBinPath, "coverage.info")

        coverageFiles += " -a " + coverageFile

        testCMakePath = os.path.join(
            cmakeFilesPath,
            "CMakeFiles",
            testName + ".dir"
        )
        testCMakePath += testPath
        testCMakePath = os.path.join(testCMakePath, testName)

        gcdaFiles = glob.iglob(os.path.join(testCMakePath, "*.gcda"))
        for f in gcdaFiles:
            if os.path.isfile(f):
                shutil.copy2(f, testBinPath)

        gcnoFiles = glob.iglob(os.path.join(testCMakePath, "*.gcno"))
        for f in gcnoFiles:
            if os.path.isfile(f):
                shutil.copy2(f, testBinPath)

        lcovCmd = "lcov --directory {} --capture --output-file {} {}".format(
            testBinPath,
            coverageFile,
            gcovTool
        )
        output, rc = pexpect.runu(lcovCmd, timeout=-1, withexitstatus=1)

        if rc != 0:
            log.error("lcov failed: rc = %d, cmdline = %s", rc, lcovCmd)
            print_process_output(output, True, "lcov")
            success = False
            break

        print_process_output(output, False, "lcov")

    if success:
        coverageFilename = "coverage_" + str(coverageFileId) + ".info"
        coverageFileId += 1

        coverageReportFile = os.path.join(coveragePath, coverageFilename)
        lcovCmd = "lcov {} -o {}".format(coverageFiles, coverageReportFile)

        output, rc = pexpect.runu(lcovCmd, timeout=-1, withexitstatus=1)
        if rc != 0:
            log.error("lcov failed: rc = %d, cmdline = %s", rc, lcovCmd)
            print_process_output(output, True, "lcov")
            success = False
        else:
            print_process_output(output, False, "lcov")

            if not remove_abs_path_from_coverage_report(coverageReportFile):
                success = False

    if success:
        log.info(
            "%sCoverage report generated successfully%s",
            COLOR_GREEN,
            COLOR_RESET
        )
    else:
        log.error(
            "%sGenerate coverage report failed%s",
            COLOR_RED,
            COLOR_RESET
        )

    return success

def send_coverage_report():
    if not enableCoverage:
        return True

    coverageFilesParam = ""
    coverageFiles = glob.iglob(os.path.join(coveragePath, "coverage_*.info"))

    for f in coverageFiles:
        coverageFilesParam += " -a " + f

    coverageReportFile = os.path.join(coveragePath, "coverage.info")
    lcovCmd = "lcov {} -o {}".format(coverageFilesParam, coverageReportFile)

    output, rc = pexpect.runu(lcovCmd, timeout=-1, withexitstatus=1)

    if rc != 0:
        log.error("lcov failed: rc = %d, cmdline = %s", rc, lcovCmd)
        print_process_output(output, True, "lcov")
        return False

    print_process_output(output, False, "lcov")

    if not reportCoverage:
        return True

    log.info("Reporting coverage to coveralls...")

    coverallsCmd = "coveralls-lcov {}".format(coverageReportFile)
    output, rc = pexpect.runu(coverallsCmd, timeout=-1, withexitstatus=1)

    if rc != 0:
        log.error("coveralls failed: rc = %d, cmdline = %s", rc, coverallsCmd)
        print_process_output(output, True, "coveralls")
        return False

    print_process_output(output, False, "coveralls")

    log.info("Coverage reported to coveralls successfully")

    return True

def parse_build_config_variables(data, buildConfig):
    tmp = data

    tmp = tmp.replace("${compiler}", buildConfig["compiler"])
    tmp = tmp.replace("${standard}", buildConfig["standard"])
    tmp = tmp.replace("${platform}", buildConfig["platform"])
    tmp = tmp.replace("${sanitizer}", buildConfig["sanitizer"])

    return tmp

def parse_test_config(testData, buildConfig):
    testConfig = {
        "returnCode": 0,
        "cmdline": ""
    }

    if "returnCode" in testData:
        testConfig["returnCode"] = testData["returnCode"]
    if "cmdline" in testData:
        testConfig["cmdline"] = testData["cmdline"]
    if "outputContains" in testData:
        testConfig["outputContains"] = parse_build_config_variables(
            testData["outputContains"],
            buildConfig
        )

    if not "buildConfig" in testData:
        return testConfig

    for testBuildConfig in testData["buildConfig"]:
        if not "config" in testBuildConfig:
            log.warning(
                "No config field for an object from buildConfig array from "
                "test %s",
                testData["name"]
            )
            continue

        configValues = testBuildConfig["config"].split(":")
        if len(configValues) != 4:
            log.warning(
                "Invalid config field from buildConfig array from test %s",
                testData["name"]
            )
            continue

        if (configValues[0] != "<any>" and
            unwrap_value(configValues[0]) != buildConfig["compiler"]):
            continue
        if (configValues[1] != "<any>" and
            unwrap_value(configValues[1]) != buildConfig["standard"]):
            continue
        if (configValues[2] != "<any>" and
            unwrap_value(configValues[2]) != buildConfig["platform"]):
            continue
        if (configValues[3] != "<any>" and
            unwrap_value(configValues[3]) != buildConfig["sanitizer"]):
            continue

        if "returnCode" in testBuildConfig:
            testConfig["returnCode"] = testBuildConfig["returnCode"]
        if "cmdline" in testBuildConfig:
            testConfig["cmdline"] = testBuildConfig["cmdline"]
        if "outputContains" in testBuildConfig:
            testConfig["outputContains"] = parse_build_config_variables(
                testBuildConfig["outputContains"],
                buildConfig
            )

        break

    return testConfig

def get_test_config(testName, buildConfig):
    testConfig = {
        "returnCode": 0,
        "cmdline": "",
    }

    for test in testsConfig:
        if test["name"] != testName:
            continue

        testConfig = parse_test_config(test, buildConfig)

        break

    return testConfig

def load_expected_reporter_output(filePath):
    file = open(filePath, mode='r')
    output = file.read()
    file.close()

    return output

def check_test_output(testName, testOutput, testConfig):
    if "outputContains" in testConfig:
        if testOutput.find(testConfig["outputContains"]) == -1:
            runTestsMtLogMutex.acquire()
            log.error("Unexpected output for test %s", testName)
            print(
                "{}Output should contains:{}".format(COLOR_GREEN, COLOR_RESET)
            )
            print(testConfig["outputContains"])
            print("{}Actual reporter output:{}".format(COLOR_RED, COLOR_RESET))
            print(testOutput)
            runTestsMtLogMutex.release()
            return False
        else:
            print_process_output(testOutput, False, "test")
    else:
        testFolder = os.path.join(testPath, testName)
        reporterOutputPath = os.path.join(
            testFolder,
            "expected_linux_reporter_output.txt"
        )

        if not os.path.exists(reporterOutputPath):
            log.error(
                "Expected reporter output does not exists [%s]",
                reporterOutputPath
            )
            return False

        expectedOutput = load_expected_reporter_output(reporterOutputPath)

        if testOutput != expectedOutput:
            runTestsMtLogMutex.acquire()
            log.error("Unexpected output for test %s", testName)
            print(
                "{}Expected reporter output:{}".format(COLOR_GREEN, COLOR_RESET)
            )
            print(expectedOutput)
            print("{}Actual reporter output:{}".format(COLOR_RED, COLOR_RESET))
            print(testOutput)
            runTestsMtLogMutex.release()
            return False
        else:
            print_process_output(testOutput, False, "test")

    return True

def run_test(testName, buildConfig):
    log.info("Running test %s...", testName)
    success = False
    unexpectedRc = False

    startTime = time.time()

    while True:
        testConfig = get_test_config(testName, buildConfig)
        testFolder = os.path.join(testPath, testName)
        testBinFolder = os.path.join(binPath, testName)
        testExe = os.path.join(testBinFolder, testName)

        if not os.path.exists(testFolder):
            log.error("Test folder does not exists [%s]", testFolder)
            break

        if not os.path.exists(testBinFolder):
            log.error("Test bin folder does not exists [%s]", testBinFolder)
            break

        if not os.path.exists(testExe):
            log.error("Test exe does not exists [%s]", testExe)
            break

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
            unexpectedRc = True

        if not check_test_output(testName, testOutput, testConfig):
            break

        if unexpectedRc:
            break

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

def run_test_mt(testName, buildConfig):
    global runTestsMtStop
    global stopOnTestCaseError

    if runTestsMtStop:
        return 0

    testPassed = run_test(testName, buildConfig)

    update_test_statistics(testPassed)

    if testPassed:
        return 1

    if stopOnTestCaseError:
        runTestsMtStop = True

    return 2

def run_tests(buildConfig):
    log.info("Running tests...")

    startTime = time.time()

    numberOfPassedTests = 0
    numberOfFailedTests = 0
    success = True

    if runTestsMt:
        with concurrent.futures.ThreadPoolExecutor(max_workers=numberOfCpus) \
            as executor:
            futureTests = {
                executor.submit(run_test_mt, testName, buildConfig ) : testName
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
                        log.fatal(
                            "Exiting because stop on test case error is set"
                        )
                elif status == 0:
                    continue
                else:
                    log.error("Unknown status = %d", status)
    else:
        for testName in testsArray:
            testPassed = run_test(testName, buildConfig)

            update_test_statistics(testPassed)
            if testPassed:
                numberOfPassedTests += 1
            else:
                numberOfFailedTests += 1
                success = False
                if stopOnTestCaseError:
                    log.fatal("Exiting because stop on test case error is set")
                    break

    if enableCoverage:
        if not generate_coverage_report(buildConfig["compiler"]):
            success = False

    endTime = time.time()
    duration = endTime - startTime
    increment_tests_time(duration)

    color = COLOR_RED
    if numberOfFailedTests == 0:
        color = COLOR_GREEN

    if success:
        log.info(
            "%sRun tests completed successfully%s",
            COLOR_GREEN,
            COLOR_RESET
        )
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

    buildConfig = {
        "compiler":  compiler,
        "standard":  "",
        "platform":  "",
        "sanitizer": ""
    }

    for std in standards:
        buildConfig["standard"] = std
        for p in platforms:
            buildConfig["platform"] = p
            for san in sanitizers:
                buildConfig["sanitizer"] = san
                if not build_tests(compiler, std, p, san):
                    buildError = True
                    if stopOnBuildError:
                        log.fatal("Exiting because stop on build error is set")
                        return False, True, False
                    else:
                        continue
                if runTests:
                    if not run_tests(buildConfig):
                        testError = True
                        if stopOnTestCaseError:
                            return False, False, True
                        elif stopOnTestError:
                            log.fatal(
                                "Exiting because stop on test error is set"
                            )
                            return False, False, True
                        else:
                            continue

    return False, buildError, testError

def build_and_run_tests(compiler, standard, platform, runTests):
    if len(compiler) == 0:
        buildConfig = {
            "compiler":  "",
            "standard":  "",
            "platform":  "",
            "sanitizer": ""
        }
        for san in sanitizers:
            buildConfig["sanitizer"] = san
            if not build_tests(sanitizer=san):
                return False

            if runTests:
                if not run_tests(buildConfig):
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
    buildConfig = {
        "compiler":  "",
        "standard":  "",
        "platform":  "",
        "sanitizer": ""
    }

    while True:
        if not run_tests(buildConfig):
            error = True
            break

        if not send_coverage_report():
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
        if not build_and_run_tests(compiler, standard, platform, True):
            error = True
            break

        if not send_coverage_report():
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
        only these tests will be run. The tests name should be separated\
        by \';\'',
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

    parser.add_argument(
        '-san',
        '--sanitizer',
        help='if it is set then the sanitizers will be enabled. Possible\
        values: <all>, address, thread, leak, ub',
        default=''
    )

    parser.add_argument(
        '-cov',
        '--coverage',
        help='if it is set then the tests will be built with the coverage\
        support but the coverage won\'t be reported.',
        action='store_true'
    )

    parser.add_argument(
        '-rcov',
        '--report-coverage',
        help='if it is set then the tests will be built with the coverage\
        support and the coverage statistics will be reported to coveralls.',
        action='store_true'
    )

    parser.add_argument(
        '-plco',
        '--print-lcov-output',
        help='if it is set then lcov output will be printed even if lcov does\
        not fail',
        action='store_true'
    )

    parser.add_argument(
        '-pco',
        '--print-coveralls-output',
        help='if it is set then coveralls output will be printed even if\
        coveralls does not fail',
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

    compiler  = args.compiler
    standard  = args.standard
    platform  = args.platform
    sanitizer = args.sanitizer

    log.info("script      path = %s", scriptPath)
    log.info("root        path = %s", rootPath)
    log.info("build       path = %s", buildPath)
    log.info("cmake files path = %s", cmakeFilesPath)
    log.info("bin         path = %s", binPath)
    log.info("test        path = %s", testPath)
    log.info("number of cpus = %d", numberOfCpus)
    log.info("compiler  = %s", compiler)
    log.info("standard  = %s", standard)
    log.info("platform  = %s", platform)
    log.info("sanitizer = %s", sanitizer)

    if args.print_cmake_output:
        printCmakeOutput = True
    if args.print_make_output:
        printMakeOutput = True
    if args.print_test_output:
        printTestOutput = True
    if args.print_lcov_output:
        printLCovOutput = True
    if args.print_coveralls_output:
        printCoverallsOutput = True
    if args.stop_on_build_error:
        stopOnBuildError = True
    if args.stop_on_test_error:
        stopOnTestError = True
    if args.stop_on_test_case_error:
        stopOnTestCaseError = True
    if args.run_tests_multithreading:
        runTestsMt = True
    if args.coverage:
        enableCoverage = True
    if args.report_coverage:
        enableCoverage = True
        reportCoverage = True

    parse_tests_list(args.tests)

    if sanitizer == "address":
        sanitizers.append("address")
    elif sanitizer == "thread":
        sanitizers.append("thread")
    elif sanitizer == "leak":
        sanitizers.append("leak")
    elif sanitizer == "ub":
        sanitizers.append("ub")
    elif sanitizer == "<all>":
        sanitizers.append("address")
        sanitizers.append("thread")
        sanitizers.append("leak")
        sanitizers.append("ub")
    elif sanitizer == "":
        sanitizers.append("")
    else:
        log.error("Unsupported sanitizer %s", sanitizer)
        sys.exit(1)

    if enableCoverage:
        shutil.rmtree(coveragePath, ignore_errors=True)
        if os.path.exists(coveragePath):
            log.critical("coverage folder exists")
            sys.exit(1)
        else:
            os.mkdir(coveragePath)

    if not load_tests():
        log.fatal("Failed to load tests")
        sys.exit(1)

    if len(requestedTests) > 0:
        for t in requestedTests:
            if not t in testsArray:
                log.fatal("Unknown test %s", t)
                sys.exit(1)

        testsArray = requestedTests

    if args.run_tests:
        run_tests_mode()
    elif args.build_tests:
        build_tests_mode(compiler, standard, platform)
    else:
        build_and_run_tests_mode(compiler, standard, platform)

    log.info("%sEverything is ok%s", COLOR_GREEN, COLOR_RESET)

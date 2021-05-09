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
from queue import LifoQueue

from inflection import *

filenameExceptions = [
    "CODE_OF_CONDUCT.md",
    "LICENSE",
    "README.md",
    "build/CMakeLists.txt",
    ".clang-format"
]

fileLengthExceptions = [
    "README.md",
    ".travis.yml",
    "CODE_OF_CONDUCT.md"
]

fileIndentingExceptions = [
    "CODE_OF_CONDUCT.md",
    ".travis.yml"
]

fileLicenseExceptions = [
    ".clang-format",
    "README.md",
    "LICENSE",
    ".gitignore",
    "CODE_OF_CONDUCT.md",
    "docs/coding_standard.md",
    "build/CMakeLists.txt",
    "build/test_config.cmake",
    ".vscode/settings.json",
    ".vscode/c_cpp_properties.json"
]

sharpLicense = [
    "# No Bugs in Production (NBP) Library",
    "# https://github.com/aenachescu/nbplib",
    "#",
    "# Licensed under the MIT License <http://opensource.org/licenses/MIT>.",
    "# SPDX-License-Identifier: MIT",
    "# Copyright (c) 2019-2020 Alin Enachescu <https://github.com/aenachescu>",
    "#",
    "# Permission is hereby granted, free of charge, to any person obtaining "
        "a copy",
    "# of this software and associated documentation files (the \"Software\"), "
        "to deal",
    "# in the Software without restriction, including without limitation the "
        "rights",
    "# to use, copy, modify, merge, publish, distribute, sublicense, and/or "
        "sell",
    "# copies of the Software, and to permit persons to whom the Software is",
    "# furnished to do so, subject to the following conditions:",
    "#",
    "# The above copyright notice and this permission notice shall be included "
        "in all",
    "# copies or substantial portions of the Software.",
    "#",
    "# THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, "
        "EXPRESS OR",
    "# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF "
        "MERCHANTABILITY,",
    "# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL "
        "THE",
    "# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER",
    "# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING "
        "FROM,",
    "# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS "
        "IN THE",
    "# SOFTWARE.",
    ""
]

blockLicense = [
    "/*",
    "No Bugs in Production (NBP) Library",
    "https://github.com/aenachescu/nbplib",
    "",
    "Licensed under the MIT License <http://opensource.org/licenses/MIT>.",
    "SPDX-License-Identifier: MIT",
    "Copyright (c) 2019-2020 Alin Enachescu <https://github.com/aenachescu>",
    "",
    "Permission is hereby granted, free of charge, to any person obtaining a "
        "copy",
    "of this software and associated documentation files (the \"Software\"), "
        "to deal",
    "in the Software without restriction, including without limitation the "
        "rights",
    "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell",
    "copies of the Software, and to permit persons to whom the Software is",
    "furnished to do so, subject to the following conditions:",
    "",
    "The above copyright notice and this permission notice shall be included "
        "in all",
    "copies or substantial portions of the Software.",
    "",
    "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, "
        "EXPRESS OR",
    "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,",
    "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL "
        "THE",
    "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER",
    "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING "
        "FROM,",
    "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS "
        "IN THE",
    "SOFTWARE.",
    "*/",
    ""
]

projectPath = ""

def init_globals(projPath):
    global projectPath

    projectPath = projPath

def check_filename(log, filePath):
    log.info("Checking file path... [%s]", filePath)

    if not filePath.startswith(projectPath):
        log.error(
            "File is not in project path. File = [%s]. Project path = [%s]",
            filePath,
            projectPath
        )
        return False

    filePathRelative = filePath[len(projectPath):]

    expectedPath = underscore(filePathRelative)

    if expectedPath != filePathRelative:
        if filePathRelative in filenameExceptions:
            log.info(
                "Invalid filename, but it is in exception list."
                " Expected = [%s]. Actual = [%s]",
                expectedPath,
                filePathRelative
            )
            return True

        log.error(
            "Invalid filename. Expected = [%s]. Actual = [%s]",
            expectedPath,
            filePathRelative
        )
        return False

    log.info("File has valid name: [%s]", filePath)

    return True

def check_eol_sequence(log, filePath, fileContent):
    log.info("Checking EOL sequence... [%s]", filePath)

    if fileContent.find(b'\r\n') != -1:
        log.error("File has CRLF sequence: [%s]", filePath)
        return False

    log.info("File has the right EOL sequence: [%s]", filePath)

    return True

def check_tabs(log, filePath, fileLines):
    log.info("Checking if file has tabs... [%s]", filePath)

    status = True
    lineId = 0

    for l in fileLines:
        lineId += 1
        pos = l.find('\t')
        if pos != -1:
            log.error(
                "Found tab. File = [%s]. Line = %d. Column = %d",
                filePath,
                lineId,
                pos + 1
            )
            status = False

    if status:
        log.info("File has no tabs: [%s]", filePath)

    return status

    return True

def check_space_before_eol(log, filePath, fileLines):
    log.info(
        "Checking if file has space characters before eol... [%s]",
        filePath
    )

    status = True
    lineId = 0

    for l in fileLines:
        lineId += 1
        if l.endswith(" "):
            log.error(
                "Found space before eol. File = [%s]. Line = %d",
                filePath,
                lineId
            )
            status = False

    if status:
        log.info("File has no space before eol: [%s]", filePath)

    return status

def check_line_length(log, filePath, fileLines):
    log.info("Checking line length... [%s]", filePath)

    status = True
    lineId = 0

    filePathRelative = filePath[len(projectPath):]

    for l in fileLines:
        lineId += 1

        if len(l) > 80:
            if filePathRelative in fileLengthExceptions:
                log.info(
                    "Found line longer than 80 character but file is in "
                    "exception list. File = [%s]. Line = %d",
                    filePath,
                    lineId
                )
                continue

            log.error(
                "Found line longer than 80 characters. File = [%s]. Line = %d",
                filePath,
                lineId
            )
            status = False

    if status:
        log.info("File has no line longer than 80 characters: [%s]", filePath)

    return status

def check_new_line_before_eof(log, filePath, fileContent):
    log.info("Checking if there is new line before eof... [%s]", filePath)

    if not fileContent.endswith(b'\n'):
        log.error("File has not new line before eof: [%s]", filePath)
        return False

    log.info("File has new line before eof: [%s]", filePath)

    return True

def check_indenting(log, filePath, fileLines):
    log.info("Checking file indenting... [%s]", filePath)

    filePathRelative = filePath[len(projectPath):]
    if filePathRelative in fileIndentingExceptions:
        log.info("File is in exception list: [%s]", filePath)
        return True

    fileExt = os.path.splitext(filePath)[1]
    specialExt = [ '.h', '.c', '.cpp' ]

    specialFile = False
    if fileExt in specialExt:
        specialFile = True

    status = True
    lineId = 0

    for l in fileLines:
        lineId += 1

        if specialFile:
            if l.startswith(" *"):
                continue
            if l.startswith(" */"):
                continue

        pos = 0
        while pos < len(l) and l[pos] == ' ':
            pos += 1

        if pos % 4 != 0:
            log.error(
                "File is not indented correctly. File = [%s]. Line = %d",
                filePath,
                lineId
            )
            status = False

    log.info("File is indented correctly: [%s]", filePath)

    return status

def check_file_license(log, filePath, fileLines):
    log.info("Checking file license... [%s]", filePath)

    filePathRelative = filePath[len(projectPath):]
    startPos = 0
    hashBang = "#!/bin/sh"

    if os.path.splitext(filePath)[1] == ".sh":
        if len(fileLines) >= 2:
            if fileLines[0] == hashBang and fileLines[1] == "":
                startPos = 2

    if len(fileLines) >= len(sharpLicense):
        pos = startPos
        matched = True
        for line in sharpLicense:
            if line != fileLines[pos]:
                matched = False
                break
            pos += 1

        if matched:
            log.info("File has license: [%s]", filePath)
            return True

    if len(fileLines) >= len(blockLicense):
        pos = startPos
        matched = True
        for line in blockLicense:
            if line != fileLines[pos]:
                matched = False
                break
            pos += 1

        if matched:
            log.info("File has license: [%s]", filePath)
            return True

    if filePathRelative in fileLicenseExceptions:
        log.info(
            "File has no license but it is in exception list: [%s]",
            filePath
        )
        return True

    log.error("File has no license: [%s]", filePath)

    return False

def check_header_guard(log, filePath, fileLines):
    log.info("Checking header guard... [%s]", filePath)

    if os.path.splitext(filePath)[1] != ".h":
        log.info("File is not c/c++ header file [%s]", filePath)
        return True

    if len(fileLines) < len(blockLicense) + 3:
        log.error("Invalid number of lines: [%s]", filePath)
        return False

    filePathRelative = filePath[len(projectPath):]
    filePathComponents = filePathRelative.split(os.path.sep)
    headerGuard = ""

    if len(filePathComponents) == 0:
        log.error("Invalid relative path: [%s]", filePathRelative)
        return False

    if filePathComponents[0] == "single_header":
        headerGuard = "_H_NBP_NBP"
    elif filePathComponents[0] == "include":
        headerGuard = "_H_NBP_"
        for i in range(1, len(filePathComponents) - 1):
            headerGuard += filePathComponents[i].upper() + "_"
        headerGuard += os.path.splitext(filePathComponents[-1])[0].upper()
    elif filePathComponents[0] == "test":
        headerGuard = "_H_NBP_TEST_"
        for i in range(1, len(filePathComponents) - 1):
            headerGuard += filePathComponents[i].upper() + "_"
        headerGuard += os.path.splitext(filePathComponents[-1])[0].upper()
    else:
        log.error("Unsupported path: [%s]", filePathRelative)
        return False

    expectedIfdef  = "#ifndef " + headerGuard
    expectedDefine = "#define " + headerGuard
    expectedEndif  = "#endif // end if " + headerGuard

    status = True

    if fileLines[len(blockLicense)] != expectedIfdef:
        log.error(
            "Not found header guard if block. Expected = [%s]. Actual = [%s]",
            expectedIfdef,
            fileLines[len(blockLicense)]
        )
        status = False

    if fileLines[len(blockLicense) + 1] != expectedDefine:
        log.error(
            "Not found header guard definition. Expected = [%s]. Actual = [%s]",
            expectedDefine,
            fileLines[len(blockLicense) + 1]
        )
        status = False

    if fileLines[-2] != expectedEndif:
        log.error(
            "Not found header guard end. Expected = [%s]. Actual = [%s]",
            expectedEndif,
            fileLines[-2]
        )
        status = False

    if status:
        log.info("File has header guard: [%s]", filePath)

    return status

def check_endif_comment(log, filePath, fileLines):
    log.info("Checking 'endif' directive comments... [%s]", filePath)

    ifDirectivesStack = LifoQueue()
    status = True
    lineId = 0

    for line in fileLines:
        lineId += 1

        if line.startswith("#endif"):
            if ifDirectivesStack.qsize() == 0:
                log.error(
                    "Found 'endif' directive but no 'if' directive in stack. "
                    "File = [%s]. Line = %d",
                    filePath,
                    lineId
                )
                status = False
                break

            lineNum, cond, ifDirective = ifDirectivesStack.get()
            expectedEndif = "#endif // end if " + cond

            if line != expectedEndif:
                log.error(
                    "Unexpected 'endif' directive comment. Expected = [%s]. "
                    "Actual = [%s]. File = [%s]. Line = %d. "
                    "'if' directive line = %d",
                    expectedEndif,
                    line,
                    filePath,
                    lineId,
                    lineNum
                )
                status = False

            continue

        if not line.startswith("#if"):
            continue

        if line.startswith("#ifndef "):
            cond = line[len("#ifndef "):]
            ifDirectivesStack.put(tuple((lineId, cond, "#ifndef ")))
            continue

        if line.startswith("#ifdef "):
            cond = line[len("#ifdef "):]
            ifDirectivesStack.put(tuple((lineId, cond, "#ifdef ")))
            continue

        if line.startswith("#if "):
            cond = line[len("#if "):]
            ifDirectivesStack.put(tuple((lineId, cond, "#if ")))
            continue

        log.error(
            "Unsupported if directive [%s]. File = [%s]. Line = %d",
            line,
            filePath,
            lineId
        )

    while ifDirectivesStack.qsize() > 0:
        lineNum, cond, ifDirective = ifDirectivesStack.get()
        log.error(
            "Not found 'endif' directive for 'if' directive [%s]. "
            "File = %s. Line = %d",
            ifDirective + cond,
            filePath,
            lineNum
        )
        status = False

    if status:
        log.info("All 'endif' directives have comments: [%s]", filePath)

    return status

def check_file_rules(log, filePath):
    if not check_filename(log, filePath):
        return False

    file = open(filePath, mode='rb')
    fileContent = file.read()
    file.close()

    fileLines = fileContent.decode('utf-8').split("\n")

    if not check_eol_sequence(log, filePath, fileContent):
        return False

    if not check_tabs(log, filePath, fileLines):
        return False

    if not check_space_before_eol(log, filePath, fileLines):
        return False

    if not check_line_length(log, filePath, fileLines):
        return False

    if not check_new_line_before_eof(log, filePath, fileContent):
        return False

    if not check_indenting(log, filePath, fileLines):
        return False

    if not check_file_license(log, filePath, fileLines):
        return False

    if not check_header_guard(log, filePath, fileLines):
        return False

    if not check_endif_comment(log, filePath, fileLines):
        return False

    return True

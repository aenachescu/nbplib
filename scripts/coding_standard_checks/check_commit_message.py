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

acceptedEmojis = [
    ":memo:",
    ":recycle:",
    ":bookmark:",
    ":rocket:",
    ":bug:",
    ":construction:",
    ":pushpin:",
    ":hammer:",
    ":warning:",
    ":heavy_check_mark:",
    ":wrench:"
]

minimumNumberOfWords = 3

def check_commit_message(log, commitMsg):
    log.info("Checking commit... [%s]", commitMsg)

    hasEmoji = False
    commitMsgWithoutEmoji = ""

    for emoji in acceptedEmojis:
        if commitMsg.startswith(emoji):
            hasEmoji = True
            commitMsgWithoutEmoji = commitMsg[len(emoji):]
            break

    if not hasEmoji:
        log.error("Commit message has no emoji: [%s]", commitMsg)
        return False

    if not commitMsgWithoutEmoji.startswith(" "):
        log.error(
            "There is no space between emoji and message [%s]",
            commitMsgWithoutEmoji
        )
        return False

    if commitMsgWithoutEmoji.endswith(" "):
        log.error(
            "There is at least one space character at the end of message [%s]",
            commitMsgWithoutEmoji
        )
        return False

    if commitMsgWithoutEmoji.find("  ") != -1:
        log.error(
            "There are more consecutive space characters [%s]",
            commitMsgWithoutEmoji
        )
        return False

    commitMsgWords = list(filter(None, commitMsgWithoutEmoji.split(" ")))

    if len(commitMsgWords) < minimumNumberOfWords:
        log.error(
            "The commit message must have at least %d words: [%s]",
            minimumNumberOfWords,
            commitMsgWithoutEmoji
        )
        return False

    log.info("Valid commit message: [%s]", commitMsg)

    return True

cmake_minimum_required (VERSION 3.17)
project(NBP)

include("${CMAKE_SOURCE_DIR}/test_config.cmake")

option(CODE_COVERAGE "enable code coverage" OFF)
option(TEST_SLEEP "enable sleep in every test" OFF)
option(ADDRESS_SANITIZER "enable address sanitizer" OFF)
option(THREAD_SANITIZER "enable thread sanitizer" OFF)
option(LEAK_SANITIZER "enable leak sanitizer" OFF)
option(UNDEFINED_BEHAVIOR_SANITIZER "enable UB sanitizer" OFF)

set(CMAKE_VERBOSE_MAKEFILE on)

# Default compiler and linker flags
set(DEFAULT_CFLAGS "-Wall -Wextra -Werror -Wconversion")
set(DEBUG_CFLAGS "")
set(OPTIMIZATION_CFLAGS "-O2")
set(SANITIZERS_CFLAGS "")
set(TEST_GLOBAL_CFLAGS "")
set(GCOV_CFLAGS "")
set(GCOV_LFLAGS "")
set(PLATFORM_CFLAGS "")
set(STANDARD_CFLAGS "")

if(NOT DEFINED COMPILER)
set(CMAKE_C_COMPILER "gcc")
else()
set(CMAKE_C_COMPILER "${COMPILER}")
endif()
unset(COMPILER CACHE)

if(DEFINED PLATFORM)
set(PLATFORM_CFLAGS "${PLATFORM}")
endif()
unset(PLATFORM CACHE)

if(DEFINED STANDARD)
set(STANDARD_CFLAGS "${STANDARD}")
endif()
unset(STANDARD CACHE)

if(CODE_COVERAGE MATCHES ON)
set(GCOV_CFLAGS "-fprofile-arcs -ftest-coverage")
set(DEBUG_CFLAGS "-g")
set(OPTIMIZATION_CFLAGS "")
set(GCOV_LFLAGS "-lgcov --coverage")
endif()
unset(CODE_COVERAGE CACHE)

if(TEST_SLEEP MATCHES OFF)
set(TEST_GLOBAL_CFLAGS "-DTEST_DISABLE_SLEEP")
endif()
unset(TEST_SLEEP CACHE)

if(ADDRESS_SANITIZER MATCHES ON)
set(SANITIZERS_CFLAGS "-fsanitize=address,pointer-compare,pointer-subtract")
set(DEBUG_CFLAGS "-g")
set(OPTIMIZATION_CFLAGS "")
endif()
unset(ADDRESS_SANITIZER CACHE)

if(THREAD_SANITIZER MATCHES ON)
set(SANITIZERS_CFLAGS "-fsanitize=thread")
set(DEBUG_CFLAGS "-g")
set(OPTIMIZATION_CFLAGS "")
endif()
unset(THREAD_SANITIZER CACHE)

if(LEAK_SANITIZER MATCHES ON)
set(SANITIZERS_CFLAGS "-fsanitize=leak")
set(DEBUG_CFLAGS "-g")
set(OPTIMIZATION_CFLAGS "")
endif()
unset(LEAK_SANITIZER CACHE)

if(UNDEFINED_BEHAVIOR_SANITIZER MATCHES ON)
set(SANITIZERS_CFLAGS "-fsanitize=undefined,shift,integer-divide-by-zero,\
unreachable,vla-bound,null,return,signed-integer-overflow,bounds,\
bounds-strict,alignment,object-size,float-divide-by-zero,\
float-cast-overflow,nonnull-attribute,returns-nonnull-attribute,bool,enum,\
vptr,pointer-overflow,builtin -fuse-ld=gold")
set(DEBUG_CFLAGS "-g")
set(OPTIMIZATION_CFLAGS "")
endif()
unset(UNDEFINED_BEHAVIOR_SANITIZER CACHE)

set(CFLAGS "${DEFAULT_CFLAGS} ${DEBUG_CFLAGS} ${OPTIMIZATION_CFLAGS}\
    ${GCOV_CFLAGS} ${SANITIZERS_CFLAGS} ${TEST_GLOBAL_CFLAGS}\
    ${PLATFORM_CFLAGS} ${STANDARD_CFLAGS}")
set(LFLAGS "${GCOV_LFLAGS} ${SANITIZERS_CFLAGS} ${PLATFORM_CFLAGS}")

message(STATUS "Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CFLAGS: ${CFLAGS}")
message(STATUS "LFLAGS: ${LFLAGS}")

# Creating targets
set(TESTS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/../test")
set(TESTS_BIN_DIR "${CMAKE_SOURCE_DIR}/../bin")
set(NBP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../include")

list(LENGTH TESTS testsLength)

math(EXPR validTestsLength "${testsLength} % 3")

if(${validTestsLength} GREATER 0)
    message(FATAL_ERROR "TESTS list is not valid. Length = ${testsLength}")
endif()

math(EXPR numberOfIterations "${testsLength} / 3 - 1")

foreach(index RANGE ${numberOfIterations})
    math(EXPR listIndex "${index} * 3")
    list(GET TESTS ${listIndex} TEST_NAME)

    math(EXPR listIndex "${index} * 3 + 1")
    list(GET TESTS ${listIndex} TEST_CFLAGS)

    math(EXPR listIndex "${index} * 3 + 2")
    list(GET TESTS ${listIndex} TEST_LFLAGS)

    message(STATUS "Configuring ${TEST_NAME} with\n"
        "---- TEST_CFLAGS: ${TEST_CFLAGS}\n"
        "---- TEST_LFLAGS: ${TEST_LFLAGS}"
    )

    set(TEST_BIN_DIR "${TESTS_BIN_DIR}/${TEST_NAME}")

    FILE(GLOB TEST_SOURCE_FILES "${TESTS_SOURCE_DIR}/${TEST_NAME}/*.c")

    add_executable(${TEST_NAME} ${TEST_SOURCE_FILES})
    target_include_directories(${TEST_NAME} PUBLIC ${NBP_INCLUDE_DIR})

    set_target_properties( ${TEST_NAME}
        PROPERTIES
        COMPILE_FLAGS "${CFLAGS} ${TEST_CFLAGS}"
        LINK_FLAGS "${LFLAGS} ${TEST_LFLAGS}"
        ARCHIVE_OUTPUT_DIRECTORY ${TEST_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${TEST_BIN_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${TEST_BIN_DIR}
    )
endforeach()

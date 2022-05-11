#
# Copyright (C) 2021 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set(TEST_ABI_LIST ${TEST_ABIS})

if (${ANDROID_ABI} IN_LIST TEST_ABI_LIST)
if (${RUN_CPP_TESTS} MATCHES "true")
    set(TEST_LIB_NAME paddleboat-tests-lib)
    set(GTEST_DIR ${ANDROID_NDK}/sources/third_party/googletest)
    add_library(gtest STATIC ${GTEST_DIR}/src/gtest_main.cc ${GTEST_DIR}/src/gtest-all.cc)
    target_include_directories(gtest PRIVATE ${GTEST_DIR})
    target_include_directories(gtest PUBLIC ${GTEST_DIR}/include)

    add_executable(${TEST_LIB_NAME}
            ${TEST_SRC_DIR}/paddleboat_tests.cpp)

    target_link_libraries(${TEST_LIB_NAME} paddleboat gtest)

    set(TARGET_TEST_DIR /data/local/tmp/${TEST_LIB_NAME})
    set(TARGET_TEST_LIB_DIR ${TARGET_TEST_DIR}/${ANDROID_ABI})
    find_program(ADB NAMES adb PATHS ${ANDROID_SDK_ROOT}/platform-tools)

    message(STATUS "Running Paddleboat tests for ABI ${ANDROID_ABI} SDK ${ANDROID_SDK_ROOT} RUN_CPP_TESTS ${RUN_CPP_TESTS}")

    add_custom_command(TARGET ${TEST_LIB_NAME} POST_BUILD
            COMMAND ${ADB} shell mkdir -p ${TARGET_TEST_LIB_DIR}
            COMMAND ${ADB} push $<TARGET_FILE:${TEST_LIB_NAME}> ${TARGET_TEST_LIB_DIR}/
            COMMAND ${ADB} push $<TARGET_FILE:paddleboat> ${TARGET_TEST_LIB_DIR}/
            COMMAND ${ADB} shell \"export LD_LIBRARY_PATH=${TARGET_TEST_LIB_DIR}\; ${TARGET_TEST_LIB_DIR}/${TEST_LIB_NAME}\")
endif () # RUN_CPP_TESTS
else()
    message(STATUS "Skipping Paddleboat tests for ABI ${ANDROID_ABI} SDK ${ANDROID_SDK_ROOT} RUN_CPP_TESTS ${RUN_CPP_TESTS}")
endif () # ANDROID_ABI in TEST_ABIS

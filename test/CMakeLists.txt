cmake_minimum_required(VERSION 3.13.0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/googletest)
include(GoogleTest)

file(GLOB TEST_SOURCES src/*.cpp)
file(GLOB ORG_SOURCES ${CMAKE_SOURCE_DIR}/src/Model.h)

set(TEST_NAME ${PROJECT_NAME}test)

add_executable(${TEST_NAME} ${ORG_SOURCES} ${TEST_SOURCES})

target_compile_options(${TEST_NAME} PRIVATE ${COMPILER_FLAGS})

target_compile_features(${TEST_NAME} PRIVATE cxx_std_20)

target_link_libraries(${TEST_NAME} gtest_main)
#gtest_discover_tests(${TEST_NAME})

# target_link_libraries(${PROGRAM}
#     PRIVATE
#         gmock
#         gtest
#         gmock_main)

# target_include_directories(${PROGRAM}
#     PUBLIC
#         #third_party/googletest/include
#         third_party/googlemock/include)

# enable_testing()

add_test(
    NAME SamplePlayerTest
    COMMAND ${TEST_NAME}
)

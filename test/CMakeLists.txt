cmake_minimum_required(VERSION 3.23)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

message(STATUS "${Yellow}Fetching googletest...${ColorReset}")
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0)
FetchContent_GetProperties(googletest)
FetchContent_MakeAvailable(googletest)
message(
  STATUS "${Green}googletest fetched to: ${googletest_SOURCE_DIR}${ColorReset}")

file(GLOB_RECURSE DMAO_PLACEHOLDER_TEST_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/placeholder/*.cpp")

add_executable(dmao_placeholder_test ${DMAO_PLACEHOLDER_TEST_SOURCES})

target_link_libraries(dmao_placeholder_test PRIVATE gtest_main dmao::dmao)

setup_compiler_flags(dmao_placeholder_test)

add_test(NAME dmao_placeholder_test COMMAND dmao_placeholder_test)

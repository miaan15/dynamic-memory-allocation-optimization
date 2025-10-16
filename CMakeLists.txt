cmake_minimum_required(VERSION 3.23)
project(dmao LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ================================================================================
option(DMAO_BUILD_BENCH "Enable build test" OFF)
option(DMAO_BUILD_DEMO "Enable build demo" OFF)
option(DMAO_BUILD_TEST "Enable build test" OFF)

# ================================================================================
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler-flags.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/message-color.cmake")

# ================================================================================
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

message(STATUS "${Yellow}Fetching eigen...${ColorReset}")
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 5.0.0)
FetchContent_GetProperties(eigen)
FetchContent_MakeAvailable(eigen)
message(STATUS "${Green}eigen fetched to: ${eigen_SOURCE_DIR}${ColorReset}")

message(STATUS "${Yellow}Fetching toml++...${ColorReset}")
FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
  GIT_TAG v3.4.0)
FetchContent_GetProperties(tomlplusplus)
FetchContent_MakeAvailable(tomlplusplus)
message(
  STATUS "${Green}toml++ fetched to: ${tomlplusplus_SOURCE_DIR}${ColorReset}")

# ================================================================================
file(GLOB_RECURSE DMAO_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE DMAO_HEADERS CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(dmao STATIC ${DMAO_SOURCES})
add_library(dmao::dmao ALIAS dmao)

setup_compiler_flags(dmao)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND WIN32)
  target_link_libraries(dmao PUBLIC stdc++exp)
endif()

target_link_libraries(dmao PUBLIC eigen)

target_sources(
  dmao
  PUBLIC FILE_SET
         dmao_headers
         TYPE
         HEADERS
         BASE_DIRS
         ${CMAKE_CURRENT_SOURCE_DIR}/src
         FILES
         ${dmao_HEADERS})

# ================================================================================
if(DMAO_BUILD_TEST)
  message(STATUS "${Yellow}Build test${ColorReset}")
  enable_testing()
  add_subdirectory(test)
endif()

if(DMAO_BUILD_DEMO)
  message(STATUS "${Yellow}Build demo${ColorReset}")
  add_subdirectory(demo)
endif()

if(DMAO_BUILD_BENCH)
  message(STATUS "${Yellow}Build bench${ColorReset}")
  add_subdirectory(bench)
endif()

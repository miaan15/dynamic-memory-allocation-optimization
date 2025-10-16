cmake_minimum_required(VERSION 3.23)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

message(STATUS "${Yellow}Fetching benchmark...${ColorReset}")
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.4)
FetchContent_GetProperties(benchmark)
FetchContent_MakeAvailable(benchmark)
message(
  STATUS "${Green}benchmark fetched to: ${benchmark_SOURCE_DIR}${ColorReset}")

file(GLOB_RECURSE DMAO_PLACEHOLDER_BENCH_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/placeholder/*.cpp")

add_executable(dmao_placeholder_bench ${DMAO_PLACEHOLDER_BENCH_SOURCES})

target_link_libraries(dmao_placeholder_bench PRIVATE benchmark::benchmark
                                                     dmao::dmao)

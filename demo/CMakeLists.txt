cmake_minimum_required(VERSION 3.23)

add_executable(dmao_basic_demo ./basic/main.cpp)
target_link_libraries(dmao_basic_demo PRIVATE dmao)

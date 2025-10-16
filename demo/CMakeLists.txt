cmake_minimum_required(VERSION 3.23)

project(dmao_demo CXX)

add_executable(dmao_demo main.cpp)

target_link_libraries(dmao_demo PRIVATE dmao)

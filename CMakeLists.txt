cmake_minimum_required(VERSION 3.14)
project(untitled)

enable_testing()

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 17)

set(ALL_FILES ${ENTITY_FILES} main.cpp)

add_executable(untitled ${ALL_FILES})
target_link_libraries(untitled chormosomes)
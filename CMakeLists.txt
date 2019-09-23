cmake_minimum_required(VERSION 3.14)
project(Genetic_Algorithm_TSP)

enable_testing()

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 17)

set(ALL_FILES ${ENTITY_FILES} main.cpp)

add_executable(${PROJECT_NAME} ${ALL_FILES})
target_link_libraries(${PROJECT_NAME} chormosomes)

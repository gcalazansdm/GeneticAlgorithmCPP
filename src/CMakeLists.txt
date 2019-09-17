
FILE(GLOB ENTITY_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(chormosomes ${ENTITY_FILES})
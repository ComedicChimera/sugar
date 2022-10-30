cmake_minimum_required(
    VERSION 3.20.0
)

set(ADT_SOURCES "buffer.c" "map.c" "queue.c" "sv.c" "vec.c")
list(TRANSFORM ADT_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/adt/")

set(MISC_SOURCES "error.c")
list(TRANSFORM MISC_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

add_library(SugarLibrary ${ADT_SOURCES} ${MISC_SOURCES})

target_include_directories(SugarLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

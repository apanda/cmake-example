cmake_minimum_required(VERSION 3.18)
include(ExternalProject)
project(everything)

# Call with name exported (argv0)
# relative path to directory (argv1)
# and name of resulting library (argv2)
function (add_static_lib_directory)
    ExternalProject_Add("${ARGV0}src" SOURCE_DIR "${CMAKE_SOURCE_DIR}/${ARGV1}"
                              INSTALL_COMMAND "") 
    ExternalProject_Get_Property(${ARGV0}src BINARY_DIR)
    add_library("${ARGV0}" STATIC IMPORTED)
    set_property(TARGET "${ARGV0}" PROPERTY IMPORTED_LOCATION
        "${BINARY_DIR}/${ARGV2}")
endfunction()

add_static_lib_directory(lib1 libs/lib1 libfun.a)
add_static_lib_directory(lib2 libs/lib2 libfun.a)


add_executable(test src/test.c)
target_link_libraries(test lib1 lib2)


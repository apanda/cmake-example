cmake_minimum_required(VERSION 3.18)
include(ExternalProject)
project(everything)

# Call with name exported (argv0)
# relative path to directory (argv1)
# and name of resulting library (argv2)
# Adds an external project pointing to an in-tree
# library.
function (add_static_lib_directory)
    # Use ExternalProject_Add to build library. Note that as long as
    # the SOURCE_DIR is not empty, CMake does not need a download command.
    # We do not need to install in this case.
    ExternalProject_Add("${ARGV0}src" SOURCE_DIR "${CMAKE_SOURCE_DIR}/${ARGV1}"
                              INSTALL_COMMAND "") 
    # Figure out where the build product will land.
    ExternalProject_Get_Property(${ARGV0}src BINARY_DIR)
    # Create the appropriate library target
    add_library("${ARGV0}" STATIC IMPORTED)
    # Tell CMake that this target depends on the external project.
    add_dependencies("${ARGV0}" "${ARGV0}src")
    # Use the build product from the external project as the library.
    set_property(TARGET "${ARGV0}" PROPERTY IMPORTED_LOCATION
        "${BINARY_DIR}/${ARGV2}")
endfunction()

add_static_lib_directory(lib1 libs/lib1 libfun.a)
add_static_lib_directory(lib2 libs/lib2 libfun.a)


add_executable(test src/test.c)
target_link_libraries(test lib1 lib2)


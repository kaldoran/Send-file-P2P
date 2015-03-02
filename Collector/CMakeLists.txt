cmake_minimum_required(VERSION 3.1)

project (Generator)

find_package(OpenSSL)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -O2 -lm -lrt -lssl -lcrypto")

file(GLOB_RECURSE Generator_SOURCES "SRC/*.c")
file(GLOB_RECURSE Generator_HEADERS "INC/*.h")

set (Generator_INCLUDE_DIRS "")
foreach (_headerFile ${Generator_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Generator_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Generator_INCLUDE_DIRS)

include_directories(${Generator_INCLUDE_DIRS})
add_executable (GeneratorExe ${Generator_SOURCES})

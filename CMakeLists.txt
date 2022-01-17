cmake_minimum_required(VERSION 3.14)
project(PyBinding)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wshadow -Wstrict-aliasing")

add_subdirectory(extern)
add_subdirectory(src)

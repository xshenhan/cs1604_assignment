cmake_minimum_required(VERSION 3.24)
project(source)

set(CMAKE_CXX_STANDARD 11)
include_directories( E:/cs1604_lib/src/cs1604/include)
link_directories( E:/cs1604_lib/src/cs1604/lib)
link_libraries(libCS1604.a)
add_executable(source main.cpp units.cpp engine.cpp field.cpp)

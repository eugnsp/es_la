cmake_minimum_required(VERSION 3.5)
project(es_la VERSION 1.0 DESCRIPTION "Linear algebra library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-psabi -m64 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3 -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -flto")

file(GLOB_RECURSE ES_LA_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(es_la STATIC "${ES_LA_SRC}")

target_include_directories(es_la PRIVATE "./include")

set(ES_UTIL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/es_util/include")
add_library(es_util INTERFACE IMPORTED)
set_target_properties(es_util PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${ES_UTIL_INCLUDE_DIR}")

target_link_libraries(es_la es_util)

include_directories("$ENV{MKLROOT}/include")
link_directories("$ENV{MKLROOT}/lib/intel64")
add_definitions(-DMKL_ILP64)
set(MKL_LIBRARIES "-Wl,--start-group" libmkl_intel_ilp64.a libmkl_sequential.a libmkl_core.a "-Wl,--end-group" pthread m dl)

target_link_libraries(es_la "${MKL_LIBRARIES}")
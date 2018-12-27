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
target_include_directories(es_la PUBLIC "include")

if (NOT TARGET es_util)
	add_subdirectory("external/es_util")
endif()
target_link_libraries(es_la PUBLIC es_util)

target_include_directories(es_la PUBLIC "$ENV{MKLROOT}/include")
add_definitions(-DMKL_ILP64)
set(MKL_LIB "$ENV{MKLROOT}/lib/intel64")
set(MKL_LIBRARIES "-Wl,--start-group" "${MKL_LIB}/libmkl_intel_ilp64.a" "${MKL_LIB}/libmkl_sequential.a" "${MKL_LIB}/libmkl_core.a" "-Wl,--end-group" pthread m dl)

target_link_libraries(es_la PUBLIC "${MKL_LIBRARIES}")
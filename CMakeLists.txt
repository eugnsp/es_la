cmake_minimum_required(VERSION 3.13)
project(es_la VERSION 1.0 DESCRIPTION "Linear algebra library")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE ES_LA_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(es_la STATIC "${ES_LA_SRC}")
target_include_directories(es_la PUBLIC "include")
target_compile_features(es_la PUBLIC cxx_std_17)
target_compile_options(es_la PRIVATE
	-Wall -Wpedantic -Wextra -Werror=return-type -m64 -march=native
	$<$<CONFIG:DEBUG>:-O0 -g> 
	$<$<CONFIG:RELEASE>:-Wno-unused-parameter -Wno-deprecated-declarations -O3 -DNDEBUG>)

if (NOT TARGET es_util)
	add_subdirectory("external/es_util")
endif()
target_link_libraries(es_la PUBLIC es_util)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

target_include_directories(es_la PUBLIC "$ENV{MKLROOT}/include")
target_compile_definitions(es_la PUBLIC MKL_ILP64)
set(MKL_LIB "$ENV{MKLROOT}/lib/intel64")
#set(MKL_LIBRARIES "-Wl,--start-group" "${MKL_LIB}/libmkl_intel_ilp64.a" "${MKL_LIB}/libmkl_sequential.a" "${MKL_LIB}/libmkl_core.a" "-Wl,--end-group" pthread m dl)
set(MKL_LIBRARIES "-Wl,--no-as-needed" mkl_intel_ilp64 mkl_sequential mkl_core Threads::Threads m dl)

target_link_directories(es_la PUBLIC "${MKL_LIB}")
target_link_libraries(es_la PUBLIC "${MKL_LIBRARIES}")

find_package(Boost)
enable_testing()

add_executable(es_la_test "test/es_la_test.cpp")
if (Boost_FOUND)
	target_include_directories(es_la_test PUBLIC "${Boost_INCLUDE_DIRS}")
endif()
target_link_libraries(es_la_test PUBLIC es_la)
target_compile_options(es_la_test PRIVATE -Wall -Wpedantic -Wextra -Werror=return-type -m64 -march=native -O0 -g)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_options(es_la PRIVATE -Wno-psabi)
	target_compile_options(es_la_test PRIVATE -Wno-psabi)
endif()

add_test(NAME es_la_test COMMAND es_la_test)

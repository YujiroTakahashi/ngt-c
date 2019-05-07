cmake_minimum_required(VERSION 2.8)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)

project(croco_ngt)

include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/croco
	${CMAKE_BINARY_DIR}/lib/croco
)

find_library(ngt-shared NAMES libngt.so PATHS /usr/lib /usr/local/lib)

add_subdirectory(lib)

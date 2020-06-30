cmake_minimum_required(VERSION 3.5)
project(dbus VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

set(SIMPPL_BUILD_EXAMPLES OFF CACHE BOOL "Simppl examples" FORCE)
set(SIMPPL_BUILD_TESTS OFF CACHE BOOL "Simppl tests" FORCE)
find_package(PkgConfig)

find_package(Threads)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/3dp/simppl")

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME} simppl) 

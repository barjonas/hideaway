cmake_minimum_required(VERSION 3.0)

project(hideaway)

find_package(Threads REQUIRED)

add_executable(hideaway hideaway.cpp)
target_compile_options(hideaway PRIVATE -Wall -Wextra -pedantic -std=c++11)
target_link_libraries(hideaway ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS hideaway RUNTIME DESTINATION bin)

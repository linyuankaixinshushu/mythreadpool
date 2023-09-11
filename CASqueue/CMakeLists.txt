cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(nomutexqueue LANGUAGES CXX)
find_package(Threads REQUIRED)
add_executable(testDequeue testDequeue.cpp)
add_executable(testEnqueue testEnqueue.cpp)
target_link_libraries(testDequeue PUBLIC Threads::Threads)
target_link_libraries(testEnqueue PUBLIC Threads::Threads)


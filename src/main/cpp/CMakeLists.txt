project(shortbite)

cmake_minimum_required(VERSION 3.4.3)

add_library(shortbite SHARED converter.cpp)

find_library(app-log log)

target_link_libraries(shortbite log)
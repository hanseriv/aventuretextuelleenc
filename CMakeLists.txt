cmake_minimum_required(VERSION 3.31)
project(JEUDAVENTURETEXTUELLE VERSION 0.0.1 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(AVANTURETEXTUELLEENC main.c)
add_library(fonctionutile STATIC fonctionutile.c)

target_link_libraries(AVANTURETEXTUELLEENC fonctionutile)


set_property(TARGET AVANTURETEXTUELLEENC PROPERTY C_STANDARD 99)

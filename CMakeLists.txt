cmake_minimum_required(VERSION 3.17)
project(thatshell C)

set(CMAKE_C_STANDARD 99)

add_executable(thatshell shell.c arrayimpl.c arrayimpl.h create.c create.h listimpl.c listimpl.h deleteimpl.c deleteimpl.h)
cmake_minimum_required(VERSION 3.10)
project(nuke C)

add_executable(nuke nuke.c)
if(MSVC)
  target_compile_definitions(nuke PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

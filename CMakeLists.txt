cmake_minimum_required(VERSION 3.25)
project(ImageProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libstatic")
set(CMAKE_BINARY_DIR "build")

add_executable(main "src/main.c")
target_include_directories(main PUBLIC "headers")

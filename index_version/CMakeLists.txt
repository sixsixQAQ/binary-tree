cmake_minimum_required(VERSION 3.1)
project(main)
set(EXE main)

add_compile_options(-g -Wall)
aux_source_directory(. SRC)
add_executable(${EXE} ${SRC})

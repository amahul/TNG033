cmake_minimum_required(VERSION 3.13.0...3.18.1)
project(TNG033-Lab-2 VERSION 1.0.0 DESCRIPTION "TNG033 Lab 2" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

add_executable(Exercise1 expression.h expression.cpp polynomial.h polynomial.cpp logarithm.h logarithm.cpp main.cpp)

enable_warnings(Exercise1)
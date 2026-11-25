cmake_minimum_required(VERSION 3.16)
project(LCSWavefront LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lcs_sequential src/sequential.cpp)
target_include_directories(lcs_sequential PRIVATE include)

find_package(OpenMP REQUIRED)
add_library(lcs_openmp_impl src/openmp_lcs.cpp)
target_include_directories(lcs_openmp_impl PUBLIC include)
target_link_libraries(lcs_openmp_impl PUBLIC OpenMP::OpenMP_CXX)

add_executable(lcs_openmp src/openmp.cpp)
target_include_directories(lcs_openmp PRIVATE include)
target_link_libraries(lcs_openmp PRIVATE lcs_openmp_impl)

add_executable(lcs_mpi src/mpi.cpp)
target_include_directories(lcs_mpi PRIVATE include "C:/Program Files (x86)/Microsoft SDKs/MPI/Include")
target_link_libraries(lcs_mpi PRIVATE "C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64/msmpi.lib")

add_executable(lcs_benchmark analysis/benchmark.cpp)
target_include_directories(lcs_benchmark PRIVATE include)
target_link_libraries(lcs_benchmark PRIVATE lcs_openmp_impl)

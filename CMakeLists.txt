cmake_minimum_required(VERSION 3.10.2)

project(Simulator)

aux_source_directory(. DIR_SRCS)

add_executable(Simulator ${DIR_SRCS})
set_property(TARGET Simulator PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET Simulator PROPERTY CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.8)
project(iupac_fsm_parser)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(common)

add_executable(iupac_fsm_parser main.cpp)
target_link_libraries(iupac_fsm_parser base_cpp common
        )
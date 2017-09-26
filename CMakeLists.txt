cmake_minimum_required(VERSION 3.8)
project(iupac_fsm_parser C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(regular-fsm)


add_executable(iupac_fsm_parser
        main.cpp)

target_link_libraries(iupac_fsm_parser
        regular-fsm
        common
        tinyxml)
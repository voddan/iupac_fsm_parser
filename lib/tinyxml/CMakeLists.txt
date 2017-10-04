add_library(tinyxml STATIC
        src/tinystr.cpp
        src/tinyxml.cpp
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp)

target_sources(tinyxml PRIVATE
        include/tinystr.h
        include/tinyxml.h)

target_include_directories(tinyxml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(tinyxml PUBLIC -DTIXML_USE_STL)

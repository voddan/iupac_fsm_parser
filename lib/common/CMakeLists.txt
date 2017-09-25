add_library(common INTERFACE)

target_link_libraries(common INTERFACE base_c base_cpp)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../)

# A dummy target for IDEs
# http://thread.gmane.org/gmane.comp.programming.tools.cmake.devel/13636
add_custom_target(_ SOURCES
        RectangularVectors.h
        stringbuilder.h
        stringhelper.h
        collectionhelper.hpp
        Comparator.hpp)
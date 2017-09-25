add_library(common
        INTERFACE
        )

#http://thread.gmane.org/gmane.comp.programming.tools.cmake.devel/13636

#target_sources(common
#        PRIVATE
#        INTERFACE
#        RectangularVectors.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/RectangularVectors.h
#        ./stringbuilder.h
#        stringhelper.h
#        collectionhelper.hpp
#        Comparator.hpp
#        test.h
#        test.cpp
#        )

target_link_libraries(common INTERFACE base_c base_cpp)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)
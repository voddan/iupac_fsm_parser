add_subdirectory(base_c)
add_subdirectory(base_cpp)
add_subdirectory(common)
add_subdirectory(tinyxml)

set(gtest_force_shared_crt ON CACHE BOOL "Linking under MSVC")
add_subdirectory(googletest)

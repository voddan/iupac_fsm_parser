set(SRC_COMMON
        bitarray.c)

set(SRC_POSIX
        nano_posix.c
        os_dir_posix.c
        os_sync_posix.c
        os_thread_posix.c
        os_tls_posix.c)

set(SRC_WIN
        bitarray.c
        nano_win.c
        os_dir_win32.c
        os_sync_win32.c
        os_thread_win32.c
        os_tls_win32.c)

if (MSVC OR MINGW)
    set(SRC ${SRC_COMMON} ${SRC_WIN})
else()
    set(SRC ${SRC_COMMON} ${SRC_POSIX})
endif()

add_library(base_c ${SRC})

target_sources(base_c PRIVATE
        bitarray.h
        defs.h
        nano.h
        os_dir.h
        os_sync.h
        os_thread.h
        os_tls.h)

target_include_directories(base_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

find_package(Threads REQUIRED)
target_link_libraries(base_c Threads::Threads)

#file (GLOB BaseC_headers base_c/*.h*)
#file (GLOB BaseCpp_headers base_cpp/*.h*)

if(UNIX OR APPLE)
    set_target_properties(common PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -Wall")
endif()


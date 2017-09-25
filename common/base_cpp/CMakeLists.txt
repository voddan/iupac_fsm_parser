set(SRC_COMMON
        bitinworker.cpp
        bitoutworker.cpp
        cancellation_handler.cpp
        chunk_storage.cpp
        common_exceptions_impl.cpp
        crc32.cpp
        d_bitset.cpp
        exception.cpp
        gray_codes.cpp
        io_base.cpp
        locale_guard.cpp
        os_sync_wrapper.cpp
        os_thread_wrapper.cpp
        output.cpp
        profiling.cpp
        properties_map.cpp
        scanner.cpp
        shared_ptr.cpp
        smart_output.cpp
        string_pool.cpp
        tlscont.cpp)

set(SRC_POSIX
        shmem_posix.cpp)

set(SRC_WIN
        shmem_win32.cpp)

if (MSVC OR MINGW)
    set(SRC ${SRC_COMMON} ${SRC_WIN})
else()
    set(SRC ${SRC_COMMON} ${SRC_POSIX})
endif()

add_library(base_cpp ${SRC})

target_sources(base_cpp PRIVATE
        array.h
        auto_iter.h
        auto_ptr.h
        bitinworker.h
        bitoutworker.h
        cancellation_handler.h
        chunk_storage.h
        crc32.h
        cyclic_array.h
        d_bitset.h
        exception.h
        gray_codes.h
        io_base.h
        list.h
        locale_guard.h
        multimap.h
        non_copyable.h
        nullable.h
        obj.h
        obj_array.h
        obj_list.h
        obj_pool.h
        os_sync_wrapper.h
        os_thread_wrapper.h
        output.h
        pool.h
        profiling.h
        properties_map.h
        ptr_array.h
        ptr_pool.h
        queue.h
        red_black.h
        reusable_obj_array.h
        scanner.h
        shared_ptr.h
        shmem.h
        smart_output.h
        string_pool.h
        temporary_thread_obj.h
        temporary_thread_obj.hpp
        tlscont.h
        tree.h
        trie.h)

target_link_libraries(base_cpp PUBLIC base_c)

target_include_directories(base_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

if(UNIX OR APPLE)
    set_target_properties(common PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -Wall")
endif()
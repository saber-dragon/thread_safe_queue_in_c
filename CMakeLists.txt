cmake_minimum_required(VERSION 2.8)

project (thread_safe_queue C)

option(ENABLE_GTEST "Build with Google gtest enabled." ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(HEADERS "list.h" "queue.h")
set(SRCs "queue.c")

set(saber_libraries "")

add_library(ts_queue STATIC ${HEADERs} ${SRCs})
target_include_directories(ts_queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

list(APPEND saber_libraries ts_queue)

if (ENABLE_GTEST)
    enable_testing()
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
            ${CMAKE_BINARY_DIR}/googletest-build
            EXCLUDE_FROM_ALL)
    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    include_directories("${gtest_SOURCE_DIR}/include")
    list(APPEND saber_libraries gtest_main)
    add_subdirectory(test)
else ()
    message(STATUS "Google Test is disabled.")
endif ()




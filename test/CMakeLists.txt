project(ts_queue_test)
set(CMAKE_CXX_STANDARD 11)

file(GLOB test_srcs "*.cc")
message(STATUS "libraries : ${saber_libraries}")

foreach (test_src ${test_srcs})
    get_filename_component(fn ${test_src} NAME_WE)
    message(STATUS "Compiling ${fn} ...")
    set(exe "${fn}")
    add_executable(${exe} ${test_src})
    target_link_libraries(${exe} ${saber_libraries} pthread)
    add_test(NAME ${exe}
            COMMAND $<TARGET_FILE:${exe}>)
endforeach ()
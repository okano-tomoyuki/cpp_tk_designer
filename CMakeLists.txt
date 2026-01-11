cmake_minimum_required(VERSION 3.10)
project(io_converter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

if (UTIX OR MINGW)
    set(DEBUG_OPTION -g)
    set(OPTIMIZE_OPTION -O2)
    set(THREAD_OPTION -lpthread)
endif()

add_subdirectory(thirdparty)

set(exec_name designer)

add_executable(${exec_name}
    main.cpp
)

target_include_directories(${exec_name}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/thirdparty
)

target_link_libraries(${exec_name}
    PRIVATE 
        CppTk::CppTk
)
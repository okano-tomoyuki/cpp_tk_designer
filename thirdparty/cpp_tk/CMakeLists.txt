cmake_minimum_required(VERSION 3.10)
project(cpp_tk VERSION 0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(Tk REQUIRED)
find_package(TCL REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${Tk_INCLUDE_DIRS}
        ${TCL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        ${Tk_LIBRARIES}
        ${TCL_LIBRARIES}
)

add_library(CppTk::CppTk ALIAS cpp_tk)
# add_subdirectory(example)
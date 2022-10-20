cmake_minimum_required(VERSION 3.18)
project(hw1_matrix_main)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(project)

add_executable(${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
        )

target_link_libraries(${PROJECT_NAME} hw1_matrix)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()



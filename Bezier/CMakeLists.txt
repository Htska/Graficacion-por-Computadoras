cmake_minimum_required(VERSION 3.28)
project(curva LANGUAGES CXX)


# Estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Flags del compilador (equivalente a -Wall -Wextra)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)


# Ejecutable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp
                               )

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
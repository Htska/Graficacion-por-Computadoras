cmake_minimum_required(VERSION 3.24)
project(going_3d)

# Estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags del compilador (equivalente a -Wall -Wextra)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Encontrar bibliotecas
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)


# Ejecutable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp
                               ${PROJECT_SOURCE_DIR}/src/Core/Application.cpp
                               ${PROJECT_SOURCE_DIR}/src/Core/Scene.cpp
                               ${PROJECT_SOURCE_DIR}/src/Core/WindowGL.cpp
                               ${PROJECT_SOURCE_DIR}/src/Core/Camera.cpp
                               ${PROJECT_SOURCE_DIR}/src/Graphics/ShaderProgram.cpp
                               ${PROJECT_SOURCE_DIR}/src/Graphics/models/Cube.cpp
                               ${PROJECT_SOURCE_DIR}/src/Graphics/models/CustomModel.cpp
                               ${PROJECT_SOURCE_DIR}/src/Utils/obj_helpers/ObjLoader.cpp
                               ${PROJECT_SOURCE_DIR}/src/Utils/stb_image.cpp
                               )

# Librerías
# Linkear las bibliotecas encontradas
target_link_libraries(${PROJECT_NAME} 
    OpenGL::GL
    GLEW::GLEW
    glfw
)
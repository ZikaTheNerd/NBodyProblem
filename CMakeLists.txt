# Inspired by this project https://github.com/andystanton/glfw-skeleton


cmake_minimum_required(VERSION 3.16)
project(NBodyProblem)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET FALSE)

#
# glfw
#
set(GLFW_BUILD_DOCS FALSE)
set(GLFW_BUILD_EXAMPLES FALSE)
set(GLFW_BUILD_TESTS FALSE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.4
        GIT_PROGRESS TRUE)

#
# glad
#
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad
        GIT_TAG v0.1.34
        GIT_PROGRESS TRUE)

#
# glm
#
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8
        GIT_PROGRESS TRUE)

#
# fetch dependencies
#
FetchContent_MakeAvailable(glfw glad glm)

#
# N-body source code
#
set(
        PROJECT_SOURCES
        src/main.cpp
        src/main.cpp
        src/Camera.cpp
        src/Particle.cpp
        src/Window.cpp
        src/Shader.cpp
        src/Shader.h
        src/ComputeShader.cpp
        src/ComputeShader.h
        src/VertexFragmentShader.cpp
        src/VertexFragmentShader.h
        src/ParticleSystem.cpp
        src/ParticleSystem.h
        src/RenderTimer.cpp
        src/RenderTimer.h
        src/RenderLoop.cpp
        src/RenderLoop.h
        src/ParticleSimulation.cpp
        src/ParticleSimulation.h
        src/ParticleDrawer.cpp
        src/ParticleDrawer.h
        src/Bloom.cpp
        src/Bloom.h
)

# Include OpenMP
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    message("OpenMP found")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_dependencies(${PROJECT_NAME} glfw glad glm)

# We currently don't need any include directories
# target_include_directories(
#        ${PROJECT_NAME} PRIVATE
#
# )
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm OpenMP::OpenMP_CXX)

# For language servers (autocomplete) to work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.25)
project(VulkanTutorial)

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

set(SOURCES src/main.cpp src/lve_window.hpp src/lve_window.cpp src/first_app.cpp src/first_app.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)
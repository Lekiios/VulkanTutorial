cmake_minimum_required(VERSION 3.25)
project(VulkanTutorial)

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)
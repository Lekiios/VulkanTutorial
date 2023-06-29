cmake_minimum_required(VERSION 3.25)
project(VulkanTutorial)

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

######################## BUILD SHADERS #################################

find_program(glslangValid "glslangValidator")
mark_as_advanced(FORCE glslangValid)
if (glslangValid)
    message(STATUS "glslangValidator found: ${glslangValid}")
else ()
    message(STATUS "glslangValidator not found!")
endif ()

#get all .vert and .frag files in shaders directory
file(GLOB GLSL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/shaders/*.frag"
        "${PROJECT_SOURCE_DIR}/shaders/*.vert"
        )

foreach (GLSL_FILE ${GLSL_SOURCE_FILES})
    set(SPIRV "${GLSL_FILE}.spv")
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${glslangValid} -V "${GLSL_FILE}" -o ${SPIRV}
            MAIN_DEPENDENCY ${GLSL_FILE})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach (GLSL_FILE)

add_custom_target(
        Shaders
        DEPENDS ${SPIRV_BINARY_FILES}
)
#########################################################################

set(SOURCES src/main.cpp src/lve_window.hpp src/lve_window.cpp src/first_app.cpp src/first_app.hpp src/lve_pipeline.hpp src/lve_pipeline.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)


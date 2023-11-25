cmake_minimum_required(VERSION 3.25)
project(VulkanTutorial)

set(CMAKE_CXX_STANDARD 20)

######################## REQUIRED PACKAGES ##############################
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
#########################################################################

######################## BUILD SHADERS #################################
###
# Find GLS_LANG_VALIDATOR for shaders build
###
find_program(glslangValid "glslangValidator")
mark_as_advanced(FORCE glslangValid)
if (glslangValid)
    message(STATUS "glslangValidator found: ${glslangValid}")
else ()
    message(STATUS "glslangValidator not found!")
endif ()

###
# Get all .vert and .frag files in shaders directory
###
file(GLOB GLSL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/shaders/*.frag"
        "${PROJECT_SOURCE_DIR}/shaders/*.vert"
        )

###
# Build each file we found in shaders directory
# TODO: Build file and copy them automatically to build directory instead of shaders
###
foreach (GLSL_FILE ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL_FILE} NAME)
    set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
            COMMAND ${glslangValid} -V "${GLSL_FILE}" -o ${SPIRV}
            MAIN_DEPENDENCY ${GLSL_FILE})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach (GLSL_FILE)

###
# Add target to complete build
###
add_custom_target(
        Shaders
        DEPENDS ${SPIRV_BINARY_FILES}
)
#########################################################################

########################### BUILD APP ###################################
set(SOURCES src/main.cpp
        src/lve_window.hpp
        src/lve_window.cpp
        src/first_app.hpp
        src/first_app.cpp
        src/lve_pipeline.hpp
        src/lve_pipeline.cpp
        src/lve_device.hpp
        src/lve_device.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)

add_dependencies(${PROJECT_NAME} Shaders)
#########################################################################


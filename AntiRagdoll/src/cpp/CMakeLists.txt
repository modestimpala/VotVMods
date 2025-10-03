cmake_minimum_required(VERSION 3.18)
set(MOD_OUTPUT_PATH_ANTIRAGDOLLCPP "C:/Users/$ENV{USERNAME}/AppData/Roaming/r2modmanPlus-local/VotV/profiles/test/shimloader/mod/AntiRagdollCpp/dlls" CACHE PATH "Path to mod output directory")

project(AntiRagdollCpp)

# Source files
file(GLOB_RECURSE HEADER_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
file(GLOB_RECURSE SOURCE_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Create library
add_library(${PROJECT_NAME} SHARED
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# Regular includes
target_include_directories(${PROJECT_NAME}
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# MSVC settings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        /wd4005
        /wd4100
        /wd4251
        /wd4996
        /FS
    )
endif()


target_link_libraries(${PROJECT_NAME} PUBLIC UE4SS )

# First check if the libvotv target exists
if(TARGET libvotv)
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
            libvotv
    )
endif()




# Copy the main DLL
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        "${MOD_OUTPUT_PATH_ANTIRAGDOLLCPP}/main.dll"
)
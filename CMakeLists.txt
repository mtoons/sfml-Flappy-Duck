cmake_minimum_required(VERSION 3.28)
project(sfmlFlappyBird LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG master
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCE_FILES src/*.cc)
add_executable(main ${SOURCE_FILES})
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE SFML::Graphics)
file(GLOB_RECURSE IMAGES ressources/*.png)
set(RESOURCE_FILES ${IMAGES} Roboto.ttf)

add_custom_command(TARGET main PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/ressources/ $<TARGET_FILE_DIR:main>/ressources)

cmake_minimum_required(VERSION 3.28...4.2)
project(sfml-enet-project LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ENET
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG 2662c0de09e36f2a2030ccc2c528a3e4c9e8138a
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ENET)

# Link toàn bộ file .cpp trong /src
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(app ${SRC_FILES})
target_compile_features(app PRIVATE cxx_std_20)
# --- Include paths ---
target_include_directories(app
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${enet_SOURCE_DIR}/include
        ${SFML_SOURCE_DIR}/include
)
target_link_libraries(app 
        PRIVATE 
            SFML::Graphics
            enet)
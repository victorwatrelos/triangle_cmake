cmake_minimum_required(VERSION 3.9)
project(triangle)

set(CMAKE_CXX_STANDARD 17)

add_executable(triangle
        main.cpp
        Angle.cpp
        Bullet.cpp
        Entity.cpp
        MathUtils.cpp
        ObjectManager.cpp
        Player.cpp
        WindowManager.cpp
        )

#include_directories(lib_includes)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/SFML/cmake/Modules")
set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/lib/SFML")
find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(triangle ${SFML_LIBRARIES})

execute_process (
        COMMAND bash -c "ln -s ${CMAKE_CURRENT_LIST_DIR}/textures ${CMAKE_CURRENT_BINARY_DIR}/textures "
        OUTPUT_VARIABLE outVar
)
execute_process (
        COMMAND bash -c "ln -s ${CMAKE_CURRENT_LIST_DIR}/ressources ${CMAKE_CURRENT_BINARY_DIR}/ressources"
        OUTPUT_VARIABLE outVar
)

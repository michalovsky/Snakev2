cmake_minimum_required( VERSION 3.14 )
set( PROJECT_NAME snake-sfml  )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )

set(SFML_INCLUDE_DIR "./SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "./SFML-2.5.1/lib")
set(SFML_DIR "./SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/Main.cpp
        ${CMAKE_SOURCE_DIR}/src/Food.cpp
        ${CMAKE_SOURCE_DIR}/src/Block.cpp
        ${CMAKE_SOURCE_DIR}/src/Route.cpp
        ${CMAKE_SOURCE_DIR}/src/Snake.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "./include" SFML_INCLUDE_DIR)

target_link_directories(${PROJECT_NAME} PUBLIC SFML_LIBRARY_DIR)

target_link_libraries ( ${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)
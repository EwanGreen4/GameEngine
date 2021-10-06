cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME GameEngine)
project(${PROJECT_NAME} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_executable(${PROJECT_NAME}
    main.cpp

    engine/GameEngine
    engine/gameengine.h
    engine/application.h
    engine/application.cpp

    engine/lib/microtar/microtar.c

    engine/resource.h
    engine/resource.cpp

    implementation.h
    implementation.cpp
    data.grc
    )

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/engine")
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

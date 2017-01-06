cmake_minimum_required(VERSION 3.6)
project(Terragen)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp
        src/Map.cpp src/Map.h
        src/Agent.cpp src/Agent.h
        src/AgentManager.cpp src/AgentManager.h
        src/CoastlineAgent.cpp
        src/MapGenerator.cpp src/MapGenerator.h
        src/RandomInt.cpp src/RandomInt.h
        src/SmoothingAgent.cpp
        )
add_executable(Terragen ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(SFML_STATIC_LIBRARIES True)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Terragen ${SFML_LIBRARIES})
endif()

target_link_libraries(Terragen ${LUA_LIBRARIES})
target_link_libraries(Terragen ${OPENGL_LIBRARIES})
if (WIN32)
    target_link_libraries(Terragen jpeg)
    target_link_libraries(Terragen winmm)
endif(WIN32)

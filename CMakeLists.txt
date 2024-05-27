cmake_minimum_required(VERSION 3.27)
project(Gems1)

set(CMAKE_CXX_STANDARD 17)


add_executable(Gems1 main.cpp
        libs/Game.cpp
        libs/Game.h
        libs/Tile.h
        libs/Bonus.cpp
        libs/Bonus.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Project 3/SFML/include/SFML)
target_link_libraries(Gems1 sfml-system sfml-window sfml-graphics sfml-audio)

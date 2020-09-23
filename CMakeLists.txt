cmake_minimum_required(VERSION 2.4)

project(Fifteen)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(SFML REQUIRED COMPONENTS graphics system windows) 
include_directories(${SFML_INCLUDE_DIR})


add_executable(main  Source.cpp Level.cpp Random.cpp X.cpp)	
add_executable(game_test  game_test.cpp Level.cpp Random.cpp X.cpp)


target_link_libraries(main PUBLIC sfml-window-s-d sfml-graphics-s-d sfml-system-s-d) 
target_link_libraries(game_test PUBLIC sfml-window-s-d sfml-graphics-s-d sfml-system-s-d)


enable_testing()
add_test(game_test game_test)

# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.24
cmake_policy(SET CMP0009 NEW)

# MY_HEADER_FILES at include/CMakeLists.txt:2 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES false RELATIVE "C:/Users/Tomer/Desktop/Studies/college/C.S/HAC-OOP1/Project_SuperPacman/include" "C:/Users/Tomer/Desktop/Studies/college/C.S/HAC-OOP1/Project_SuperPacman/include/*.h")
set(OLD_GLOB
  "CharMatrix.h"
  "GameEditor.h"
  "GameObject.h"
  "GridSubWindow.h"
  "HorizontalWindow.h"
  "Inputs.h"
  "MainWindow.h"
  "StaticObject.h"
  "SubWindow.h"
  "ToolsSubWindow.h"
  "board.h"
  "button.h"
  "character.h"
  "game.h"
  "gameMenu.h"
  "ghost.h"
  "lvlClock.h"
  "map.h"
  "menuButton.h"
  "pacman.h"
  "resources.h"
  "result.h"
  "round.h"
  "scoreBoard.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/Tomer/Desktop/Studies/college/C.S/HAC-OOP1/Project_SuperPacman/out/build/x64-Debug/CMakeFiles/cmake.verify_globs")
endif()

# MY_SOURCE_FILES at src/CMakeLists.txt:1 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES false RELATIVE "C:/Users/Tomer/Desktop/Studies/college/C.S/HAC-OOP1/Project_SuperPacman/src" "C:/Users/Tomer/Desktop/Studies/college/C.S/HAC-OOP1/Project_SuperPacman/src/*.cpp")
set(OLD_GLOB
  "CharMatrix.cpp"
  "GameEditor.cpp"
  "GridSubWindow.cpp"
  "HorizontalWindow.cpp"
  "Inputs.cpp"
  "MainWindow.cpp"
  "Resources.cpp"
  "SubWindow.cpp"
  "ToolsSubWindow.cpp"
  "board.cpp"
  "character.cpp"
  "game.cpp"
  "gameMenu.cpp"
  "ghost.cpp"
  "lvlClock.cpp"
  "main.cpp"
  "map.cpp"
  "menuButton.cpp"
  "pacman.cpp"
  "round.cpp"
  "scoreBoard.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/Tomer/Desktop/Studies/college/C.S/HAC-OOP1/Project_SuperPacman/out/build/x64-Debug/CMakeFiles/cmake.verify_globs")
endif()

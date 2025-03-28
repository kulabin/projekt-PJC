cmake_minimum_required(VERSION 3.28)
project(projekt_PJC)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)


add_executable(projekt_PJC main.cpp
        Menus/BaseMenu.cpp
        Menus/BaseMenu.h
        Menus/MainMenu.cpp
        Menus/MainMenu.h
        Menus/PauseMenu.cpp
        Menus/PauseMenu.h
        Menus/SettingsMenu.cpp
        Menus/SettingsMenu.h
        GameLogic/Word.cpp
        GameLogic/Word.h
        Menus/DifficultyMenu.cpp
        Menus/DifficultyMenu.h
        GameLogic/wordManager.cpp
        GameLogic/wordManager.h)
target_link_libraries(projekt_PJC sfml-graphics)
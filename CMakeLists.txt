cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

project (Progetto)

include_directories(include)

add_library(ScacchieraL
    include/Game.h
    include/RepGame.h
    include/Scacchiera.h
    include/Pezzi.h
    src/Scacchiera.cpp
    src/Pezzi.cpp
    src/MosseSpeciali1.cpp
    src/MosseSpeciali2.cpp
    src/Game.cpp
    src/RepGame.cpp
)

add_library(PedinaL
    include/Scacchiera.h
    src/Pedina.cpp
)

add_executable (Scacchiera
    src/Gioco.cpp
)

add_executable (Replay
    src/Replay.cpp
)

target_link_libraries(Scacchiera ScacchieraL)
target_link_libraries(Scacchiera PedinaL)

target_link_libraries(Replay ScacchieraL)
target_link_libraries(Replay PedinaL)


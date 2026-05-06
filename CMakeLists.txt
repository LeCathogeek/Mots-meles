cmake_minimum_required(VERSION 4.2)
project(u_p26_etienne_pacault_jeu_de_lettres C)

set(CMAKE_C_STANDARD 99)

add_library(GameLibrary jeu.h jeu.c)
add_library(StructuresLibrary structures.h
        structures.c)
add_library(SettingLibrary parametres.h parametres.c)
add_library(GridLibrary grid.h grid.c)
add_library(ScoreLibrary score.h score.c)

add_executable(mots_meles main.c)

target_link_libraries(GameLibrary m)
target_link_libraries(mots_meles GameLibrary)
target_link_libraries(StructuresLibrary m)
target_link_libraries(mots_meles StructuresLibrary)
target_link_libraries(SettingLibrary m)
target_link_libraries(mots_meles SettingLibrary)
target_link_libraries(GridLibrary m)
target_link_libraries(mots_meles GridLibrary)
target_link_libraries(ScoreLibrary m)
target_link_libraries(mots_meles ScoreLibrary)
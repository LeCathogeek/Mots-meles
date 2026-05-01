cmake_minimum_required(VERSION 4.2)
project(u_p26_etienne_pacault_jeu_de_lettres C)

set(CMAKE_C_STANDARD 99)

add_library(ToolsLibrary caisse_a_outils.h
        caisse_a_outils.c)

add_executable(u_p26_etienne_pacault_jeu_de_lettres main.c
        caisse_a_outils.h
        caisse_a_outils.c)

target_link_libraries(ToolsLibrary m)
target_link_libraries(u_p26_etienne_pacault_jeu_de_lettres ToolsLibrary)
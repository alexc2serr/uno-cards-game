cmake_minimum_required(VERSION 3.26)
project(PracticaUNO C)

set(CMAKE_C_STANDARD 11)

add_executable(PracticaUNO main.c
        card.c
        card.h
        player.c
        player.h
        game.c
        game.h)

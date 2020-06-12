TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        boxes.cpp \
        bullets.cpp \
        button.cpp \
        finish.cpp \
        game.cpp \
        game_collision.cpp \
        game_create_end_level.cpp \
        game_gracz.cpp \
        game_init.cpp \
        game_wrog.cpp \
        gun.cpp \
        main.cpp \
        player.cpp \
        randomdog.cpp \
        rifle.cpp \
        sagittarius.cpp \
        teleport.cpp \
        walls.cpp \
        weapons.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    boxes.h \
    bullets.h \
    button.h \
    finish.h \
    game.h \
    gun.h \
    player.h \
    randomdog.h \
    rifle.h \
    sagittarius.h \
    teleport.h \
    walls.h \
    weapons.h

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        boxes.cpp \
        button.cpp \
        finish.cpp \
        game.cpp \
        main.cpp \
        player.cpp \
        sagittarius.cpp \
        teleport.cpp \
        walls.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    boxes.h \
    button.h \
    finish.h \
    game.h \
    player.h \
    sagittarius.h \
    teleport.h \
    walls.h

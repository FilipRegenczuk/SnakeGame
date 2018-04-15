#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T09:42:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app

RC_ICONS = snake.ico

SOURCES += main.cpp \
    game.cpp \
    food.cpp \
    score.cpp \
    button.cpp \
    board.cpp \
    snake.cpp

HEADERS  += \
    game.h \
    food.h \
    score.h \
    button.h \
    board.h \
    snake.h

FORMS    +=

RESOURCES += \
    resource.qrc

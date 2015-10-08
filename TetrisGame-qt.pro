#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T13:20:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TetrisGame-qt
TEMPLATE = app


SOURCES += main.cpp\
        TetrisGameWindow.cpp \
    TetrisGame.cpp \
    RandomBox.cpp

HEADERS  += TetrisGameWindow.h \
    TetrisGame.h \
    RandomBox.h

FORMS    += TetrisGameWindow.ui
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    images.qrc

OTHER_FILES += \
    icon.rc

RC_FILE += icon.rc


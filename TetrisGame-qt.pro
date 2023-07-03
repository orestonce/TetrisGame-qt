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
		core/TetrisGame.cpp \
    core/RandomBox.cpp \
    core/Subject.cpp \
	gui/TetrisGameWindow.cpp

HEADERS  += core/TetrisGame.h \
    core/RandomBox.h \
    core/Subject.h \
	gui/TetrisGameWindow.h

FORMS    += gui/TetrisGameWindow.ui
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
	gui/images.qrc

OTHER_FILES += \
	gui/icon.rc \
    README.txt

RC_FILE += gui/icon.rc


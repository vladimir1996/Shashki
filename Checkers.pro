QT       += core gui

TARGET = Checkers
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chesswidget.cpp \
    checkers.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    chesswidget.h \
    checkers.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

#-------------------------------------------------
#
# Project created by QtCreator 2014-11-30T19:40:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = statisticCourseWork
TEMPLATE = app

QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    polinomdialog.cpp \
    ref_func.cpp \
    matrix_func.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    polinomdialog.h \
    reg_func.h \
    matrix_func.h

FORMS    += mainwindow.ui \
    dialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Qwt-6.1.1/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Qwt-6.1.1/lib/ -lqwtd
else:unix: LIBS += -L$$PWD/../../../../../Qwt-6.1.1/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../Qwt-6.1.1/include
DEPENDPATH += $$PWD/../../../../../Qwt-6.1.1/include

QT       += openglwidgets core gui

qmake
TARGET = ../3DViewerV2.0

pro
contains(CONFIG, windows) {
   LIBS += -lopengl32
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(gif_lib/gifimage/qtgifimage.pri)

SOURCES += \
    ../controller/controller.cc \
    ../controller/singleton.cc \
    ../model/command.cc \
    ../main.cc \
    ../model/facade.cc \
    ../model/parser.cc \
    render.cc \
    view.cc

HEADERS += \
    ../controller/controller.h \
    ../controller/singleton.h \
    ../model/command.h \
    ../model/facade.h \
    ../model/parser.h \
    render.h \
    view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#-------------------------------------------------
#
# Project created by QtCreator 2019-08-06T11:44:11
#
#-------------------------------------------------

QT       -= core gui

TARGET = ImageProcess
TEMPLATE = lib

DEFINES += IMAGEPROCESS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        imageprocess.cpp

HEADERS += \
        imageprocess.h

RC_FILE = version.rc

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    contains(QT_ARCH, i386){
        CONFIG(release, debug|release): LIBS += -L$$PWD/ -lopencv_core2413 -lopencv_highgui2413 -lopencv_imgproc2413
        CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lopencv_core2413d -lopencv_highgui2413d -lopencv_imgproc2413d
    }
    else{
    }
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

CONFIG(release, debug|release): DESTDIR += ../bin/release
CONFIG(debug, debug|release): DESTDIR += ../bin/debug

#VERSION = v2.0.0.1
QMAKE_TARGET_PRODUCT
QMAKE_TARGET_PRODUCT = "ImageProcess"
QMAKE_TARGET_COMPANY = "成都术有科技有限公司"
QMAKE_TARGET_DESCRIPTION = "文件描述"
QMAKE_TARGET_COPYRIGHT = "版权"

#-------------------------------------------------
#
# Project created by QtCreator 2019-08-06T11:56:42
#
#-------------------------------------------------

QT       -= core gui

TARGET = usbDevice
TEMPLATE = lib

CONFIG += c++11

SOURCES += \
        CyUsbEx.cpp \
        HCameraLists.cpp \
        HCameraPythonZ.cpp \
        UsbLists.cpp \
        usbdevice.cpp

HEADERS += \
        CyUsbEx.h \
        HCameraLists.h \
        HCameraPythonZ.h \
        IHCamera.h \
        IUsb.h \
        UsbLists.h \
        htdevdefs.h \
        lib/CyAPI.h \
        usbdevice.h

RC_FILE = version.rc

win32: LIBS += -L$$PWD/lib/cyusb/x86/ -lCyAPI -llegacy_stdio_definitions -luser32
else: LIBS += -L$$PWD/lib/cyusb/x64/ -lCyAPI -llegacy_stdio_definitions -luser32

INCLUDEPATH += $$PWD/lib/cyusb/include
DEPENDPATH += $$PWD/lib/cyusb/include

CONFIG(release, debug|release): DESTDIR += ../bin/release
CONFIG(debug, debug|release): DESTDIR += ../bin/debug

#VERSION = 1.0.0.0
QMAKE_TARGET_PRODUCT = "usbDevice"
QMAKE_TARGET_COMPANY = "成都术有科技有限公司"
QMAKE_TARGET_DESCRIPTION = "文件描述"
QMAKE_TARGET_COPYRIGHT = "版权"

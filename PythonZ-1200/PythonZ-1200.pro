#-------------------------------------------------
#
# Project created by QtCreator 2019-08-09T17:00:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PythonZ-1200
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        assistant.cpp \
        main.cpp \
        mainwindow.cpp \
        view.cpp

HEADERS += \
        assistant.h \
        mainwindow.h \
        view.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release): DESTDIR += ../bin/release
CONFIG(debug, debug|release): DESTDIR += ../bin/debug

RESOURCES += \
    resource.qrc

#RC_ICONS += a.ico
RC_FILE = version.rc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../bin/release/ -lImageProcess
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../bin/debug/ -lImageProcess

INCLUDEPATH += $$PWD/../ImageProcess
DEPENDPATH += $$PWD/../ImageProcess

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../bin/release/ -lusbDevice
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../bin/debug/ -lusbDevice

INCLUDEPATH += $$PWD/../usbDevice
DEPENDPATH += $$PWD/../usbDevice

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -lopencv_core2413 -lopencv_highgui2413 -lopencv_imgproc2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lopencv_core2413d -lopencv_highgui2413d -lopencv_imgproc2413d

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

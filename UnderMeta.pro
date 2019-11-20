#-------------------------------------------------
#
# Project created by QtCreator 2019-10-05T12:13:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnderMeta
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS



#Rules to find Libs in linux systems
linux-g++* | unix{

    CONFIG += link_pkgconfig
    PKGCONFIG += exiv2

}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    exivbackend.cpp \
    DarkStyle.cpp

HEADERS += \
        mainwindow.h \
    exivbackend.h \
    DarkStyle.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    mainres.qrc \
    darkstyle.qrc

### for libcomponent.a
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/material-widget/lib/release/ -lcomponents
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/material-widget/lib/debug/ -lcomponents
else:unix: LIBS += -L$$PWD/material-widget/lib/ -lcomponents

INCLUDEPATH += $$PWD/material-widget/include
DEPENDPATH += $$PWD/material-widget/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/material-widget/lib/release/libcomponents.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/material-widget/lib/debug/libcomponents.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/material-widget/lib/release/components.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/material-widget/lib/debug/components.lib
else:unix: PRE_TARGETDEPS += $$PWD/material-widget/lib/libcomponents.a
### --------------

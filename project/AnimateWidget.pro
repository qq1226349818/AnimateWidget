QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg xml

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XAnimateWidget-Roate.cpp \
    XAnimateWidget.cpp \
    XDragWidget.cpp \
    XSVGLabel.cpp \
    XSVGPushButton.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    XAnimateWidget-Roate.h \
    XAnimateWidget.h \
    XDragWidget.h \
    XSVGLabel.h \
    XSVGPushButton.h \
    widget.h

FORMS += \
    XDragWidget.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Downloads/Close.svg \
    ../Downloads/new.svg

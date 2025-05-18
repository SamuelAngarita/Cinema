QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Create.cpp \
    image.cpp \
    imagemovie.cpp \
    lists.cpp \
    main.cpp \
    mainwindow.cpp \
    moviebuilder.cpp \
    moviedirector.cpp \
    moviesgui_display.cpp \
    moviesgui_search.cpp \
    newlist.cpp \
    themovies.cpp

HEADERS += \
    Create.h \
    image.h \
    imagemovie.h \
    lists.h \
    mainwindow.h \
    moviebuilder.h \
    moviedirector.h \
    moviesgui_display.h \
    moviesgui_search.h \
    newlist.h \
    themovies.h

FORMS += \
    lists.ui \
    mainwindow.ui \
    moviesgui_display.ui \
    moviesgui_search.ui \
    newlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc

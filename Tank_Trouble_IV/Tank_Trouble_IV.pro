QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    astar.cpp \
    bullet.cpp \
    enemytank.cpp \
    gamedata.cpp \
    gameview.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pausewidget.cpp \
    playertank.cpp \
    singlegamewidget.cpp \
    tank.cpp \
    welcomewidget.cpp \
    registerdialog.cpp \
    winwidget.cpp

HEADERS += \
    astar.h \
    bullet.h \
    enemytank.h \
    gamedata.h \
    gameview.h \
    loginwidget.h \
    mainwindow.h \
    parameter.h \
    pausewidget.h \
    playertank.h \
    singlegamewidget.h \
    tank.h \
    welcomewidget.h \
    registerdialog.h \
    winwidget.h

FORMS += \
    loginwidget.ui \
    mainwindow.ui \
    pausewidget.ui \
    singlegamewidget.ui \
    welcomewidget.ui \
    registerdialog.ui \
    winwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../gameimages/gameimages.qrc

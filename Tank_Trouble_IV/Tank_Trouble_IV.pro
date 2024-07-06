QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #PlayerScene.cpp \
    bullet_s.cpp \
    gamemap.cpp \
    griditem.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pausewidget.cpp \
    #shell.cpp \
    registerdialog.cpp \
    tank.cpp \
    singlegamewidget.cpp \
    #testtank.cpp \
    welcomewidget.cpp


HEADERS += \
    #PlayerScene.h \
    bullet_s.h \
    gamemap.h \
    griditem.h \
    loginwidget.h \
    mainwindow.h \
    registerdialog.h \
    #testtank.h \
    welcomewidget.h \
    pausewidget.h \
    singlegamewidget.h \
    tank.h \
    #shell.h \

FORMS += \
    loginwidget.ui \
    mainwindow.ui \
    pausewidget.ui \
    registerdialog.ui \
    singlegamewidget.ui \
    welcomewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../gameimages/gameimages.qrc

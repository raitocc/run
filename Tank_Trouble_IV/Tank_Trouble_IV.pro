QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# release断点调试
# QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
# QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

# 禁用优化
# QMAKE_CXXFLAGS_RELEASE -= -O2
# QMAKE_CXXFLAGS_RELEASE += -O0

# 启用调试信息
# QMAKE_CXXFLAGS_RELEASE += -g



SOURCES += \
    #PlayerScene.cpp \
    bullet_s.cpp \
    enemytank.cpp \
    failedwidget.cpp \
    gamemap.cpp \
    gameview.cpp \
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
    tankturret.cpp \
    testsheel.cpp \
    welcomewidget.cpp


HEADERS += \
    #PlayerScene.h \
    bullet_s.h \
    enemytank.h \
    failedwidget.h \
    gamemap.h \
    gameview.h \
    griditem.h \
    loginwidget.h \
    mainwindow.h \
    registerdialog.h \
    #testtank.h \
    tankturret.h \
    testsheel.h \
    welcomewidget.h \
    pausewidget.h \
    singlegamewidget.h \
    tank.h
    #shell.h \

FORMS += \
    failedwidget.ui \
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
    ../gameimages/gameimages.qrc \
    login_background.qrc

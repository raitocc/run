QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    astar.cpp \
    bullet.cpp \
    double_players_game_rules_dialog.cpp \
    enemytank.cpp \
    gamedata.cpp \
    gameview.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pausewidget.cpp \
    playertank.cpp \
    single_player_game_rules_dialog.cpp \
    singlegamewidget.cpp \
    tank.cpp \
    welcomewidget.cpp \
    registerdialog.cpp \
    winwidget.cpp

HEADERS += \
    astar.h \
    bullet.h \
    double_players_game_rules_dialog.h \
    enemytank.h \
    gamedata.h \
    gameview.h \
    loginwidget.h \
    mainwindow.h \
    parameter.h \
    pausewidget.h \
    playertank.h \
    single_player_game_rules_dialog.h \
    singlegamewidget.h \
    tank.h \
    welcomewidget.h \
    registerdialog.h \
    winwidget.h

FORMS += \
    double_players_game_rules_dialog.ui \
    loginwidget.ui \
    mainwindow.ui \
    pausewidget.ui \
    single_player_game_rules_dialog.ui \
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

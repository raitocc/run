#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "pausewidget.h"
#include "singlegamewidget.h"
#include "welcomewidget.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>

#include <QStackedWidget>
#include "loginwidget.h"
#include "PlayerScene.h"
#include <QGraphicsRectItem>

/*
 * mainwindow管理各个窗口
 */
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




protected:
    void keyPressEvent(QKeyEvent *event) override;


private:
    Ui::MainWindow *ui;
    LoginWidget* mLoginWidget;//初始的登入页面
    WelcomeWidget* mWelcomeWidget;//登入成功页面
    SingleGameWidget* mSingleGameWidget;//单人游戏页面
    PauseWidget* mPauseWidget;//暂停游戏页面

    QString userName;//用户名
    QStackedWidget *stackedWidget;
    PlayerScene *playerScene;


    void setupMap();




private slots:
    void slotLogin();//登入

    void slotBackToLogin();//返回登入页面

    void slotSingleStart();//单人游戏开始

    void slotSinglePause();//单人游戏中暂停

    void slotBackToGame();//暂停页面返回游戏

    void slotExitToMenu();//退出到菜单

    void handleLoginSuccess(const QString &username);

};



#endif // MAINWINDOW_H

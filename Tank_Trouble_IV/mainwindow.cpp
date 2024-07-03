#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLoginWidget = new LoginWidget(this);
    connect(mLoginWidget,&LoginWidget::signalLogin,this,&MainWindow::slotLogin);
    userName = "NULLNULLNULLNULL";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotLogin()//登录按钮按下后处理
{
    mWelcomeWidget = new WelcomeWidget(this);
    mWelcomeWidget->show();
    userName = "Admin";
    if(mLoginWidget) delete mLoginWidget;
    connect(mWelcomeWidget,&WelcomeWidget::signalBackLogin,this,&MainWindow::slotBackToLogin);
    connect(mWelcomeWidget,&WelcomeWidget::signalSingleStart,this,&MainWindow::slotSingleStart);
}

void MainWindow::slotBackToLogin()//返回
{
    if(mWelcomeWidget) delete mWelcomeWidget;
    mLoginWidget = new LoginWidget(this);
    connect(mLoginWidget,&LoginWidget::signalLogin,this,&MainWindow::slotLogin);
    mLoginWidget->show();
    userName = "NULLNULLNULLNULL";
}

void MainWindow::slotSingleStart()//开始单人游戏
{
    if(mWelcomeWidget) delete mWelcomeWidget;
    mSingleGameWidget = new SingleGameWidget(this);
    connect(mSingleGameWidget,&SingleGameWidget::signalPause,this,&MainWindow::slotSinglePause);
    mSingleGameWidget->show();
}

void MainWindow::slotSinglePause()//单人游戏暂停
{
    mPauseWidget = new PauseWidget(this);
    mPauseWidget->show();
    connect(mPauseWidget,&PauseWidget::signalBackToGame,this,&MainWindow::slotBackToGame);
    connect(mPauseWidget,&PauseWidget::signalExitToMenu,this,&MainWindow::slotExitToMenu);
}

void MainWindow::slotBackToGame()//暂停时返回游戏
{
    if(mPauseWidget)delete mPauseWidget;
}

void MainWindow::slotExitToMenu()//暂停页面返回主菜单
{
    if(mPauseWidget)delete mPauseWidget;
    if(mSingleGameWidget)delete mSingleGameWidget;
    mWelcomeWidget = new WelcomeWidget(this);
    connect(mWelcomeWidget,&WelcomeWidget::signalBackLogin,this,&MainWindow::slotBackToLogin);
    connect(mWelcomeWidget,&WelcomeWidget::signalSingleStart,this,&MainWindow::slotSingleStart);
    mWelcomeWidget->show();
}

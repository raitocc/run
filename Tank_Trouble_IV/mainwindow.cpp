#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPointers();//所有指针置空
    mLoginWidget = new LoginWidget(this);
    connect(mLoginWidget,&LoginWidget::signalLogin,this,&MainWindow::slotLogin);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //qDebug()<<mLoginWidget<<" "<<mWelcomeWidget<<" "<<mSingleGameWidget<<" "<<mPauseWidget;
    if(mLoginWidget!=nullptr) mLoginWidget->resize(this->width(),this->height());
    if(mWelcomeWidget!=nullptr) mWelcomeWidget->resize(this->width(),this->height());
    if(mSingleGameWidget!=nullptr) mSingleGameWidget->resize(this->width(),this->height());
    if(mPauseWidget!=nullptr) mPauseWidget->resize(this->width(),this->height());
}

void MainWindow::initPointers()
{
    mWelcomeWidget = nullptr;
    mLoginWidget = nullptr;
    mSingleGameWidget = nullptr;
    mPauseWidget = nullptr;
}

void MainWindow::slotLogin()//登录按钮按下后处理
{
    mWelcomeWidget = new WelcomeWidget(this);
    mWelcomeWidget->show();
    if(mLoginWidget) delete mLoginWidget;
    mLoginWidget = nullptr;
    connect(mWelcomeWidget,&WelcomeWidget::signalBackLogin,this,&MainWindow::slotBackToLogin);
    connect(mWelcomeWidget,&WelcomeWidget::signalSingleStart,this,&MainWindow::slotSingleStart);
}

void MainWindow::slotBackToLogin()//返回
{
    if(mWelcomeWidget) delete mWelcomeWidget;
    mWelcomeWidget = nullptr;
    mLoginWidget = new LoginWidget(this);
    connect(mLoginWidget,&LoginWidget::signalLogin,this,&MainWindow::slotLogin);
    mLoginWidget->show();
    userName = "";
}

void MainWindow::slotSingleStart()//开始单人游戏
{
    if(mWelcomeWidget) delete mWelcomeWidget;
    mWelcomeWidget = nullptr;
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
    mPauseWidget = nullptr;
}

void MainWindow::slotExitToMenu()
{
    if(mPauseWidget)delete mPauseWidget;
    mPauseWidget = nullptr;
    if(mSingleGameWidget)delete mSingleGameWidget;
    mSingleGameWidget = nullptr;
    mWelcomeWidget = new WelcomeWidget(this);
    connect(mWelcomeWidget,&WelcomeWidget::signalBackLogin,this,&MainWindow::slotBackToLogin);
    connect(mWelcomeWidget,&WelcomeWidget::signalSingleStart,this,&MainWindow::slotSingleStart);
    mWelcomeWidget->show();
}

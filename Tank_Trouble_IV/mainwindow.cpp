#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "loginwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    stackedWidget(new QStackedWidget(this)),
    playerScene(new PlayerScene(this))
{
    ui->setupUi(this);
    mLoginWidget = new LoginWidget(this);
    stackedWidget->addWidget(mLoginWidget);
     // 连接登录成功信号到处理槽
    connect(mLoginWidget,&LoginWidget::signalLogin,this,&MainWindow::slotLogin);
    userName = "NULLNULLNULLNULL";
    // 设置堆栈窗口为中心窗口
    setCentralWidget(stackedWidget);


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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 处理键盘事件逻辑
    QMainWindow::keyPressEvent(event); // 调用基类的实现，如果需要的话
}


void MainWindow::handleLoginSuccess(const QString &username)
{
    qDebug() << "Login successful! Username:" << username;

    // 移除登录界面
    stackedWidget->removeWidget(stackedWidget->currentWidget());

    // 添加并显示地图界面
    stackedWidget->addWidget(playerScene);
    stackedWidget->setCurrentWidget(playerScene);

    // 加载地图图片，这里使用 QPixmap 加载地图图片，具体根据你的需求和地图数据来修改
    QPixmap mapPixmap(":/images/map_image.png"); // 使用资源文件加载地图图片

    // 设置地图显示
    playerScene->setMap(mapPixmap);
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

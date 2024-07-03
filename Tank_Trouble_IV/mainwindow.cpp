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
    if(mLoginWidget) delete mLoginWidget;
}

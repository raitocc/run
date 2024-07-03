#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_pushButton_clicked()
{
    //按钮按下发送对应信号
    emit signalLogin();
}


void LoginWidget::on_btnExit_clicked()
{
    //提示确认是否退出
    if(QMessageBox::Yes == QMessageBox::question(0, tr("Exit"),QString(tr("Exit the Game?")),QMessageBox::Yes | QMessageBox::No))
    {
        this->parentWidget()->close();
    }
}


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
    emit signalLogin();
}


void LoginWidget::on_btnExit_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(0, tr("Exit"),QString(tr("Exit the Game?")),QMessageBox::Yes | QMessageBox::No))
    {
        this->parentWidget()->close();
    }
}


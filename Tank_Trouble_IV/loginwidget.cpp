#include "loginwidget.h"
#include "registerdialog.h"
#include "ui_loginwidget.h"
#include <QFile>

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

void LoginWidget::on_pushButton_clicked()//登录按钮按下
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if(isLoginValid(username, password))
    {
        // 执行登录成功后的逻辑
        emit signalLogin();
    }
    else
    {
        QMessageBox::warning(this, tr("Login Error"), tr("Invalid username or password."));
    }
}


void LoginWidget::on_btnExit_clicked()
{
    //提示确认是否退出
    if(QMessageBox::Yes == QMessageBox::question(0, tr("Exit"),QString(tr("Exit the Game?")),QMessageBox::Yes | QMessageBox::No))
    {
        this->parentWidget()->close();
    }
}


void LoginWidget::on_btnRegister_clicked()//弹出注册对话框
{
    RegisterDialog registerDialog(this);
    registerDialog.exec();
}

bool LoginWidget::isLoginValid(const QString &username, const QString &password)//验证用户名与密码
{
    QFile file("userdata.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if(parts.size() == 2 && parts[0] == username && parts[1] == password)
            {
                return true;
            }
        }
        file.close();
    }
    return false;
}


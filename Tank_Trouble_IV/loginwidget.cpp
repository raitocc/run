#include "loginwidget.h"
#include "registerdialog.h"
#include "ui_loginwidget.h"
#include <QFile>

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    // 创建并配置数据库连接

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("rm-cn-j4g3tbaf00003b.rwlb.rds.aliyuncs.com");
    db.setPort(3306);
    db.setDatabaseName("ali");
    db.setUserName("yrxY");
    db.setPassword("Yrx200555");

    // 尝试打开数据库连接
    if (db.open()) {
        qDebug() << "数据库连接成功";

    } else {
        qDebug() << "数据库连接失败:" << db.lastError().text();
    }
}

LoginWidget::~LoginWidget()
{
    // 关闭数据库连接
    QSqlDatabase::database().close();
    delete ui;
}

void LoginWidget::paintevent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/login_background.png"));
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

bool LoginWidget::isLoginValid(const QString &new_username, const QString &new_password)//验证用户名与密码
{
    // 连接数据库
    QSqlDatabase db = QSqlDatabase::database(); // 获取默认数据库连接

    // 准备SQL查询语句
    QSqlQuery query;

    // 执行查询
    if (query.exec("SELECT password FROM users WHERE username = '" + new_username + "' AND password = '" + new_password + "'")) {
        if (query.next()) {
            // 获取数据库中的加密密码
            QString storedPassword = query.value(0).toString();
            // 比较两个密码是否一致
            if (storedPassword == new_password) {
                qDebug() << "登录成功";
                // 关闭数据库连接
                db.close();
                return true;
            }
        }
    }

    qDebug() << "查询失败:" << query.lastError().text();
    // 关闭数据库连接
    db.close();
    return false;
}


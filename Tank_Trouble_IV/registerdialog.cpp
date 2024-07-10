#include "registerdialog.h"
#include "qevent.h"
#include "ui_registerdialog.h"


RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Register");

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

    // //创建表
    // QSqlQuery query;
    // if (query.exec("CREATE TABLE users ("
    //                "username VARCHAR(50) NOT NULL,"
    //                "password VARCHAR(255) NOT NULL,"
    //                "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
    //                ")")) {
    //     qDebug() << "表创建成功";
    // } else {
    //     qDebug() << "创建表失败:" << query.lastError().text();
    // }

    // QSqlQuery query;
    // query.exec("insert into users(username,password) values('mike',1)");
}

RegisterDialog::~RegisterDialog()
{
    // 关闭数据库连接
    QSqlDatabase::database().close();
    delete ui;
}

void RegisterDialog::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setOpacity(0.5);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/background/login_background.png"));
}

void RegisterDialog::closeEvent(QCloseEvent *event)//关闭事件
{
    if(!ui->usernameLineEdit->text().isEmpty() || !ui->passwordLineEdit->text().isEmpty() || !ui->confirmPasswordLineEdit->text().isEmpty())
    {
        int ret = QMessageBox::warning(this, tr("Unsaved Changes"),
                                       tr("You have unsaved changes. Are you sure you want to close?"),
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::No);
        if(ret == QMessageBox::No)
        {
            event->ignore();//阻止关闭
            return;
        }
    }
    event->accept();
}

bool RegisterDialog::isInputValid()//输入是否合法
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    if(username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty())
    {
        QMessageBox::warning(this, tr("Input Error"), tr("All fields are required."));
        return false;
    }

    if(password != confirmPassword)
    {
        QMessageBox::warning(this, tr("Input Error"), tr("Passwords do not match."));
        return false;
    }

    return true;
}

bool RegisterDialog::isUserRegistered(const QString &username)//用户名是否已经被注册过
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username",username);
    if(query.exec()){
        if(query.next()){
            int count = query.value(0).toInt();
            if(count>0){
                //用户名已存在
                qDebug() << "该用户名已被注册";
                return true;
            }
        }
    }
    return false;
}

void RegisterDialog::on_registerButton_clicked()//注册按钮按下
{
    if(isInputValid())
    {
        QString new_username = ui->usernameLineEdit->text();
        QString new_password = ui->passwordLineEdit->text();

        // 检查用户是否已存在
        if(isUserRegistered(new_username))
        {
            QMessageBox::warning(this, tr("Registration Error"), tr("Username already registered."));
            return;
        }

        // 将新用户信息写入文件
        QSqlQuery query;
        if (query.exec("insert into users (username, password) values ('" + new_username + "', '" + new_password + "')")) {
            qDebug() << "用户注册成功";
            QMessageBox::information(this, tr("Registration"), tr("Registration Successful!"));
            accept();
        }
        else {
            qDebug() << "用户注册失败:" << query.lastError().text();
        }
    }
    else {
        qDebug() << "无法打开数据库连接";
    }

}

void RegisterDialog::on_cancelButton_clicked()
{
    this->close();
}


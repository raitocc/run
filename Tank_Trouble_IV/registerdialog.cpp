#include "registerdialog.h"
#include "qevent.h"
#include "ui_registerdialog.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Register");
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
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
    QFile file("userdata.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if(parts.size() == 2 && parts[0] == username)
            {
                return true;
            }
        }
        file.close();
    }
    return false;
}

void RegisterDialog::on_registerButton_clicked()//注册按钮按下
{
    if(isInputValid())
    {
        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        // 检查用户是否已存在
        if(isUserRegistered(username))
        {
            QMessageBox::warning(this, tr("Registration Error"), tr("Username already registered."));
            return;
        }

        // 将新用户信息写入文件
        QFile file("userdata.txt");
        if(file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&file);
            out << username << "," << password << "\n";
            file.close();
            QMessageBox::information(this, tr("Registration"), tr("Registration Successful!"));
            accept();
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Could not open file for writing."));
        }
    }

}


void RegisterDialog::on_cancelButton_clicked()
{
    this->close();
}


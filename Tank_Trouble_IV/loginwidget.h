#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QPainter>
#include "QMessageBox"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void paintevent(QPaintEvent * event);

private slots:
    void on_pushButton_clicked();

    void on_btnExit_clicked();

    void on_btnRegister_clicked();

private:
    bool isLoginValid(const QString &username, const QString &password); // 验证用户名与密码

public:
    Ui::LoginWidget *ui;

signals:
    void signalLogin();
};

#endif // LOGINWIDGET_H

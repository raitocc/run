#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

protected:
    void closeEvent(QCloseEvent *event) override; // 添加 closeEvent 函数

private slots:
    void on_registerButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::RegisterDialog *ui;

    bool isInputValid();//输入是否合法

    bool isUserRegistered(const QString &username);//用户名不能重名
};

#endif // REGISTERDIALOG_H

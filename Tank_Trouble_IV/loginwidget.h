#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
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

private slots:
    void on_pushButton_clicked();

    void on_btnExit_clicked();

public:
    Ui::LoginWidget *ui;

signals:
    void signalLogin();
};

#endif // LOGINWIDGET_H

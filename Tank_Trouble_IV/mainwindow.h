#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "singlegamewidget.h"
#include "welcomewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginWidget* mLoginWidget;
    WelcomeWidget* mWelcomeWidget;
    SingleGameWidget* mSingleGameWidget;

    QString userName;

private slots:
    void slotLogin();

    void slotBackToLogin();

    void slotSingleStart();
};
#endif // MAINWINDOW_H

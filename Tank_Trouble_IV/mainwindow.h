#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "pausewidget.h"
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

protected:

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    LoginWidget* mLoginWidget;
    WelcomeWidget* mWelcomeWidget;
    SingleGameWidget* mSingleGameWidget;
    PauseWidget* mPauseWidget;

    QString userName;

    void initPointers();//初始化指针

private slots:
    void slotLogin();

    void slotBackToLogin();

    void slotSingleStart();

    void slotSinglePause();

    void slotBackToGame();

    void slotExitToMenu();
};
#endif // MAINWINDOW_H

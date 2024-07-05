#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();

private slots:

    void on_btnBack_clicked();

    void on_btnSingle_clicked();

signals:
    void signalBackLogin();

    void signalSingleStart();

public:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H

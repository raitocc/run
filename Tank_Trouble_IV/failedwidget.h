#ifndef FAILEDWIDGET_H
#define FAILEDWIDGET_H

#include <QWidget>

namespace Ui {
class FailedWidget;
}

class FailedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FailedWidget(QWidget *parent = nullptr);
    ~FailedWidget();

private slots:
    void on_btnRestart_clicked();

    void on_btnBackToMenu_clicked();

signals:
    void signalRestart();

    void signalBack();

private:
    Ui::FailedWidget *ui;
};

#endif // FAILEDWIDGET_H

#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>
#include "QMessageBox"

namespace Ui {
class PauseWidget;
}

class PauseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PauseWidget(QWidget *parent = nullptr);
    ~PauseWidget();

private slots:
    void on_btnBack_clicked();

    void on_btnExit_clicked();

private:
    Ui::PauseWidget *ui;

signals:
    void signalBackToGame();

    void signalExitToMenu();
};

#endif // PAUSEWIDGET_H

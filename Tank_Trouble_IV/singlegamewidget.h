#ifndef SINGLEGAMEWIDGET_H
#define SINGLEGAMEWIDGET_H

#include <QWidget>
#include "gamedata.h"

namespace Ui {
class SingleGameWidget;
}

class SingleGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGameWidget(QWidget *parent = nullptr);
    ~SingleGameWidget();

    void newGame();
private slots:
    void on_btnPause_clicked();

private:
    Ui::SingleGameWidget *ui;
    GameData* data;

signals:
    void signalPause();
};

#endif // SINGLEGAMEWIDGET_H

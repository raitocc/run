#ifndef SINGLEGAMEWIDGET_H
#define SINGLEGAMEWIDGET_H

#include <QWidget>
#include "gamemap.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QGraphicsRectItem>
//#include "testtank.h"
#include <QKeyEvent>
#include <QTimer>


namespace Ui {
class SingleGameWidget;
}

class SingleGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGameWidget(QWidget *parent = nullptr);
    ~SingleGameWidget();

    void drawMap();
    bool eventFilter(QObject *watched, QEvent *event);
    void setViewFocus();//设置视图为其焦点

public slots:
    void on_btnPause_clicked();

    void advance();

    void slotFailed();//游戏失败

private:
    Ui::SingleGameWidget *ui;
    GameMap map;
    QGraphicsScene* scene;

    //testTank* tank;

    QTimer* timer;

    void centerViewOnTank();


signals:
    void signalPause();
};

#endif // SINGLEGAMEWIDGET_H

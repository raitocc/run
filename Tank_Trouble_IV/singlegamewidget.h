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

public slots:
    void on_btnPause_clicked();

    void advance();

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

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
    double msx;
    double msy;
    explicit SingleGameWidget(QWidget *parent = nullptr);
    ~SingleGameWidget();

    void drawMap();
    bool eventFilter(QObject *watched, QEvent *event);
    //鼠标
    void mouseMoveEvent(QMouseEvent *event) ;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setViewFocus();//设置视图为其焦点public slots:
    void on_btnPause_clicked();
    void advance();

protected:

private:
    Ui::SingleGameWidget *ui;
    GameMap map;
    QGraphicsScene* scene;

    //testTank* tank;

    QTimer* timer;

    void centerViewOnTank();
    void setInitGraphicView();

private slots:
    //void slotMouseMove(QMouseEvent* event);
    //void slotMousePress(QMouseEvent* event);

signals:
    void signalPause();
};

#endif // SINGLEGAMEWIDGET_H

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(QWidget *parent);

    void wheelEvent(QWheelEvent *event);


    // void mouseMoveEvent(QMouseEvent *event);
    // void mousePressEvent(QMouseEvent *event);

// signals:
//     void signalMouseMove(QMouseEvent *event);
//     void signalMousePress(QMouseEvent *event);
};

#endif // GAMEVIEW_H

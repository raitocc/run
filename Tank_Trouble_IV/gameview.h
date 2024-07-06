#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QWidget>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event);

signals:
};

#endif // GAMEVIEW_H

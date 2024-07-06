#ifndef BULLET_H
#define BULLET_H

#include "tank.h"
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>

class testSheel : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    testSheel(tank* shooter, QPointF startPos, QPointF targetPos);
    void move();

private:
    qreal speed;
    QPointF direction;
    tank* shooter;

public slots:
    void onMove();

signals:
    void hitTarget(QGraphicsItem* target);
};

#endif // BULLET_H

// bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QPointF startPos, qreal angle, qreal speed, QGraphicsScene *scene);
    ~Bullet();

private slots:
    void move();

private:
    QTimer *timer;
    qreal angle;
    qreal speed;
};

#endif // BULLET_H



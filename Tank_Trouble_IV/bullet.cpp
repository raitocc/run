// bullet.cpp
#include "bullet.h"
#include <QtMath>

Bullet::Bullet(QPointF startPos, qreal angle, qreal speed, QGraphicsScene *scene)
    : angle(angle), speed(speed)
{
    setPixmap(QPixmap(":/new/prefix1/bullet.png"));
    setPos(startPos);
    scene->addItem(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(1000 / 60); // 60 FPS
}

Bullet::~Bullet()
{
    delete timer;
}

void Bullet::move()
{
    qreal dx = speed * qCos(qDegreesToRadians(angle));
    qreal dy = speed * qSin(qDegreesToRadians(angle));
    moveBy(dx, dy);

    if (!scene()->sceneRect().contains(pos())) {
        scene()->removeItem(this);
        delete this;
    } else {
        QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
        for (QGraphicsItem *item : collidingItems) {
            if (QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item)) {
                if (rectItem->brush().color() == Qt::black) {
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
            }
        }
    }
}

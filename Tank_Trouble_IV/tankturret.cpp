#include "tankturret.h"

TankTurret::TankTurret(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), targetDirection(0, 0)
{
    // 初始化时可以设置一个默认的贴图
    setPixmap(QPixmap(":/new/prefix1/TankTurret.png"));
    this->setTransformOriginPoint(3,12);
}

void TankTurret::setDirection(int tankRotation, const QPointF &direction)
{
    qreal angle = std::atan2(direction.y(), direction.x()) * 180 / M_PI;
    this->setRotation(angle-tankRotation+90);
}


void TankTurret::setPixmap(const QPixmap &pixmap)
{
    QGraphicsPixmapItem::setPixmap(pixmap);
}

// void TankTurret::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
// {
//     // Update the turret's direction based on mouse movement
//     QPointF scenePos = event->scenePos();
//     setDirection(scenePos - pos());
//     QGraphicsPixmapItem::mouseMoveEvent(event);
// }

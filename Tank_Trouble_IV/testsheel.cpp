#include "testsheel.h"
#include <QtMath>

testSheel::testSheel(tank *shooter, QPointF startPos, QPointF targetPos)
    : QObject(), QGraphicsRectItem()
{
    setRect(0, 0, 5, 5);
    setPos(startPos);

    this->shooter = shooter;

    // 计算方向向量
    QLineF line(startPos, targetPos);
    direction = line.unitVector().p2() - line.unitVector().p1();
    speed = 1; // 可以调整子弹速度

    qDebug() << "子弹生成位置：" << startPos << " 目标位置：" << targetPos;
    qDebug() << "方向向量：" << direction;

        QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &testSheel::onMove);
    timer->start(16); // 大约60 FPS
}

void testSheel::move()
{
    setPos(mapToScene(direction * speed));

    qDebug() << "子弹当前位置：" << pos();

    // 检查碰撞
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item);
        // 确保子弹不会与发射者（坦克）自己碰撞，并且碰到除了空白元素（白色）外的任何其他物体时被删除
        if (item != this && item != shooter && (rectItem == nullptr || rectItem->brush().color() != Qt::white)) {
            emit hitTarget(item);
            qDebug() << "子弹碰撞";
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // 如果子弹超出场景边界，则删除它
    if (!scene()->sceneRect().contains(this->pos())) {
        qDebug() << "子弹超出场景边界";
        scene()->removeItem(this);
        delete this;
    }
}


void testSheel::onMove()
{
    move();
}

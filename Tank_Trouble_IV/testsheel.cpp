#include "testsheel.h"
#include <QtMath>

testSheel::testSheel(tank *shooter, QPointF startPos, QPointF targetPos)
    : QObject(), QGraphicsRectItem()
{
    setRect(2, 6, 5, 5);

    this->shooter = shooter;
    this->setBrush(QBrush(Qt::red));
    // 计算方向向量
    QLineF line(startPos, targetPos);
    direction = line.unitVector().p2() - line.unitVector().p1();
    speed = 1.5; // 可以调整子弹速度
    QPointF bias = direction * 12;
    setPos(startPos+bias);

    //qDebug() << "子弹生成位置：" << startPos << " 目标位置：" << targetPos;
    //qDebug() << "方向向量：" << direction;

    //QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &testSheel::onMove);
    //timer->start(16); // 大约60 FPS
}

void testSheel::move()
{
    setPos(mapToScene(direction * speed));

    //qDebug() << "子弹当前位置：" << pos();

    // 检查碰撞
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item);
        // 确保子弹不会与发射者（坦克）自己碰撞，并且碰到除了空白元素（白色）外的任何其他物体时被删除(1是key，右边的==1的1是value，1代表可破坏墙体)
        if (rectItem && rectItem->data(1)==1) {
            // 子弹碰到可破坏墙体
            //qDebug()<<"子弹撞箱子了";
            rectItem->setBrush(QBrush(Qt::white));
            rectItem->setData(1,2);
            scene()->removeItem(this);
            delete this;
            return;
        }
        if (item != this && item != shooter && (rectItem == nullptr || rectItem->brush().color() != Qt::white ) && item!=shooter->getTurret()) {
            emit hitTarget(item);
            //qDebug() << "子弹碰撞";
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // 如果子弹超出场景边界，则删除它
    if (!scene()->sceneRect().contains(this->pos())) {
        //qDebug() << "子弹超出场景边界";
        scene()->removeItem(this);
        delete this;
    }
}

tank* testSheel::getShooter()
{
    return shooter;
}


void testSheel::onMove()
{
    move();
}

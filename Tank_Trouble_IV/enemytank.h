// enemytank.h
#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QObject>
#include <QRect>
#include <QGraphicsItem>
#include <QPointF>
#include<Qqueue>
#include "gamemap.h"  // 包含地图类头文件

class EnemyTank : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EnemyTank(QObject *parent = nullptr);
    EnemyTank(int x, int y, int health, QObject *parent = nullptr);

    QRect getRect() const;
    void setRect(const QRect &value);

    int getHealth() const;
    void setHealth(int value);

    bool isAlive() const;
        void move(const QPointF &playerPos);  // 敌方坦克移动函数
    void attackPlayer();  // 敌方坦克攻击玩家函数，信号槽连接实现

signals:
    void tankDestroyed();

public slots:
    void takeDamage(int damage);

private:
    QRect rect;
    int health;
     GameMap *map;  // 地图对象指针
};

#endif // ENEMYTANK_H

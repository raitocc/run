#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "tank.h" // 引入基类 Tank 的头文件
#include <QPen>

class EnemyTank : public Tank
{
public:
    EnemyTank(int initialBulletID, QGraphicsItem* parent = nullptr);

    int bulletID() const;
    int id() const;

    void setBulletID(int bulletID);//设置tankID的函数
    void setID(int id);
    void init();

    void fire();//射击子弹

private:
    int _bulletID;
    QPointF _rotationCenter;
    int _id;

};

#endif // ENEMYTANK_H

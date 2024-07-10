#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "tank.h" // 引入基类 Tank 的头文件

class EnemyTank : public Tank
{
public:
    EnemyTank(int initialBulletID,QGraphicsItem* parent = nullptr);

    int bulletID() const;
     void setBulletID(int bulletID);//设置tankID的函数

private:
    int _bulletID;
};

#endif // ENEMYTANK_H

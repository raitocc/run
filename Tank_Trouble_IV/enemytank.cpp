#include "enemytank.h"

EnemyTank::EnemyTank(int initialBulletID,QGraphicsItem* parent)
    : Tank(parent) // 初始化 _bulletID 为 0
{
    setBulletID(initialBulletID);
}

int EnemyTank::bulletID() const
{
    return _bulletID;
}

#include "enemytank.h"
#include "parameter.h"

EnemyTank::EnemyTank(int initialBulletID,QGraphicsItem* parent)
    : Tank(parent) // 初始化 _bulletID 为 0
{
    setBulletID(initialBulletID);
    init();
}

int EnemyTank::bulletID() const
{
    return _bulletID;
}

int EnemyTank::id() const
{
    return _id;
}

void EnemyTank::setBulletID(int bulletID)
{
    _bulletID = bulletID;
}

void EnemyTank::setID(int id)
{
    _id = id;
}

void EnemyTank::init()
{
    this->setPen(Qt::NoPen);//设置无边框

    //设置数值
    _HP = 20;
    _maxHP = 20;
    _moveSpeed = 0.8;
    _shootSpeed = 1;
    clearMovingState();//清空移动状态标记
    _turret = nullptr;
    _rotationCenter = QPointF(TANK_WIDTH/2,TANK_LENGTH*2/3);

    //z
    this->setZValue(3);

    this->setRect(0,0,TANK_WIDTH,TANK_LENGTH);//设置碰撞箱
    this->setTransformOriginPoint(_rotationCenter);//设置旋转中心


    //绘制炮筒
    this->creatTurret();
}

void EnemyTank::fire()
{

}

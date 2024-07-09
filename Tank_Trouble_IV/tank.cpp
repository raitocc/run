#include "tank.h"
//#include "turret.h" // 还没有有Turret类的头文件

// 构造函数
Tank::Tank(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    _HP = 100;
    _maxHP = 100;
    _moveSpeed = 5;
    _shootSpeed = 1;
    for (int i = 0; i < 4; ++i)
    {
        _movingState[i] = false;
    }
    _turret = nullptr;
}

// 获取血量
int Tank::HP() const
{
    return _HP;
}

// 获取移动速度
int Tank::moveSpeed() const
{
    return _moveSpeed;
}

// 获取射击速度
int Tank::shootSpeed() const
{
    return _shootSpeed;
}

// 获得移动状态
bool Tank::movingState(int dir) const
{
    return _movingState[dir];
}

// 获取炮塔
Turret* Tank::turret() const
{
    return _turret;
}

// 设置血量
void Tank::setHP(int hp)
{
    _HP = hp;
}

// 设置最大血量
void Tank::setMaxHP(int maxHP)
{
    _maxHP = maxHP;
}

// 增加血量
void Tank::addHP(int num)
{
    _HP += num;
    if (_HP > _maxHP) {
        _HP = _maxHP;
    }
}

// 减少血量
void Tank::reduceHP(int num)
{
    _HP -= num;
    if (_HP < 0) {
        _HP = 0;
    }
}

// 设置移动速度
void Tank::setMoveSpeed(int moveSpeed)
{
    _moveSpeed = moveSpeed;
}

// 设置射击速度
void Tank::setShootSpeed(int shootSpeed)
{
    _shootSpeed = shootSpeed;
}

// 设置移动状态
void Tank::setMovingState(int dir,bool state)
{
    _movingState[dir] = state;
    // for(int i=0;i<4;i++)
    // {
    //     qDebug()<<_movingState[i];
    // }
}

// 设置炮筒
void Tank::setTurret(Turret* turret)
{
    _turret = turret;
}

QPointF Tank::centerPoint()
{
    return QPointF(this->rect().center());
}



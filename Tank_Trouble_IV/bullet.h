#ifndef BULLET_H
#define BULLET_H

#include "tank.h"
#include <QGraphicsRectItem>

class Bullet : public QGraphicsRectItem
{
public:
    Bullet();//构造函数

    //get类
    int id() const;
    int damage() const;
    int speed() const;
    const QLineF &direction() const;
    Tank* shooter() const;//发射该子弹的坦克

    //设置类
    void setId(int id);
    void setDamage(int damage);
    void setSpeed(int speed);
    void setDirection(const QLineF& direction);

private:
    int _id;//标识子弹类型id
    int _damage;//伤害
    int _speed;//移动速度
    QLineF _direction;//方向向量
    Tank* _shooter;
};

#endif // BULLET_H

#ifndef BULLET_H
#define BULLET_H

#include "tank.h"
#include <QtMath>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsScene>

class Bullet : public QGraphicsRectItem
{
public:
    Bullet(int id,Tank* shooter);//构造函数
    Bullet(int id,Tank* shooter,QPointF begin,QPointF tar);//构造函数

    //get类
    int id() const;
    int damage() const;
    int speed() const;
    const QPointF &direction() const;
    Tank* shooter() const;//发射该子弹的坦克

    //设置类
    void setId(int id);
    void setDamage(int damage);
    void setSpeed(double speed);
    void setDirection(const QPointF &direction);

    void init();//初始化
    void init(QPointF begin, QPointF tar);//初始化

private:
    int _id;//标识子弹类型id
    int _damage;//伤害
    double _speed;//移动速度
    QPointF _direction;//方向向量
    Tank* _shooter;
    void advance(int phase) override;
    void move();//移动
    bool checkCollision();//检查碰撞
    void hitBox(QGraphicsRectItem* box);
    void hitTank(Tank* tank);
};

class BulletSupply :public QGraphicsRectItem
{
public:
    BulletSupply(int id, int num, QPointF pos);

    // int id() const;
    // int num() const;

    // void setId(int id);
    // void setNum(int num);
private:
    int _id;
    int _num;
};

#endif // BULLET_H

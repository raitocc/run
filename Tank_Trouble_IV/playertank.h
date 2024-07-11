#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include "tank.h"
#include <QVector>
#include <QPen>

class PlayerTank : public Tank
{
public:
    PlayerTank();

public:
    //get类函数
    int bulletNum(int id);
    int propsNum(int id) const;
    int currentBullet() const;
    QPointF rotationCenter() const;
    bool shootAble() const;

    //设置类
    void switchBullet(int id);
    void addBullet(int id, int amout);
    void removeBullet(int id, int amout);
    void setShootAble(bool f);
    void init();//初始化


    //void fire(QPointF tarPos);//发射子弹

    void update();//由View定时器调用




protected:
    //void keyPressEvent(QKeyEvent* event) override;
    //void keyReleaseEvent(QKeyEvent* event) override;
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    //void advance(int phase) override;

private:
    QVector<int> _bulletNum;//剩余子弹数（只标识非子弹，由唯一id标识）
    QVector<int> _propsNum;//游戏道具剩余数量
    int _currentBullet;//现在携带的子弹
    QPointF _center;
    QPointF _rotationCenter;

    bool _shootAble;

    void handleCollision();//解决吃道具

private slots:
    void reetShootAbleState();


};

#endif // PLAYERTANK_H

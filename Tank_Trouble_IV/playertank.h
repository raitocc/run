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

    //设置类
    void switchBullet(int id);
    void addBullet(int id, int amout);
    void removeBullet(int id, int amout);
    void init();//初始化
    void clearMovingState();//清空移动



protected:
    //void keyPressEvent(QKeyEvent* event) override;
    //void keyReleaseEvent(QKeyEvent* event) override;
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void advance(int phase) override;

private:
    QVector<int> _bulletNum;//剩余子弹数（只标识非子弹，由唯一id标识）
    QVector<int> _propsNum;//游戏道具剩余数量
    int _currentBullet;//现在携带的子弹
    QPointF _center;
    QPointF _rotationCenter;

    void move();//移动
    bool checkCollision();//检查是否碰撞
    void adjustPosition();//卡墙调整函数
    void updateDirection();//旋转坦克
};

#endif // PLAYERTANK_H

#ifndef TANK_H
#define TANK_H

#include <QGraphicsRectItem>

class Turret; // 假设有Turret类

class Tank : public QGraphicsRectItem
{
public:
    Tank(QGraphicsItem* parent = nullptr);

    int HP() const;
    int moveSpeed() const;
    int shootSpeed() const;
    bool movingState(int dir) const;
    Turret* turret() const;

    void setHP(int hp);
    void setMaxHP(int maxHP);
    void addHP(int num);
    void reduceHP(int num);
    void setMoveSpeed(int moveSpeed);
    void setShootSpeed(int shootSpeed);
    void setMovingState(int dir, bool state);
    void setTurret(Turret* turret);
    QPointF centerPoint();//中心点

protected:
    int _HP;
    int _maxHP;
    qreal _moveSpeed;
    qreal _shootSpeed;
    bool _movingState[4];
    Turret* _turret;


};

#endif // TANK_H

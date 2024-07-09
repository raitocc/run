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
    bool movingState() const;
    Turret* turret() const;

    void setHP(int hp);
    void setMaxHP(int maxHP);
    void addHP(int num);
    void reduceHP(int num);
    void setMoveSpeed(int moveSpeed);
    void setShootSpeed(int shootSpeed);
    void setMovingState(const int movingState[4]);
    void setTurret(Turret* turret);

protected:
    int _HP;
    int _maxHP;
    int _moveSpeed;
    int _shootSpeed;
    bool _movingState[4];
    Turret* _turret;
};

#endif // TANK_H

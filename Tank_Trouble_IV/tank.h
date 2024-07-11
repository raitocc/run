#ifndef TANK_H
#define TANK_H


#include <QGraphicsRectItem>

class Tank;
class GameData;

class Turret:public QGraphicsRectItem
{
public:
    Turret(Tank *parent = nullptr);
    void setDirection(const QPointF &target);
    Tank* parentTank() const;

private:
    Tank* _parentTank;
};

class Tank : public QGraphicsRectItem
{
public:
    Tank(QGraphicsItem* parent = nullptr);

    int HP() const;
    int moveSpeed() const;
    int shootSpeed() const;
    bool movingState(int dir) const;
    Turret* turret() const;
    GameData *gameData() const;

    void setHP(int hp);
    void setMaxHP(int maxHP);
    void addHP(int num);
    void reduceHP(int num);
    void setMoveSpeed(int moveSpeed);
    void setShootSpeed(int shootSpeed);
    void setMovingState(int dir, bool state);
    void setTurret(Turret* turret);
    void setGameData(GameData* data);
    void clearMovingState();//清空移动数据


    void creatTurret();

protected:
    int _HP;
    int _maxHP;
    qreal _moveSpeed;
    qreal _shootSpeed;
    bool _movingState[4];
    Turret* _turret;
    GameData *_data;


    void move();//移动
    bool checkCollision();//检查是否碰撞
    void adjustPosition(QPointF oldPos);//卡墙调整函数
    void updateDirection();//旋转坦克
    void advance(int phase) override;


};

#endif // TANK_H

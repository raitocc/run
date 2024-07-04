#ifndef TESTTANK_H
#define TESTTANK_H

#include "gamemap.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>

#define tankLength 30

class testTank : public QGraphicsRectItem
{
public:
    testTank(GameMap *gameMap);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void advance();

private:
    bool movingUp, movingDown, movingLeft, movingRight;
    void updateDirection();
    bool checkCollision();
    void setRandomInitialPosition(GameMap *gameMap); // 设置随机初始位置

    qreal speed;
    qreal rotationAngle;
    QGraphicsEllipseItem *head; // 坦克头部
};

#endif // TANK_H

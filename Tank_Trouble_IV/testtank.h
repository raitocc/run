#ifndef TESTTANK_H
#define TESTTANK_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

#define tankLength 30

class testTank : public QGraphicsRectItem
{
public:
    testTank();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void advance();

private:
    bool movingUp, movingDown, movingLeft, movingRight;
    void updateDirection();

    qreal speed;
    qreal rotationAngle;
};

#endif // TANK_H

#include "testtank.h"
#include <QBrush>
#include <QGraphicsScene>

testTank::testTank()
    : movingUp(false), movingDown(false), movingLeft(false), movingRight(false), speed(2.0), rotationAngle(0)
{
    setRect(0, 0, tankLength * 2 / 3, tankLength);
    setBrush(QBrush(Qt::red));
    setTransformOriginPoint(this->rect().width()/2,this->rect().height()/2);
}

void testTank::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        movingUp = true;
        break;
    case Qt::Key_S:
        movingDown = true;
        break;
    case Qt::Key_A:
        movingLeft = true;
        break;
    case Qt::Key_D:
        movingRight = true;
        break;
    default:
        break;
    }
    updateDirection();
}

void testTank::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        movingUp = false;
        break;
    case Qt::Key_S:
        movingDown = false;
        break;
    case Qt::Key_A:
        movingLeft = false;
        break;
    case Qt::Key_D:
        movingRight = false;
        break;
    default:
        break;
    }
    updateDirection();
}

void testTank::updateDirection()
{
    if (movingUp && movingRight) {
        setRotation(45);
    } else if (movingUp && movingLeft) {
        setRotation(-45);
    } else if (movingDown && movingRight) {
        setRotation(135);
    } else if (movingDown && movingLeft) {
        setRotation(-135);
    } else if (movingUp) {
        setRotation(0);
    } else if (movingDown) {
        setRotation(180);
    } else if (movingLeft) {
        setRotation(-90);
    } else if (movingRight) {
        setRotation(90);
    }
}

void testTank::advance()
{
    if (movingUp) {
        moveBy(0, -speed);
    }
    if (movingDown) {
        moveBy(0, speed);
    }
    if (movingLeft) {
        moveBy(-speed, 0);
    }
    if (movingRight) {
        moveBy(speed, 0);
    }
}

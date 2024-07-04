#include "testtank.h"
#include <QBrush>
#include <QGraphicsScene>
#include "singlegamewidget.h"


testTank::testTank(GameMap* gameMap)
    : movingUp(false), movingDown(false), movingLeft(false), movingRight(false), speed(2.0), rotationAngle(0)
{
    setRect(0, 0, tankLength * 2 / 3, tankLength);
    setBrush(QBrush(Qt::red));
    setTransformOriginPoint(this->rect().width()/2,this->rect().height()/2);


    head = new QGraphicsEllipseItem(-tankLength / 6, -tankLength / 6, tankLength / 3, tankLength / 3, this);
    head->setBrush(QBrush(Qt::yellow));
    head->setPos(rect().width() / 2, 0);

    setRandomInitialPosition(gameMap);//随机放置坦克
}

void testTank::setRandomInitialPosition(GameMap *gameMap)
{
    QVector<QVector<int>> map = gameMap->getmap();
    QVector<QPair<int, int>> whiteCells;
    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < map[i].size(); ++j)
        {
            if (map[i][j] == 2)
            {
                whiteCells.append(qMakePair(i, j));
            }
        }
    }

    if (!whiteCells.isEmpty())
    {
        int selectedNum = QRandomGenerator::global()->bounded(whiteCells.size());
        QPair<int, int> pos = whiteCells[selectedNum];
        int row = pos.first;
        int col = pos.second;

        // 将坦克放在白色块的中心
        setPos(col * gridSize + gridSize / 2 - rect().width() / 2, row * gridSize + gridSize / 2 - rect().height() / 2);
        //gridSize宏定义在"singlegamewidget.h"中，因此#include "singlegamewidget.h"
    }
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

void testTank::updateDirection()//更新转向
{
    int oldRotation = this->rotation();
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
    if(checkCollision())
    {
        setRotation(oldRotation);
    }
}

bool testTank::checkCollision()//碰撞检测，黑色方块为墙体，不可通过
{
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item);
        if (rectItem && rectItem->brush().color() == Qt::black)
        {
            return true;
        }
    }
    return false;
}

void testTank::advance()//timer调用advance函数，用于实现状态更新
{
    QPointF oldPos = pos();
    int oldRotation = this->rotation();
    if (movingUp && movingRight)
    {
        moveBy(speed/1.414, -speed/1.414);
    }
    else if (movingUp && movingLeft)
    {
        moveBy(-speed/1.414, -speed/1.414);
    }
    else if (movingDown && movingRight)
    {
        moveBy(speed/1.414, speed/1.414);
    }
    else if (movingDown && movingLeft)
    {
        moveBy(-speed/1.414, speed/1.414);
    }
    else if (movingUp)
    {
        moveBy(0, -speed);
    }
    else if (movingDown)
    {
        moveBy(0, speed);
    }
    else if (movingLeft)
    {
        moveBy(-speed, 0);
    }
    else if (movingRight)
    {
        moveBy(speed, 0);
    }
    updateDirection();
    if (checkCollision())//如果碰到则不作改变
    {
        setPos(oldPos);
        setRotation(oldRotation);
    }
}

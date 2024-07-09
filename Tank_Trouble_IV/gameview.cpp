#include "gameview.h"
#include "qevent.h"
#include "parameter.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView{parent}
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(true);
}

void GameView::setGameData(GameData *data)
{
    this->data=data;
}

void GameView::wheelEvent(QWheelEvent *event)
{
    // 禁止鼠标滚轮移动视图
    event->ignore();
}

// void GameView::mouseMoveEvent(QMouseEvent *event)
// {
//     SingleGameWidget *itsParent = dynamic_cast<SingleGameWidget *>(this->parent());
//     itsParent->setTurretRotation(event);
// }

void GameView::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        //qDebug()<<"ViewPress";
        switch (event->key())
        {
        case Qt::Key_W:
            data->playerTank()->setMovingState(UP,true);
            break;
        case Qt::Key_D:
            data->playerTank()->setMovingState(RIGHT,true);
            break;
        case Qt::Key_S:
            data->playerTank()->setMovingState(DOWN,true);
            break;
        case Qt::Key_A:
            data->playerTank()->setMovingState(LEFT,true);
            break;
        }
    }
}

void GameView::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        //qDebug()<<"ViewRelease";
        switch (event->key())
        {
        case Qt::Key_W:
            data->playerTank()->setMovingState(UP,false);
            break;
        case Qt::Key_D:
            data->playerTank()->setMovingState(RIGHT,false);
            break;
        case Qt::Key_S:
            data->playerTank()->setMovingState(DOWN,false);
            break;
        case Qt::Key_A:
            data->playerTank()->setMovingState(LEFT,false);
            break;
        }
    }
}



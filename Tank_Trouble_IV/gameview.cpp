#include "gameview.h"
#include "qevent.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView{parent}
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setMouseTracking(true);
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
    // 模拟鼠标事件，获取当前鼠标位置
    qDebug()<<"!";

}

bool *GameView::get()
{

}

#include "gameview.h"
#include "qevent.h"

GameView::GameView(QWidget *parent):QGraphicsView(parent)
{
    this->setMouseTracking(true);
}

//禁用滚轮事件
void GameView::wheelEvent(QWheelEvent *event)
{
    // 禁止鼠标滚轮移动视图
    event->ignore();
}

// void GameView::mouseMoveEvent(QMouseEvent *event)
// {
//     emit signalMouseMove(event);
// }

// void GameView::mousePressEvent(QMouseEvent *event)
// {
//     emit signalMousePress(event);
// }

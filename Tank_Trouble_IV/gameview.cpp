#include "gameview.h"
#include "qevent.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView{parent}
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GameView::wheelEvent(QWheelEvent *event)
{
    // 禁止鼠标滚轮移动视图
    event->ignore();
}

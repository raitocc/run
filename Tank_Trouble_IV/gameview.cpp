#include "gameview.h"
#include "qevent.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView{parent}
{
    qDebug()<<"!!!!!!!!!";
}

void GameView::wheelEvent(QWheelEvent *event)
{
    // 禁止鼠标滚轮移动视图
    event->ignore();
}

#include "gameview.h"
#include "qevent.h"
#include "singlegamewidget.h"

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

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    //SingleGameWidget *itsParent = dynamic_cast<SingleGameWidget *>(this->parent());
    //itsParent->setTurretRotation(event);
}

// void GameView::keyPressEvent(QKeyEvent *event)
// {
//     // 模拟鼠标事件，获取当前鼠标位置
//     qDebug()<<"!";
//     QPoint mousePos = QCursor::pos();
//     QPointF scenePos = mapToScene(mapFromGlobal(mousePos));
//     QMouseEvent mouseEvent(QEvent::MouseMove, mapFromGlobal(mousePos), mousePos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
//     SingleGameWidget *itsParent = dynamic_cast<SingleGameWidget *>(this->parent());
//     itsParent->setTurretRotation(&mouseEvent);
// }

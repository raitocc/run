#include "shell.h"

// 更新子弹位置
void shell::updatePosition()
{
    if(status==1)
    {

    }
}

// 发射子弹
void shell::fire(){

}

// 检查子弹是否应该被移除
bool shell::shouldRemove() {
    // 根据实际情况判断子弹是否应该被移除
    // 例如，子弹是否已经飞出屏幕
    return !status;
}

void shell::QMousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        fire();
    }
}

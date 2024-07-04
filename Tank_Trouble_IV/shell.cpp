#include "shell.h"
#include "tank.h"

int id;
tank tk(id);

// 更新子弹位置
void shell::updatePosition(double deltaTime)
{
    if(status==1)
    {
        shell_x=shell_x + cos(tk.angle)*shell_speed * deltaTime;
        shell_y=shell_y + sin(tk.angle)*shell_speed * deltaTime;
        lifespan -= deltaTime;
    }
}

// 发射子弹
void shell::fire(){
    status=1;
    shell_x=tk.tank_x;
    shell_y=tk.tank_Y;
    double deltatime=0.01667;
    while(lifespan>0)
    {
        updatePosition(deltatime);
    }
}

// 子弹爆炸效果
void shell::hit() {

}
//鼠标左键点击
void shell::QMousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        fire();
    }
}

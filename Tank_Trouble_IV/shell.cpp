#include "shell.h"

// 更新子弹位置
void shell::updatePosition(double deltaTime)
{
    //子弹处于空闲状态
    if(status==0)
    {
        return;
    }
    //子弹移动
    shell_x=shell_x + cos(tk.angle)*shell_speed * deltaTime;
    shell_y=shell_y - sin(tk.angle)*shell_speed * deltaTime;
    shell_rect.moveTo(shell_x,shell_y);
    //子弹存在时间消耗
    lifespan -= deltaTime;
    //子弹位置超出屏幕，变为空闲状态
    if(shell_x<=shell_rect.width()||shell_y<=-shell_rect.height())
    {
        status=0;
    }
}

// 发射子弹
void shell::fire(QMouseEvent *event){
    if(event->button()==Qt::LeftButton)
    {
        //将子弹从空闲状态改为使用状态
        status=1;
        //设置子弹坐标
        shell_x=tk.tank_x;
        shell_y=tk.tank_Y-1/2*tank_length;
        shell_rect.moveTo(shell_x,shell_y);

        //绘制子弹
        shell_painter.drawPixmap(shell_x,shell_y,my_bullet);

        double deltatime=0.01667;
        while(lifespan>0)
        {
            updatePosition(deltatime);
        }
    }
}

//子弹碰撞检测
void shell::collisionDetection()
{
    //如果子弹矩形框和敌方坦克矩形框或墙相交，变为空闲状态
}

// 子弹爆炸效果
void shell::hit() {

}



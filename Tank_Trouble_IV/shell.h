#define SHELL_H

#include<QMouseEvent>
#define basic_shell_speed 20;

enum shell_name={"普通子弹","爆炸弹","穿透弹","穿墙跟踪弹"}

class shell
{
    shell_name name;//炮弹名称
    int ID;//编号便于记录
    int ATK;//攻击力
    int shell_speed;//子弹速度
    int width;//子弹宽度，间接定义碰撞体积
    double shell_x;
<<<<<<< HEAD
    double shell_y;//炮弹的坐标
    bool status;//是否存在的状态
    //构造函数
    //子弹目前尚不存在
    shell(shell_name sn,int ID,bool ifexist = 0) :name(sn),ID(ID),status(ifexist)
    {
        switch(sn){
        case "普通子弹":
            ATK=2;
            width=1;
            shell_speed=0.8*basic_shell_speed;
            break;
        case "爆炸弹":
            ATK=4;
            width=3;
            shell_speed=0.5*basic_shell_speed;
            break;
        case "穿透弹":
            ATK=4;
            width=1;
            shell_speed=1.2*basic_shell_speed;
            break;
        case "穿墙跟踪弹":
            ATK=2;
            width=1;
            shell_speed=0.8*basic_shell_speed;
            break;
        default:
            break;
        }
    }
    ~shell(){};
    void updatePosition();
    void mousePressEvent(QMouseEvent *event);
    bool shouldRemove();
=======
    double shell_Y;//炮弹的坐标
    shell();
>>>>>>> 1ed2a62f8206d43d840e20c9d5f82445a1d3aa7d

    
};

// 更新子弹位置
shell::void updatePosition() {
    if(status=1)
    {

    }
}

// 按下鼠标左键发射子弹
shell::void shell::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton)
    {
        status=1;
    }
    updatePosition();
}

// 检查子弹是否应该被移除
shell::bool shouldRemove() {
    // 根据实际情况判断子弹是否应该被移除
    // 例如，子弹是否已经飞出屏幕
    return !status;
}


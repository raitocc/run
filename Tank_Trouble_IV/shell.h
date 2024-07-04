#define SHELL_H

#include<QMouseEvent>
#include<QtMath>
#include<QPixmap>
#include "tank.h"
#define basic_shell_speed 20;
#define basic_shell_lifespan 1000;
#define Regular_Bullets 0;
#define Explosive_Bullets 1;
#define Armor_Piercing_Bullets 2;
#define Wall_Penetrating_Tracer_Bullets 3;

class shell
{
    int name;//炮弹名称
    int ID;//编号便于记录
    int ATK;//攻击力
    int shell_speed;//子弹速度
    int width;//子弹宽度，间接定义碰撞体积
    double shell_x;
    double shell_y;//炮弹的坐标
    float lifespan;//子弹存在时间
    bool status;//是否存在的状态
    QPixmap my_bullet;//子弹资源对象
    static tank tk;
public:
    //构造函数
    //子弹目前尚不存在
    shell(int sn,int ID,bool ifexist = 0) :name(sn),ID(ID),status(ifexist)
    {
        my_bullet.load("C:/Users/HUAWEI/Downloads/shoot.png");
        lifespan=basic_shell_lifespan;
        switch(sn){
        case 0:
            ATK=2;
            width=1;
            shell_speed=0.8*basic_shell_speed;
            break;
        case 1:
            ATK=4;
            width=3;
            shell_speed=0.5*basic_shell_speed;
            break;
        case 2:
            ATK=4;
            width=1;
            shell_speed=1.2*basic_shell_speed;
            break;
        case 3:
            ATK=2;
            width=1;
            shell_speed=0.8*basic_shell_speed;
            break;
        default:
            break;
        }
    }
    ~shell(){};
    void updatePosition(double deltaTime);
    void QMousePressEvent(QMouseEvent *event);
    void fire();
    void hit();
};




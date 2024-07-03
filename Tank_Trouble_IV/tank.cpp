#include "tank.h"

void tank::inital_tank
    (
    string name_,
    string info_,
    int HP_,
    int tank_speed_,
    int attck_speed_,
    int width_,
    int length_,
    int shell_kind_
    )
{
    name=name_;
    info=info_;
    HP=MAX_HP=HP_;
    tank_speed=tank_speed_;//默认移速
    attck_speed=attck_speed_;//默认攻速
    width=width_;
    length=length_;//默认体积
    shell= new int[shellkind];
    shell[shell_kind_]=MAXNUM;//默认子弹数量为无穷
}
//我设定的子弹种类 #0普通子弹 #1双发普通子弹 #3爆炸子弹
tank::tank(int ID):ID(ID){
    //这里我想的是每个tank型号我们定一个ID,创建时直接用ID就可以创建
    switch(ID)
    {
    case(1000)://默认机型
        inital_tank("","梦开始的地方",10,basic_tank_speed,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5000)://nomal
        inital_tank("Normal Tank","",4,basic_tank_speed*0.8,basic_attck_speed*0.5,tank_width,tank_length,0);
        break;
    case(5001)://advanced
        inital_tank("Advanced Tank","",8,basic_tank_speed,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5002)://elite
        inital_tank("Elite Tank","",20,basic_tank_speed,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5003)://commander
        inital_tank("Commander Tank","",24,basic_tank_speed*1.2,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5004)://boss
        inital_tank("boss Tank","",30,basic_tank_speed*1.2,basic_attck_speed*1.2,tank_width,tank_length,1);
        break;
    case(5005)://BOSS
        inital_tank("BOSS Tank","",40,basic_tank_speed*1.2,basic_attck_speed*1.5,tank_width,tank_length,1);
        break;
    case(5006)://Gun turret
        inital_tank("Gun Turret","",4,0,basic_attck_speed,tank_width,tank_length,1);
        break;
    case(5007)://Bomb turret
        inital_tank("Bomb turret","",4,0,basic_attck_speed*0.5,tank_width,tank_length,2);
        break;
    }
}
tank::~tank() {
    delete[] shell;
}

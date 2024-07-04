#ifndef TANK_H
#define TANK_H

#include <Qstring>
using namespace std;

#define basic_tank_speed 5
#define basic_attck_speed 5
//#define basic_turning_speed
#define tank_width 1
#define tank_length 2//留了几个宏方便你们定义

#define shellkind 10//子弹最大种类
#define MAXNUM 2000000000;

class tank
{
public:
    int ID;//tank编号
    string name;
    string info;
    int HP;//当前生命值
    int MAX_HP;//最大生命上限
    int tank_speed;//坦克移速
    int attck_speed;//攻速
    //int turning_speed;//转向速度
    int* shell;//当前携带各种子弹及其数量
    double width;//坦克宽度
    double length;//坦克长度,间接决定坦克体积
    double tank_x;
    double tank_Y;//坦克的坐标
    double angle;//炮筒角度，0-360
    tank(int ID);
    ~tank();
    void inital_tank(string name,string info,int HP,int tank_speed,int attck_speed,int width,int length,int shell_kind);
};
#endif // TANK_H

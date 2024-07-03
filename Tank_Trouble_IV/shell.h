#ifndef SHELL_H
#define SHELL_H
#include <Qstring>
using namespace std;
#define basic_shell_speed 20;
class shell
{
    string name;//炮弹名称
    int ID;//编号便于记录
    int ATK;//攻击力
    int shell_speed;//子弹速度
    int width;//子弹宽度，间接定义碰撞体积
    double shell_x;
    double shell_Y;//炮弹的坐标

};

#endif // SHELL_H

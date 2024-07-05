#ifndef TANK_H
#define TANK_H

#include <QGraphicsRectItem>
#include <Qstring>
#include <QGraphicsPixmapItem>//图形元素
//#include <QGraphicsview>//视图
#include <QGraphicsScene>//场景
#include <QMouseEvent>>
using namespace std;

#define basic_tank_speed 2
#define basic_attck_speed 5
//#define basic_turning_speed
#define tank_width 20
#define tank_length 30//留了几个宏方便你们定义

#define shellkind 10//子弹最大种类
#define MAXNUM 2000000000;

class tank : public QGraphicsPixmapItem
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
    double tank_y;//坦克的坐标
    double tank_angle;//坦克角度，0-360
    double shell_angle;//炮筒角度，0-360
    bool movingUp, movingDown, movingLeft, movingRight;//当前移动方向
    void updateDirection();
    bool IFPLAYER;//是否为玩家

    tank(int ID);
    ~tank();
    //tank坐标实时更新？
    void SET_X(int x){tank_x=x;}
    void SET_Y(int y){tank_y=y;}

    void inital_tank(string name,string info,int HP,int tank_speed,int attck_speed,int width,int length,int shell_kind);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event) ;
    void mousePressEvent(QMouseEvent *event);

    void tank_move();//
    void resetMoving();
};
#endif // TANK_H

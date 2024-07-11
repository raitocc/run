#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "tank.h" // 引入基类 Tank 的头文件
#include <QPen>

enum aiState {
    wandering,//随机游走
    Chasing,//追击
    Attacking,//攻击
    Avoid,//躲避
};

struct Point {
    int row, col;
    Point(int x, int y) : row(x), col(y) {}
    bool operator ==(const Point& p) const
    {
        return col == p.col && row == p.row;
    }
    bool operator !=(const Point& p) const
    {
        return col!=p.col||row!=p.row;
    }
};

// struct Node
// {
//     Point point;
//     int f, g, h;
//     Node* parent;

//     Node(Point point, int f, int g, int h, Node* parent)
//         : point(point), f(f), g(g), h(h), parent(parent) {}

//     bool operator>(const Node& other) const {
//         return f > other.f;
//     }
// };

// // 自定义哈希函数，用于 Point 结构体在 unordered_map 中的哈希
// struct PointHash {
//     std::size_t operator()(const Point& point) const {
//         return std::hash<int>()(point.row) ^ std::hash<int>()(point.col);
//     }
// };

class EnemyTank : public Tank
{
public:
    EnemyTank(int initialBulletID, QGraphicsItem* parent = nullptr);

    int bulletID() const;
    int id() const;
    aiState state() const;


    void setBulletID(int bulletID);//设置tankID的函数
    void setID(int id);
    void init();

    void fire();//射击子弹

private:
    int _bulletID;
    QPointF _rotationCenter;
    int _id;

    QGraphicsRectItem* _hpRect;//血条

    void setHpRect();
    void advance(int phase);

    ////////////////////////////////////
    aiState _state;
    int _aiTimerCounter;//120帧过高，利用计时器降低到30帧来更新ai
    int _aiUpdateFrequency;
    int wanderingCounter;
    QPair<int,int> wanderGoal;

    bool playerDetected();//判断是否发现玩家

    void aiTimerCount();//计数并且调用状态更新
    void updateState();//状态更新
    void wander();//游走
    void headToGoal();//前往游走目标点
    void chase();//追击
    void attack();//攻击
    void avoid();//躲避

    int currentStep;
    QVector<Point> path;
    void setMovingStateOfWonder();
    bool isCollision(int x, int y);


    QVector<Point> findPath(Point start, Point goal);//寻路
    inline int map(int a,int b);

};

#endif // ENEMYTANK_H

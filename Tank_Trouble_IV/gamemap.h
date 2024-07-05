#ifndef GAMEMAP_H
#define GAMEMAP_H

#include<QVector>
#include<QRandomGenerator>

#define gridSize 50
#define tanklength 30

class GameMap
{
public:
    GameMap();
    void createMap();
    bool checkConnectivity();

    int getrow();
    int getcol();
    const QVector<QVector<int>>& getmap();

    //我移了一下
    void setRandomInitialPosition(int &x,int &y); // 设置随机初始位置

private:
    QVector<QVector<int>> map;//0代表不可破坏墙体，1代表可破坏墙体，2代表空
    int row;
    int col;
};

#endif // GAMEMAP_H

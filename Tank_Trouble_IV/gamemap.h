#ifndef GAMEMAP_H
#define GAMEMAP_H

#include<QPointF>
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

    int getCellType(int x, int y) const;  // 获取指定坐标的格子类型
    QPointF gridToMap(int x, int y) const;  // 格子坐标转场景坐标
    QPointF mapToGrid(const QPointF &pos) const;
    int getrow();
    int getcol();
    const QVector<QVector<int>>& getmap();

    //我移了一下
    void setRandomInitialPosition(int &x,int &y); // 设置随机初始位置
    QVector<QPair<int, int>> generateSpawnPoints(int n) ;

private:
    QVector<QVector<int>> map;//0代表不可破坏墙体，1代表可破坏墙体，2代表空
    int row;
    int col;
};

#endif // GAMEMAP_H

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include<QVector>
#include<QRandomGenerator>

class GameMap
{
public:
    GameMap();
    void createMap();
    bool checkConnectivity();

    int getrow();
    int getcol();
    const QVector<QVector<int>>& getmap();

private:
    QVector<QVector<int>> map;//0代表不可破坏墙体，1代表可破坏墙体，2代表空
    int row;
    int col;
};

#endif // GAMEMAP_H

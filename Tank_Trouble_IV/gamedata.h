#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QVector>
#include <QRandomGenerator>

class GameData
{
public:
    GameData();

    void newData();//从第一关开始创建新游戏数据
    void createMap(int row,int col);//创建地图

    //get类函数
    int score() const;
    int money() const;
    int level() const;
    int gridType(int row, int col) const;
    int mapRow() const;
    int mapCol() const;
    //int playerTank() const;
    //int enermyTank(int id);


private:
    QVector<QVector<int>> _map;//0代表不可破坏墙体，1代表可破坏墙体，2代表空
    int _score;//分数
    int _money;//金钱
    int _level;//当前关卡

    bool checkConnectivity(int row, int col);//创建地图辅助函数，检查连通性
};

#endif // GAMEDATA_H

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QVector>
#include <QRandomGenerator>

class GameData
{
public:
    GameData();

    void newData(int level);
    void newMap(int level);
    void newTank(int level);

private:
    QVector<QVector<int>> _map;//0代表不可破坏墙体，1代表可破坏墙体，2代表空
    int _score;//分数
    int _money;//金钱
    int _level;//当前关卡
};

#endif // GAMEDATA_H

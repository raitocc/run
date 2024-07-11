#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "bullet.h"
#include "enemytank.h"
#include "playertank.h"
#include <QVector>
#include <QRandomGenerator>

class GameData
{
public:
    GameData();

    void newData();//从第一关开始创建新游戏数据
    void createMap(int row,int col);//创建地图
    void createTank(int n);//创建坦克
    Bullet* addBullet(int id, Tank *shooter, QPointF begin, QPointF tar);//添加子弹

    //get类函数
    int score() const;
    int money() const;
    int level() const;
    int gridType(int row, int col) const;
    const QVector<QVector<int>>& map();
    int mapRow() const;
    int mapCol() const;
    //Bullet* bullet(int id);
    PlayerTank* playerTank() const;
    EnemyTank *enemyTank(int n) const;
    int enemyNum() const;
    bool deadEnemy(int n) const;
    //int enermyTank(int id);
    QPair<int,int> randomSpacePoint();//随机一个空白点
    QVector<QPair<int, int> > randomSpacePoint(int num, int beginRow, int beginCol, int EndRow, int EndCol);//随机n个空白点，指定范围


    //删改
    void addScore(int n);
    void addMoney(int n);
    void reduceMoney(int n);
    void setDeadEnemy(int n,bool f);
    void setMap(int row, int col, int type);
    void addBulletSupply(int id, int num, QGraphicsScene* scene);
    void switchPlayerCurrentBullet();//顺序切换子弹
    void switchBullet(int id);//顺序切换子弹
    void setSupplyFlag(int row, int col, bool f);//设置位置补给标记






private:
    QVector<QVector<int>> _map;//0代表不可破坏墙体，1代表可破坏墙体，2代表空
    QVector<QVector<bool>> _hasSupply;//true代表该位置已经有补给
    int _score;//分数
    int _money;//金钱
    int _level;//当前关卡
    PlayerTank* _playerTank;
    QVector<EnemyTank*> _enemyTanks;
    //QList<BulletSupply*> _bulletSupply;
    QVector<bool> _deadEnemy;//记录对应位置敌人是否死亡，死亡为true
    //QVector<Bullet*> _bullets;

    bool checkConnectivity(int row, int col);//创建地图辅助函数，检查连通性
    QVector<QPair<int, int>> generateSpawnPoints(int n);//创建坦克辅助函数，选择出生点

public slots:
    void advance();//由SingleGameWidget的timer调用
};

#endif // GAMEDATA_H

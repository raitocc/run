#include "gamedata.h"
#include "parameter.h"
#include <iostream>
#include <queue>


GameData::GameData()
{
    this->_level=1;
    this->_money=0;
    this->_score=0;
}

void GameData::newData()
{
    this->_level=1;
    this->_money=0;
    this->_score=0;
    int col = QRandomGenerator::global()->bounded(18,19);
    int row = col *3/4;
    createMap(row, col);
    createTank(3);
}

void GameData::createMap(int row, int col)//创建地图
{
    _map.resize(row);
    for(auto& i : _map)
    {
        i.resize(col);
    }

    _hasSupply.resize(row);
    for(auto& i : _hasSupply)
    {
        i.resize(col);
        for(int j=0;j<i.size();j++)
        {
            i[j]=0;
        }
    }

    // 随机放置方块（不包括外圈的墙）
    int totalCells = (row - 2) * (col - 2);
    int numZeros = totalCells / 4;
    int numOnes = totalCells / 4;
    int numTwos = totalCells - numZeros - numOnes;

    // 初始化数组
    std::vector<int> cells;
    cells.insert(cells.end(), numZeros, WALL);
    cells.insert(cells.end(), numOnes, BOX);
    cells.insert(cells.end(), numTwos, AIR);

    // 使用QRandomGenerator进行手动打乱
    for (int i = cells.size() - 1; i > 0; --i) {
        int j = QRandomGenerator::global()->bounded(i + 1);
        std::swap(cells[i], cells[j]);
    }
    for(int i = 1; i < row - 1; ++i)
    {
        for(int j = 1; j < col - 1; ++j)
        {
            _map[i][j] = cells[(i - 1) * (col - 2) + (j - 1)];
        }
    }

    // 设置外圈为不可破坏的墙
    for(int i = 0; i < row; ++i)
    {
        _map[i][0] = WALL;
        _map[i][col - 1] = WALL;
    }
    for(int j = 0; j < col; ++j)
    {
        _map[0][j] = WALL;
        _map[row - 1][j] = WALL;
    }

    // 检查连通性
    while(!checkConnectivity(row,col))
    {
        for (int i = cells.size() - 1; i > 0; --i) {
            int j = QRandomGenerator::global()->bounded(i + 1);
            std::swap(cells[i], cells[j]);
        }
        for(int i = 1; i < row - 1; ++i)
        {
            for(int j = 1; j < col - 1; ++j)
            {
                _map[i][j] = cells[(i - 1) * (col - 2) + (j - 1)];
            }
        }
    }

    // 打印数组
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            std::cout << _map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GameData::createTank(int n)
{
    QVector<QPair<int, int>> p = generateSpawnPoints(n);
    //先放置玩家坦克
    _playerTank = new PlayerTank;
    _playerTank->setGameData(this);
    _playerTank->setPos(p[0].first*GRIDSIZE+GRIDSIZE/2-TANK_WIDTH/2,p[0].second*GRIDSIZE+GRIDSIZE/2-TANK_LENGTH/2);
    //放置敌方坦克
    _enemyTanks.resize(n-1);
    _deadEnemy.resize(n-1);
    for(int i =1;i<n;i++)
    {
        _deadEnemy[i-1] = false;
        _enemyTanks[i-1] = new EnemyTank(0);
        _enemyTanks[i-1]->setGameData(this);
        _enemyTanks[i-1]->setID(i-1);
        _enemyTanks[i-1]->setPos(p[i].first*GRIDSIZE+GRIDSIZE/2-TANK_WIDTH/2,p[i].second*GRIDSIZE+GRIDSIZE/2-TANK_LENGTH/2);
    }
}

int GameData::score() const
{
    return _score;
}

int GameData::money() const
{
    return _money;
}

int GameData::level() const
{
    return _level;
}

int GameData::gridType(int row, int col) const
{
    return _map[row][col];
}

const QVector<QVector<int> > &GameData::map()
{
    return _map;
}

int GameData::mapRow() const
{
    return _map.size();
}

int GameData::mapCol() const
{
    return _map[0].size();
}

// Bullet *GameData::bullet(int id)
// {
//     if(id>=_bullets.size())
//     {
//         qDebug()<<"不存在id为: "<<id<<"的子弹";
//             return nullptr;
//     }
//     return _bullets[id];
// }

PlayerTank* GameData::playerTank() const
{
    return _playerTank;
}

EnemyTank *GameData::enemyTank(int n) const
{
    if(n>=_enemyTanks.size())
    {
        qDebug()<<"不存在id为:"<<n<<"的敌方坦克";
            return nullptr;
    }
    return _enemyTanks[n];
}

int GameData::enemyNum() const
{
    return _enemyTanks.size();
}

bool GameData::deadEnemy(int n) const
{
    if(n>=_enemyTanks.size())
    {
        qDebug()<<"不存在id为:"<<n<<"的敌方坦克";
            return false;
    }
    return _deadEnemy[n];
}

void GameData::addScore(int n)
{
    _score+=n;
}

void GameData::addMoney(int n)
{
    _money+=n;
}

void GameData::reduceMoney(int n)
{
    _money-=n;
}

void GameData::setDeadEnemy(int n, bool f)
{
    if(n>=_enemyTanks.size())
    {
        qDebug()<<"不存在id为:"<<n<<"的敌方坦克";
            return ;
    }
    _deadEnemy[n] = f;
}

void GameData::setMap(int row, int col, int type)
{
    _map[row][col] = type;
}

void GameData::addBulletSupply(int id, int num, QGraphicsScene *scene)
{
    //随机选取一个可用位置
    QPair<int,int> pair;
    do
    {
        pair = randomSpacePoint();
    }
    while(_hasSupply[pair.first][pair.second]);
    //检验该位置是否已经生成道具

    //qDebug()<<"生成位置"<<pair.first<<pair.second;
    if(pair.first == -1)
    {
        return;
    }
    BulletSupply* supply = new BulletSupply(id, num,pair.first,pair.second,this);
    _hasSupply[pair.first][pair.second] = true;
    supply->setData(ITEM_TYPE,BULLET_SUPLLY);
    supply->setData(BULLET_TYPE,id);
    supply->setData(BULLET_AMOUNT,num);
    supply->setZValue(1);
    scene->addItem(supply);
}

void GameData::switchPlayerCurrentBullet()
{
    //qDebug()<<"?";
    int current = this->playerTank()->currentBullet();
    int i = current;
    do
    {
        i = (i+1)%MAX_BULLET_TYPE;
    }
    while(this->playerTank()->bulletNum(i)==0);
    this->playerTank()->switchBullet(i);
}

void GameData::switchBullet(int id)
{
    this->playerTank()->switchBullet(id);
}

void GameData::setSupplyFlag(int row, int col, bool f)
{
    _hasSupply[row][col] = f;
}

Bullet *GameData::addBullet(int id, Tank* shooter,QPointF begin, QPointF tar)
{
    Bullet* bullet = new Bullet(id,shooter,begin,tar);
    return bullet;
}

bool GameData::checkConnectivity(int row, int col)//检查连通性
{
    std::vector<std::vector<bool>> visited(row, std::vector<bool>(col, false));
    std::queue<std::pair<int, int>> q;
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    bool foundStart = false;

    // 找到第一个1或2的方块
    for(int i = 1; i < row - 1 && !foundStart; ++i)
    {
        for(int j = 1; j < col - 1 && !foundStart; ++j)
        {
            if(_map[i][j] == 1 || _map[i][j] == 2)
            {
                q.push({i, j});
                visited[i][j] = true;
                foundStart = true;
            }
        }
    }

    // 如果没有找到1或2的方块，返回false
    if(!foundStart)
        return false;

    // 广度优先搜索
    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for(auto& dir : directions)
        {
            int newX = x + dir[0];
            int newY = y + dir[1];
            if(newX >= 1 && newX < row - 1 && newY >= 1 && newY < col - 1 && !visited[newX][newY])
            {
                if(_map[newX][newY] == 1 || _map[newX][newY] == 2)
                {
                    visited[newX][newY] = true;
                    q.push({newX, newY});
                }
            }
        }
    }

    // 检查所有的1或2的方块是否都访问过
    for(int i = 1; i < row - 1; ++i)
    {
        for(int j = 1; j < col - 1; ++j)
        {
            if((_map[i][j] == 1 || _map[i][j] == 2) && !visited[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

QVector<QPair<int, int>> GameData::generateSpawnPoints(int n)//产生随机出生点
{
    QVector<QPair<int, int>> whiteCells;

    // 遍历地图以找到所有白色块的位置
    for (int i = 0; i < _map.size(); ++i) {
        for (int j = 0; j < _map[i].size(); ++j) {
            if (_map[i][j] == AIR) {
                whiteCells.append(qMakePair(i, j));
            }
        }
    }

    QVector<QPair<int, int>> spawnPoints;

    // 如果存在白色块，则随机选择 n 个位置
    if (!whiteCells.isEmpty()) {
        for (int k = 0; k < n; ++k) {
            int selectedNum = QRandomGenerator::global()->bounded(whiteCells.size());
            QPair<int, int> pos = whiteCells[selectedNum];
            int row = pos.first;
            int col = pos.second;

            // 将坦克放在白色块的中心
            spawnPoints.append(qMakePair(col, row));

            // 移除已选中的白色块以防止重复选择
            whiteCells.removeAt(selectedNum);
        }
    }

    return spawnPoints;
}

QPair<int, int> GameData::randomSpacePoint()
{
    QVector<QPair<int, int>> airPoints;

    // 遍历地图，找到所有AIR点的位置
    for (int i = 0; i < _map.size(); ++i) {
        for (int j = 0; j < _map[i].size(); ++j) {
            if (_map[i][j] == AIR) {
                airPoints.append(QPair<int, int>(i, j));
            }
        }
    }

    // 如果没有找到AIR点，返回一个无效点
    if (airPoints.empty()) {
        return QPair<int, int>(-1, -1);  // 无效点
    }

    // 随机选择一个AIR点
    int randomIndex = QRandomGenerator::global()->bounded(airPoints.size());
    return airPoints[randomIndex];
}

inline int max(int a, int b)
{
    return a > b ? a:b;
}

inline int min(int a, int b)
{
    return a > b ? b:a;
}

QVector<QPair<int, int>> GameData::randomSpacePoint(int num, int beginRow, int beginCol, int EndRow, int EndCol)
{
    QVector<QPair<int, int>> result;
    QVector<QPair<int, int>> candidates;

    // 1. 遍历指定范围内的所有点，将空白点加入 candidates 列表
    for (int row = max(0,beginRow); row <= min(EndRow,_map.size()-1); ++row) {
        for (int col = max(0,beginCol); col <= min(EndCol,_map[0].size()-1); ++col) {
            if (_map[row][col] == AIR) {
                candidates.append(QPair<int, int>(row, col));
            }
        }
    }

    // 2. 如果 candidates 列表为空，则返回空列表
    if (candidates.isEmpty()) {
        return result;
    }

    // 3. 随机从 candidates 列表中选取 num 个点
    QRandomGenerator* randomGenerator = QRandomGenerator::global();
    while (result.size() < num && !candidates.isEmpty()) {
        int index = randomGenerator->bounded(candidates.size());
        result.append(candidates[index]);
        candidates.removeAt(index); // 从候选列表中移除已选择的点
    }

    return result;
}

void GameData::advance()
{

}


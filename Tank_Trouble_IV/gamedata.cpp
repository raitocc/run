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
    int col = QRandomGenerator::global()->bounded(30,51);
    int row = col *3/4;
    createMap(row, col);
    createTank(col/3);
}

void GameData::createMap(int row, int col)//创建地图
{
    _map.resize(row);
    for(auto& i : _map)
    {
        i.resize(col);
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
    _playerTank->setPos(p[0].first*GRIDSIZE+GRIDSIZE/2-TANK_WIDTH/2,p[0].second*GRIDSIZE+GRIDSIZE/2-TANK_LENGTH/2);
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

void GameData::advance()
{

}


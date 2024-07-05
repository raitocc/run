#include "gamemap.h"
#include <queue>
#include <algorithm>
#include <iostream>

GameMap::GameMap() {}

void GameMap::createMap()
{
    // 随机生成地图的行列数（加上外圈的墙）
    col = QRandomGenerator::global()->bounded(30, 51) + 2;
    row = col * 3 / 4;
    map.resize(row);
    for(auto& i : map)
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
    cells.insert(cells.end(), numZeros, 0);
    cells.insert(cells.end(), numOnes, 1);
    cells.insert(cells.end(), numTwos, 2);

    // 使用QRandomGenerator进行手动打乱
    for (int i = cells.size() - 1; i > 0; --i) {
        int j = QRandomGenerator::global()->bounded(i + 1);
        std::swap(cells[i], cells[j]);
    }
    for(int i = 1; i < row - 1; ++i)
    {
        for(int j = 1; j < col - 1; ++j)
        {
            map[i][j] = cells[(i - 1) * (col - 2) + (j - 1)];
        }
    }

    // 设置外圈为不可破坏的墙（0）
    for(int i = 0; i < row; ++i)
    {
        map[i][0] = 0;
        map[i][col - 1] = 0;
    }
    for(int j = 0; j < col; ++j)
    {
        map[0][j] = 0;
        map[row - 1][j] = 0;
    }

    // 检查连通性
    while(!checkConnectivity())
    {
        for (int i = cells.size() - 1; i > 0; --i) {
            int j = QRandomGenerator::global()->bounded(i + 1);
            std::swap(cells[i], cells[j]);
        }
        for(int i = 1; i < row - 1; ++i)
        {
            for(int j = 1; j < col - 1; ++j)
            {
                map[i][j] = cells[(i - 1) * (col - 2) + (j - 1)];
            }
        }
    }

    // 打印数组
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool GameMap::checkConnectivity()
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
            if(map[i][j] == 1 || map[i][j] == 2)
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
                if(map[newX][newY] == 1 || map[newX][newY] == 2)
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
            if((map[i][j] == 1 || map[i][j] == 2) && !visited[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

int GameMap::getrow()
{
    return row;
}

int GameMap::getcol()
{
    return col;
}

const QVector<QVector<int> > &GameMap::getmap()
{
    return map;
}

void GameMap::setRandomInitialPosition(int &x,int &y)
{
    QVector<QVector<int>> map = getmap();
    QVector<QPair<int, int>> whiteCells;
    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < map[i].size(); ++j)
        {
            if (map[i][j] == 2)
            {
                whiteCells.append(qMakePair(i, j));
            }
        }
    }

    if (!whiteCells.isEmpty())
    {
        int selectedNum = QRandomGenerator::global()->bounded(whiteCells.size());
        QPair<int, int> pos = whiteCells[selectedNum];
        int row = pos.first;
        int col = pos.second;

        // 将坦克放在白色块的中心
        //setPos(col * gridSize + gridSize / 2 - rect().width() / 2, row * gridSize + gridSize / 2 - rect().height() / 2);
        x=col * gridSize + gridSize / 2;
        y=row * gridSize + gridSize / 2;
        //gridSize宏定义在"singlegamewidget.h"中，因此#include "singlegamewidget.h"
    }
}

#include "gamemap.h"
#include "qdebug.h"
#include <queue>
#include <algorithm>
#include <iostream>

GameMap::GameMap() {}

void GameMap::createMap()
{
    // 随机生成地图的行列数
    col = QRandomGenerator::global()->bounded(12, 21);
    row = col * 3 / 4;
    map.resize(row);
    for(auto& i : map)
    {
        i.resize(col);
    }

    // 随机放置方块(设置墙的数量)
    int totalCells = row * col;
    int numZeros = totalCells / 4;
    int numOnes = totalCells / 4;
    int numTwos = totalCells - numZeros - numOnes;

    std::vector<int> cells;
    cells.insert(cells.end(), numZeros, 0);
    cells.insert(cells.end(), numOnes, 1);
    cells.insert(cells.end(), numTwos, 2);

    // 使用QRandomGenerator进行手动打乱
    for (int i = cells.size() - 1; i > 0; --i) {
        int j = QRandomGenerator::global()->bounded(i + 1);
        std::swap(cells[i], cells[j]);
    }

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            map[i][j] = cells[i * col + j];
        }
    }

    // 检查连通性
    while(!checkConnectivity())
    {
        for (int i = cells.size() - 1; i > 0; --i) {
            int j = QRandomGenerator::global()->bounded(i + 1);
            std::swap(cells[i], cells[j]);
        }
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < col; ++j)
            {
                map[i][j] = cells[i * col + j];
            }
        }
    }

    // 打印数组
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            std::cout<<map[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

bool GameMap::checkConnectivity()
{
    std::vector<std::vector<bool>> visited(row, std::vector<bool>(col, false));
    std::queue<std::pair<int, int>> q;
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    bool foundStart = false;

    // 找到第一个1或2的方块
    for(int i = 0; i < row && !foundStart; ++i)
    {
        for(int j = 0; j < col && !foundStart; ++j)
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
            if(newX >= 0 && newX < row && newY >= 0 && newY < col && !visited[newX][newY])
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
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            if((map[i][j] == 1 || map[i][j] == 2) && !visited[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

// enemytank.cpp
#include "enemytank.h"

EnemyTank::EnemyTank(QObject *parent) : QObject(parent)
{
    health = 100;
}

EnemyTank::EnemyTank(int x, int y, int health, QObject *parent) : QObject(parent)
{
    rect = QRect(x, y, 50, 50); // Example size and position
    this->health = health;
}

QRect EnemyTank::getRect() const
{
    return rect;
}

void EnemyTank::setRect(const QRect &value)
{
    rect = value;
}

int EnemyTank::getHealth() const
{
    return health;
}

void EnemyTank::setHealth(int value)
{
    health = value;
}

bool EnemyTank::isAlive() const
{
    return health > 0;
}

void EnemyTank::takeDamage(int damage)
{
    health -= damage;
    if (health <= 0)
    {
        emit tankDestroyed();
    }
}

void EnemyTank::move(const QPointF &playerPos)
{
    // 创建一个二维数组来记录每个格子的访问状态
    QVector<QVector<bool>> visited(map->getrow(), QVector<bool>(map->getcol(), false));

    // 创建一个队列来存储待访问的格子
    QQueue<QPointF> q;

    // 将敌方坦克的当前位置加入队列并标记为已访问
    QPointF startPos = map->mapToGrid(this->pos());

    q.push_back(startPos);
    visited[startPos.y()][startPos.x()] = true;

    // 创建一个二维数组来存储每个格子的父节点，用于回溯最短路径
    QVector<QVector<QPointF>> parent(map->getrow(), QVector<QPointF>(map->getcol(), QPointF(-1, -1)));

    // 定义四个方向的偏移量，用于表示上下左右移动
    QVector<int> dx = {0, 1, 0, -1};
    QVector<int> dy = {-1, 0, 1, 0};

    // 使用广度优先搜索算法寻找最短路径
    while (!q.empty()) {
        QPointF curr = q.front();
        q.pop_front();

        // 如果当前格子为玩家位置，则找到最短路径
        if (curr == map->mapToGrid(playerPos)) {
            // 回溯最短路径并移动敌方坦克
            while (curr != startPos) {
                QPointF prev = parent[curr.y()][curr.x()];
                qreal dx = curr.x() - prev.x();
                qreal dy = curr.y() - prev.y();
                setRotation(qRadiansToDegrees(qAtan2(-dy, dx)));
                setPos(map->gridToMap(curr.x(), curr.y()));
                curr = prev;
            }
            return;
        }

        // 遍历四个方向的相邻格子
        for (int i = 0; i < 4; ++i) {
            int nx = curr.x() + dx[i];
            int ny = curr.y() + dy[i];

            // 如果相邻格子是可行走的格子且未访问过，则将其加入队列并标记为已访问
            if (nx >= 0 && nx < map->getcol() && ny >= 0 && ny < map->getrow() &&
                map->getCellType(nx, ny) == 2 && !visited[ny][nx]) {
                q.push_back(QPointF(nx, ny));
                visited[ny][nx] = true;
                parent[ny][nx] = curr;
            }
        }
    }
}

void EnemyTank::attackPlayer()
{
    // 实现攻击玩家的逻辑，可以通过信号槽来实现
    // emit signalAttackPlayer(/* 玩家位置 */);
}

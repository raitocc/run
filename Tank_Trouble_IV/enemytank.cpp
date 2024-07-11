#include "enemytank.h"
#include "gameview.h"
#include "parameter.h"
#include <queue>

EnemyTank::EnemyTank(int initialBulletID,QGraphicsItem* parent)
    : Tank(parent) // 初始化 _bulletID 为 0
{
    setBulletID(initialBulletID);
    init();
}

int EnemyTank::bulletID() const
{
    return _bulletID;
}

int EnemyTank::id() const
{
    return _id;
}

aiState EnemyTank::state() const
{
    return _state;
}

void EnemyTank::setBulletID(int bulletID)
{
    _bulletID = bulletID;
}

void EnemyTank::setID(int id)
{
    _id = id;
}

void EnemyTank::init()
{
    this->setPen(Qt::NoPen);//设置无边框

    //设置数值
    wanderGoal = QPair<int,int>(-1,-1);
    wanderingCounter = 32767;
    chasingCounter = 0;
    shootBulletCounter = 0;
    _aiTimerCounter = 30;
    _aiUpdateFrequency = 30;

    _HP = 20;
    _maxHP = 20;
    _moveSpeed = 0.6;
    _shootSpeed = 1;
    _state = wandering;
    clearMovingState();//清空移动状态标记
    _turret = nullptr;
    _rotationCenter = QPointF(TANK_WIDTH/2,TANK_LENGTH*2/3);

    //z
    this->setZValue(3);

    this->setRect(0,0,TANK_WIDTH,TANK_LENGTH);//设置碰撞箱
    this->setTransformOriginPoint(_rotationCenter);//设置旋转中心


    //绘制炮筒
    this->creatTurret();

    //设置血条
    _hpRect = new QGraphicsRectItem(this);
    _hpRect->setRect(0,0,TANK_WIDTH*4/3,HPRECT_HEIGHT);//血条长度TANK_WIDTH*4/3
    _hpRect->setBrush(QColor(Qt::red));
    _hpRect->setPos(-TANK_WIDTH/6,TANK_LENGTH+HPRECT_HEIGHT+3);
    //_hpRect->ItemIgnoresTransformations;
}

void EnemyTank::fire()
{

}

void EnemyTank::setHpRect()//设置血条
{
    QRectF rect = _hpRect->rect();
    rect.setWidth(_HP / (_maxHP * 1.0) * TANK_WIDTH*4/3.0);
    _hpRect->setRect(rect);

}

void EnemyTank::advance(int phase)
{
    if(phase == 0)
    {
        return;
    }
    else
    {
        move();
        setHpRect();
        aiTimerCount();
    }
}

void EnemyTank::aiTimerCount()
{
    _aiTimerCounter = (_aiTimerCounter+1)%(120/_aiUpdateFrequency);
    //qDebug()<<_aiTimerCounter;
    if(_aiTimerCounter==0)
    {
        updateState();
    }
}

void EnemyTank::updateState()
{
    //qDebug()<<this<<"UPDATE"<<wanderingCounter;
    wanderingCounter++;
    chasingCounter++;
    if (playerDetected())
    {
        qDebug()<<"CHASE";
        _state = Chasing;
    }else
    {
        qDebug()<<"WANDERING";
        _state = wandering;
    }
    //_state = Chasing;
    switch (_state)
    {
    case wandering:
        wander();
        break;
    case Chasing:
        chase();
        break;
    default:
        break;
    }
}

bool EnemyTank::playerDetected()
{
    int detectionRange = 7;//检测半径

    // 假设敌方坦克的当前位置是 tankX，tankY
    int tankX = ((this->pos().x() + this->rect().center().x()) / GRIDSIZE);
    int tankY = ((this->pos().y() + this->rect().center().y()) / GRIDSIZE);

    // 获取游戏视图
    GameView* view = dynamic_cast<GameView*>(this->scene()->views()[0]);

    // 假设玩家的位置是 (playerX, playerY)，根据游戏逻辑获取玩家的位置信息
    int playerX = ((view->gameData()->playerTank()->pos().x() + view->gameData()->playerTank()->rect().center().x()) / GRIDSIZE);
    int playerY = ((view->gameData()->playerTank()->pos().y() + view->gameData()->playerTank()->rect().center().y()) / GRIDSIZE);

    // 假设检测的范围是6格内（包括当前位置）

    // 根据坐标差值来判断玩家是否在指定范围内
    for (int dx = -detectionRange; dx <= detectionRange; ++dx)
    {
        for (int dy = -detectionRange; dy <= detectionRange; ++dy)
        {
            if (dx * dx + dy * dy <= detectionRange * detectionRange)
            {
                // 计算目标位置
                int targetX = tankX + dx;
                int targetY = tankY + dy;

                // 假设 playerX 和 playerY 是玩家的坐标
                if (targetX == playerX && targetY == playerY)
                {
                    if(!findPath(Point(tankY,tankX),Point(playerY,playerX)).empty())
                    {return true;} // 玩家在范围内且能到达
                }
            }
        }
    }

    return false; // 未检测到玩家
}



//游走状态可用转换为其他任何状态，每次回到游走状态的时候重新切换目标点
//找到目标点后则若干秒不再切换目标点
//随机游走状态，检查目标点是否为空，如果为空，则随机选取周围n可用的目标点,如果n个点均不可到达，则goal置为空，不移动。有goal则向goal移动
void EnemyTank::wander()
{
    GameView* view = dynamic_cast<class GameView*>(this->scene()->views()[0]);
    int goalPointNum = 10;
    int wanderSec = 10;
    int randomSec = 5;
    if(wanderingCounter>wanderSec*_aiUpdateFrequency)//新的目标点，找到后若干秒才能再次执行
    {
        if(QRandomGenerator::global()->bounded(0,randomSec*_aiUpdateFrequency)==0)
        {
            path.clear();
            int tcol = (this->pos()+this->rect().center()).x()/GRIDSIZE;
            int trow = (this->pos()+this->rect().center()).y()/GRIDSIZE;
            QVector<QPair<int,int>> goals = view->gameData()->randomSpacePoint(goalPointNum,trow-7,tcol-7,trow+7,tcol+7);
            // for(int i =0;i<goals.size();i++)
            // {
            //     qDebug()<<goals[i];
            // }
            int i = 0;
            do
            {
                path = findPath(Point(trow,tcol),Point(goals[i].first,goals[i].second));
                i++;
            }
            while(path.empty()&&i<goalPointNum);
            if(path.empty())//目标点均不可用,用-1，-1标记
            {
                wanderGoal = QPair<int,int>(-1,-1);
                clearMovingState();
                //qDebug()<<"NoGoal"<<wanderGoal;
            }
            else//找到一个可用目标点
            {
                currentStep = 0;
                wanderGoal.first = path[path.size()-1].row;
                wanderGoal.second = path[path.size()-1].col;
                //qDebug()<<"FindGoal"<<wanderGoal;
                // for(int i =0;i<path.size();i++)
                // {
                //     qDebug()<<path[i].row<<path[i].col;
                // }
            }
            wanderingCounter = 0;//计时器置为0
        }
    }
    else
    {
        headToGoal();
    }
}

void EnemyTank::headToGoal()
{
    //qDebug()<<"CHASE";
    if (currentStep >= path.size())
    {
        // 如果已经到达路径终点，停止移动
        clearMovingState();
        return;
    }

    // 获取当前坦克的中心位置
    int currentX = (this->pos() + this->rect().center()).x();
    int currentY = (this->pos() + this->rect().center()).y();

    // 获取目标位置（路径中的下一个点）
    int goalX = path[currentStep].col * GRIDSIZE + GRIDSIZE / 2;
    int goalY = path[currentStep].row * GRIDSIZE + GRIDSIZE / 2;

    // 计算与目标点的距离
    int deltaX = goalX - currentX;
    int deltaY = goalY - currentY;

    // 如果已经接近目标点，则更新到下一个路径点
    if (abs(deltaX) < 5 && abs(deltaY) < 5)
    {
        currentStep++;
        clearMovingState();
        return;
    }

    // 更新移动状态，优先选择横向或纵向移动
    clearMovingState();

    if (abs(deltaX) > abs(deltaY))
    {
        if (deltaX > 0)
        {
            _movingState[RIGHT] = true;
        }
        else
        {
            _movingState[LEFT] = true;
        }
    }
    else
    {
        if (deltaY > 0)
        {
            _movingState[DOWN] = true;
        }
        else
        {
            _movingState[UP] = true;
        }
    }

    //qDebug() << "Current Position:" << currentX << currentY;
    //qDebug() << "Goal Position:" << goalX << goalY;
    //qDebug() << "Current Step:" << currentStep;
}



bool EnemyTank::isPathClear(QPointF start, QPointF end)
{
    // 检查从start到end的直线路径是否没有障碍物
    GameView* view = dynamic_cast<class GameView*>(this->scene()->views()[0]);
    int x1 = start.x();
    int y1 = start.y();
    int x2 = end.x();
    int y2 = end.y();

    // 使用DDA算法或Bresenham算法检查直线路径上的每一个格子
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        // 检查当前位置是否为墙
        if (view->gameData()->gridType(y1 / GRIDSIZE, x1 / GRIDSIZE) == BOX || view->gameData()->gridType(y1 / GRIDSIZE, x1 / GRIDSIZE) == WALL)
        {
            return false;
        }
        if (x1 == x2 && y1 == y2)
        {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    return true;
}


void EnemyTank::chase()
{
    qreal resetSec = 3;
    GameView* view = dynamic_cast<class GameView*>(this->scene()->views()[0]);
    QPointF playerPos = view->gameData()->playerTank()->pos() + QPointF(TANK_WIDTH / 2, TANK_LENGTH / 2);
    PlayerTank* playerTank = view->gameData()->playerTank();
    // 检查与玩家坦克之间是否有障碍物
    if (isPathClear(this->pos() + this->rect().center(), playerPos))
    {
        qDebug() << "ATTACK";
        view->createBullet(this->_bulletID,this,this->pos()+this->rect().center(),playerPos);
    }
    //qDebug()<<chasingCounter<<"/"<<_aiUpdateFrequency*resetSec;
    if(chasingCounter>_aiUpdateFrequency*resetSec)
    {
        //qDebug()<<"!";

        int tcol = (this->pos() + this->rect().center()).x() / GRIDSIZE;
        int trow = (this->pos() + this->rect().center()).y() / GRIDSIZE;
        int pcol = (playerTank->pos() + playerTank->rect().center()).x() / GRIDSIZE;
        int prow = (playerTank->pos() + playerTank->rect().center()).y() / GRIDSIZE;

        // 更新目标点为玩家坦克的位置，并且每次追击调用时重新规划路径
        QVector<Point> newPath = findPath(Point(trow, tcol), Point(prow, pcol));

        if (!newPath.empty())
        {
            path = newPath;
            currentStep = 0;
        }

        chasingCounter = 0;
    }
    else
    {
        // 保证路径被设置后持续调用 headToGoal 来保持敌方坦克的移动状态
        headToGoal();
    }
}

void EnemyTank::attack()
{

}

void EnemyTank::avoid()
{

}


QVector<Point> EnemyTank::findPath(Point start, Point goal) {
    // 获取地图数据
    GameView* view = dynamic_cast<class GameView*>(this->scene()->views()[0]);
    QVector<QVector<int>> map = view->gameData()->map();

    int rows = map.size();
    if (rows == 0) return QVector<Point>();
    int cols = map[0].size();
    if (cols == 0) return QVector<Point>();

    // 定义移动方向
    const std::vector<Point> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    // 检查坐标是否在地图范围内且是可通行区域
    auto isValid = [&](int r, int c) {
        return r >= 0 && r < rows && c >= 0 && c < cols && map[r][c] == AIR;
    };

    // 初始化队列
    std::queue<Point> queue;
    // 记录每个节点的父节点，用于回溯路径
    std::vector<std::vector<Point>> cameFrom(rows, std::vector<Point>(cols, {-1, -1}));

    // 将起点加入队列
    queue.push(start);
    // 将起点标记为已访问
    cameFrom[start.row][start.col] = start;

    // BFS 算法主循环
    while (!queue.empty()) {
        // 从队列中取出第一个节点
        Point current = queue.front();
        queue.pop();

        // 如果找到目标节点
        if (current.row == goal.row && current.col == goal.col) {
            // 回溯路径
            QVector<Point> path;
            Point parent = current;
            while (parent != start) {
                path.prepend(parent);
                parent = cameFrom[parent.row][parent.col];
            }
            path.prepend(start);
            return path;
        }

        // 遍历当前节点的邻居节点
        for (const auto& dir : directions) {
            int newRow = current.row + dir.row;
            int newCol = current.col + dir.col;
            Point neighbor(newRow, newCol);

            // 检查邻居节点是否有效且未访问过
            if (isValid(newRow, newCol) && cameFrom[newRow][newCol] == Point(-1, -1)) {
                // 将邻居节点加入队列
                queue.push(neighbor);
                // 设置邻居节点的父节点
                cameFrom[newRow][newCol] = current;
            }
        }
    }

    // 没有找到路径
    return QVector<Point>();
}

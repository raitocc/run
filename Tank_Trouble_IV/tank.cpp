#include "tank.h"
#include "parameter.h"
#include "qgraphicsscene.h"
//#include "turret.h" // 还没有有Turret类的头文件

// 构造函数
Tank::Tank(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    _HP = 100;
    _maxHP = 100;
    _moveSpeed = 5;
    _shootSpeed = 1;
    for (int i = 0; i < 4; ++i)
    {
        _movingState[i] = false;
    }
    _turret = nullptr;
}

// 获取血量
int Tank::HP() const
{
    return _HP;
}

// 获取移动速度
int Tank::moveSpeed() const
{
    return _moveSpeed;
}

// 获取射击速度
int Tank::shootSpeed() const
{
    return _shootSpeed;
}

// 获得移动状态
bool Tank::movingState(int dir) const
{
    return _movingState[dir];
}

// 获取炮塔
Turret* Tank::turret() const
{
    return _turret;
}

// 设置血量
void Tank::setHP(int hp)
{
    _HP = hp;
}

// 设置最大血量
void Tank::setMaxHP(int maxHP)
{
    _maxHP = maxHP;
}

// 增加血量
void Tank::addHP(int num)
{
    _HP += num;
    if (_HP > _maxHP) {
        _HP = _maxHP;
    }
}

// 减少血量
void Tank::reduceHP(int num)
{
    _HP -= num;
    if (_HP < 0) {
        _HP = 0;
    }
}

// 设置移动速度
void Tank::setMoveSpeed(int moveSpeed)
{
    _moveSpeed = moveSpeed;
}

// 设置射击速度
void Tank::setShootSpeed(int shootSpeed)
{
    _shootSpeed = shootSpeed;
}

// 设置移动状态
void Tank::setMovingState(int dir,bool state)
{
    _movingState[dir] = state;
    // for(int i=0;i<4;i++)
    // {
    //     qDebug()<<_movingState[i];
    // }
}

// 设置炮筒
void Tank::setTurret(Turret* turret)
{
    _turret = turret;
}

void Tank::clearMovingState()
{
    for(int i =0;i<4;i++)
    {
        _movingState[i]=false;
    }
}

void Tank::creatTurret()
{
    _turret = new Turret(this);
}


void Tank::move()
{
    QPointF oldPos = pos();
    int oldRotation = this->rotation();
    bool moved = false;
    bool movingUp = _movingState[UP];
    bool movingRight = _movingState[RIGHT];
    bool movingDown = _movingState[DOWN];
    bool movingLeft = _movingState[LEFT];
    int count = (movingDown+movingLeft+movingRight+movingUp);
    // 尝试主要方向的移动
    if (!moved && movingUp && movingRight)
    {
        moveBy(_moveSpeed/1.414, -_moveSpeed/1.414);
        if (!checkCollision()) {
            moved = true;
        } else {
            setPos(oldPos);
        }
    }
    if (!moved && movingUp && movingLeft)
    {
        moveBy(-_moveSpeed/1.414, -_moveSpeed/1.414);
        if (!checkCollision()) {
            moved = true;
        } else {
            setPos(oldPos);
        }
    }
    if (!moved && movingDown && movingRight)
    {
        moveBy(_moveSpeed / 1.414, _moveSpeed / 1.414);
        if (!checkCollision()) {
            moved = true;
        } else {
            setPos(oldPos);
        }
    }
    if (!moved && movingDown && movingLeft)
    {
        moveBy(-_moveSpeed / 1.414, _moveSpeed / 1.414);
        if (!checkCollision()) {
            moved = true;
        } else {
            setPos(oldPos);
        }
    }

    // 如果主要方向移动受阻，分别尝试各个单独方向的移动
    if (!moved) {
        if (movingUp)
        {
            if(count>=2)moveBy(0, -_moveSpeed/1.414);
            else moveBy(0, -_moveSpeed);
            if (!checkCollision()) {
                moved = true;
            } else {
                setPos(oldPos);
            }
        }
        if (!moved && movingDown)
        {
            if(count>=2)moveBy(0, _moveSpeed/1.414);
            else moveBy(0, _moveSpeed);
            if (!checkCollision()) {
                moved = true;
            } else {
                setPos(oldPos);
            }
        }
        if (!moved && movingLeft)
        {
            if(count>=2)moveBy(-_moveSpeed/1.414, 0);
            else moveBy(-_moveSpeed, 0);
            if (!checkCollision()) {
                moved = true;
            } else {
                setPos(oldPos);
            }
        }
        if (!moved && movingRight)
        {
            if(count>=2)moveBy(_moveSpeed/1.414, 0);
            else moveBy(_moveSpeed, 0);
            if (!checkCollision()) {
                moved = true;
            } else {
                setPos(oldPos);
            }
        }
    }

    // 更新方向
    if (moved) {
        updateDirection();
    } else {
        setRotation(oldRotation);
    }
}

bool Tank::checkCollision()
{
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        // 检查是否碰到障碍物
        if (item->data(GRID_TYPE)==WALL||item->data(GRID_TYPE)==BOX)
        {
            //qDebug()<<"COLL";
            return true;
        }
    }
    return false;
}

void Tank::adjustPosition()
{
    qDebug()<<"卡墙";
    QPointF oldPos = this->pos();
    const int maxAttempts = 40; // 最大尝试次数
    const qreal stepSize = 0.4; // 微调步进值
    for(int i = 0;i<maxAttempts;i++)
    {
        moveBy(0,stepSize);
        if(!checkCollision()) return;
    }
    this->setPos(oldPos);
    for(int i = 0;i<maxAttempts;i++)
    {
        moveBy(0,-stepSize);
        if(!checkCollision()) return;
    }
    this->setPos(oldPos);
    for(int i = 0;i<maxAttempts;i++)
    {
        moveBy(-stepSize,0);
        if(!checkCollision()) return;
    }
    this->setPos(oldPos);
    for(int i = 0;i<maxAttempts;i++)
    {
        moveBy(stepSize,0);
        if(!checkCollision()) return;
    }
    this->setPos(oldPos);
}

void Tank::updateDirection()
{
    bool movingUp = _movingState[UP];
    bool movingRight = _movingState[RIGHT];
    bool movingDown = _movingState[DOWN];
    bool movingLeft = _movingState[LEFT];
    if (movingUp && movingRight) {
        setRotation(45);
        if(checkCollision())
        {
            adjustPosition();
        }
    } else if (movingUp && movingLeft) {
        setRotation(-45);
        if(checkCollision())
        {
            adjustPosition();
        }
    } else if (movingDown && movingRight) {
        setRotation(135);
        if(checkCollision())
        {
            adjustPosition();
        }
    } else if (movingDown && movingLeft) {
        setRotation(-135);
        if(checkCollision())
        {
            adjustPosition();
        }
    } else if (movingUp) {
        setRotation(0);
        if(checkCollision())
        {
            adjustPosition();
        }
    } else if (movingDown) {
        setRotation(180);
        if(checkCollision())
        {
            adjustPosition();
        }
    } else if (movingLeft) {
        setRotation(-90);
        if(checkCollision())
        {
            adjustPosition();
        }
    } else if (movingRight) {
        setRotation(90);
        if(checkCollision())
        {
            adjustPosition();
        }
    }
}

//会调用2次，在第一个阶段，所有项目都以 phase == 0 调用，表明场景中的项目即将前进，然后所有项目都以 phase == 1 调用
void Tank::advance(int phase)
{
    if(phase == 0)
    {
        return;
    }
    else
    {
        move();
    }
}


Turret::Turret(Tank *parent)
{
    this->setParentItem(parent);
    this->setRect(0,0,TANK_WIDTH/2,TANK_LENGTH);

    _parentTank = parent;

    QPixmap pix(":/sources/TankTurret.png");
    QPixmap scaledPix =pix.scaled(TANK_WIDTH/2,TANK_LENGTH);
    this->setBrush(QBrush(scaledPix));
    this->setPen(Qt::NoPen);

    this->setTransformOriginPoint(QPointF(this->rect().width()/2,this->rect().height() * 3/4));
    this->setPos(parent->rect().center()-this->transformOriginPoint());
    qDebug()<<"TURRET"<<this->pos()<<this->brush();
    this->setZValue(5);
}

void Turret::setDirection(const QPointF &target)
{
    QPointF begin = _parentTank->pos()+_parentTank->rect().center();
    qreal angle = std::atan2(target.y()-begin.y(), target.x()-begin.x()) * 180 / M_PI;
    this->setRotation(angle- _parentTank->rotation() +90);
}

Tank *Turret::parentTank() const
{
    return _parentTank;
}

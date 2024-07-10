#include "playertank.h"
#include "parameter.h"
#include "qgraphicsscene.h"

PlayerTank::PlayerTank()
{
    init();
}

int PlayerTank::bulletNum(int id)
{
    return _bulletNum[id];
}

int PlayerTank::propsNum(int id) const
{
    return _propsNum[id];
}

int PlayerTank::currentBullet() const
{
    return _currentBullet;
}

QPointF PlayerTank::rotationCenter() const
{
    return _rotationCenter;
}

void PlayerTank::switchBullet(int id)
{
    _currentBullet = id;
}

void PlayerTank::addBullet(int id, int amout)
{
    if(id>=_bulletNum.size())
    {
        qDebug()<<"不存在id为:"<<id<<"的子弹";
        return;
    }
    _bulletNum[id] += amout;
}

void PlayerTank::removeBullet(int id, int amout)
{
    if(id>=_bulletNum.size())
    {
        qDebug()<<"不存在id为:"<<id<<"的道具";
        return;
    }
    _bulletNum[id] -= amout;
}

void PlayerTank::init()//初始化
{
    this->setPen(Qt::NoPen);//设置无边框

    //设置数值
    _HP = 20;
    _maxHP = 20;
    _moveSpeed = 0.8;
    _shootSpeed = 1;
    clearMovingState();//清空移动状态标记
    _turret = nullptr;
    _bulletNum.resize(MAX_BULLET_TYPE);
    _propsNum.resize(MAX_PROP_TYPE);
    _bulletNum[0] = INT_MAX;
    _rotationCenter = QPointF(TANK_WIDTH/2,TANK_LENGTH*2/3);
    for(int i=1;i<_bulletNum.size();i++)
    {
        _bulletNum[i]=0;
    }
    for(int i=1;i<_bulletNum.size();i++)
    {
        _propsNum[i]=0;
    }

    this->setRect(0,0,TANK_WIDTH,TANK_LENGTH);//设置碰撞箱
    this->setTransformOriginPoint(_rotationCenter);//设置旋转中心


    //使其接收键盘事件
    this->setFlag(ItemIsFocusable);
    this->setFocus();

}

void PlayerTank::clearMovingState()
{
    for(int i =0;i<4;i++)
    {
        _movingState[i]=false;
    }
}

void PlayerTank::move()
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

    // 如果主要方向移动受阻，分别尝试各个单独方向的移动,向下向右移动的向量为正方向
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

bool PlayerTank::checkCollision()
{
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        // 检查是否碰到障碍物
        if (item->data(GRIDTYPE)==WALL||item->data(GRIDTYPE)==BOX)
        {
            //qDebug()<<"COLL";
            return true;
        }
    }
    return false;
}

void PlayerTank::adjustPosition()
{
    qDebug() << "尝试解决卡住的问题";
    QPointF oldPos = this->pos();
    const int maxAttempts = 20;
    qreal initialStepSize = 0.4;
    qreal stepSize = initialStepSize;

    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        bool moved = false;

        for (int direction = 0; direction < 4; ++direction) {
            qreal dx = 0, dy = 0;
            switch (direction) {
            case 0: dy = -stepSize; break; // 向上移动
            case 1: dy = stepSize; break; // 向下移动
            case 2: dx = -stepSize; break; // 向左移动
            case 3: dx = stepSize; break; // 向右移动
            }

            moveBy(dx, dy);
            if (!checkCollision()) {
                moved = true;
                break; // 成功移动，跳出内循环
            }
            moveBy(-dx, -dy); // 没有成功移动，回到原来位置
        }

        if (moved) {
            break; // 成功移动，跳出外循环
        } else {
            // 逐步增加步进值
            stepSize += initialStepSize;
        }
    }

    // 如果尝试了多次仍然无法解决，回到原始位置
    if (!checkCollision()) {
        return; // 已经成功移动到目标位置
    } else {
        this->setPos(oldPos); // 回到原始位置
    }
}


void PlayerTank::updateDirection()
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
void PlayerTank::advance(int phase)
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

// void PlayerTank::keyPressEvent(QKeyEvent *event)
// {
//     qDebug()<<"Press";
// }

// void PlayerTank::keyReleaseEvent(QKeyEvent *event)
// {
//     qDebug()<<"Release";
// }

// QVariant PlayerTank::itemChange(GraphicsItemChange change, const QVariant &value)
// {
//     if(change == QGraphicsItem::ItemFlagsHaveChanged)
//     {
//         if(value.toBool())
//         {
//             qDebug()<<"Item has gained focus!";
//         }
//         else
//         {
//             qDebug()<<"Item has lost focus!";
//         }
//     }
//     return QGraphicsItem::itemChange(change, value);
// }


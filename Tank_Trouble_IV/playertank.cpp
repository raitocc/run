#include "playertank.h"
#include "gameview.h"
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

bool PlayerTank::shootAble() const
{
    return _shootAble;
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

void PlayerTank::setShootAble(bool f)
{
    _shootAble = f;
}

void PlayerTank::init()//初始化
{
    this->setPen(Qt::NoPen);//设置无边框

    //设置数值
    _HP = 20;
    _maxHP = 20;
    _moveSpeed = 0.8;
    _currentBullet = 0;
    _shootSpeed = 4;//频率
    clearMovingState();//清空移动状态标记
    _turret = nullptr;
    _bulletNum.resize(MAX_BULLET_TYPE);
    _propsNum.resize(MAX_PROP_TYPE);
    _bulletNum[0] = INT_MAX;
    _rotationCenter = QPointF(TANK_WIDTH/2,TANK_LENGTH/2);
    _shootAble = true;

    //z
    this->setZValue(3);

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
    // this->setFlag(ItemIsFocusable);
    // this->setFocus();

    //绘制炮筒
    this->creatTurret();

}

void PlayerTank::update()
{
    handleCollision();
}

void PlayerTank::handleCollision()//解决吃道具
{
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        // 子弹补给
        if (item->data(ITEM_TYPE)==BULLET_SUPLLY)
        {
            int id = item->data(BULLET_TYPE).toInt();
            int amout = item->data(BULLET_AMOUNT).toInt();
            //qDebug()<<id<<amout;
            this->addBullet(id,amout);
            this->scene()->removeItem(item);
            GameView* view = dynamic_cast<class GameView*>(this->scene()->views()[0]);
            view->gameData()->setSupplyFlag(item->pos().y()/GRIDSIZE,item->pos().x()/GRIDSIZE,false);
        }
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


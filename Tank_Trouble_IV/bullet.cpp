#include "bullet.h"
#include "parameter.h"

Bullet::Bullet(int id, Tank *shooter) :_id(id),_shooter(shooter)
{
    init();
}

Bullet::Bullet(int id, Tank *shooter, QPointF begin, QPointF tar):_id(id),_shooter(shooter)
{
    init(begin,tar);
}

int Bullet::id() const
{
    return _id;;
}

int Bullet::damage() const
{
    return _damage;
}

int Bullet::speed() const
{
    return _speed;
}

const QPointF &Bullet::direction() const
{
    return _direction;
}

Tank *Bullet::shooter() const
{
    return _shooter;
}

void Bullet::setId(int id)
{
    _id = id;
}

void Bullet::setDamage(int damage)
{
    _damage = damage;
}

void Bullet::setSpeed(double speed)
{
    _speed = speed;
}

void Bullet::setDirection(const QPointF &direction)
{
    _direction = direction;
}

void Bullet::init()
{

}

void Bullet::init(QPointF begin, QPointF tar)//初始化
{
    this->setRect(0,0,5,5);
    QLineF line(begin, tar);
    _direction = line.unitVector().p2() - line.unitVector().p1();
    _speed = 2.0;
    this->setData(ITEM_TYPE,BULLET);
    this->setBrush(QBrush(Qt::red));//红色
    setPos(begin-this->rect().center());//设置初始位置
    this->setZValue(2);
    _damage = 5;
}

void Bullet::advance(int phase)
{
    if(phase == 0) return;
    move();
}

void Bullet::move()
{
    this->setPos(this->pos()+_direction*_speed);
    if(checkCollision())
    {
        //qDebug()<<"COLLISION";
        delete this;
    }
}

bool Bullet::checkCollision()
{
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item);
        // 检查是否碰到地图格子
        if (rectItem->data(ITEM_TYPE)==GRID&&rectItem->data(GRID_TYPE)!=AIR)
        {
            //子弹碰到箱子
            if(rectItem->data(GRID_TYPE)==BOX)
            {
                hitBox(rectItem);
            }
            return true;
        }
        if(rectItem->data(ITEM_TYPE)==PLAYER_TANK||rectItem->data(ITEM_TYPE)==ENEMY_TANK)
        {
            Tank *tank = dynamic_cast<Tank *>(item);
            if(tank!=this->shooter())
            {
                hitTank(tank);
                return true;
            }
        }
    }
    return false;
}

void Bullet::hitBox(QGraphicsRectItem *box)
{
    box->setData(GRID_TYPE,AIR);
    box->setBrush(Qt::white);
}

void Bullet::hitTank(Tank *tank)
{
    tank->reduceHP(this->damage());
}

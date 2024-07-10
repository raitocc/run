#include "bullet.h"
#include "gameview.h"
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


//0为普通子弹，1为高速子弹
void Bullet::init(QPointF begin, QPointF tar)//初始化
{
    this->setRect(0,0,5,5);
    QLineF line(begin, tar);
    _direction = line.unitVector().p2() - line.unitVector().p1();
    this->setData(ITEM_TYPE,BULLET);
    setPos(begin-this->rect().center());//设置初始位置
    this->setZValue(2);
    switch (_id)
    {
    case 0://普通基础子弹
        _speed = 2.0;
        this->setBrush(QBrush(Qt::black));//黑色
        _damage = 5;
        break;
    case 1://高速子弹
        _speed = 5.0;
        this->setBrush(QBrush(Qt::red));//红色
        _damage = 7;
        break;
    }
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
    //消除箱子，这个格子的map置为AIR
    box->setData(GRID_TYPE,AIR);
    box->setBrush(Qt::white);
    GameView* view = dynamic_cast<class GameView*>(this->scene()->views()[0]);
    int row = box->rect().center().y()/GRIDSIZE;
    int col = box->rect().center().x()/GRIDSIZE;
    qDebug()<<row<<col;
    view->gameData()->setMap(row,col,AIR);
}

void Bullet::hitTank(Tank *tank)
{
    tank->reduceHP(this->damage());
}

////////////////////BULLET_SUPPLY////////////////////////////

BulletSupply::BulletSupply(int id, int num, QPointF pos)
{
    this->setRect(0,0,GRIDSIZE/3,GRIDSIZE/3);
    _id=id;
    _num=num;
    this->setData(ITEM_TYPE,BULLET_SUPLLY);
    this->setPos(pos);
}

BulletSupply::BulletSupply(int id, int num, int row, int col)
{
    this->setRect(0,0,GRIDSIZE/3,GRIDSIZE/3);
    _id=id;
    _num=num;
    this->setData(ITEM_TYPE,BULLET_SUPLLY);
    this->setPos(col*GRIDSIZE+GRIDSIZE/2-this->rect().center().x(),row*GRIDSIZE+GRIDSIZE/2-this->rect().center().y());
    QPixmap wall(":/new/prefix1/wall.png");
    QPixmap resizedwall =wall.scaled(GRIDSIZE/3, GRIDSIZE/3);

}

int BulletSupply::id() const
{
    return _id;
}

int BulletSupply::num() const
{
    return _num;
}

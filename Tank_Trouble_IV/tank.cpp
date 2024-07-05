#include "tank.h"
#include "bullet.h"
#include "qevent.h"
#include "qpainter.h"

void tank::inital_tank
    (
    string name_,
    string info_,
    int HP_,
    int tank_speed_,
    int attck_speed_,
    int width_,
    int length_,
    int shell_kind_
    )
{
    name=name_;
    info=info_;
    HP=MAX_HP=HP_;
    tank_speed=tank_speed_;//默认移速
    attck_speed=attck_speed_;//默认攻速
    width=width_;
    length=length_;//默认体积
    shell= new int[shellkind];
    shell[shell_kind_]=MAXNUM;//默认子弹数量为无穷
}
//我设定的子弹种类 #0普通子弹 #1双发普通子弹 #3爆炸子弹
//tank::tank(int ID):ID(ID),tank_angle (0), movingUp(false), movingDown(false), movingLeft(false), movingRight(false){


tank::tank(int ID):ID(ID),tank_angle (0), movingUp(false), movingDown(false), movingLeft(false), movingRight(false),QGraphicsPixmapItem(), cannonRotation(0.0){
    //这里我想的是每个tank型号我们定一个ID,创建时直接用ID就可以创建
    switch(ID)
    {
    case(1000)://默认机型
        inital_tank("","梦开始的地方",10,basic_tank_speed,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5000)://nomal
        inital_tank("Normal Tank","",4,basic_tank_speed*0.8,basic_attck_speed*0.5,tank_width,tank_length,0);
        break;
    case(5001)://advanced
        inital_tank("Advanced Tank","",8,basic_tank_speed,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5002)://elite
        inital_tank("Elite Tank","",20,basic_tank_speed,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5003)://commander
        inital_tank("Commander Tank","",24,basic_tank_speed*1.2,basic_attck_speed,tank_width,tank_length,0);
        break;
    case(5004)://boss
        inital_tank("boss Tank","",30,basic_tank_speed*1.2,basic_attck_speed*1.2,tank_width,tank_length,1);
        break;
    case(5005)://BOSS
        inital_tank("BOSS Tank","",40,basic_tank_speed*1.2,basic_attck_speed*1.5,tank_width,tank_length,1);
        break;
    case(5006)://Gun turret
        inital_tank("Gun Turret","",4,0,basic_attck_speed,tank_width,tank_length,1);
        break;
    case(5007)://Bomb turret
        inital_tank("Bomb turret","",4,0,basic_attck_speed*0.5,tank_width,tank_length,2);
        break;
    }

    // 初始化坦克身体和炮筒贴图并缩小
    tankBodyPixmap.load(":/new/prefix1/tankbody.png");
    QPixmap resettankBodyPixmap = tankBodyPixmap.scaled(20, 20, Qt::KeepAspectRatio);

    tankFirePixmap.load(":/new/prefix1/tankfire.png");
    QPixmap resettankFirePixmap = tankFirePixmap.scaled(5, 5, Qt::KeepAspectRatio);

    // 设置坦克身体的初始贴图
    setPixmap(resettankBodyPixmap);
    setTransformOriginPoint(resettankBodyPixmap.width() / 2, resettankBodyPixmap.height() / 2);

    // 设置坦克炮筒的初始贴图


    updateCannonRotation(QCursor::pos());  // 初始根据鼠标位置更新炮筒角度


}


// 假设计算角度的函数如下，这里仅作示意
int calculateAngle(const QPoint &targetPos) {
    // 计算炮筒应该指向鼠标位置的角度
    QPoint tankPos = mapToScene(pos());  // 坦克在场景中的位置
    QPoint direction = targetPos - tankPos;
    qreal angle = qRadiansToDegrees(qAtan2(direction.y(), direction.x()));
    return angle;
}

// 更新炮筒角度的函数
void updateCannonRotation(const QPoint &targetPos) {
    // 计算炮筒应该指向的角度
    // 这里假设根据鼠标位置计算炮筒角度的函数是 updateCannonRotation，具体实现视情况而定
    // 示意性地显示如何更新炮筒的角度
    int angle = calculateAngle(targetPos);
    //setRotation(angle);
}


void tank::setTankBodyPixmap(const QPixmap &pixmap) {
    tankBodyPixmap = pixmap;
    setPixmap(tankBodyPixmap.scaled(30, 30, Qt::KeepAspectRatio));
    setTransformOriginPoint(tankBodyPixmap.width() / 2, tankBodyPixmap.height() / 2);
}

void tank::setTankFirePixmap(const QPixmap &pixmap) {
    tankFirePixmap = pixmap;
}

void tank::updateCannonRotation(const QPointF &targetPos) {
    // 计算炮筒应该旋转的角度
    qreal dx = targetPos.x() - scenePos().x();  // 鼠标相对于坦克的x距离
    qreal dy = targetPos.y() - scenePos().y();  // 鼠标相对于坦克的y距离
    cannonRotation = qRadiansToDegrees(qAtan2(dy, dx));  // 计算角度

    // 更新炮筒的贴图和角度
    QPixmap rotatedPixmap = tankFirePixmap.transformed(QTransform().rotate(cannonRotation));
    setPixmap(rotatedPixmap);


}
tank::~tank() {
    delete[] shell;
}

void tank::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        movingUp = true;
        break;
    case Qt::Key_S:
        movingDown = true;
        break;
    case Qt::Key_A:
        movingLeft = true;
        break;
    case Qt::Key_D:
        movingRight = true;
        break;
    default:
        break;
    }
    updateDirection();
}

void tank::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        movingUp = false;
        break;
    case Qt::Key_S:
        movingDown = false;
        break;
    case Qt::Key_A:
        movingLeft = false;
        break;
    case Qt::Key_D:
        movingRight = false;
        break;
    default:
        break;
    }
    updateDirection();
}

void tank::updateDirection()
{
    if (movingUp && movingRight) {
        setRotation(45);
    } else if (movingUp && movingLeft) {
        setRotation(-45);
    } else if (movingDown && movingRight) {
        setRotation(135);
    } else if (movingDown && movingLeft) {
        setRotation(-135);
    } else if (movingUp) {
        setRotation(0);
    } else if (movingDown) {
        setRotation(180);
    } else if (movingLeft) {
        setRotation(-90);
    } else if (movingRight) {
        setRotation(90);
    }
}

//void tank::tank_move()
void tank::tank_move()//让坦克斜角运动时候不会被一面墙卡住
{
    QPointF oldPos = pos();
    int oldRotation = this->rotation();

    bool moved = false;
    int count = (movingDown+movingLeft+movingRight+movingUp);
    // 尝试主要方向的移动
    if (movingUp && movingRight)
    {
        moveBy(tank_speed/1.414, -tank_speed/1.414);
        moveBy(tank_speed / 1.414, -tank_speed / 1.414);
        if (!checkCollision()) {
            moved = true;
        } else {
            setPos(oldPos);
        }
    }
    if (!moved && movingUp && movingLeft)
    {
        moveBy(-tank_speed/1.414, -tank_speed/1.414);
        moveBy(-tank_speed / 1.414, -tank_speed / 1.414);
        if (!checkCollision()) {
            moved = true;
        } else {
            setPos(oldPos);
        }
    }
    if (!moved && movingDown && movingRight)
    {
        moveBy(tank_speed / 1.414, tank_speed / 1.414);
        if (!checkCollision()) {
            moved = true;
        } else {
            setPos(oldPos);
        }
    }
    if (!moved && movingDown && movingLeft)
    {
        moveBy(-tank_speed / 1.414, tank_speed / 1.414);
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
            if(count>=2)moveBy(0, -tank_speed/1.414);
            else moveBy(0, -tank_speed);
            if (!checkCollision()) {
                moved = true;
            } else {
                setPos(oldPos);
            }
        }
        if (!moved && movingDown)
        {
            if(count>=2)moveBy(0, tank_speed/1.414);
            else moveBy(0, tank_speed);
            if (!checkCollision()) {
                moved = true;
            } else {
                setPos(oldPos);
            }
        }
        if (!moved && movingLeft)
        {
            if(count>=2)moveBy(-tank_speed/1.414, 0);
            else moveBy(-tank_speed, 0);
            if (!checkCollision()) {
                moved = true;
            } else {
                setPos(oldPos);
            }
        }
        if (!moved && movingRight)
        {
            if(count>=2)moveBy(tank_speed/1.414, 0);
            else moveBy(tank_speed, 0);
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

void tank::resetMoving()
{
    movingDown=false;
    movingLeft=false;
    movingRight=false;
    movingUp=false;
}
bool tank::checkCollision()
{
    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems)
    {
        QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item);
        if (rectItem && rectItem->brush().color() == Qt::black)
        {
            return true;
        }
    }
    return false;
}

// void tank::setCannonRotation(qreal angle)
// {
//     cannonRotation = angle;
//     update();
// }

// void tank::updateCannonDirection(QPointF mousePos)
// {
//     QPointF tankCenter = pos() + QPointF(width / 2, length / 2);
//     QLineF line(tankCenter, mousePos);
//     setCannonRotation(-line.angle()); // -line.angle() to adjust to Qt's coordinate system
// }

// void tank::shoot()
// {

//     QPointF startPos = pos() + QPointF(width / 2, length / 2);
//     qreal cannonAngle = cannonRotation;  // Assuming the cannon rotates with the tank
//     qreal bulletSpeed = 10.0; // Define bullet speed
//     Bullet *bullet = new Bullet(startPos, cannonAngle, bulletSpeed, scene());

// }

// void tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
//     QGraphicsPixmapItem::paint(painter, option, widget);
//     // 绘制炮筒
//     painter->save();
//     painter->translate(width / 2, length / 2);
//     painter->rotate(cannonRotation);
//     painter->drawRect(QRectF(4, -12, 2, 10));
//     painter->restore();
// }
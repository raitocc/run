#include "gameview.h"
#include "qevent.h"
#include "parameter.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView{parent}
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(true);
    connect(&playerTankShootableTimer,&QTimer::timeout,this,&GameView::slotSwitchplayerTankShootableState);
}

void GameView::setGameData(GameData *data)
{
    this->data=data;
}

GameData* GameView::gameData() const
{
    return data;
}

void GameView::clearDeadTank()
{
    for(int i =0;i<data->enemyNum();i++)
    {
        if(!data->deadEnemy(i)&&data->enemyTank(i)->HP()<=0)
        {
            this->scene()->removeItem(data->enemyTank(i));
            data->addScore(50);
            data->addMoney(5);
            //qDebug()<<data->score()<<data->money();
            data->setDeadEnemy(i,true);
        }
    }
}

void GameView::setRandomBullet()//放置随机补给
{
    int averageSec = 3;
    int num = 1;
    int ran = QRandomGenerator::global()->bounded(0,120*averageSec*num);
    if(ran<num)
    {
        int amout = QRandomGenerator::global()->bounded(3,8);
        //qDebug()<<"产生随机子弹掉落物"<<ran+1<<"数量"<<amout;
        data->addBulletSupply(ran+1,amout,this->scene());
    }
}

void GameView::createBullet(int id, Tank* shooter,QPointF begin, QPointF tar)
{
    shooter->turret()->setDirection(tar);//更新炮筒转向
    QGraphicsRectItem* rect = data->addBullet(id,shooter,begin,tar);
    this->scene()->addItem(rect);
}

void GameView::wheelEvent(QWheelEvent *event)
{
    // 禁止鼠标滚轮移动视图
    event->ignore();
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();
    QPointF scenePos = this->mapToScene(viewPos);
    data->playerTank()->turret()->setDirection(scenePos);
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        //qDebug()<<"ViewPress";
        switch (event->key())
        {
        case Qt::Key_W:
            data->playerTank()->setMovingState(UP,true);
            break;
        case Qt::Key_D:
            data->playerTank()->setMovingState(RIGHT,true);
            break;
        case Qt::Key_S:
            data->playerTank()->setMovingState(DOWN,true);
            break;
        case Qt::Key_A:
            data->playerTank()->setMovingState(LEFT,true);
            break;
        }
    }
}

void GameView::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        //qDebug()<<"ViewRelease";
        switch (event->key())
        {
        case Qt::Key_W:
            data->playerTank()->setMovingState(UP,false);
            break;
        case Qt::Key_D:
            data->playerTank()->setMovingState(RIGHT,false);
            break;
        case Qt::Key_S:
            data->playerTank()->setMovingState(DOWN,false);
            break;
        case Qt::Key_A:
            data->playerTank()->setMovingState(LEFT,false);
            break;
        }
    }
}

void GameView::centerViewOnTank()
{
    // 获取坦克的中心位置
    QPointF tankCenter = data->playerTank()->pos() + QPointF(TANK_WIDTH/2, TANK_LENGTH / 2);

    // 计算视图的边界
    QRectF sceneRect = scene()->sceneRect();
    qreal halfWidth = this->viewport()->width() / 2;
    qreal halfHeight = this->viewport()->height() / 2;

    // 计算新的中心位置，确保不超出边界
    qreal newCenterX = qMin(sceneRect.right() - halfWidth, qMax(sceneRect.left() + halfWidth, tankCenter.x()));
    qreal newCenterY = qMin(sceneRect.bottom() - halfHeight, qMax(sceneRect.top() + halfHeight, tankCenter.y()));

    // 设置视图的中心
    this->centerOn(newCenterX, newCenterY);
}

void GameView::advance()
{
    centerViewOnTank();
    clearDeadTank();
    setRandomBullet();
    data->playerTank()->update();
}

void GameView::slotSwitchplayerTankShootableState()
{
    playerTankShootableTimer.stop();
    data->playerTank()->setShootAble(true);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    //左键按下，增添子弹
    if(data->playerTank()->shootAble()&&event->button() == Qt::LeftButton)
    {
        QPoint viewPos = event->pos();
        QPointF scenePos = this->mapToScene(viewPos);
        data->playerTank()->turret()->setDirection(scenePos);//更新炮筒转向
        PlayerTank* tank = data->playerTank();

        // qreal biasx = std::sin(M_PI*tank->rotation()/360.0) * QLineF(tank->pos()+tank->transformOriginPoint(),tank->pos()+tank->rect().center()).length();
        // qreal biasy = std::cos(M_PI*tank->rotation()/360.0) * QLineF(tank->pos()+tank->transformOriginPoint(),tank->pos()+tank->rect().center()).length();

        // qDebug()<<biasx<<biasy;
        if(tank->bulletNum(tank->currentBullet()>0))
        {
            QGraphicsRectItem* rect = data->addBullet(tank->currentBullet(),tank,tank->pos()+tank->rect().center()/*+QPointF(biasx,biasy)*/,scenePos);
            tank->addBullet(tank->currentBullet(),-1);//子弹数减一，减到零自动换下一个可用子弹
            if(tank->bulletNum(tank->currentBullet())==0)
            {
                this->data->switchPlayerCurrentBullet();
            }
            //qDebug()<<tank->pos();
            //qDebug()<<tank->pos()+tank->rect().center();
            this->scene()->addItem(rect);
            playerTankShootableTimer.start(1000/tank->shootSpeed());
            tank->setShootAble(false);
        }
    }
    //右键按下，顺序切换子弹
    if(data->playerTank()->shootAble()&&event->button() == Qt::RightButton)
    {
        this->data->switchPlayerCurrentBullet();
    }
}



#include "singlegamewidget.h"
#include "tank.h"
#include "tankturret.h"
#include "ui_singlegamewidget.h"
#include "testsheel.h"

//在这里创建（声明）tank才能在析构函数里面正常析构,因为我没在widget里面放指针
tank* tank1;//创建
TankTurret* turret1;

SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
    ,level(1)//默认从第一关开始
    ,money(0)//默认金币为零，可以以后放下面去
{
    ui->setupUi(this);
    map.createMap();
    ifFailed = false;

    //this->setMouseTracking(true);

    int tank_X,tank_Y;
    map.setRandomInitialPosition(tank_X,tank_Y);
    //tank = new testTank(&map);
    //tank = new testTank;

    tank1 = new class tank(1000);//堆上创建
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, gridSize * map.getcol(), gridSize * (map.getrow()+2)); // col和row是地图的列数和行数
    ui->graphicsView->setScene(scene);
    drawMap();

    //添加事件过滤器
    this->installEventFilter(this);

    tank1->setPos(gridSize, gridSize);
    scene->addItem(tank1);
    //强聚焦，始终接收键盘事件设置焦点策略
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
    //坦克重生点设置
    //不好意思有点误差
    tank1->setPos(tank_X-tank1->width/2, tank_Y-tank1->length/2);//设置坦克出生点
    tank1->setZValue(5); // 设置 tank1 的 Z 值为 1，防止被场景遮挡,这个可以有效解决其他的遮挡问题
    connect(tank1,&tank::signalGameFailed,this,&SingleGameWidget::slotFailed);


    turret1 = new TankTurret;
    turret1->setParentItem(tank1);
    turret1->setPos(tank1->width/2-8,-5);//试出来的数字，具有很大的不可重复利用性
    tank1->setTurret(turret1);

    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->centerOn(0,0);

    //强聚焦，始终接收键盘事件设置焦点策略
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();

    timer = new QTimer;
    timer->start(1000/165);//165Hz

    //与计时器有关请放到advance槽函数中，不需要重复connect
    connect(timer,&QTimer::timeout,this,&SingleGameWidget::advance);

    //血条实现d
    ui->progressBar->setRange(0,tank1->MAX_HP);
    //设置当前进度的值
    ui->progressBar->setValue(tank1->MAX_HP);
    //
    ui->progressBar->setFormat(QString::number(tank1->HP)+"/"+QString::number(tank1->MAX_HP));
    ui->progressBar->setInvertedAppearance(false); //true:反方向  false:正方向
    ui->progressBar->setAlignment(Qt::AlignCenter);  // This will add text over Progress Bar
    ui->progressBar->setStyleSheet("QProgressBar{height:25px; "//高度24像素
                                     "text-align: center; "//文本居中
                                     "font-size: 15px; "//字体大小14像素
                                     "color: white; "//文本颜色为白色
                                     "border-radius: 5px; "//5像素圆角
                                     "background: #e2e3e4;}"//浅灰色背景
                                     "QProgressBar::chunk{border-radius: 5px;"//填充部分也有5像素的圆角
                                   "background: red}" );//背景颜色为红色
    //槽函数，时刻检测血量变化
    connect(timer, &QTimer::timeout, this, &SingleGameWidget::if_HP_changed);
    connect(this, &SingleGameWidget::HP_changed, this, &::SingleGameWidget::progressBar_valueChanged);
}

bool SingleGameWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->graphicsView)
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            QGraphicsScene *scene = ui->graphicsView->scene();
            for (auto item : scene->items())
            {
                if (tank *tank0 = dynamic_cast<tank *>(item))
                {
                    if (event->type() == QEvent::KeyPress)
                    {
                        tank0->keyPressEvent(keyEvent);
                    }
                    else if (event->type() == QEvent::KeyRelease)
                    {
                        tank0->keyReleaseEvent(keyEvent);
                    }
                    return true;
                }
            }
        }
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            //qDebug() << "左键按下";

            // 获取点击位置在QGraphicsView的坐标
            QPoint viewPos = mouseEvent->pos();
            QPointF scenePos = ui->graphicsView->mapToScene(viewPos);

            //qDebug() << "点击位置在QGraphicsView坐标：" << viewPos;
            //qDebug() << "点击位置在场景坐标：" << scenePos;

            // 创建子弹并添加到场景中
            testSheel *bullet = new testSheel(tank1, tank1->pos(), scenePos);
            connect(timer,&QTimer::timeout,bullet,&testSheel::onMove);
            scene->addItem(bullet);
        }
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void SingleGameWidget::setViewFocus()
{
    ui->graphicsView->setFocus();
}

void SingleGameWidget::timerStart()
{
    timer->start(1000/60);
}

void SingleGameWidget::setTurretRotation()//设置炮筒转向
{
    // QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    // QPoint viewPos = mouseEvent->pos();
    // QPointF scenePos = ui->graphicsView->mapToScene(viewPos);
    // qDebug()<<"MouseMove";
    // // 更新炮筒的方向
    // turret1->setDirection(tank1->rotation(),scenePos - (tank1->pos()+QPoint(tank1->width/2-8,-5)));
    QPoint globalMousePos = QCursor::pos();
    QPoint viewPos = ui->graphicsView->mapFromGlobal(globalMousePos);
    QPointF scenePos = ui->graphicsView->mapToScene(viewPos);

    turret1->setDirection(tank1->rotation(), scenePos - (tank1->pos() + QPoint(tank1->width / 2 - 8, -5)));
}


SingleGameWidget::~SingleGameWidget()
{
    delete ui;
}

void SingleGameWidget::drawMap()
{
    for(int i = 0; i < map.getrow(); ++i)
    {
        for(int j = 0; j < map.getcol(); ++j)
        {
            QGraphicsRectItem *rect = scene->addRect(j*gridSize, i*gridSize, gridSize, gridSize);
            QPixmap wall(":/new/prefix1/wall.png");
            QPixmap resizedwall =wall.scaled(gridSize, gridSize);
            QPixmap box(":/new/prefix1/box.png");
            QPixmap resizedbox =box.scaled(gridSize, gridSize);
             rect->setPen(Qt::NoPen); // 确保没有边框
            // Load pixmap based on map element
            switch (map.getmap()[i][j])
            {
            case 0: // 不可破坏墙
                rect->setBrush(QBrush(resizedwall)); // 加载不可破坏墙的贴图
                rect->setData(1,0);
                break;
            case 1: // 可破坏墙体
                rect->setBrush(QBrush(resizedbox)); // 加载可破坏墙体的贴图
                rect->setData(1,1);
                break;
            case 2: // 其他类型的墙体或空白
                rect->setBrush(QBrush(Qt::white)); // 或者使用默认的白色填充
                rect->setData(1,2);
                break;
            }
        }
    }
    //scene->addItem(tank);

    //scene->addItem(tank); // 添加坦克或其他游戏元素
}

//按下暂停按钮
void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
    tank1->resetMoving();
    timer->stop();
}

void SingleGameWidget::advance()
{
    tank1->tank_move();
    centerViewOnTank();
    //tank1->GetOutOfWall();
    setTurretRotation();
}

void SingleGameWidget::slotFailed()
{
    timer->stop();
    tank1->resetMoving();
    if(!ifFailed){
        ifFailed = true;
        emit signalGameFailed();
    }
}

void SingleGameWidget::centerViewOnTank()
{
    // 获取坦克的中心位置
    QPointF tankCenter = tank1->pos() + QPointF(tank1->width / 2, tank1->length / 2);

    // 计算视图的边界
    QRectF sceneRect = scene->sceneRect();
    qreal halfWidth = ui->graphicsView->viewport()->width() / 2;
    qreal halfHeight = ui->graphicsView->viewport()->height() / 2;

    // 计算新的中心位置，确保不超出边界
    qreal newCenterX = qMin(sceneRect.right() - halfWidth, qMax(sceneRect.left() + halfWidth, tankCenter.x()));
    qreal newCenterY = qMin(sceneRect.bottom() - halfHeight, qMax(sceneRect.top() + halfHeight, tankCenter.y()));

    // 设置视图的中心
    ui->graphicsView->centerOn(newCenterX, newCenterY);
}



void SingleGameWidget::resizeEvent(QResizeEvent *event)//窗口size大小变化
{
    QWidget::resizeEvent(event);
    qDebug()<<"Resize";
    // 调整 QGraphicsView 的大小以适应窗口
    ui->graphicsView->setGeometry(0, 70, this->width(), this->height()-70);
}

void SingleGameWidget::if_HP_changed()
{
    //显示与实际血量不一致时发射信号
    if(ui->progressBar->value()!=tank1->HP){
    emit HP_changed();
    //直接赋值，//不知道会不会直接跳到槽
    ui->progressBar->setValue(tank1->MAX_HP);
    }
}
void SingleGameWidget::progressBar_valueChanged()
{
    //血量变化的信号
    //重设文本和进度条
    //ui->progressBar->setValue(tank1->MAX_HP);
    ui->progressBar->setFormat(QString::number(tank1->HP)+"/"+QString::number(tank1->MAX_HP));
}

//接受获胜判定的信号进入下一关
void SingleGameWidget::change_label_level()
{
    level++;
    ui->label_level->setText("当前关卡:"+QString::number(level));
}


// void SingleGameWidget::change_label_money()
// {
//         ui->label_money->setText("金币数:"+QString::number(money));
// }


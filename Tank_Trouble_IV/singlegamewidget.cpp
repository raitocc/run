#include "singlegamewidget.h"
#include "tank.h"
#include "ui_singlegamewidget.h"
//#include <QPainter>

#include <QtMath>

// 计算角度的函数
double calculateAngle(double x1, double y1, double x2, double y2)
{
    // 计算 y 和 x 方向上的差值
    double deltaY = y2 - y1;
    double deltaX = x2 - x1;

    // 计算弧度
    double radians = qAtan2(deltaY, deltaX);

    // 将弧度转换为角度
    double degrees = qRadiansToDegrees(radians);

    // 确保角度在 0 到 360 度之间
    if (degrees < 0) {
        degrees += 360;
    }

    return degrees;
}

//在这里创建（声明）tank才能在析构函数里面正常析构,因为我没在widget里面放指针
tank* tank1;//创建


SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    map.createMap();
    int tank_X,tank_Y;
    map.setRandomInitialPosition(tank_X,tank_Y);
    //tank = new testTank(&map);
    //tank = new testTank;
    tank1 = new class tank(1000);//堆上创建

    // 设置坦克的身体和炮筒贴图
    tank1->setTankBodyPixmap(QPixmap(":/new/prefix1/tankbody.png"));
    tank1->setTankFirePixmap(QPixmap(":/new/prefix1/tankfire.png"));

    // 更新炮筒的角度，可以在适当的时机调用，比如在鼠标移动事件中
    tank1->updateCannonRotation(QCursor::pos());
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, gridSize * map.getcol(), gridSize * (map.getrow()+2)); // col和row是地图的列数和行数
    ui->graphicsView->setScene(scene);
    //设置鼠标默认追踪
    ui->graphicsView->setMouseTracking(true);
    this->setMouseTracking(true);
    drawMap();
    //添加事件过滤器
    tank1->setPos(gridSize, gridSize);
    scene->addItem(tank1);
    ui->graphicsView->viewport()->installEventFilter(this);
    //确保 QGraphicsView 和 QWidget 允许鼠标事件传递
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    //强聚焦，始终接收键盘事件设置焦点策略
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
    //坦克重生点设置
    //不好意思有点误差
    tank1->setPos(tank_X-tank1->width/2, tank_Y-tank1->length/2);//设置坦克出生点
    tank1->setZValue(5); // 设置 tank1 的 Z 值为 1，防止被场景遮挡,这个可以有效解决其他的遮挡问题
    ui->graphicsView->installEventFilter(this);
    this->installEventFilter(this);//事件过滤器
    ui->graphicsView->centerOn(0,0);

    //初始化视图
    setInitGraphicView();

    timer = new QTimer;
    timer->start(1000/60);//60fps
    connect(timer,&QTimer::timeout,this,&SingleGameWidget::advance);
}

//事件过滤器
bool SingleGameWidget::eventFilter(QObject *watched, QEvent *event)
{
    //鼠标
    if (watched == ui->graphicsView->viewport())
    {
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            mouseMoveEvent(mouseEvent);
            return true;
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            mousePressEvent(mouseEvent);
            return true;
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            mouseReleaseEvent(mouseEvent);
            return true;
        }
    }
    //按键
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
        // if(event->type()==QEvent::)
        // {
        //     qDebug()<<"Wheel";
        //     return true;
        // }
    }
    return QWidget::eventFilter(watched, event);
}

void SingleGameWidget::setViewFocus()
{
    ui->graphicsView->setFocus();
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
             rect->setPen(Qt::NoPen); // 确保没有边框

            QPixmap wall(":/new/prefix1/wall.png");
            QPixmap resizedwall =wall.scaled(gridSize, gridSize);
            QPixmap box(":/new/prefix1/box.png");
            QPixmap resizedbox =box.scaled(gridSize, gridSize);
            // Load pixmap based on map element
            switch (map.getmap()[i][j])
            {
            case 0: // 不可破坏墙
                rect->setBrush(QBrush(resizedwall)); // 加载不可破坏墙的贴图
                break;
            case 1: // 可破坏墙体
                rect->setBrush(QBrush(resizedbox)); // 加载可破坏墙体的贴图
                break;
            case 2: // 其他类型的墙体或空白
                rect->setBrush(QBrush(QColor(255, 255, 255))); // 或者使用默认的白色填充
                break;
            }
        }
    }
    //scene->addItem(tank);

    //scene->addItem(tank); // 添加坦克或其他游戏元素
}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
    tank1->resetMoving();
}

void SingleGameWidget::advance()
{
    tank1->tank_move();
    centerViewOnTank();
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

//初始化视图
void SingleGameWidget::setInitGraphicView()
{
    //强聚焦，始终接收键盘事件设置焦点策略
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();


    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //连接鼠标事件信号与槽函数
    // connect(ui->graphicsView,&GameView::signalMouseMove,this,&SingleGameWidget::slotMouseMove);
    // connect(ui->graphicsView,&GameView::signalMousePress,this,&SingleGameWidget::slotMousePress);

    //安装事件过滤器
    ui->graphicsView->installEventFilter(this);

}void SingleGameWidget::mouseMoveEvent(QMouseEvent *event)
{
    //需要实时更新
    //if(event->button()==Qt::LeftButton){
        setMouseTracking(true);
        msx=event->pos().x();
        msy=event->pos().y();//相对坐标
        //qDebug()<<msx<<msy;
        int tank_x=tank1->pos().x()-tanklength/3;
        int tank_y=tank1->pos().y()-tanklength/2;
        tank1->shell_angle=calculateAngle(msx,msy,tank_x,tank_y);//得出炮筒角度
        ui->label_2->setText(QString::number(msx)+","+QString::number(msy));
    //}
}//我感觉并不需要
void SingleGameWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"pressed!";
    //想法是激活追踪
    //但是以后再实现
}void SingleGameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        tank1->shell_angle=calculateAngle(event->pos().x(),event->pos().y(),tank1->pos().x()-tanklength/3,tank1->pos().y()-tanklength/2);//得出炮筒角度
    //发射炮弹

    }

}
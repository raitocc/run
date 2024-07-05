#include "singlegamewidget.h"
#include "tank.h"
#include "ui_singlegamewidget.h"
#define gridSize 50
#define tanklength 30

//在这里创建（声明）tank才能在析构函数里面正常析构,因为我没在widget里面放指针
tank* tank1;//创建

SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    map.createMap();
    //tank = new testTank;
    tank1 = new class tank(1000);//堆上创建
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    drawMap();
    //添加事件过滤器
    tank1->setPos(gridSize, gridSize);
    scene->addItem(tank1);
    //坦克重生点设置

    tank1->setPos(500, 300);//设置坦克出生点
    tank1->setZValue(1); // 设置 tank1 的 Z 值为 1，防止被场景遮挡,这个可以有效解决其他的遮挡问题
    ui->graphicsView->installEventFilter(this);
    timer = new QTimer;
    timer->start(1000/60);
    connect(timer,&QTimer::timeout,this,&SingleGameWidget::advance);
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
    return QWidget::eventFilter(watched, event);
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
            QGraphicsRectItem *rect = scene->addRect(j*gridSize,i*gridSize,gridSize,gridSize);
            switch (map.getmap()[i][j])
            {
            case 0:
                rect->setBrush(QBrush(QColor(0,0,0)));
                break;
            case 1://可破坏墙体
                rect->setBrush(QBrush(QColor(0,255,255)));
                break;
            case 2:
                rect->setBrush(QBrush(QColor(255,255,255)));
                break;
            }
        }
    }
}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
    tank1->resetMoving();
}

void SingleGameWidget::advance()
{
    tank1->tank_move();
}


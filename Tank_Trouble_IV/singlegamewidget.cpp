#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"
#include "parameter.h"


//调用newGame函数，传入关卡数作为参数进行初始化工作
SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    newGameData();//从第一关新建游戏数据
    initView();//初始化视图
    initTimer();//初始化Timer
}

SingleGameWidget::~SingleGameWidget()
{
    delete ui;
    delete data;
}

void SingleGameWidget::newGameData()
{
    data = new GameData;
    data->newData();
}


void SingleGameWidget::initView()
{
    ui->graphicsView->setGameData(data);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);//强聚焦
    ui->graphicsView->setFocus();
    drawMap();//绘制地图
    drawTank();//绘制坦克
}

void SingleGameWidget::initTimer()
{
    timer = new QTimer(this);
    timer->start(1000/120);
    connect(timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    connect(timer,&QTimer::timeout,ui->graphicsView,&GameView::advance);
}

void SingleGameWidget::drawMap()
{
    int row = data->mapRow();
    int col = data->mapCol();
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            QGraphicsRectItem *rect = scene->addRect(j*GRIDSIZE, i*GRIDSIZE, GRIDSIZE, GRIDSIZE);
            rect->setData(ITEM_TYPE,GRID);
            QPixmap wall(":/sources/wall.png");
            QPixmap resizedwall =wall.scaled(GRIDSIZE, GRIDSIZE);
            QPixmap box(":/sources/box.png");
            QPixmap resizedbox =box.scaled(GRIDSIZE, GRIDSIZE);
            rect->setPen(Qt::NoPen); // 确保没有边框
            // Load pixmap based on map element
            switch (data->gridType(i,j))
            {
            case WALL: // 不可破坏墙
                rect->setBrush(QBrush(resizedwall)); // 加载不可破坏墙的贴图
                rect->setData(GRID_TYPE,WALL);
                break;
            case BOX: // 可破坏墙体
                rect->setBrush(QBrush(resizedbox)); // 加载可破坏墙体的贴图
                rect->setData(GRID_TYPE,BOX);
                break;
            case AIR: // 其他类型的墙体或空白
                rect->setBrush(QBrush(Qt::white)); // 留白
                rect->setData(GRID_TYPE,AIR);
                break;
            }
        }
    }
    ui->graphicsView->resize(this->width(),this->height()-STATEBAR_HEIGHT);
}

void SingleGameWidget::drawTank()
{
    //处理玩家坦克
    QPixmap body(":/sources/TankBody.png");
    QPixmap resizedbody =body.scaled(TANK_WIDTH, TANK_LENGTH);
    data->playerTank()->setBrush(QBrush(resizedbody));
    data->playerTank()->setData(ITEM_TYPE,PLAYER_TANK);
    scene->addItem(data->playerTank());
}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
}

void SingleGameWidget::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->resize(this->width(),this->height()-STATEBAR_HEIGHT);
    QWidget::resizeEvent(event);
}

// void SingleGameWidget::keyPressEvent(QKeyEvent *event)
// {
//     qDebug()<<"WidgetPress";
// }

// void SingleGameWidget::keyReleaseEvent(QKeyEvent *event)
// {
//     qDebug()<<"WidegtRelease";
// }

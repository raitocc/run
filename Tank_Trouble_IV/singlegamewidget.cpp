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
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    drawMap();//绘制地图
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
                rect->setData(GRIDTYPE,WALL);
                break;
            case BOX: // 可破坏墙体
                rect->setBrush(QBrush(resizedbox)); // 加载可破坏墙体的贴图
                rect->setData(GRIDTYPE,BOX);
                break;
            case AIR: // 其他类型的墙体或空白
                break;
            }
        }
    }
    ui->graphicsView->resize(this->width(),this->height()-STATEBAR_HEIGHT);
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

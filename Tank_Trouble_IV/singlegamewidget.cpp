#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"
#define gridSize 50
#define tanklength 30


SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    map.createMap();
    tank = new testTank;
    scene = new QGraphicsScene(this);
    // // 循环创建格子并添加到场景中
    // for (int row = 0; row < numCells; ++row) {
    //     for (int col = 0; col < numCells; ++col) {
    //         // 计算当前格子的位置
    //         int x = col * gridSize;
    //         int y = row * gridSize;


    //         QRandomGenerator *generator = QRandomGenerator::global();

    //         // 生成范围在 [0, 2] 内的随机整数
    //         int randomValue = generator->bounded(3);

    //         // 使用随机数来确定 GridItem 的类型
    //         GridItem::Type itemType = static_cast<GridItem::Type>(randomValue);


    //         // 创建矩形项并设置位置和大小
    //         QGraphicsRectItem *rect = new QGraphicsRectItem(x, y, gridSize, gridSize);
    //         scene->addItem(rect);
    //     }
    // }
    // QGraphicsRectItem *rect1 = new QGraphicsRectItem(50, 0, 1000, 1000);
    // scene->addItem(rect1);
    ui->graphicsView->setScene(scene);
    drawMap();
    //添加事件过滤器
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
                if (testTank *tank = dynamic_cast<testTank *>(item))
                {
                    if (event->type() == QEvent::KeyPress)
                    {
                        tank->keyPressEvent(keyEvent);
                    }
                    else if (event->type() == QEvent::KeyRelease)
                    {
                        tank->keyReleaseEvent(keyEvent);
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
    tank->setPos(gridSize, gridSize);
    scene->addItem(tank);
}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
}

void SingleGameWidget::advance()
{
    tank->advance();
}


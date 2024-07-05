#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"



SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    map.createMap();
    tank = new testTank(&map);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, gridSize * map.getcol(), gridSize * (map.getrow()+2)); // col和row是地图的列数和行数
    ui->graphicsView->setScene(scene);
    drawMap();
    //添加事件过滤器
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->centerOn(0,0);
    timer = new QTimer;
    timer->start(1000/60);//60fps
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
            QGraphicsRectItem *rect = scene->addRect(j*gridSize, i*gridSize, gridSize, gridSize);
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

    scene->addItem(tank); // 添加坦克或其他游戏元素
}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
}

void SingleGameWidget::advance()
{
    tank->advance();
    centerViewOnTank();
}

void SingleGameWidget::centerViewOnTank()
{
    // 获取坦克的中心位置
    QPointF tankCenter = tank->pos() + QPointF(tank->rect().width() / 2, tank->rect().height() / 2);

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


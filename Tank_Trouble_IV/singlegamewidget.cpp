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

    //强聚焦，始终接收键盘事件设置焦点策略
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();

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
    scene->addItem(tank);
}

void SingleGameWidget::on_btnPause_clicked()
{
    tank->resetMoving();
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


#include "singlegamewidget.h"
#include "tank.h"
#include "ui_singlegamewidget.h"

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
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, gridSize * map.getcol(), gridSize * (map.getrow()+2)); // col和row是地图的列数和行数
    ui->graphicsView->setScene(scene);
    drawMap();
    //添加事件过滤器
    tank1->setPos(gridSize, gridSize);
    scene->addItem(tank1);
    //强聚焦，始终接收键盘事件设置焦点策略
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
    //坦克重生点设置
    //不好意思有点误差
    tank1->setPos(tank_X-tank1->width/2, tank_Y-tank1->length/2);//设置坦克出生点
    tank1->setZValue(5); // 设置 tank1 的 Z 值为 1，防止被场景遮挡,这个可以有效解决其他的遮挡问题
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->centerOn(0,0);

    //强聚焦，始终接收键盘事件设置焦点策略
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();

    timer = new QTimer;
    timer->start(1000/60);//60fps
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
    connect(this, &SingleGameWidget::HP_changed, this, &SingleGameWidget::on_progressBar_valueChanged);
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


void SingleGameWidget::if_HP_changed()
{
    //显示与实际血量不一致时发射信号
    if(ui->progressBar->value()!=tank1->HP)
    emit HP_changed();
}
void SingleGameWidget::on_progressBar_valueChanged()
{
    //血量变化的信号
    //重设文本和进度条
    ui->progressBar->setValue(tank1->MAX_HP);
    ui->progressBar->setFormat(QString::number(tank1->HP)+"/"+QString::number(tank1->MAX_HP));
}


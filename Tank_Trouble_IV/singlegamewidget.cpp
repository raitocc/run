#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"
#include"griditem.h"


SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    map.createMap();

    scene = new QGraphicsScene(this);

    // 定义格子的大小
    int gridSize = 50;
    int numCells = 50;

    // 循环创建格子并添加到场景中
    for (int row = 0; row < numCells; ++row) {
        for (int col = 0; col < numCells; ++col) {
            // 计算当前格子的位置
            int x = col * gridSize;
            int y = row * gridSize;


            QRandomGenerator *generator = QRandomGenerator::global();

            // 生成范围在 [0, 2] 内的随机整数
            int randomValue = generator->bounded(3);

            // 使用随机数来确定 GridItem 的类型
            GridItem::Type itemType = static_cast<GridItem::Type>(randomValue);


            // 创建矩形项并设置位置和大小
            QGraphicsRectItem *rect = new QGraphicsRectItem(x, y, gridSize, gridSize);
            scene->addItem(rect);
        }
    }
    QGraphicsRectItem *rect1 = new QGraphicsRectItem(50, 0, 1000, 1000);
    scene->addItem(rect1);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(200,200);


}

SingleGameWidget::~SingleGameWidget()
{
    delete ui;

}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
}


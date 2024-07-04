#include "PlayerScene.h"
#include <QVBoxLayout>


PlayerScene::PlayerScene(QWidget *parent) : QWidget(parent)
{
    mapView = new QGraphicsView(this);
    mapScene = new QGraphicsScene(this);
    mapView->setScene(mapScene);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mapView);
    setLayout(layout);

    setupMap(); // 初始化地图
}

PlayerScene::~PlayerScene()
{
    // 如果有需要清理的资源，可以在这里添加代码
}


void PlayerScene::setMap(const QPixmap &mapPixmap)
{
    // 清除之前的场景内容
    mapScene->clear();

    // 添加新的地图图片到场景中
    mapScene->addPixmap(mapPixmap);

    // 根据需要设置视图的大小和缩放等属性
    mapView->fitInView(mapScene->sceneRect(), Qt::KeepAspectRatio);
}

void PlayerScene::setupMap()
{
    const int tileSize = 40; // 每个方块的大小
    const int padding = 2; // 方块之间的间隔

    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            QGraphicsRectItem *item = new QGraphicsRectItem(j * (tileSize + padding), i * (tileSize + padding), tileSize, tileSize);

            switch (map[i][j]) {
            case EMPTY:
                item->setBrush(Qt::white);
                break;
            case UNBREAKABLE:
                item->setBrush(Qt::gray);
                break;
            case BREAKABLE:
                item->setBrush(Qt::darkGray);
                break;
            default:
                item->setBrush(Qt::white);
            }

            scene->addItem(item);
        }
    }

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void PlayerScene::updateMap()
{
    // 在这里添加地图更新逻辑，例如根据用户操作更新地图显示
    // 可以根据需要实现具体的功能
}

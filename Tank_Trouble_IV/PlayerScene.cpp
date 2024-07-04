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

void PlayerScene::setupMap()
{
    // 在这里添加地图初始化逻辑，例如添加地图元素等
    // 这只是一个示例，具体根据你的地图数据和需求来实现


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

void PlayerScene::updateMap()
{
    // 在这里添加地图更新逻辑，例如根据用户操作更新地图显示
    // 可以根据需要实现具体的功能
}

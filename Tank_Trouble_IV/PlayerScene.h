#ifndef PLAYERSCENE_H
#define PLAYERSCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class PlayerScene : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerScene(QWidget *parent = nullptr);

    virtual ~PlayerScene(); // 声明析构函数为虚函数

    void setMap(const QPixmap &mapPixmap); // 设置地图的函数
    void setupMap();
    void updateMap(); // 更新地图的函数

private:
    QGraphicsView *mapView;
    QGraphicsScene *mapScene;
};

#endif // PLAYERSCENE_H

#ifndef PLAYERSCENE_H
#define PLAYERSCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>


#include <QKeyEvent>

#include <QStackedWidget>

#include <QGraphicsRectItem>


#define EMPTY 0
#define UNBREAKABLE 1
#define BREAKABLE 2


class PlayerScene : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerScene(QWidget *parent = nullptr);

    virtual ~PlayerScene(); // 声明析构函数为虚函数

    void setMap(const QPixmap &mapPixmap); // 设置地图的函数
    void setupMap();
    void updateMap(); // 更新地图的函数


    QGraphicsScene *scene;
    QGraphicsView *view;
    const int MAP_SIZE = 10;
    int map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 2, 0, 0, 1, 0, 2, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 2, 0, 0, 0, 0, 2, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 2, 0, 0, 1, 0, 2, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };


private:
    QGraphicsView *mapView;
    QGraphicsScene *mapScene;
};

#endif // PLAYERSCENE_H

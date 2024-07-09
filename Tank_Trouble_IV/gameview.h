#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "gamedata.h"
#include <QGraphicsView>
#include <QWidget>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    void setGameData(GameData* data);

protected:
    void wheelEvent(QWheelEvent *event) override;

    //void mouseMoveEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    GameData* data;


signals:
};

#endif // GAMEVIEW_H

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "gamedata.h"
#include "qtimer.h"
#include <QGraphicsView>
#include <QWidget>
#include <QtMath>
#include <QRandomGenerator>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    void setGameData(GameData* data);
    GameData *gameData() const;

    void clearDeadTank();
    void setRandomBullet();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void centerViewOnTank();//追随坦克

private:
    GameData* data;

      int numItemsSpawned = 0; // 已经刷新的物品数量

    QTimer playerTankShootableTimer;

public slots:
    void advance();
    void slotSwitchplayerTankShootableState();


signals:
};

#endif // GAMEVIEW_H

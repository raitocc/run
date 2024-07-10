#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "gamedata.h"
#include <QGraphicsView>
#include <QWidget>
#include <QtMath>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    void setGameData(GameData* data);

    void clearDeadTank();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void centerViewOnTank();//追随坦克

private:
    GameData* data;

    QTimer playerTankShootableTimer;

public slots:
    void advance();
    void slotSwitchplayerTankShootableState();


signals:
};

#endif // GAMEVIEW_H

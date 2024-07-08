#ifndef TANKTURRET_H
#define TANKTURRET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class TankTurret : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TankTurret(QGraphicsItem *parent = nullptr);
    void setDirection(int tankRotation, const QPointF &direction);
    void setPixmap(const QPixmap &pixmap); // 添加设置贴图的方法

protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPointF targetDirection;
};

#endif // TANKTURRET_H

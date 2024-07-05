#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsRectItem>

class GridItem : public QGraphicsRectItem {
public:
    enum Type {
        Empty,
        BreakableWall,
        UnbreakableWall
    };

    GridItem(int x, int y, int size, Type itemType, QGraphicsItem *parent = nullptr);

private:
    Type type;
};

#endif // GRIDITEM_H

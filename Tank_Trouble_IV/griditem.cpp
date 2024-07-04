#include "griditem.h"
#include <QBrush>

GridItem::GridItem(int x, int y, int size, Type itemType, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, size, size, parent), type(itemType) {
    // 根据类型设置颜色或其他属性
    switch (type) {
    case Empty:
        setBrush(Qt::white);
        break;
    case BreakableWall:
        setBrush(Qt::gray);
        break;
    case UnbreakableWall:
        setBrush(Qt::black);
        break;
    default:
        break;
    }
}

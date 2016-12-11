#include "CircleItem.h"

#include <QGraphicsEllipseItem>
CircleItem::CircleItem()
{
    QGraphicsEllipseItem circle(0, 0, 20, 20);

    this->setRect(circle.rect());
    setFlags(ItemIsMovable | ItemIsSelectable);
}

CircleItem::~CircleItem()
{
}

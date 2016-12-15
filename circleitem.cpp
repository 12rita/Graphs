#include "circleItem.h"
#include "textitem.h"
#include <QGraphicsEllipseItem>
CircleItem::CircleItem()

{
	st++;
	QGraphicsEllipseItem circle(0, 0, 20, 20);

	this->setRect(circle.rect());
	setFlags(ItemIsMovable | ItemIsSelectable);
}
void CircleItem::tie(QGraphicsTextItem *tex)

{
	text = tex;

}

CircleItem::~CircleItem()
{
}

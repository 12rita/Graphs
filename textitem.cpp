#include "textitem.h"
#include <QGraphicsTextItem>


textItem::textItem(QString a, QGraphicsItem *c)
{
    circle = c;
    this->setPlainText(a);
   
}
textItem::~textItem()
{

}

void textItem::movement()
{
    this->setPos(circle->x(), circle->y());
}

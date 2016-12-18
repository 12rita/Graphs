#include "lineItem.h"


#include <QGraphicsLineItem>


lineItem::lineItem(QGraphicsItem* a, QGraphicsItem* b)
{
	ver1 = a;
	ver2 = b;

	this->setLine(a->x() + 10, a->y() + 10, b->x() + 10, b->y() + 10);//магические числа
	setFlag(ItemIsSelectable);
}

lineItem::~lineItem()
{
}

void lineItem::redo()
{
	this->setLine(ver1->x() + 10, ver1->y() + 10, ver2->x() + 10, ver2->y() + 10);//тоже самое
}

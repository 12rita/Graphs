#ifndef LINEITEM_H
#define LINEITEM_H
#include <QGraphicsLineItem>
#include <QPointF>
#include "circleItem.h"

class lineItem : public QGraphicsLineItem//Вместо двух классов lineitem и textitem
                                         //можно было создать один, устанавливающий все связи
{
public:
	lineItem();
	QGraphicsItem* ver1;
	QGraphicsItem* ver2;
	lineItem(QGraphicsItem* a, QGraphicsItem* b);
	void redo();
	~lineItem();
};
#endif // LINEITEM_H

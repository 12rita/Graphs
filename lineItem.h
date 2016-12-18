#ifndef LINEITEM_H
#define LINEITEM_H
#include <QGraphicsLineItem>
#include <QPointF>
#include "circleItem.h"

class lineItem : public QGraphicsLineItem
{
public:
	lineItem();
	QGraphicsItem* ver1;//why not cirleitem ?
	QGraphicsItem* ver2;//
	lineItem(QGraphicsItem* a, QGraphicsItem* b);
	void redo();
	~lineItem();
};
#endif // LINEITEM_H

#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H
#include <QGraphicsEllipseItem>
#include <QPointF>
#include "textitem.h"

class CircleItem : public QGraphicsEllipseItem
{
public:
	CircleItem();
	QGraphicsTextItem* text;
	static int st;


	//QGraphicsEllipseItem* vertex1;
	void tie(QGraphicsTextItem* tex);

	~CircleItem();
};


#endif // CIRCLEITEM_H

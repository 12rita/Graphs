#ifndef PAINTERWINDOW_H
#define PAINTERWINDOW_H

#include <QMainWindow>
#include "qgraphicsview.h"
#include <QMenu>
//#include "triangleitem.h"
#include <QPair>
#include <QColor>
#include "circleItem.h"
#include "lineItem.h"
#include <vector>
#include <QGraphicsTextItem>
#include <QObject>
#include "textitem.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include "dialog.h"

namespace Ui {
class PainterWindow;
}

class PainterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PainterWindow(QWidget *parent = 0);
    ~PainterWindow();
    void setupMenus();
    void setupSceneThings();
    QIcon createIcon(QColor color);

private:
    Ui::PainterWindow *ui;
    std::vector<lineItem*> lines;
    std::vector<CircleItem*>vertex;
    std::vector<textItem*>names;
    QGraphicsView *mView;
    QGraphicsScene *mScene;

public slots:
    void paintCircle();
    void rotateItem();
    void zoomIn();
    void zoomOut();
    void setColor(QAction*);
    void AddEdge();
    void rework();
    void DeleteEdge();
    void writeTeX();
    void ShowDialog();
    void paintCircle1(QString *a);
    void RemoveCircle(QString *a);
    void AddEdge1(QString *a, QString *b);
    void DeleteEdge1(QString *a, QString *b);
    void ClearAll();



};

#endif // PAINTERWINDOW_H


#include <QtWidgets/QMainWindow>



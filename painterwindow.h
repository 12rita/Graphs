#ifndef PAINTERWINDOW_H
#define PAINTERWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include "qgraphicsview.h"
#include <QMenu>
//#include "triangleitem.h"
#include <QPair>
#include <QColor>
#include "CircleItem.h"
#include "lineItem.h"
#include <vector>
#include <QGraphicsTextItem>
#include <QObject>
#include "textitem.h"

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
    //void sceneChanged();
    void AddEdge();
    void rework();
    void DeleteEdge();


};

#endif // PAINTERWINDOW_H


#include <QtWidgets/QMainWindow>



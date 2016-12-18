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
#include "dialog1.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include "help.h"
#include <QColorDialog>
namespace Ui {
class PainterWindow;
}

class PainterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PainterWindow(QWidget *parent = 0);
    ~PainterWindow();
    void setupMenus();//why not privat?
    void setupSceneThings();//too
    QIcon createIcon(QColor color);

private:
    Ui::PainterWindow *ui;
    std::vector<lineItem*> lines;//may be smart pointers?
    std::vector<CircleItem*> vertex;//
    std::vector<textItem*> names;//
    std::vector<textItem*> names_lines;//
    std::vector<QColor> colors;
    QGraphicsView *mView;
    QGraphicsScene *mScene;

public slots:
    void paintCircle();
    void rotateItem();//do not use?
    void zoomIn();
    void zoomOut();
    void setColor(QAction*);
    void AddEdge();
    void rework();
    void DeleteEdge();
    void writeTeX();
    void ShowDialog();//
    void ShowDialog1();
    void ShowDialog2();
    void ShowDialogCol();
    void paintCircle1(QString *a);//may be overload paint circle?
    void RemoveCircle(QString *a);
    void AddEdge1(QString *a, QString *b);//--
    void DeleteEdge1(QString *a, QString *b);//--
    void ClearAll();
    void rename(QString a,QString b);

protected:
void keyPressEvent(QKeyEvent *event);
//void mousePressEvent(QMouseEvent *event);



};

#endif // PAINTERWINDOW_H


#include <QtWidgets/QMainWindow> //in the end??



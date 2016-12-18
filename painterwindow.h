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
    void setupMenus();//можно в приват
    void setupSceneThings();//тоже
    QIcon createIcon(QColor color);

private:
    Ui::PainterWindow *ui;
    std::vector<lineItem*> lines;//можно использовать умные указатели, для гарантии разрушения
    std::vector<CircleItem*> vertex;//
    std::vector<textItem*> names;//
    std::vector<textItem*> names_lines;//
    std::vector<QColor> colors;
    QGraphicsView *mView;
    QGraphicsScene *mScene;

public slots:
    void paintCircle();
    void rotateItem();//неиспользуется?
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
    void paintCircle1(QString *a);//перегрузка
    void RemoveCircle(QString *a);
    void AddEdge1(QString *a, QString *b);//можно было перегрузить предыдущую функцию
    void DeleteEdge1(QString *a, QString *b);//тоже
    void ClearAll();
    void rename(QString a,QString b);

protected:
void keyPressEvent(QKeyEvent *event);
//void mousePressEvent(QMouseEvent *event);



};

#endif // PAINTERWINDOW_H


#include <QtWidgets/QMainWindow> //в конце?



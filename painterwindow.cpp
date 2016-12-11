#include "painterwindow.h"
#include "ui_painterwindow.h"

PainterWindow::PainterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PainterWindow)
{
    ui->setupUi(this);
    setupSceneThings();
    setupMenus();
}




void PainterWindow::setupMenus() {
   /* QAction *clearAction = new QAction("Clear window", this);
    connect(clearAction, SIGNAL(triggered()), mScene, SLOT(clear()));*/

    QAction *rotateAction = new QAction("Rotate", this);
    connect(rotateAction, SIGNAL(triggered()), this, SLOT(rotateItem()));

  // QMenu *menu = new QMenu("Paint", this);
    // menu->addAction(clearAction);


    QMenu *menu1 = new QMenu("Object", this);
    menu1->addAction(rotateAction);

    QMenuBar* mBar = menuBar();



    QToolBar* tBar = new QToolBar(this);
    tBar->addAction(rotateAction);


    QAction *drawCircle = new QAction("Circle", this);
    connect(drawCircle, SIGNAL(triggered()), this, SLOT(paintCircle()));
    tBar->addAction(drawCircle);

    QAction *zoomin = new QAction("zoomIn", this);
    connect(zoomin, SIGNAL(triggered()), this, SLOT(zoomIn()));
    tBar->addAction(zoomin);

    QAction *zoomout = new QAction("zoomOut", this);
    connect(zoomout, SIGNAL(triggered()), this, SLOT(zoomOut()));
    tBar->addAction(zoomout);

    QAction *addEdge = new QAction("Edge", this);
    connect(addEdge, SIGNAL(triggered()), this, SLOT(AddEdge()));
    tBar->addAction(addEdge);

    QAction *deleteob = new QAction("Delete", this);
    connect(deleteob, SIGNAL(triggered()), this, SLOT(DeleteEdge()));
    tBar->addAction(deleteob);

    auto colors = std::vector<QColor>();
    colors.push_back(QColor(95, 36, 138));
    colors.push_back(QColor(218, 206, 61));

    QActionGroup* ag = new QActionGroup(this);

    QToolBar* colorToolbar = new QToolBar(this);
    for (const auto& color : colors) {
        QAction* colorAction = new QAction(createIcon(color), "someColor", this);
        colorAction->setData(color);
        ag->addAction(colorAction);
        colorToolbar->addAction(colorAction);
    }

    connect(ag, SIGNAL(triggered(QAction*)), this, SLOT(setColor(QAction*)));


    addToolBar(colorToolbar);
    addToolBar(tBar);
   // mBar->addMenu(menu);
    mBar->addMenu(menu1);



}

//void PainterWindow::sceneChanged() {
//	auto items = mScene->selectedItems();
//	if (items.count() == 0)
//	{
//		return;
//	}
//	auto item = items.front();
//	auto collidingIts = item->collidingItems();
//	for (auto colIt : collidingIts) {
//		static_cast<Circle1Item*>(colIt)->setBrush(QBrush(QColor(255, 0, 0)));
//
//	}
//}

void PainterWindow::rework()
{
    for (auto i : lines)

    {

        mScene->removeItem(i);
        i->redo();
        mScene->addItem(i);
    }
    for (auto i: names)
    {
      mScene->removeItem(i);
        i->movement();
        mScene->addItem(i);
    }
}

void PainterWindow::setupSceneThings() {
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, 1000, 1000);
    mView = new QGraphicsView(this);
    mView->setScene(mScene);
    this->setCentralWidget(mView);

    connect(mScene, SIGNAL(changed(const QList<QRectF> &)), this, SLOT(rework()));
}

void PainterWindow::paintCircle() {
    CircleItem* mCircle = new CircleItem();
    mScene->addItem(mCircle);
    mCircle->setPos(mView->mapToScene(0,0));
    vertex.push_back(mCircle);
  // setObjectName(QString::number(vertex.size()));
textItem* name = new textItem(QString::number(vertex.size()), mCircle);
names.push_back(name);
//this-> QGraphicstextItem::setPlainText(name);
mScene->addItem(name);
   // qPrintable( objectName(QString::number(vertex.size()));

}

void PainterWindow::rotateItem() {
    auto items = mScene->selectedItems();
    if (items.count() == 0)
    {
        return;
    }
    auto item = items.front();
    item->setRotation(item->rotation() + 25);
}

void PainterWindow::zoomIn() {

    mView->scale(1.25, 1.25);
}

void PainterWindow::zoomOut() {
    mView->scale(0.8, 0.8);
}
void PainterWindow::AddEdge()
{

    auto selectedCircles = mScene->selectedItems();
    for (int i = 0; i < selectedCircles.size();i++)
    {
        for (int j = i+1; j < selectedCircles.size(); j++)
        {
             bool flag = true;


            for (auto k:lines )
            {

                if (((k->ver1==selectedCircles[i])&& (k->ver2==selectedCircles[j])) || ((k->ver2==selectedCircles[i])&& (k->ver1==selectedCircles[j])) )
                {
        flag=false;
                }

            }
            if (flag)
             {
                 lineItem* newline = new lineItem(selectedCircles[i], selectedCircles[j]);
                 mScene->addItem(newline);
                 lines.push_back(newline);
             }




            //mScene->addLine(coordinates1, coordinates2, coordinates3, coordinates4);
        }
    }
    //LineItem* mLine = new LineItem(coordinates1, coordinates2, coordinates3, coordinates4);
    //mLine->x();

    // mScene->addItem(mLine);

}
void PainterWindow::DeleteEdge()
{
    auto selected = mScene->selectedItems();
    for (auto i : selected)
    {
        mScene->removeItem(i);
        lines.clear();
      

        
    }
}
QIcon PainterWindow::createIcon(QColor color) {

    QPixmap mPix(20, 20);

    QPainter mPaint(&mPix);
    mPaint.setBrush(QBrush(color));
    mPaint.drawRect(0, 0, 20, 20);

    return QIcon(mPix);

}

void PainterWindow::setColor(QAction* mAct) {

    auto color = mAct->data().value<QColor>();
    auto items = mScene->selectedItems();
    if (items.count() == 0)
    {
        return;
    }
    auto item = items.front();

    static_cast<CircleItem*>(item)->setBrush(QBrush(color));
}
PainterWindow::~PainterWindow()
{
    delete ui;
}

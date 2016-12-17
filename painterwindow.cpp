#include "painterwindow.h"
#include "ui_painterwindow.h"

PainterWindow::PainterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PainterWindow)
{
    ui->setupUi(this);
    setupSceneThings();
    setupMenus();
     connect(this, SIGNAL(mouseDoubleClickEvent(QMouseEvent * event)), this, SLOT(ShowDialogCol()));

}


int CircleItem::st=0;

void PainterWindow::rename(QString a,QString b)
{
    for(auto i: vertex)
    {
        if (i->text->toPlainText()==a)
        {
            i->text->setPlainText(b);
        }
    }
}

void PainterWindow::setupMenus() {



    QMenu *menu = new QMenu("File", this);

   QMenuBar* mBar = menuBar();

   QMenu *menu1 = new QMenu("View", this);

   QMenu *menu2 = new QMenu("Design", this);
  QMenu *menu3=new QMenu("Help", this);



    QToolBar* tBar = new QToolBar(this);


    QAction *helping = new QAction("Help", this);
    connect(helping, SIGNAL(triggered(bool)), this, SLOT(ShowDialog2()));
   menu3->addAction(helping);


    QAction *newg = new QAction("New graph", this);
    connect(newg, SIGNAL(triggered(bool)), this, SLOT(ShowDialog()));
    menu->addAction(newg);

    QAction *comm = new QAction("Command", this);
    connect(comm, SIGNAL(triggered(bool)), this, SLOT(ShowDialog1()));
    menu->addAction(comm);

    QAction *drawCircle = new QAction("Vertex", this);
    connect(drawCircle, SIGNAL(triggered()), this, SLOT(paintCircle()));
    menu2->addAction(drawCircle);

    QAction *addEdge = new QAction("Edge", this);
    connect(addEdge, SIGNAL(triggered()), this, SLOT(AddEdge()));
    menu2->addAction(addEdge);

    QAction *zoomin = new QAction("Zoom in", this);
    connect(zoomin, SIGNAL(triggered()), this, SLOT(zoomIn()));
    menu1->addAction(zoomin);

    QAction *zoomout = new QAction("Zoom out", this);
    connect(zoomout, SIGNAL(triggered()), this, SLOT(zoomOut()));
    menu1->addAction(zoomout);

    QAction *saving = new QAction("Save", this);
    connect(saving, SIGNAL(triggered()), this, SLOT(writeTeX()));
    menu->addAction(saving);

    QAction *clearin = new QAction("Clear all", this);
    connect(clearin, SIGNAL(triggered()), this, SLOT(ClearAll()));
    menu2->addAction(clearin);

    QAction *deleteob = new QAction("Delete", this);
    connect(deleteob, SIGNAL(triggered()), this, SLOT(DeleteEdge()));
    tBar->addAction(deleteob);

    QAction *colour = new QAction("Colour", this);
    connect(colour, SIGNAL(triggered()), this, SLOT(ShowDialogCol()));
    tBar->addAction(colour);

   // auto colors = std::vector<QColor>();

    colors.push_back(QColor(251, 251, 40));
    colors.push_back(QColor(237, 230, 203));
    colors.push_back(QColor(61, 248, 215));
  //  colors.push_back(QColorDialog::getColor());


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
    mBar->addMenu(menu);
    mBar->addMenu(menu1);
    mBar->addMenu(menu2);
    mBar->addMenu(menu3);
}


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

void PainterWindow::ClearAll(){
    lines.clear();
    names.clear();
    vertex.clear();
    mScene->clear();
   CircleItem::st=0;

}

void PainterWindow::ShowDialog()
{
    Dialog* dial= new Dialog(this);
    dial->show();
}
void PainterWindow::ShowDialog1()
{
    Dialog1* dial= new Dialog1(this);
    dial->show();
}
void PainterWindow::ShowDialog2()
{
    Help* h= new Help (this);
    h->show();
}
void PainterWindow::ShowDialogCol()
{
    QColorDialog* c= new QColorDialog (this);
    c->show();
}
void PainterWindow::setupSceneThings() {
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, 2000, 2000);
    mView = new QGraphicsView(this);
    mView->setScene(mScene);
    this->setCentralWidget(mView);

    connect(mScene, SIGNAL(changed(const QList<QRectF> &)), this, SLOT(rework()));
}

void PainterWindow::paintCircle() {

     CircleItem* mCircle = new CircleItem();
    textItem* name = new textItem(QString::number(mCircle->st), mCircle);

    mScene->addItem(mCircle);
    mCircle->setPos(mView->mapToScene(0,0));
    vertex.push_back(mCircle);

    names.push_back(name);

    mScene->addItem(name);
    mCircle->tie(name);
}
void PainterWindow::paintCircle1(QString* a){
    CircleItem* mCircle = new CircleItem();
    mScene->addItem(mCircle);
    mCircle->setPos(mView->mapToScene(0,0));
    vertex.push_back(mCircle);
    textItem* name=new textItem(*a, mCircle);
    names.push_back(name);
    mScene->addItem(name);
    mCircle->tie(name);

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

                   if (((k->ver1==selectedCircles[i])&& (k->ver2==selectedCircles[j])) || ((k->ver2==selectedCircles[i])&& (k->ver1==selectedCircles[j]))  || (selectedCircles[i] == k) || (selectedCircles[j]==k) )
                       flag=false;

               }
            if (flag)
             {
                 lineItem* newline = new lineItem(selectedCircles[i], selectedCircles[j]);
                 mScene->addItem(newline);
                 lines.push_back(newline);
             }

        }
    }


}

void PainterWindow::DeleteEdge()
{
    auto selected = mScene->selectedItems();
   for (auto i :  selected)
    {

       for (auto k:lines )
       {


           if ((k->ver1==i)  || (k->ver2==i) || (k==i))
           {
                for (auto n=0; n<lines.size(); n++)
                {
                     if (lines[n]==k)
                    {

                        lines.erase(lines.begin()+n);
                        mScene->removeItem(k);
                    }
                }
           }
        }
       for (auto k: names)
       {
           if (k->circle==i)
           {
              for (auto n=0; n< names.size(); n++)
              {
                  if (names[n]==k)
                  {
                      names.erase(names.begin()+n);
                      mScene->removeItem(k);
                  }
              }
           }
       }
       for (auto k: vertex)
       {
           if (k==i)
           {
              for (auto n=0; n< vertex.size(); n++)
              {
                  if (vertex[n]==k)
                  {
                      vertex.erase(vertex.begin()+n);
                      mScene->removeItem(k);
                  }
              }
           }
       }



   for (auto k:lines )
   {
        bool f1=false;
        bool f2=false;

   for (auto j: vertex)
   {
     if (k->ver1==j)
        f1=true;
     if (k->ver2==j)
           f2=true;
   }
     if ((!f1) || (!f2 ))
              {
                   for (auto n=0; n<lines.size(); n++)
                   {
                        if (lines[n]==k)
                       {

                           lines.erase(lines.begin()+n);
                           mScene->removeItem(k);
                       }
                   }
              }
}
     }
   for (auto k:lines )
   {
        bool f1=false;
        bool f2=false;

   for (auto j: vertex)
   {
     if (k->ver1==j)
        f1=true;
     if (k->ver2==j)
           f2=true;
   }
     if ((!f1) || (!f2 ))
              {
                   for (auto n=0; n<lines.size(); n++)
                   {
                        if (lines[n]==k)
                       {

                           lines.erase(lines.begin()+n);
                           mScene->removeItem(k);
                       }
                   }
              }
}
}

void PainterWindow::RemoveCircle(QString* a){

   for (auto i: vertex)
   {

       if (i->text->toPlainText() == *a)
       {
           for (auto j=0; j<vertex.size(); j++)
           {
               if (vertex[j]==i)
               {
                   for (auto k: lines)
                   {
                       if ((k->ver1 ==i) ||(k->ver2== i) )
                       {
                           for (auto v=0; v<lines.size(); v++)
                           {
                               if (lines[v]==k)
                               {
                                   mScene->removeItem(k);
                                   lines.erase(lines.begin()+v);
                               }
                           }
                       }
                   }
           mScene->removeItem(i);
           vertex.erase(vertex.begin()+j);
           }
           }
       }

       for (auto i: names)
       {
           if (i->toPlainText()== *a )
           {
               for (auto j=0; j<names.size(); j++)
               {
                   if (names[j]==i)
                   {
                       mScene->removeItem(i);
                       names.erase(names.begin()+j);
                   }
               }
           }
       }

   }
}


void PainterWindow::AddEdge1(QString* a, QString* b)
 {
     //if(((*a).ismpty())||((*b).isempty())) return;
     QGraphicsItem* circle1=nullptr;
     QGraphicsItem* circle2=nullptr;
     for (auto i:names)
     {
         if (i->toPlainText()== *a)
            circle1=i->circle;
         if (i->toPlainText()== *b)
            circle2=i->circle;

     }

     bool flag = false;
     bool f1 = false;
     bool f2 = false;
     for (auto i : vertex)
     {
        if (i == circle1) f1 = true;
        if (i == circle2) f2 = true;
     }
     if ((f1)&&(f2)) flag = true;



    for (auto k:lines )
    {

        if (((k->ver1==circle1)&& (k->ver2==circle2)) || ((k->ver2==circle1)&& (k->ver1==circle2)) || (circle1==circle2)  )
        {
            flag=false;
        }

    }
    if (flag)
     {
         lineItem* newline = new lineItem(circle1, circle2);
         mScene->addItem(newline);
         lines.push_back(newline);
     }

 }

void PainterWindow:: DeleteEdge1(QString* a, QString* b)
{
    QGraphicsItem* circle1;
    QGraphicsItem* circle2;
    for (auto i:names)
    {
        if (i->toPlainText()== *a)
           circle1=i->circle;
        if (i->toPlainText()== *b)
           circle2=i->circle;

    }
    int flag = 0;


   for (auto k:lines )
   {

       if (((k->ver1==circle1)&& (k->ver2==circle2)) || ((k->ver2==circle1)&& (k->ver1==circle2)) )
       {
 mScene->removeItem(k);
 lines.erase(lines.begin()+flag);
       }
       flag++;

   }

}



QIcon PainterWindow::createIcon(QColor color) {

    QPixmap mPix(20, 20);

    QPainter mPaint(&mPix);
    mPaint.setBrush(QBrush(color));
    mPaint.drawRect(0, 0, 20, 20);
   return QIcon(mPix);


}


void PainterWindow::writeTeX()
{
    QFile mWrite("TeX.txt");
    QTextStream out (&mWrite);
     if (!mWrite.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

    out<<"\\documentclass{article} \n \\usepackage{tikz} \n \\begin{document} \n \\begin{tikzpicture} \n [scale=0.1,auto=left,every node/.style={circle,fill=blue!20}] \n";

    for (int i=0; i<names.size(); i++)
    {
       out<<" \\node (n"<<names[i]->toPlainText()<<") at ("<<names[i]->circle->x()<<","<<names[i]->circle->y()<<") {"<<names[i]->toPlainText()<<"} ;\n";

    }
    out<<" \\foreach \\from/\\to in {";


    for (auto k:lines )
    {
        CircleItem* c1;
        CircleItem* c2;
      c1= dynamic_cast<CircleItem*>(k->ver1);
      c2= dynamic_cast<CircleItem*>(k->ver2);

       if (k!=lines.back())
            {
auto text1=c1->text->toPlainText();
auto text2=c2->text->toPlainText();

out<< "n"<<text1<<"/n"<<text2<<",";
            }
            else
            {
                auto text1=c1->text->toPlainText();
                auto text2=c2->text->toPlainText();

                out<< "n"<<text1<<"/n"<<text2;

            }

      }

   out<<"}\n";
      out<< "\\draw (\\from) -- (\\to); \n";

   out<< " \\end{tikzpicture} \n";

   out << "\\end{document}\n";

}


void PainterWindow::keyPressEvent(QKeyEvent *event)
{
if(event->key()==Qt::Key_A&&QApplication::keyboardModifiers() == Qt::ControlModifier){
for(CircleItem* item:vertex)
{
item->setSelected(true);
}
}
}

 QPixmap::mouseDoubleClickEvent( QMouseEvent * e )
{
if ( e->button() == Qt::LeftButton )
{
...
}
}

/*void PainterWindow::mousePressEvent(QMouseEvent *event)
{
    QMoveEvent* m;


    for (auto i: colors)

    {
   auto Pix = createIcon(i);
   if (event->button()==Qt::RightButton) //mouseDoubleClickEvent(*event))
{
   if ( Pix == qgraphicsitem_cast<QGraphicsPixmapItem*>((m->pos())))
   {
    ShowDialogCol();
   }

}
}
}*/

void PainterWindow::setColor(QAction* mAct)

{ auto color = mAct->data().value<QColor>();
    auto items = mScene->selectedItems();
    for (auto i: items)
    {
        for (auto j:vertex)
            if(j==i)
                static_cast<CircleItem*>(i)->setBrush(QBrush(color));
    }


}


PainterWindow::~PainterWindow()
{
    writeTeX();
    delete ui;
}

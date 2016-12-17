#include "dialog1.h"
#include "ui_dialog1.h"
#include "painterwindow.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}



void Dialog1::on_pushButton_clicked()
{
      parser();
}

void Dialog1::parser()
{
    auto p = dynamic_cast<PainterWindow*>(parent());
    QString line;
    line = ui->lineEdit->text();
    QTextStream a(&line);

    QString l1, l2, l3, l4;
    a >> l1;
    if (l1 == "add")
    {
        a >> l2;
        if(l2 == "vertex")
        {
            a>>l3;

            p->paintCircle1(&l3);
        }
        if (l2=="edge")
        {
            a>>l3;
            a>>l4;
            p->AddEdge1(&l3,&l4);

        }
    }
    else if (l1 == "delete")
    {
        a>>l2;
        if (l2=="vertex")
        {
            a>>l3;
            p->RemoveCircle(&l3);
        }
        if (l2=="edge")
        {
            a>>l3;
            a>>l4;
            p->DeleteEdge1(&l3, &l4);
        }
    }
    else if (l1 == "rename")
    {
        a>>l2;
        a>>l3;
        p->rename(l2,l3);
    }
}
Dialog1::~Dialog1()
{
    delete ui;
}

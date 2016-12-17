#include "dialog.h"
#include "ui_dialog.h"
#include "painterwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}
void Dialog::on_pushButton_clicked()
{
  QString a = ui->lineEdit->text();
  auto p = dynamic_cast<PainterWindow*>(parent());
    p->paintCircle1(&a);//так я могу создать несколько вершин с одинаковым именем,
    //но когда в комманде указываю соеденить вершину с этим именем с какой-то другой,
    //соединяется только последняя вершина с данным именем, а не все
}

void Dialog::on_pushButton_3_clicked()
{
    QString a = ui->lineEdit->text();
    auto p = dynamic_cast<PainterWindow*>(parent());
p->RemoveCircle(&a);
}

void Dialog::on_pushButton_2_clicked()
{

       QString a=ui->lineEdit_2->text();
       QString b=ui->lineEdit_3->text();

       if ((a==NULL) || (b==NULL))
       {
           return;
       }

       auto p = dynamic_cast<PainterWindow*>(parent());
       if ( ui->comboBox->currentText()=="Add edge")
       {
         p->AddEdge1(&a, &b);//нет запрета на одинаковые вершины

   }
   else
       {
           p->DeleteEdge1(&a, &b);
       }

}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_6_clicked()//очень полезный слот
{

}

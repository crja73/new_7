#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cmath>
#include <math.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::lol(double a)//возвращает знак числа
{
    if(a>0)
        return(1);
    else if (a<0)
        return(-1);
    else
        return (0);
}

void MainWindow::samoper(int N)
{
    peresech=false;
    double x0=0,y0=0,x1=0,x2=0,y1=0,y2=0,
            x3=0,y3=0;
    double v1x,v1y,v2x,v2y,v3x,v3y,v4x,v4y,v1_x,v1_y,v2_x,v2_y,v3_x,v3_y,v4_x,v4_y;
    int a1,a2,a3,a4;
    for (int i=N-1; i>1;i--)//Проверка на самопересечение
    {

        x3=ui->tableWidget->item(i,0)->text().toDouble();//последняя точка
        y3=ui->tableWidget->item(i,1)->text().toDouble();
        x2=ui->tableWidget->item(i-1,0)->text().toDouble();
        y2=ui->tableWidget->item(i-1,1)->text().toDouble();
        for(int j=0;j<i-2;j++)
        {
            x0=ui->tableWidget->item(j,0)->text().toDouble();
            y0=ui->tableWidget->item(j,1)->text().toDouble();
            x1=ui->tableWidget->item(j+1,0)->text().toDouble();
            y1=ui->tableWidget->item(j+1,1)->text().toDouble();

            v1x=x0-x3;
            v1y=y0-y3;
            v2x=x1-x3;
            v2y=y1-y3;
            v3x=x0-x2;
            v3y=y0-y2;
            v4x=x1-x2;
            v4y=y1-y2;

            v1_x=x3-x0;
            v1_y=y3-y0;
            v2_x=x3-x1;
            v2_y=y3-y1;
            v3_x=x2-x0;
            v3_y=y2-y0;
            v4_x=x2-x1;
            v4_y=y2-y1;

            a1=lol(v2x*v1y-v2y*v1x);
            a2=lol(v4x*v3y-v4y*v3x);
            a3=lol(v1_x*v3_y-v1_y*v3_x);
            a4=lol(v2_x*v4_y-v2_y*v4_x);

            if((a1!=a2&&a3!=a4))
            {
                peresech=true;
                break;
            }
        }
        for(int j=i+1;j<N;j++)
        {

            x0=ui->tableWidget->item(j,0)->text().toDouble();
            y0=ui->tableWidget->item(j,1)->text().toDouble();

            if(j==N-1)
            {
                x1=ui->tableWidget->item(0,0)->text().toDouble();
                y1=ui->tableWidget->item(0,1)->text().toDouble();
            }
            else
            {
                x1=ui->tableWidget->item(j+1,0)->text().toDouble();
                y1=ui->tableWidget->item(j+1,1)->text().toDouble();
            }

            v1x=x0-x3;
            v1y=y0-y3;
            v2x=x1-x3;
            v2y=y1-y3;
            v3x=x0-x2;
            v3y=y0-y2;
            v4x=x1-x2;
            v4y=y1-y2;

            v1_x=x3-x0;
            v1_y=y3-y0;
            v2_x=x3-x1;
            v2_y=y3-y1;
            v3_x=x2-x0;
            v3_y=y2-y0;
            v4_x=x2-x1;
            v4_y=y2-y1;

            a1=lol(v2x*v1y-v2y*v1x);
            a2=lol(v4x*v3y-v4y*v3x);
            a3=lol(v1_x*v3_y-v1_y*v3_x);
            a4=lol(v2_x*v4_y-v2_y*v4_x);

            if((a1!=a2&&a3!=a4))
            {
                peresech=true;
                break;
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{

    ui->spinBox->setMinimum(3);
     int count = ui-> spinBox -> value(); // получаем колво вершин
     if (count == 0)
     {
        QMessageBox:: information(this, "", "введите хотя бы одну точку");
        ui->label_per->setText("");
        ui->label_ploshad->setText("");
        return;


     }
     else
     {
         double mas_x[15];
         double mas_y[15];

         bool error = false;
         bool junc = true;

         for(int i = 0; i < count; i++) // цикл который проходит по строчкам
         {
             QTableWidgetItem * item_x = ui-> tableWidget -> item(i, 0);
             QTableWidgetItem * item_y = ui-> tableWidget -> item(i, 1);

             if(item_x == nullptr)
             {
                 item_x = new QTableWidgetItem;
                 ui-> tableWidget -> setItem(i,0,item_x);
             }
             if(item_y == nullptr)
             {
                 item_y = new QTableWidgetItem;
                 ui-> tableWidget -> setItem(i,1,item_y);
             }
             QString text_x = item_x -> text();
             QString text_y = item_y -> text();

             bool ok_x = false;
             bool ok_y = false;


             double x = text_x.toDouble(&ok_x);
             double y = text_y.toDouble(&ok_y);

             if (ok_x)
             {
                 item_x -> setBackground(Qt::white);
             }
             else
             {
                 item_x -> setBackground(Qt::red);
                 error = true;
             }

             if (ok_y)
             {
                 item_y -> setBackground(Qt::white);
             }
             else
             {
                 item_y -> setBackground(Qt::red);
                 error = true;
             }

             mas_x[i] = x;
             mas_y[i] = y;



         }
         bool tochka=true;
         bool pryam=true;


         //считываем тут с:

         if(error)
         {
             ui->label_per->setText("");
             ui->label_ploshad->setText("");
             QMessageBox:: information(this, "", "ошибка данных");
             return;
         }
         else
         {
             // проверка на самопересечение
            samoper(count);
            if(!peresech){
                junc = false;
            }
            else{
                ui->label_per->setText("");
                ui->label_ploshad->setText("");
                QMessageBox:: information(this, "", "Пересечение");
                return;

            }
            for(int i=1; i<count; i++)
            {
                double x1 = ui->tableWidget->item(0,0)->text().toDouble();
                double y1 = ui->tableWidget->item(0,1)->text().toDouble();
                double xi = ui->tableWidget->item(i,0)->text().toDouble();
                double yi = ui->tableWidget->item(i,1)->text().toDouble();
                if(abs(xi-x1)>0 || abs(yi-y1)>0)
                {
                    tochka=false;
                    if(!tochka)
                    {
                        for(int i=2; i<=count-1; i++)
                        {
                            double xn = ui->tableWidget->item(count-1,0)->text().toDouble();
                            double yn = ui->tableWidget->item(count-1,1)->text().toDouble();
                            if(abs(((xi-x1)/(xn-x1))-((yi-y1)/(yn-y1)))>0)
                            {
                                pryam=false;
                            }
                        }
                    }
                    else
                    {
                        pryam=false;
                    }
                }
            }
            if(pryam){
                QMessageBox::information(this,"erroe","Введены координаты прямой");
                return;
            }





             if (junc == false)
             {
                 //тут считаем площадь и периметр
                 double ploshad, perimetr = 0;
                 double f1 = 0, f2 = 0, d;
                 perimetr = 0;
                 if (count > 2)
                 {
                     for (int j = 0; j < count; j ++)
                     {
                         if (j + 1 == count)
                         {
                            f1 += mas_x[j] * mas_y[0];
                            f2 += mas_y[j] * mas_x[0];
                         }
                         else
                         {
                             f1 += mas_x[j] * mas_y[j + 1];
                             f2 += mas_y[j] * mas_x[j + 1];
                         }
                     }
                     ploshad = 0.5 * abs(f1 - f2); // посчитали площадь многоугольника




                     for (int i = 0; i < count; i ++) // заходим в цикл, чтобы считать длины сторон многоугольника
                     {
                         if (i + 1 == count)
                         {
                             double iks = mas_x[i] - mas_x[0];
                             double ygrek = mas_y[i] - mas_y[0];
                             double summa = pow(iks, 2) + pow(ygrek, 2);
                             d = pow(summa, 0.5);
                         }
                         else
                         {
                             double iks = mas_x[i] - mas_x[i+1];
                             double ygrek = mas_y[i] - mas_y[i+1];
                             double summa = pow(iks, 2) + pow(ygrek, 2);
                             d = pow(summa, 0.5);
                         }
                         perimetr += d;

                     }
                     if(isinf(perimetr)or isinf(ploshad) or isnan(perimetr) or isnan(ploshad))
                     {
                         QMessageBox::warning(this, "Ошибка", "Ошибка");
                         ui->label_per->setVisible(false);
                         ui->label_ploshad->setVisible(false);
                         return;
                     }
                     else
                     {
                         ui -> label_per -> setNum(perimetr);
                         ui -> label_ploshad -> setNum(ploshad);
                         ui->label_per->setVisible(true);
                         ui->label_ploshad->setVisible(true);


                     }





                 }
                 else
                 {
                    if (count == 2)
                    {
                        for (int i = 0; i < 1; i ++) // заходим в цикл, чтобы считать длины сторон многоугольника
                        {

                            double iks = mas_x[i] - mas_x[i+1];
                            double ygrek = mas_y[i] - mas_y[i+1];
                            double summa = pow(iks, 2) + pow(ygrek, 2);
                            d = pow(summa, 0.5);

                            perimetr += d;

                        }
                        ui -> label_per -> setNum(perimetr);
                        ploshad = 0;
                        ui -> label_ploshad -> setNum(ploshad);

                    }
                    else
                    {
                        ploshad = 0;
                        perimetr = 0;
                        ui -> label_per -> setNum(perimetr);
                        ui -> label_ploshad -> setNum(ploshad);
                    }

                 }
            }
         }

     }
     

}

void MainWindow::on_spinBox_valueChanged(int arg1)
{

    ui-> tableWidget -> setRowCount(arg1);
    ui-> tableWidget -> setColumnCount(2);
    ui->label_per->setText("");
    ui->label_ploshad->setText("");



}


void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    QString text = item -> text();

    bool ok;
    text.toDouble(&ok);

    if(ok)
    {
        item -> setBackground(Qt:: white);
    }
    else
    {
        item -> setBackground(Qt:: red);
    }
}

double MainWindow::vektor_proz(double a[2], double b[2])
{
    double rez = (a[0] * b[1]) - (b[0] * a[1]);
    return rez;
}

void MainWindow::on_pushButton_2_clicked()
{
    double count = ui-> spinBox -> value();
    ui->label_per->setText("");
    ui->label_ploshad->setText("");
    for (int i =0; i < count; i++)
    {
        ui-> tableWidget -> setItem(i, 0, nullptr);
        ui-> tableWidget -> setItem(i, 1, nullptr);
    }


}

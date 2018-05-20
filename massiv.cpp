#include "massiv.h"
#include "ui_massiv.h"
#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <QtGui>
#include <qinputdialog.h>
Massiv::Massiv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Massiv)
{
    ui->setupUi(this);
}

Massiv::~Massiv()
{
    delete ui;
}
void siftDown(int *numbers, int root, int bottom,int &srav,int &pers)
{
  int maxChild; // индекс максимального потомка
  int done = 0; // флаг того, что куча сформирована
  // Пока не дошли до последнего ряда
  while ((root * 2 <= bottom) && (!done))
  {
    srav++;
    if (root * 2 == bottom)    // если мы в последнем ряду,
      maxChild = root * 2;    // запоминаем левый потомок
    // иначе запоминаем больший потомок из двух
    else if (numbers[root * 2]>numbers[root * 2 + 1])
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
    // если элемент вершины меньше максимального потомка
    if (numbers[root]< numbers[maxChild])
    {
      int temp = numbers[root]; // меняем их местами
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
      pers++;
    }
    else // иначе
      done = 1; // пирамида сформирована
  }
}
void heapSort(int *numbers, int array_size,int &srav,int &pers, double &seconds)
{
  time_t start, end;
  start = clock();
  // Формируем нижний ряд пирамиды
  for (int i = (array_size / 2) - 1; i >= 0; i--){
    siftDown(numbers, i, array_size,srav,pers);}
  // Просеиваем через пирамиду остальные элементы
  for (int i = array_size - 1; i >= 1; i--)
  {
    int temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    siftDown(numbers, 0, i - 1,srav,pers);
  }
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
}
void Massiv::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Выход","Вы на главное меню?", QMessageBox::Yes| QMessageBox::No);
        if(reply==QMessageBox::Yes){
            this->close();
            emit firstWindow();
        }
}

void Massiv::on_pushButton_2_clicked()
{
    double seconds=0;
    int pers=0;
    int srav=0;
    int n;
    n=ui->razmer->text().toInt();
    int *a1=new int[n];
    if(ui->sredn->isChecked()){
        if(ui->piramida->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            heapSort(a1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
    }
}

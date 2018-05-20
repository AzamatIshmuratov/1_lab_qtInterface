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
using namespace std;
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
void quickSort(int *a ,int l, int r, int &srav, int &pers)
{
   int w,x,i,j;
   i=l;
   j=r;
   x=a[(l+r)/2];
   while (i<=j){
       while (a[i]<x) i++;
       while (x<a[j]) j--;
       srav++;
       if (i<=j){
         w=a[i];
         a[i]=a[j];
         a[j]=w;
         i++;
         j--;
         pers++;
       }
   }
   if (l<j) quickSort(a,l,j,srav,pers);
   if (i<r) quickSort(a,i,r,srav,pers);
}
void BubSort(int *arr, int col,int &srav,int &pers, double &seconds) {
    time_t start, end;
    int trash=0;
    start = clock();
    for (int i=0; i<=col-1 ; i++)
    {
        for (int j=i+1; j<=col; j++)
        {
            srav++;
            if (arr[i]>arr[j])
            {
                trash=arr[i];
                arr[i]=arr[j];
                arr[j]=trash;
                pers++;
            }
        }
    }
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
}
void Swap(int *Mas, int i)
{
   int temp;
   temp=Mas[i];
   Mas[i]=Mas[i-1];
   Mas[i-1]=temp;
}
void ShakerSort(int *Mas, int Start, int N,int &srav,int &pers, double &seconds)
{
    time_t start, end;
   int Left, Right, i;
   Left=Start;
   Right=N-1;
   start = clock();
   while (Left<=Right){
      for (i=Right; i>=Left; i--){
        srav++;
        if (Mas[i-1]>Mas[i]){
                Swap(Mas, i);
                pers++;
        }
      }
      Left++;
      for (i=Left; i<=Right; i++){
        srav++;
        if (Mas[i-1]>Mas[i]){
            Swap(Mas, i);
            pers++;
        }
      }
      Right--;
  }
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
}
void SortBestCase(int *arr, int col) {
    time_t start, end;
    int trash=0;
    start = clock();
    for (int i=0; i<=col-1 ; i++)
    {
        for (int j=i+1; j<=col; j++)
        {
            if (arr[i]>arr[j])
            {
                trash=arr[i];
                arr[i]=arr[j];
                arr[j]=trash;
            }
        }
    }
}

void reverse(int *a, int n){
    for (int i  = 0; i < n / 2; i++){
       swap(a[i], a[n - i - 1]);
    }
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
        if(ui->quick->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            time_t start, end;
            start = clock();
            quickSort(a1,0,n-1,srav,pers);
            end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->bub->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            BubSort(a1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->shake->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            ShakerSort(a1,1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
    }
    if(ui->bad->isChecked()){
        if(ui->piramida->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            reverse(a1,n);
            heapSort(a1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->quick->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            reverse(a1,n);
            time_t start, end;
            start = clock();
            quickSort(a1,0,n-1,srav,pers);
            end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->bub->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            reverse(a1,n);
            BubSort(a1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->shake->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            reverse(a1,n);
            ShakerSort(a1,1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
    }
    if(ui->best->isChecked()){
        if(ui->piramida->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            heapSort(a1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->quick->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            time_t start, end;
            start = clock();
            quickSort(a1,0,n-1,srav,pers);
            end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->bub->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            BubSort(a1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
        if(ui->shake->isChecked()){
            for(int i=0;i<n;++i){
                        a1[i]=rand()%101;
            }
            SortBestCase(a1,n);
            ShakerSort(a1,1,n,srav,pers,seconds);
            ui->pers->setText(QString::number(pers));
            ui->sravn->setText(QString::number(srav));
            ui->vrem->setText(QString::number(seconds));
        }
    }
    delete []a1;
}

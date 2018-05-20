#include "baza.h"
#include "ui_baza.h"
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
#include <QMessageBox>
#include <QtGui>
#include <qinputdialog.h>
const int M=536; //ЧИСЛО ГОРОДОВ
using namespace std;
Baza::Baza(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Baza)
{
    ui->setupUi(this);
}

Baza::~Baza()
{
    delete ui;
}
typedef struct gorod{
   string name;
   int god;
   int naselenie;
};

void siftDownG(gorod *numbers, int root, int bottom,int &srav,int &pers)
{
  time_t start, end;
  int maxChild; // индекс максимального потомка
  int done = 0; // флаг того, что куча сформирована
  // Пока не дошли до последнего ряда
  while ((root * 2 <= bottom) && (!done))
  {
    srav++;
    if (root * 2 == bottom)    // если мы в последнем ряду,
      maxChild = root * 2;    // запоминаем левый потомок
    // иначе запоминаем больший потомок из двух
    else if (numbers[root * 2].god>numbers[root * 2 + 1].god)
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
    // если элемент вершины меньше максимального потомка
    if (numbers[root].god < numbers[maxChild].god)
    {
      gorod temp = numbers[root]; // меняем их местами
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
      pers++;
    }
    else // иначе
      done = 1; // пирамида сформирована
  }
}
void siftDownN(gorod *numbers, int root, int bottom,int &srav,int &pers)
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
    else if (numbers[root * 2].naselenie>numbers[root * 2 + 1].naselenie)
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
    // если элемент вершины меньше максимального потомка
    if (numbers[root].naselenie < numbers[maxChild].naselenie)
    {
      gorod temp = numbers[root]; // меняем их местами
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
      pers++;
    }
    else // иначе
      done = 1; // пирамида сформирована
  }
}
// Функция сортировки на куче

void heapSortG(gorod *numbers, int array_size,int &srav,int &pers,double &seconds)
{
    time_t start, end;
    start = clock();
  // Формируем нижний ряд пирамиды
  for (int i = (array_size / 2) - 1; i >= 0; i--){
    siftDownG(numbers, i, array_size,srav,pers);}
  // Просеиваем через пирамиду остальные элементы
  for (int i = array_size - 1; i >= 1; i--)
  {
    gorod temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    siftDownG(numbers, 0, i - 1,srav,pers);
  }
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
}

void heapSortN(gorod *numbers, int array_size,int &srav,int &pers,double &seconds)
{
    time_t start, end;
    start = clock();
  // Формируем нижний ряд пирамиды
  for (int i = (array_size / 2) - 1; i >= 0; i--){
    siftDownN(numbers, i, array_size,srav,pers);}
  // Просеиваем через пирамиду остальные элементы
  for (int i = array_size - 1; i >= 1; i--)
  {
    gorod temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    siftDownN(numbers, 0, i - 1,srav,pers);
  }
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
}
void quickSortG(gorod *a ,int l, int r, int &srav, int &pers)
{
   gorod w;
   int x,i,j;
   i=l;
   j=r;
   x=a[(l+r)/2].god;
   while (i<=j){
       while (a[i].god<x) i++;
       while (x<a[j].god) j--;
       srav++;
       if (i<=j){
         pers++;
         w=a[i];
         a[i]=a[j];
         a[j]=w;
         i++;
         j--;
       }
   }
   if (l<j) quickSortG(a,l,j,srav,pers);
   if (i<r) quickSortG(a,i,r,srav,pers);
}
void quickSortN(gorod *a ,int l, int r, int &srav, int &pers)
{
   gorod w;
   int x,i,j;
   i=l;
   j=r;
   x=a[(l+r)/2].naselenie;
   while (i<=j){
       while (a[i].naselenie<x) i++;
       while (x<a[j].naselenie) j--;
       srav++;
       if (i<=j){
         pers++;
         w=a[i];
         a[i]=a[j];
         a[j]=w;
         i++;
         j--;
       }
   }
   if (l<j) quickSortN(a,l,j,srav,pers);
   if (i<r) quickSortN(a,i,r,srav,pers);
}
void BubSortG(gorod *arr, int col,int &srav,int &pers,double &seconds) {
    time_t start, end;
    start = clock();
    gorod trash;
    start = clock();
    for (int i=0; i<col-1 ; i++)
    {
        for (int j=i+1; j<col; j++)
        {
            srav++;
            if (arr[i].god>arr[j].god)
            {
                pers++;
                trash=arr[i];
                arr[i]=arr[j];
                arr[j]=trash;
            }
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
}
void BubSortN(gorod *arr, int col,int &srav,int &pers,double &seconds) {
    time_t start, end;
    start = clock();
    gorod trash;
    start = clock();
    for (int i=0; i<col-1 ; i++)
    {
        for (int j=i+1; j<col; j++)
        {
            srav++;
            if (arr[i].naselenie>arr[j].naselenie)
            {
                pers++;
                trash=arr[i];
                arr[i]=arr[j];
                arr[j]=trash;
            }
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
}
void Baza::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Выход","Вы дей?", QMessageBox::Yes| QMessageBox::No);
        if(reply==QMessageBox::Yes){
            this->close();
            emit firstWindow();
        }
}

void Baza::on_piramida_clicked()
{
    double seconds=0;
    int pers=0;
    int srav=0;
    QString valueAsString;
    ifstream fin;
            ofstream fout1;
            ofstream fout2;
            fout1.open("GorodaSortedGod.txt");
            fout2.open("GorodaSortedNaselenie.txt");
            fin.open("Goroda.txt");
            struct gorod g[M];
            for(int i=0;i<M;++i){
            fin >> g[i].name>> g[i].naselenie >> g[i].god;
            }
                heapSortG(g,M,srav,pers,seconds);
                for(int i=0;i<M;++i){
                                fout1 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
            }
                ui->pers_god->setText(QString::number(pers));
                ui->sravn_god->setText(QString::number(srav));
                ui->vrem_god->setText(QString::number(seconds));
                seconds=0;
                pers=0;
                srav=0;
                heapSortN(g,M,srav,pers,seconds);
                            for(int i=0;i<M;++i){
                                fout2 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
                }
                ui->pers_nas->setText(QString::number(pers));
                ui->sravn_nas->setText(QString::number(srav));
                ui->vrem_nas->setText(QString::number(seconds));
                fout1.close();
                fout2.close();
                fin.close();
}

void Baza::on_quick_clicked()
{
    double seconds=0;
    int pers=0;
    int srav=0;
    QString valueAsString;
    ifstream fin;
            ofstream fout1;
            ofstream fout2;
            fout1.open("GorodaSortedGod.txt");
            fout2.open("GorodaSortedNaselenie.txt");
            fin.open("Goroda.txt");
            struct gorod g[M];
            for(int i=0;i<M;++i){
            fin >> g[i].name>> g[i].naselenie >> g[i].god;
            }
                time_t start, end;
                start = clock();
                quickSortG(g,0,M-1,srav,pers);
                end = clock();
                seconds = (double)(end - start) / CLOCKS_PER_SEC;
                for(int i=0;i<M;++i){
                                fout1 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
                }
                ui->pers_god->setText(QString::number(pers));
                ui->sravn_god->setText(QString::number(srav));
                ui->vrem_god->setText(QString::number(seconds));
                seconds=0;
                pers=0;
                srav=0;
                start = clock();
                quickSortN(g,0,M-1,srav,pers);
                end = clock();
                seconds = (double)(end - start) / CLOCKS_PER_SEC;
                for(int i=0;i<M;++i){
                                fout2 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
                }
                ui->pers_nas->setText(QString::number(pers));
                ui->sravn_nas->setText(QString::number(srav));
                ui->vrem_nas->setText(QString::number(seconds));
                fout1.close();
                fout2.close();
                fin.close();
}

void Baza::on_bub_clicked()
{
    double seconds=0;
    int pers=0;
    int srav=0;
    QString valueAsString;
    ifstream fin;
            ofstream fout1;
            ofstream fout2;
            fout1.open("GorodaSortedGod.txt");
            fout2.open("GorodaSortedNaselenie.txt");
            fin.open("Goroda.txt");
            struct gorod g[M];
            for(int i=0;i<M;++i){
            fin >> g[i].name>> g[i].naselenie >> g[i].god;
            }
                BubSortG(g,M,srav,pers,seconds);
                for(int i=0;i<M;++i){
                                fout1 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
            }
                ui->pers_god->setText(QString::number(pers));
                ui->sravn_god->setText(QString::number(srav));
                ui->vrem_god->setText(QString::number(seconds));
                seconds=0;
                pers=0;
                srav=0;
                BubSortN(g,M,srav,pers,seconds);
                            for(int i=0;i<M;++i){
                                fout2 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
                }
                ui->pers_nas->setText(QString::number(pers));
                ui->sravn_nas->setText(QString::number(srav));
                ui->vrem_nas->setText(QString::number(seconds));
                fout1.close();
                fout2.close();
                fin.close();
}

void Baza::on_shake_clicked()
{
    double seconds=0;
    int pers=0;
    int srav=0;
    QString valueAsString;
    ifstream fin;
            ofstream fout1;
            ofstream fout2;
            fout1.open("GorodaSortedGod.txt");
            fout2.open("GorodaSortedNaselenie.txt");
            fin.open("Goroda.txt");
            struct gorod g[M];
            for(int i=0;i<M;++i){
            fin >> g[i].name>> g[i].naselenie >> g[i].god;
            }
                ShakerSortG(g,1,M);
                for(int i=0;i<M;++i){
                                fout1 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
            }
                ui->pers_god->setText(QString::number(pers));
                ui->sravn_god->setText(QString::number(srav));
                ui->vrem_god->setText(QString::number(seconds));
                seconds=0;
                pers=0;
                srav=0;
                ShakerSortG(g,1,M);
                            for(int i=0;i<M;++i){
                                fout2 <<  g[i].name <<"   "<< g[i].naselenie << "   "<< g[i].god << "\n";
                }
                ui->pers_nas->setText(QString::number(pers));
                ui->sravn_nas->setText(QString::number(srav));
                ui->vrem_nas->setText(QString::number(seconds));
                fout1.close();
                fout2.close();
                fin.close();
}

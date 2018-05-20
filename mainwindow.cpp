#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
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
const int M=537;
using namespace std;
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

typedef struct gorod{
   string name;
   int god;
   int naselenie;
};

// Функция сортировки на куче

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

void BubSort(int *arr, int col) {
    time_t start, end;
    int pers=0, srav=0;
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
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  cout << "\nВремя Сортировки Пузырьком = " << seconds;
  cout<<"\nКоличество: Сравнений: "<<srav<<"  Перестановок: "<<pers;
}


void Swap(int *Mas, int i)
{
   int temp;
   temp=Mas[i];
   Mas[i]=Mas[i-1];
   Mas[i-1]=temp;
}
void ShakerSort(int *Mas, int Start, int N)
{
    time_t start, end;
    int pers=0, srav=0;
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
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  cout << "\nВремя Шейкерной сортировки = " << seconds;
  cout<<"\nКоличество: Сравнений: "<<srav<<"  Перестановок: "<<pers;
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
       cout<<a[i]<<endl;
    }
}


void MainWindow::on_Baza_clicked()
{
    hide();
    window1= new Baza(this);
    connect(window1, &Baza::firstWindow, this,&MainWindow::show);
    window1->show();
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
}

void MainWindow::on_Massiv_clicked()
{
    hide();
    window2= new Massiv(this);
    connect(window2, &Massiv::firstWindow, this,&MainWindow::show);
    window2->show();
}

void MainWindow::on_Out_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Выход","Вы дей?", QMessageBox::Yes| QMessageBox::No);
        if(reply==QMessageBox::Yes){
            QApplication::quit();
        }
}

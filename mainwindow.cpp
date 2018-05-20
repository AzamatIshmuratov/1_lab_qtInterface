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
            /*ifstream fin;
            ofstream fout1;
            ofstream fout2;
            fout1.open("GorodaSortedGod.txt");
            fout2.open("GorodaSortedNaselenie.txt");
            fin.open("Goroda.txt");
            struct gorod g[M];
            for(int i=0;i<M;++i){
               fin >> g[i].name>> g[i].naselenie >> g[i].god;
            }*/
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
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Выход","Выйти?", QMessageBox::Yes| QMessageBox::No);
        if(reply==QMessageBox::Yes){
            QApplication::quit();
        }
}

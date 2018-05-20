#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>

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

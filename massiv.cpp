#include "massiv.h"
#include "ui_massiv.h"
#include <QApplication>
#include <QMessageBox>

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

void Massiv::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Выход","Вы дей?", QMessageBox::Yes| QMessageBox::No);
        if(reply==QMessageBox::Yes){
            this->close();
            emit firstWindow();
        }
}

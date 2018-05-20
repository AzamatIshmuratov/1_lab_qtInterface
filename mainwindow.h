#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "baza.h"
#include "massiv.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Baza_clicked();

    void on_Massiv_clicked();

    void on_Out_clicked();

private:
    Ui::MainWindow *ui;
    Baza *window1;
    Massiv *window2;
};

#endif // MAINWINDOW_H

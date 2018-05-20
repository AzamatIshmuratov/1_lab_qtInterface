#ifndef BAZA_H
#define BAZA_H

#include <QDialog>

namespace Ui {
class Baza;
}

class Baza : public QDialog
{
    Q_OBJECT

public:
    explicit Baza(QWidget *parent = 0);
    ~Baza();
signals:
    void firstWindow();
private slots:
    void on_pushButton_clicked();

    void on_piramida_clicked();

    void on_quick_clicked();

    void on_bub_clicked();

private:
    Ui::Baza *ui;
};

#endif // BAZA_H

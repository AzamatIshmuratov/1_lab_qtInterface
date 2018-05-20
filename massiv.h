#ifndef MASSIV_H
#define MASSIV_H

#include <QDialog>

namespace Ui {
class Massiv;
}

class Massiv : public QDialog
{
    Q_OBJECT

public:
    explicit Massiv(QWidget *parent = 0);
    ~Massiv();
signals:
    void firstWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Massiv *ui;
};

#endif // MASSIV_H

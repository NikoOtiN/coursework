#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "polinomdialog.h"
namespace Ui {
class Dialog;
}

struct dialog_data{
    int amount;
    double step;
    double startX;
    double deviation;
    QVector<double> formulaV;
    double a;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    dialog_data getData();
public slots:
    void showPolinomDialog();
    void functionChanged();
    void check();
private:
    Ui::Dialog *ui;
    polinomDialog *pD;
    QVector<double> function;
};

#endif // DIALOG_H

#ifndef POLINOMDIALOG_H
#define POLINOMDIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVector>
#include <QDebug>
#include <QPushButton>

struct pData{
    QString resS;
    QVector<double> resD;
};

class polinomDialog : public QDialog
{
    Q_OBJECT
public:
    explicit polinomDialog(QWidget *parent = 0);
private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *firstLayout;
    QHBoxLayout *secondLayout;
    QHBoxLayout *thirdLayout;
    QLabel *p1TextL;
    QLabel *p2TextL;
    QSpinBox *pCountSB;
    QVector<QLabel*> xVectorL;
    QVector<QSpinBox*> wVectorSB;
    QPushButton *okButton;
    QPushButton *cancelButton;



signals:

public slots:
    void changeFormulaLayout(int value);
    pData getData();
};

#endif // POLINOMDIALOG_H

#include "polinomdialog.h"

polinomDialog::polinomDialog(QWidget *parent) :
    QDialog(parent)
{
    p1TextL = new QLabel("Полином");
    pCountSB = new QSpinBox();
    pCountSB->setMinimum(1);
    p2TextL = new QLabel("степени.");
    firstLayout = new QHBoxLayout();
    firstLayout->addWidget(p1TextL);
    firstLayout->addWidget(pCountSB);
    firstLayout->addWidget(p2TextL);
    connect(pCountSB,SIGNAL(valueChanged(int)),SLOT(changeFormulaLayout(int)));
    secondLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(firstLayout);
    xVectorL.push_back(new QLabel("y = "));
    wVectorSB.push_back(new QSpinBox());
    secondLayout->addWidget(xVectorL.front());
    secondLayout->addWidget(wVectorSB.front());
    mainLayout->addLayout(secondLayout);

    okButton = new QPushButton("Ок");
    cancelButton = new QPushButton("Отмена");
    thirdLayout = new QHBoxLayout();
    thirdLayout->addWidget(okButton);
    thirdLayout->addWidget(cancelButton);
    connect(okButton,SIGNAL(clicked()),SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),SLOT(reject()));
    mainLayout->addLayout(thirdLayout);
    setLayout(mainLayout);
    pCountSB->setValue(2);
    wVectorSB[0]->setValue(5);
    wVectorSB[1]->setValue(4);
}


void polinomDialog::changeFormulaLayout(int value)
{
    QString x = "x<sup>%1</sup>";
    int size = wVectorSB.size();
    if(value<=0)
    {
        return;
    }
    if(value>size)
    {
        int needAdd = value - size;
        for(int i = 0; i <needAdd; i++)
        {
            xVectorL.push_back(new QLabel("+"));
            secondLayout->addWidget(xVectorL.back());
            wVectorSB.push_back(new QSpinBox());
            wVectorSB.back()->setMinimum(-100);
            secondLayout->addWidget(wVectorSB.back());
            xVectorL.push_back(new QLabel(x.arg(size+i)));
            secondLayout->addWidget(xVectorL.back());
        }
    }else{
        int needDel = size - value;
        for(int i = 0;i<needDel;i++)
        {            
            secondLayout->removeWidget(xVectorL.back());
            delete xVectorL.back();
            xVectorL.pop_back();
            secondLayout->removeWidget(wVectorSB.back());   
            delete wVectorSB.back();
            wVectorSB.pop_back();
            secondLayout->removeWidget(xVectorL.back());
            delete xVectorL.back();
            xVectorL.pop_back();
        }
    }
}

pData polinomDialog::getData()
{
    pData data;
    data.resS.append(xVectorL.front()->text());
    data.resS.append(QString::number(wVectorSB.front()->value()));
    data.resD.push_back(wVectorSB.front()->value());
    for(int i = 1; i < pCountSB->value(); i++)
    {
        if(wVectorSB[i]->value()>=0)
        {
            data.resS.append(xVectorL[i*2-1]->text());
        }
        data.resS.append(QString::number(wVectorSB[i]->value()));
        data.resD.push_back(wVectorSB[i]->value());
        data.resS.append(xVectorL[i*2]->text());
    }
    return data;
}

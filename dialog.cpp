#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->changeFormula,SIGNAL(clicked()),this,SLOT(showPolinomDialog()));
    connect(ui->cancelButton,SIGNAL(clicked()),SLOT(reject()));
    connect(ui->okButton,SIGNAL(clicked()),SLOT(check()));
    function.push_back(5);
    function.push_back(4);
    pD = NULL;
}

void Dialog::showPolinomDialog()
{
    if(!pD)
    {
        pD = new polinomDialog();
        connect(pD,SIGNAL(accepted()),SLOT(functionChanged()));
    }
    pD->show();
}

void Dialog::check()
{
    if(ui->step->value()==0)
    {
       QMessageBox::warning(this,"Неккоректное заполнение","Шаг не может быть равен 0");
    }else{
        emit accept();
    }
}

void Dialog::functionChanged()
{
    pData data = pD->getData();
    ui->function_label->setText(data.resS);
    function=data.resD;
}

dialog_data Dialog::getData()
{
    dialog_data data;
    data.amount=ui->amount->value();
    data.step=ui->step->value();
    data.deviation=ui->deviation_sb->value();
    data.a=ui->level_sb->value();
    data.formulaV=function;
    data.startX=ui->startXSB->value();
    return data;
}

Dialog::~Dialog()
{
    delete ui;
}

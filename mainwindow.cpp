#include "mainwindow.h"
#include "ui_mainwindow.h"

QString tittle = "<p>Поиск уравнения регрессии.</p><p>1. Линейниное уравнение %1</p>";
QString polinom = "<p>%1. Полином %2-й степени - %3. Остаточная дисперсия S<sub>%2</sub>=%4</p>";
QString check = "<p>Проверка гипотезы о незначимом различии дисперсий S<sub>%1</sub>=%2 и S<sub>%3</sub>=%4</p> \
                 <p>Статистика Фишера F = %5. Критическое значение F<sub>кр</sub> = %6";
QString correct = "<p> F &lt; F<sub>кр</sub> Гипотеза принимается. В качестве уравнения регрессии принимается Полином %1 степени.";
QString uncorrect = "<p> F &gt; F<sub>кр</sub> Гипотеза отвергается. Увеличиваем степень полинома.";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainTab = new QTabWidget();
    createMainPlot();
    mainTab->addTab(mainPlot,"Визуализация данных");

    enterData = new QAction("Ввести данные",this);
    connect(enterData,SIGNAL(triggered()),SLOT(showDialog()));
    connect(legend,SIGNAL(checked(QVariant,bool,int)),this,SLOT(showItem(QVariant,bool)));
    menuBar()->addAction(enterData);
    dataDialog = NULL;

    reportTextEdit = new QTextEdit();
    reportTextEdit->setReadOnly(true);
    QFont font("Times", 14, QFont::Bold);
    reportTextEdit->setFont(font);
    mainTab->addTab(reportTextEdit,"Отчет");
    setCentralWidget(mainTab);
}

void MainWindow::showDialog()
{
    if(dataDialog==NULL)
    {
        dataDialog= new Dialog();
        connect(dataDialog,SIGNAL(accepted()),SLOT(go_calc()));
    }
    dataDialog->show();
}

void MainWindow::go_calc()
{
    dialog_data data = dataDialog->getData();
    result res = do_regression_analysis(data.amount,data.step,data.startX,data.formulaV,data.deviation,data.a);
    populate(res);
}

void MainWindow::populate(result res)
{
    functions.clear();
    reportTextEdit->clear();
    mainPlot->detachItems();
    QVector<int> colorBox = getColorBox();
    QwtPlotCurve *res_exp = new QwtPlotCurve("Экпериментальные данные");
    res_exp->setSamples(res.data.vX,res.data.vY);
    res_exp->setStyle(QwtPlotCurve::Dots);
    res_exp->setPen(Qt::black,3);
    res_exp->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    res_exp->attach(mainPlot);

    for(int k = 0; k < res.wV.size(); k++)
    {
        QString func = QString("y = %1").arg(QString::number(res.wV[k].front()));
        for(int i = 1; i < res.wV[k].size(); i++)
        {
            if(res.wV[k][i]>=0)
            {
                func.append(QString("+%1 x<sup> %2 </sup>").arg(QString::number(res.wV[k][i]),
                                                                QString::number(i)));
            }else{
                func.append(QString("%1 x<sup> %2 </sup>").arg(QString::number(res.wV[k][i]),
                                                                QString::number(i)));
            }

        }
        functions << func;
        QwtPlotCurve *reg_model = new QwtPlotCurve(func);
        reg_model->setPen(Qt::GlobalColor(colorBox.back()),2);
        colorBox.pop_back();
        qDebug() << "size" << res.data.vX.size() << res.regY[k].size();
        reg_model->setSamples(res.data.vX,res.regY[k]);
        reg_model->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        reg_model->attach(mainPlot);
    }
    setLegendsTrue();
    writeReport(res);
}

void MainWindow::createMainPlot()
{
    mainPlot = new QwtPlot();
    mainPlot->setTitle("Результаты эксперимента");
    mainPlot->setAxisTitle(QwtPlot::xBottom,"Свободная переменная");
    mainPlot->setAxisTitle(QwtPlot::yLeft,"Зависимая перменная");
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette( Qt::gray );
    canvas->setBorderRadius( 10 );
    mainPlot->setCanvas(canvas);
    legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    mainPlot->insertLegend(legend);
    mainPlot->setAutoReplot(true);
}

void MainWindow::showItem(QVariant n, bool b)
{
    QwtPlotItem *item = mainPlot->infoToItem(n);
    item->setVisible(b);
    mainPlot->replot();
}

void MainWindow::setLegendsTrue()
{
    QwtPlotItemList items = mainPlot->itemList(QwtPlotItem::Rtti_PlotItem);
    for ( int i = 0; i < items.size(); i++ )
    {
            const QVariant itemInfo = mainPlot->itemToInfo( items[i] );

            QwtLegendLabel *legendLabel =
                qobject_cast<QwtLegendLabel *>( legend->legendWidget( itemInfo ) );
            if ( legendLabel )
                legendLabel->setChecked( true );
    }
}

void MainWindow::writeReport(result res)
{
    reportTextEdit->append(tittle.arg(functions.front()));
    for(int i = 1; i<functions.size(); i++)
    {
        reportTextEdit->append(polinom.arg(QString::number(i+1),QString::number(i+1),
                                           functions.at(i),QString::number(res.dispersion.at(i))));
        reportTextEdit->append(check.arg(QString::number(i),QString::number(res.dispersion.at(i-1)),
                                         QString::number(i+1),QString::number(res.dispersion.at(i)),
                                         QString::number(res.fisher_t.at(i-1)),QString::number(res.fisher_cr.at(i-1))));
        if(res.fisher_t.at(i-1)<res.fisher_cr.at(i-1))
        {
            reportTextEdit->append(correct.arg(QString::number(i)));
        }else{
            reportTextEdit->append(uncorrect);
        }
    }
}

QVector<int> MainWindow::getColorBox()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    QVector<int> colorBox(10);
    for(int i = 0; i<10; i++)
    {
        colorBox[i]=i+6;
    }
    std::shuffle(colorBox.begin(),colorBox.end(),std::default_random_engine(seed));
    colorBox+=colorBox;
    return colorBox;
}


MainWindow::~MainWindow()
{
    delete ui;
}

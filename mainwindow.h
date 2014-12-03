#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_legend_label.h>
#include <array>
#include "dialog.h"
#include "reg_func.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTabWidget *mainTab;
    QwtPlot *mainPlot;
    QwtLegend *legend;
    QAction *enterData;
    Dialog *dataDialog;
    QTextEdit *reportTextEdit;
    void createMainPlot();
    void populate(result res);
    QVector<int> getColorBox();
    QVector<QString> functions;

    void setLegendsTrue();
    void writeReport(result res);
public slots:
    void showDialog();
    void go_calc();
    void showItem(QVariant n, bool b);


};

#endif // MAINWINDOW_H

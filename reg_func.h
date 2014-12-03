#ifndef REG_FUNC_H
#define REG_FUNC_H
#include <QVector>
#include <random>
#include <chrono>
#include <QDebug>
#include <iostream>
#include <cmath>
#include "matrix_func.h"
struct xy{
    QVector<double> vX;
    QVector<double> vY;
};

struct result
{
    xy data;
    QVector<QVector<double>> wV;
    QVector<QVector<double>> regY;
    QVector<double> dispersion;
    QVector<double> fisher_t;
    QVector<double> fisher_cr;
};

double F_test_cr(int v1, int v2, double level);
double F_test(const double a, const double b);
double s(QVector<double> mainY, QVector<double> regY, int k);
QVector<QVector<double>> createMatrix(xy d, int pow);
QVector<double> regression_vector(QVector<double> func, QVector<double> xV);
void print_v(QVector<double> v);
xy create_exp(int amount, double step, double startx, QVector<double> function, double g);
double calc_func(QVector<double> function,double x);
result do_regression_analysis(int amount, double step,
                              double startx, QVector<double> function, double g, double level);

#endif // REG_FUNC_H

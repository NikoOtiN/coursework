#ifndef MATRIX_FUNC_H
#define MATRIX_FUNC_H
#include <QDebug>
#include <QVector>
#include <iostream>

QVector<double> xVector(QVector<QVector<double>> A, QVector<double> b1);
QVector<QVector<double>> transpose(QVector<QVector<double>> a);
QVector<QVector<double>> inverse(QVector<QVector<double>> a);
QVector<QVector<double>> multipl(QVector<QVector<double>> a, QVector<QVector<double>> b);
void print(QVector<QVector<double>> a);

#endif // MATRIX_FUNC_H


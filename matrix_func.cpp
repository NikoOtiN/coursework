#include "matrix_func.h"

QVector<double> xVector(QVector<QVector<double>> a, QVector<double> b1)
{
    QVector<QVector<double>> b2;
    for(auto y : b1)
    {
        b2.push_back(QVector<double>(1,y));
    }
    QVector<QVector<double>> aT = transpose(a);
    QVector<QVector<double>> atA = multipl(aT,a);
    QVector<QVector<double>> invAtA = inverse(atA);
    QVector<QVector<double>> atB = multipl(aT,b2);
    QVector<QVector<double>> x = multipl(invAtA,atB);
    QVector<double> result;
    if(x.front().size()==1)
    {
        qDebug() << "Вектор икс получен";
        for(auto row : x)
        {
            result.push_back(row.front());
        }
    }
    return result;
}

QVector<QVector<double>> transpose(QVector<QVector<double>> a)
{
        int m = a.size();
        int n = a.front().size();
        QVector<double> r(m);
        QVector<QVector<double>> aT(n,r);
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                aT[j][i]=a[i][j];
            }
        }
        return aT;
}

QVector<QVector<double>> inverse(QVector<QVector<double>> a)
{
    int m = a.size();
    int n = a.front().size();
    if(n!=m)
    {
        qDebug() << "n!=m";
        return a;
    }

    //Единичная матрица
    QVector<double> e(n,0);
    QVector<QVector<double>> one(n,e);
    for(int i =0; i<n;i++)
    {
        one[i][i]=1;
    }
    //Объединение
    for(int i = 0; i < n; i++)
    {
        a[i]+=one[i];
    }

    int nn=n+n;
    //Прямой ход
    for(int k = 0; k < m; k++)
    {
        double akk = a[k][k];
        if(akk==0)
        {
            qDebug() << "front element equal 0";
        }
        for(int i = 0; i<nn; i++)
        {
            if(a[k][i]!=0)
            {
                a[k][i]/=akk;
            }
        }
        for(int i = k+1; i<m; i++)
        {
            double front_el = a[i][k];
            for(int j = k; j<nn; j++)
            {
                a[i][j]-=front_el*a[k][j];
            }
        }
    }

    for(int k = m-1; k>=0; k--)
    {
        for(int i = k-1; i>=0; i--)
        {
            double front_el = a[i][k];
            for(int j = k; j<nn;j++)
            {
                a[i][j]-=front_el*a[k][j];
            }
        }
    }
    QVector<QVector<double>> L;
    for(int i = 0; i<m;i++)
    {
        QVector<double> tmp;
        tmp = a[i];
        tmp.erase(tmp.begin()+n,tmp.end());
        L.push_back(tmp);
        a[i].erase(a[i].begin(),a[i].begin()+n);
    }
    return a;
}

double product(QVector<QVector<double>> a, QVector<QVector<double>> b,int i, int j)
{
    double sum=0;
    QVector<double> row = a.at(i);
    for(int ii =0; ii<row.size();ii++)
    {
        sum+=row[ii]*b[ii][j];
    }
    return sum;
}


QVector<QVector<double>> multipl(QVector<QVector<double>> a, QVector<QVector<double>> b)
{
    int m = a.size();
    int n = b.front().size();

    if(a.front().size()!=b.size())
    {
        qDebug() << "mxn";
    }

    QVector<double> e(n,0);
    QVector<QVector<double>> ab(m,e);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j< n;j++)
        {
            ab[i][j]=product(a,b,i,j);
        }
    }
    return ab;
}



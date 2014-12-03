#include "reg_func.h"

result do_regression_analysis(int amount, double step, double startx,
                              QVector<double> function, double g, double level)
{
    result res;
    xy data = create_exp(amount,step,startx,function,g);
    int degree = 2;
    bool run = true;
    while(run&&(degree<10))
    {

        QVector<QVector<double>> matrix = createMatrix(data,degree);
        res.wV.push_back(xVector(matrix,data.vY));
        res.regY.push_back(regression_vector(res.wV.back(),data.vX));
        res.dispersion.push_back(s(data.vY,res.regY.back(),degree-1));
        int dSize = res.dispersion.size();
        if(dSize>1)
        {
            double f_test = F_test(res.dispersion.back(),res.dispersion[dSize-2]);
            double f_cr = F_test_cr(amount - degree - 1,amount - degree - 2, 1-level);
            res.fisher_t.push_back(f_test);
            res.fisher_cr.push_back(f_cr);
            if(f_test<f_cr)run=false;
        }
        degree++;
    }
    print_v(res.fisher_t);
    print_v(res.fisher_cr);
    res.data = data;
    return res;
}

double s(QVector<double> mainY, QVector<double> regY, int k)
{
    double koef = mainY.size()-k-1;
    double sum = 0;
    for(int i = 0; i < mainY.size(); i++)
    {
        sum+= (mainY[i]-regY[i])*(mainY[i]-regY[i]);
    }
    double s = sum/koef;
    return s;
}

QVector<QVector<double>> createMatrix(xy d, int p)
{
    int xSize = d.vX.size();
    QVector<QVector<double>> matrix;
    for(int i =0; i < xSize; i++)
    {
        QVector<double> tmp;
        for(int j=0; j<p; j++)
        {
            tmp.push_back(pow(d.vX[i],j));
        }
        matrix.push_back(tmp);
    }
    return matrix;
}

QVector<double> regression_vector(QVector<double> func, QVector<double> xV)
{
    QVector<double> regV;
    for(auto x : xV)
    {
        regV.push_back(calc_func(func,x));
    }
    return regV;
}

xy create_exp(int amount, double step, double startx, QVector<double> function, double g)
{
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed1);
    std::normal_distribution<double> distribution(0,g);
    double x = startx;
    xy data;
    for(int i = 0; i <amount; i++)
    {
        data.vY.push_back(calc_func(function,x) + distribution(generator));
        data.vX.push_back(x);
        x+=step;
    }
    return data;
}

double calc_func(QVector<double> function, double x)
{
    double sum=function.front();
    for(int i = 1; i < function.size();i++)
    {
        sum+=function[i]*pow(x,i);
    }
    return sum;
}

void print_v(QVector<double> v)
{
    for(auto e : v)
    {
       qDebug() << e ;
    }
}
//Расчет квантили норм. распределения.
double quantile(double level)
{
   double q, t;
   double one = 1;

   t = level < 0.5 ? level : one - level;
   t = sqrt(-2 * log(t));
   q = t - ((0.010328 * t + 0.802853) * t + 2.515517) /
      (((0.001308 * t + 0.189269) * t + 1.432788) * t + 1);
   return level > 0.5 ? q : -q;
}

//Статистика Фишера
double F_test(const double a, const double b)
{
    return a>b ? a/b : b/a;
}

//Критическое значение статистики Фишера
double F_test_cr(int v1, int v2, double level)
{
    double u = quantile(level);
    double h = 2.0*(v1-1)*(v2-1)/(v1+v2-2);
    double l = (pow(u,2)-3)/6;
    double w = (u*sqrt(h+l)/h) - (1.0/(v1-1)-1.0/(v2-1))*(l+5.0/6.0-2.0/(3.0*h));
    return exp(2*w);
}

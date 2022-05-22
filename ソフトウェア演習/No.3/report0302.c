#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// target function 1
double f1(double x)
{
    return x * x;
}

// target function 2
double f2(double x)
{
    return x * x * x + x * x;
}

// target function 3
double f3(double x)
{
    return sin(x) + cos(x);
}

// calculation of the area of micro-trapezoid
double trapezoid(double w1, double w2, double h)
{
    return (w1 + w2) * h / 2.0;
}

// general intergral function by calculating and summing up the area of micro-trapezoid
double integral(double x1, double x2, int n, double (*func)())
{
    double area;
    area = 0;
    double range = x2 - x1; //積分範囲
    double h = range / n;   //台形間隔
    for (double i = 0; i < n; i++)
    {
        area += trapezoid(func(x1 + (h)*i), func(x1 + (h) * (i + 1)), h);
    }
    return area;
}

int main()
{
    double (*func[])() = {f1, f2, f3};
    double val[3][2] = {{1.0, 10.0}, {1.0, 10.0}, {M_PI / 3.0, M_PI}};

    int i;

    for (i = 0; i < 3; i++)
    {
        printf("f%d: %f\n", i, integral(val[i][0], val[i][1], 10000, *func[i]));
    }

    return EXIT_SUCCESS;
}
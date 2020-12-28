#include <cstdio>

int add(int parametre1,int paramtre2)
{
    return parametre1 + paramtre2;
}
double add(double parametre1,double parametre2)
{
    return parametre1 + parametre2;
}

int main()
{
    int a = add(1,1);
    double b = add(1.0,1.0);
    int c = add(3.99,0.99);

    printf("a: %d, b: %f, c: %d",a,b,c);
    return 0;
}
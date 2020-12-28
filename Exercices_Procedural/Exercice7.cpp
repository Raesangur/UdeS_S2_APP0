#include <cstdio>

template <typename monType>
monType fonction(monType parametre1, monType parametre2)
{
    return parametre1 + parametre2;
}

int main()
{
    int a = fonction(1, 1);
    double b = fonction(1.0, 1.0);
    int c = fonction(3.99, 0.99);

    printf("a: %d, b: %f, c: %d", a, b, c);
    return 0;
}
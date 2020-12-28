#include <cstdio>

int* fonction(int parametre)
{
    int* chiffreCool = new int;
    *chiffreCool = parametre;

    return chiffreCool;
}

int main()
{
    int* pa = fonction(42);
    int a = *pa;

    printf("%d\n", a);

    delete pa;
    return 0;
}
#include <cstdio>

int* fonction(int parametre)
{
    int chiffreCool = parametre;
    return &chiffreCool;
}

int main()
{
    int* pa = fonction(42);
    int a = *pa;

    printf("%d\n", a);
    return 0;
}
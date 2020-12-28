#include <cstdio>
#include <cstring>

int main()
{
    const char* merveilleuxMessage = "Bon matin";

    int tailleMessage = strlen(merveilleuxMessage) + 1;
    char* coolString = new char[tailleMessage + 1];

    for (int i = 0; i < tailleMessage; i++)
    {
        coolString[i] = merveilleuxMessage[i];
    }
    coolString[tailleMessage - 1] = '!';
    coolString[tailleMessage] = '\0';

    printf("%s\n", coolString);
    delete[] coolString;
    return 0;
}
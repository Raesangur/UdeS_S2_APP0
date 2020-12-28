#include <cstdio>
#include <cstring>

class string
{
private:
    char* allocatedString;

    void AjoutExclamation()
    {
        allocatedString[tailleString - 2] = '!';
        allocatedString[tailleString - 1] = '\0';
    }

public:
    const int tailleString;

    string(const char* message) : tailleString{(int)strlen(message) + 2}
    {
        allocatedString = new char[tailleString];
        strcpy(allocatedString, message);

        AjoutExclamation();
    }
    ~string()
    {
        delete[] allocatedString;
        printf("Memoire libre maintenant\n");
    }

    void Print();
};

void string::Print()
{
    printf("%s\n", allocatedString);
}

int main()
{
    string merveilleuxMessage{"Bon matin"};

    merveilleuxMessage.Print();

    return 0;
}
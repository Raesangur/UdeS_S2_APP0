#include <cstdio>
#include <string>

class myString
{
public:
    std::string str;
    myString(const char* text) : str{text}
    {
        printf("Creation de la string\n");
    }
    myString(myString& copiedString) : str{copiedString.str}
    {
        printf("Copie de la string\n");
    }
    ~myString()
    {
        printf("Destruction de la string\n");
    }
};

void utiliserString(myString str)
{
    printf("Utilisation de la string\n");
    str.str = "";
}

int main()
{
    myString merveilleuxMessage{"Bon matin"};

    utiliserString(merveilleuxMessage);
    printf("%s\n", merveilleuxMessage.str.c_str());

    return 0;
}
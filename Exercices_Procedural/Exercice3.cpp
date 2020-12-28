#include <cstdio>
#include <string>

class Personne
{
public:
    std::string nom;

    Personne(std::string nomPersonne) : nom(nomPersonne)
    {
        printf("Bon matin %s\n", nom.c_str());
    }
    ~Personne()
    {
        printf("Bonne fin de matin %s\n", nom.c_str());
    }
};

int main()
{
    Personne george{"George"};
    Personne jonathan("Jonathan");

    if(true)
    {
        Personne emilia{"Emilia"};
    }

    return 0;
}
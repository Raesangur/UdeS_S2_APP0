#include <cstdio>
#include <string>

class Personne
{
private:
    std::string _nom;

public:
    Personne(std::string nom) : _nom{nom}
    {
    }

    std::string Get_Nom()
    {
        return _nom;
    }
};

int main()
{
    Personne bob("Bob");

    std::string nomDeBob = bob.Get_Nom();
    printf("%s\n", nomDeBob.c_str());

    return 0;
}
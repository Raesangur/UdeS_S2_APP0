#include <cstdio>
#include <string>

class Personne
{
private:
    std::string _nom;

public:
    Personne(const std::string& nom) : _nom{nom}
    {
    }

    const std::string& Get_Nom()
    {
        return _nom;
    }
};

int main()
{
    Personne bob("Bob");

    const std::string& nomDeBob = bob.Get_Nom();
    printf("%s\n", nomDeBob.c_str());

    return 0;
}
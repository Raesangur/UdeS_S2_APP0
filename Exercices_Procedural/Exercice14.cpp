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
    void Set_Nom(const std::string& nouveauNom)
    {
        if (nouveauNom != "cthulhu")
        {
            _nom = nouveauNom;
        }
    }
};

int main()
{
    Personne bob("Bob");

    bob.Set_Nom("Bobinette");

    bob.Set_Nom("cthulhu");

    const std::string& nomDeBob = bob.Get_Nom();
    printf("%s\n", nomDeBob.c_str());

    return 0;
}
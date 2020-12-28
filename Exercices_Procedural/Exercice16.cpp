#include <cstdio>
#include <string>

class Personne
{
private:
    std::string m_nom;
    int m_age;
    float m_salaireHoraire;

public:
    Personne(const std::string& nom, int age, float salaire) : m_nom{nom}, m_age{age}, m_salaireHoraire{salaire}
    {
        printf("Bon matin %s\n", m_nom.c_str());
    }

    bool operator==(const Personne& autrePersonne)
    {
        return (autrePersonne.m_nom == m_nom) && (autrePersonne.m_age == m_age);
    }
    Personne operator+(const Personne& autrePersonne)
    {
        return Personne{m_nom, m_age + autrePersonne.m_age, m_salaireHoraire + autrePersonne.m_salaireHoraire};
    }
};

int main()
{
    Personne jonathan1{"Jonathan", 21, 15.75};
    Personne jonathan2{"Jonathan", 21, 20.50};
    Personne phillipe{"Phillipe", 47, 45.00};

    if (jonathan1 == jonathan2)
    {
        printf("Les deux Jonathans sont egaux!\n");
    }

    if (jonathan1 == phillipe)
    {
        printf("Jonathan et Phillipe sont la meme personne?\n");
    }

    Personne megaJonathan = jonathan1 + phillipe;

    return 0;
}

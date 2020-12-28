#include <stdio.h>

class Personne
{
public:
    char nom[128];
    char prenom[128];
    int  age;

    void afficher()
    {
        printf("Nom: %s\n", nom);
        printf("Prenom: %s\n", prenom);
        printf("Age: %d\n", age);
    }
};


int main()
{
    class Personne p;

    printf("Nom: ");
    scanf("%s", p.nom);
    printf("Prenom: ");
    scanf("%s", p.prenom);
    printf("Age: ");
    scanf("%d", &p.age);

    p.afficher();

    return 0;
}
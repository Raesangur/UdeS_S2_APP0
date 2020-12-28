#include <cstdio>
#include <string>

int main()
{
    const char* phraseDeBase = " inventa le langage C en ";

    std::string prenom{"Dennis"};
    std::string nomFamille = "Ritchie";
    int annee = 1972;

    std::string phrase;
    if(phrase.empty() == true)
    {
        printf("La phrase est vide\n");
    }
    phrase = prenom + ' ' + nomFamille;
    phrase.append(phraseDeBase);

    auto anneeString = std::to_string(annee);
    phrase.append(anneeString);

    printf("%s",phrase.c_str());
    printf("Pointeur1: %p, Pointeur2: %p", phrase.c_str(), phrase.data());
    return 0;
}
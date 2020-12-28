#include "classeImagePGM.hpp"
#include <algorithm>
#include <cinttypes>
#include <cstdint>
#include <cstdio>

uint16_t& ImagePGM::Pixel(uint16_t ligne, uint16_t colonne) const
{
    // L'image n'as pas de dimensions de base. Nous devons donc simuler ces dimensions.
    // Un tableau int x[3][5] est un tableau de 3 int[5] successifs
    // Se déplacer dans le tableau à l'aide d'un pointeur nécessite de déplacer le pointeur
    // par la taille d'un int[5], et non pas un simple int.
    // Nous devons donc multiplier la colonne par la largeur de l'image.
    return m_image[ligne * m_largeur + colonne];
}

void ImagePGM::Imprime()
{
    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            printf("%" PRIu16 " ", Pixel(i, j));
        }
        printf("\n");
    }
}


ImagePGM::ImagePGM(const std::string& nomFichier) : m_nomFichier{nomFichier}
{
    // Ouverture du fichier
    FILE* fichier = fopen(m_nomFichier.c_str(), "r");
    if(fichier == nullptr)
    {
        throw std::exception();
    }

    // Création d'un tampon initial pour la lecture des métadonnées
    // (Ce tampon pourraît être alloué dynamiquement pour permettre la lecture de lignes plus
    //  longues dans les cas où il y aurait beaucoup de pixels par lignes. Cependant, l'utilisation
    //  de fscanf après la lecture des métadonnées permet de skipper l'utilisation du buffer et sa
    //  taille limitée ne pose pas de problèmes.)
    uint16_t numLigne = 0;
    char     tampon[128];
    int      i = 0;

    // Durant les lignes de code qui suivent, l'utilisation de la macro `PRIu16` est souvent
    // utilisée pour le formatting de strings. Il s'agit d'une macro définie par le standard qui
    // accomodera toujours des entiers non-signés 16-bits. Elle est définie dans <inttypes.h> ou
    // <cinttypes>. Son utilisation n'est pas nécessaire, mais est plus portable et standard. Il
    // faut aussi savoir que des `string literals` adjacentes se font concaténer durant le processus
    // de translation du compilateur.

    while(!feof(fichier))
    {
        if(numLigne < 3)
        {
            // Lecture de la ligne dans le tampon de traitement de données
            fgets(tampon, sizeof(tampon), fichier);

            // Ignorer la ligne s'il s'agit d'un commentaire
            if(tampon[0] == '#')
            {
                // Facultatif, ajout des commentaires d'en-tête
                m_commentaires.emplace_back(tampon);
                continue;    // Le mot-clé `continue` skip à la prochaine boucle
            }

            if(numLigne == 0)
            {
                // Conversion du tampon en std::string pour recherche.
                // L'utilisation de la librairie string.h est une autre solution possible.
                std::string tempString{tampon};
                if(tempString.find("P2") == std::string::npos)
                {
                    // Le 'P2' n'a pas été trouvé comme première ligne!
                    throw std::exception();
                }
            }
            else if(numLigne == 1)
            {
                // Scan de la ligne pour la largeur et la hauteur
                sscanf(tampon, "%" PRIu16 " %" PRIu16, &m_largeur, &m_hauteur);
            }
            else if(numLigne == 2)
            {
                // Scan de la ligne pour la valeur maximale d'un pixel
                sscanf(tampon, "%" PRIu16, &m_maxVal);

                // Rendu ici, on pourrait changer la taille du tampon pour accomoder des lignes
                // entières.
                // On va juste allouer la taille nécessaire à l'image
                m_image = new uint16_t[m_largeur * m_hauteur];
            }
        }
        else
        {
            // On scan linéairement le fichier pour retrouver toutes les valeurs des pixels
            fscanf(fichier, "%" PRIu16, &m_image[i++]);
        }
        numLigne++;
    }

    // On n'oublie pas de fermer le fichier!
    fclose(fichier);
}

ImagePGM::ImagePGM(const ImagePGM& autreImage)
: m_nomFichier{autreImage.m_nomFichier},
  m_commentaires{autreImage.m_commentaires},
  m_hauteur{autreImage.m_hauteur},
  m_largeur{autreImage.m_largeur},
  m_maxVal{autreImage.m_maxVal}
{
    // Une fois tous les membres copiés, il reste à allouer la mémoire du nouvel objet, et y copier
    // tous les pixels de l'autre image.
    m_image = new uint16_t[m_largeur * m_hauteur];

    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            Pixel(i, j) = autreImage.Pixel(i, j);
        }
    }
}

ImagePGM::~ImagePGM()
{
    // Il faut libérer la mémoire!
    delete[] m_image;
}

bool ImagePGM::operator==(const ImagePGM& autreImage)
{
    // On compare en premier les métadonnées
    if((m_largeur != autreImage.m_largeur) || (m_hauteur != autreImage.m_hauteur)
       || (m_maxVal != autreImage.m_maxVal))
    {
        return false;
    }

    // Puis on compare chaque pixel individuellement
    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            if(Pixel(i, j) == autreImage.Pixel(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

bool ImagePGM::operator!=(const ImagePGM& autreImage)
{
    return !(*this == autreImage);
}

void ImagePGM::Sauvegarde(const std::string& nomFichier)
{
    // Ouverture du fichier en écriture
    FILE* fichier = fopen(nomFichier.c_str(), "w");
    if(fichier == nullptr)
    {
        throw std::exception();
    }

    // Écriture des métadonnées
    for(const std::string& comm : m_commentaires)
    {
        // Écriture des commentaires (facultatif)
        fprintf(fichier, "%s\n", comm.c_str());
    }

    // clang-format est un outil de formatting automatique de code, ignorez les petits commentaires
    // d'instruction
    /* clang-format off */
    fprintf(fichier,
            "P2\n"
            "%" PRIu16 " %" PRIu16 "\n"
            "%" PRIu16 "\n",
            m_largeur, m_hauteur,
            m_maxVal);
    /* clang-format on */

    std::string ligne;
    ligne.reserve(sizeof("65535") * m_largeur);
    // Le sizeof retourne 6 à cause du terminating character '\0', nous n'en voulont pas, mais nous
    // voulons des espaces à la place, donc ça tombe bien.

    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            ligne += std::to_string(Pixel(i, j)) + ' ';
        }
        fprintf(fichier, "%s\n", ligne.c_str());
        ligne.clear();
    }
}


// Fonctions de l'APP4 à réimplémenter
// Une seule de ces fonctions devra être faite dans le cadre de cet APP0.
void ImagePGM::CreerNegatif()
{
    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            Pixel(i, j) = m_maxVal - Pixel(i, j);
        }
    }
}

std::vector<uint16_t> ImagePGM::CreerHistogramme()
{
    // Crée un vecteur (tableau à taille variable), et réserve la taille nécessaire, en
    // initialisant tous les éléments à 0.
    std::vector<uint16_t> histogramme(m_maxVal, 0);

    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            // Incrémente la quantité à l'intensité du pixel
            histogramme[Pixel(i, j)]++;
        }
    }

    return histogramme;
}

uint16_t ImagePGM::CouleurPreponderante()
{
    std::vector<uint16_t> histogramme = CreerHistogramme();

    int indexOfGreater = 0;
    for(int i = 0; i < histogramme.size(); i++)
    {
        // Regarde si la valeur actuelle est plus grande que la dernier plus grande valeur trouvée
        if(histogramme[i] > histogramme[indexOfGreater])
        {
            indexOfGreater = i;
        }
    }

    // L'index de l'histogramme représente l'intensité lumineuse
    return indexOfGreater;
}

void ImagePGM::EclaircirNoircir(int32_t valeur)
{
    if((valeur > m_maxVal) || (valeur < -m_maxVal))
    {
        throw std::exception();
    }

    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            int32_t newVal = valeur + Pixel(i, j);

            // Clipping de la valeur entre 0 et m_maxVal
            // (qu'il a fallu caster pour qu'il soit du même type que newVal)
            Pixel(i, j) = std::max(0, std::min(newVal, (int32_t)m_maxVal));
        }
    }
}

void ImagePGM::Pivoter90(bool gaucheDroite)
{
    // Déréférencer `this` nous donne directement l'objet, qu'on passe au constructeur de la classe
    // pour en faire une copie.
    ImagePGM copieOriginelle(*this);
    std::swap(m_hauteur, m_largeur);    // The old switcharoo

    for(int i = 0; i < m_hauteur; i++)
    {
        for(int j = 0; j < m_largeur; j++)
        {
            if(gaucheDroite == ANTIHORAIRE)
            {
                Pixel(i, j) = copieOriginelle.Pixel(j, m_hauteur - i - 1);
            }
            else
            {
                Pixel(i, j) = copieOriginelle.Pixel(m_largeur - j - 1, i);
            }
        }
    }
}

ImagePGM ImagePGM::Extraire(int ligneCoin1, int colonneCoin1, int ligneCoin2, int colonneCoin2)
{
    if((ligneCoin1 > ligneCoin2) || (colonneCoin1 > colonneCoin2))
    {
        throw std::exception();
    }

    // Création de la sous-image et copie des métadonnées
    ImagePGM sousImage;
    sousImage.m_commentaires = m_commentaires;
    sousImage.m_hauteur      = ligneCoin2 - ligneCoin1;
    sousImage.m_largeur      = colonneCoin2 - colonneCoin1;
    sousImage.m_maxVal       = m_maxVal;
    sousImage.m_image        = new uint16_t[sousImage.m_hauteur * sousImage.m_largeur];

    for(int i = ligneCoin1; i < ligneCoin2; i++)
    {
        for(int j = colonneCoin1; j < colonneCoin2; j++)
        {
            sousImage.Pixel(i - ligneCoin1, j - colonneCoin1) = Pixel(i, j);
        }
    }

    return sousImage;
}

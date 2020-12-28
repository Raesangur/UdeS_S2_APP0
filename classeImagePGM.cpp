#include "classeImagePGM.hpp"
#include <cinttypes>
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
  m_largeur{autreImage.m_largeur}
{
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
    if((m_largeur != autreImage.m_largeur) || (m_hauteur != autreImage.m_hauteur)
       || (m_maxVal != autreImage.m_maxVal))
    {
        return false;
    }

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
int      ImagePGM::CreerHistogramme();
uint16_t ImagePGM::CouleurPreponderante();
int      ImagePGM::EclaircirNoircir();
int      ImagePGM::Pivoter90(bool gaucheDroite);
int      ImagePGM::Extraire(int ligneCoin1, int colonneCoin1, int ligneCoin2, int colonneCoin2);

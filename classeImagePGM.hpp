#pragma once
#include <string>
#include <vector>


class ImagePGM
{
private:
    const std::string m_nomFichier;
    uint16_t*         m_image   = nullptr;
    uint16_t          m_largeur = 0;
    uint16_t          m_hauteur = 0;
    uint16_t          m_maxVal  = 0;

    // Optionnel, seulement si vous voulez garder les commentaires d'en-tête
    std::vector<std::string> m_commentaires;

    private:
    uint16_t& Pixel(uint16_t ligne, uint16_t colonne) const;

public:
    ImagePGM(const std::string& nomFichier);
    ImagePGM(const ImagePGM& autreImage);
    ~ImagePGM();

    void Sauvegarde(const std::string& nomFichier);
    void Imprime();

    bool operator==(const ImagePGM& autreImage);
    bool operator!=(const ImagePGM& autreImage);

    // Fonctions à réimplémenter en C++.
    // Une seule de ces fonctions devra être faite dans le cadre de cet APP0.
    void CreerNegatif();
    int CreerHistogramme();
    uint16_t CouleurPreponderante();
    int EclaircirNoircir();
    int Pivoter90(bool gaucheDroite);
    ImagePGM Extraire(int ligneCoin1, int colonneCoin1, int ligneCoin2, int colonneCoin2);

};

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

    // private:
public:
    uint16_t& Pixel(uint16_t ligne, uint16_t colonne);

public:
    ImagePGM(const std::string& nomFichier);
    ~ImagePGM();

    void Sauvegarde(const std::string& nomFichier);
    void Imprime();
};

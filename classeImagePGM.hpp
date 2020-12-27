#pragma once
#include <string>

class ImagePGM
{
private:
    const std::string m_nomFichier;
    uint16_t* m_image = nullptr;
    uint16_t m_largeur = 0;
    uint16_t m_hauteur = 0;
    uint16_t m_maxVal = 0;

//private: 
public:
    uint16_t& Pixel(uint16_t ligne, uint16_t colonne);
    void Imprime();

public:
    ImagePGM(const std::string& nomFichier);
    ~ImagePGM();

    void Sauvegarder(const std::string& nomFichier);
};
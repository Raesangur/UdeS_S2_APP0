#include "classeImagePGM.hpp"

int main()
{
    ImagePGM someInstance("E:/OneDrive_Uni/OneDrive - USherbrooke/S2/APP0/Problematique/Project1/Sherbrooke_Frontenac_nuit.pgm");

    uint16_t col = someInstance.CouleurPreponderante();
}
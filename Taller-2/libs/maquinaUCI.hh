#ifndef MAQUINA_HH
#define MAQUINA_HH

#include "medicionPaciente.hh"

struct Maquina {
    unsigned char idMaquina;
    int numMediciones;
    Medicion* mediciones;
};

#endif
#ifndef SALA_HH
#define SALA_HH

#include "maquinaUCI.hh"

struct Sala {
    unsigned char idSala;
    unsigned char numMaquinas;
    Maquina* maquinas;
};

#endif
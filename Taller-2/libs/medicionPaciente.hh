#ifndef MEDICION_HH
#define MEDICION_HH

#include "lecturaSensor.hh"

struct Medicion {
    char idPaciente[11];
    char fechaHora[24];
    int numLecturas;
    Lectura* lecturas;
};

#endif
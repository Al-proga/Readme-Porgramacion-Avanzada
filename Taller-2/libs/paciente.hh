#ifndef PACIENTE_HH
#define PACIENTE_HH

struct Paciente {
    int id;
    char tipoDocumento[4];
    char documento[15];
    char nombres[50];
    char apellidos[50];
    char fechaNacimiento[11];
    char telefono[20];
    char email[50];
    char tipoSangre[4];
    char entidadSalud[30];
    char medicinaPrepagada[30];
};

#endif
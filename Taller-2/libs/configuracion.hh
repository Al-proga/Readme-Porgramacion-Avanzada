#ifndef CONFIGURACION_HH
#define CONFIGURACION_HH

struct ConfiguracionSensor {
    char tipoSensor[1];
    double min;
    double max;
};

struct ArchivoConfiguracion {
    int numSensores;
    ConfiguracionSensor* sensores;
};

#endif
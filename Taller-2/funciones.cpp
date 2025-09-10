#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "libs/paciente.hh"
#include "libs/archivoPacientes.hh"
#include "libs/configuracion.hh"
#include "libs/salaUCI.hh"

using namespace std;

struct InfoAnomalia
{
    char idPaciente[11];
    char nombrePaciente[101];
    char fechaHora[24];
    Lectura lecturaAnomala;
};

struct MedicionECG
{ 
    char fechaHora[24]; 
    double valor; 
};

char* trim(char* str)
{ 
    while(isspace(*str))
    { 
        str++; 
        if (*str == '\0') 
        return str;
    } 

    char* end = str + strlen(str) - 1; 
    
    while(end > str && isspace(*end)) end--; 
    *(end + 1) = '\0'; 
    return str; 
}

char** separarLinea(char* linea, int& numTokens, char delimitador)
{ 
    char* tokensTemporales[30]; 
    numTokens = 0; 
    char tokenBuffer[200]; 
    int indiceBuffer = 0; 

    for(size_t i = 0; i <= strlen(linea); ++i)
    { 
        if(linea[i] == delimitador || linea[i] == '\0')
        { 
            tokenBuffer[indiceBuffer] = '\0'; 
            char* tokenLimpio = trim(tokenBuffer); 
            tokensTemporales[numTokens] = new char[strlen(tokenLimpio) + 1]; 
            strcpy(tokensTemporales[numTokens], tokenLimpio); 
            numTokens++; 
            indiceBuffer = 0; 
        } else { 
            tokenBuffer[indiceBuffer] = linea[i]; 
            indiceBuffer++; 
        } 
    } 
    
    char** tokensFinales = new char*[numTokens]; 
    for (int i = 0; i < numTokens; i++)
    { 
        tokensFinales[i] = tokensTemporales[i]; 
    } 
    return tokensFinales; 
}

Paciente crearPacienteDesdeTokens(char** tokens)
{ 
    Paciente p; 
    p.id = atoi(tokens[0]); 
    strcpy(p.tipoDocumento, tokens[1]); 
    strcpy(p.documento, tokens[2]); 
    strcpy(p.nombres, tokens[3]); 
    strcpy(p.apellidos, tokens[4]); 
    strcpy(p.fechaNacimiento, tokens[5]); 
    strcpy(p.telefono, tokens[6]);
    strcpy(p.email, tokens[7]); 
    strcpy(p.tipoSangre, tokens[8]); 
    strcpy(p.entidadSalud, tokens[9]); 
    strcpy(p.medicinaPrepagada, tokens[10]); 
    return p; 
}

ArchivoPacientes cargarArchivoPacientes(const char* nombreArchivo)
{ 
    ArchivoPacientes datos; 
    datos.numPacientes = 0; 
    datos.pacientes = NULL; 
    ifstream archivo(nombreArchivo); 
    
    if (!archivo.is_open()){ return datos; } 
    
    char buffer[500]; 
    while (archivo.getline(buffer, 500)){ datos.numPacientes++; } 
    archivo.close(); 
    
    if (datos.numPacientes == 0){ return datos; } 

    datos.pacientes = new Paciente[datos.numPacientes]; 
    archivo.open(nombreArchivo); 
    if (!archivo.is_open()){ delete[] datos.pacientes; datos.pacientes = NULL; datos.numPacientes = 0; return datos; } 
    
    int i = 0; 
    while (archivo.getline(buffer, 500))
    { 
        char** tokens; 
        int numTokens = 0; 
        tokens = separarLinea(buffer, numTokens, ';'); 
        
        if(numTokens > 0) datos.pacientes[i++] = crearPacienteDesdeTokens(tokens); 
        for (int j = 0; j < numTokens; j++){ delete[] tokens[j]; } 
        delete[] tokens; 
    } 
            
    archivo.close(); 
    cout << "-> Se cargaron " << datos.numPacientes << " pacientes." << endl; 
    return datos; 
}

ConfiguracionSensor crearConfigDesdeTokens(char** tokens)
{ 
    ConfiguracionSensor c; 
    strcpy(c.tipoSensor, tokens[0]); 
    c.min = atof(tokens[1]); 
    c.max = atof(tokens[2]); 
    return c; 
}

ArchivoConfiguracion cargarArchivoConfig(const char* nombreArchivo)
{ 
    ArchivoConfiguracion datos; 
    datos.numSensores = 0; 
    datos.sensores = NULL; 
    ifstream archivo(nombreArchivo); 
    if (!archivo.is_open()){ return datos; } 
    
    char buffer[100]; 
    while(archivo.getline(buffer, 100)){ datos.numSensores++; } 
    
    archivo.close(); 
    if(datos.numSensores == 0){ return datos; } 
    
    datos.sensores = new ConfiguracionSensor[datos.numSensores]; 
    archivo.open(nombreArchivo); 
    if (!archivo.is_open()){ delete[] datos.sensores; datos.sensores = NULL; datos.numSensores = 0; return datos; } 
    
    int i = 0; 
    while (archivo.getline(buffer, 100))
    { 
        char** tokens; 
        int numTokens = 0; 
        tokens = separarLinea(buffer, numTokens, ',');
        if(numTokens > 0) datos.sensores[i++] = crearConfigDesdeTokens(tokens); 

        for(int j = 0; j < numTokens; j++) { delete[] tokens[j]; } 
        delete[] tokens; 
    } 
    
    archivo.close(); 
    cout << "-> Se cargaron " << datos.numSensores << " reglas de configuracion." << endl; 
    return datos; 
}

bool FechaMayor(const char fecha1[], const char fecha2[])
{ 
    int dia1, mes1, anio1, h1, m1, s1, ms1; 
    int dia2, mes2, anio2, h2, m2, s2, ms2; 
    sscanf(fecha1, "%d/%d/%d %d:%d:%d.%d", &dia1, &mes1, &anio1, &h1, &m1, &s1, &ms1); 
    sscanf(fecha2, "%d/%d/%d %d:%d:%d.%d", &dia2, &mes2, &anio2, &h2, &m2, &s2, &ms2); 
    
    if(anio1 != anio2) return anio1 > anio2;
    if(mes1 != mes2) return mes1 > mes2; 
    if(dia1 != dia2) return dia1 > dia2; 
    if(h1 != h2) return h1 > h2; 
    if(m1 != m2) return m1 > m2; 
    if(s1 != s2) return s1 > s2; 
    return ms1 > ms2; 
}

bool esLecturaAnomala(const Lectura& lectura, const ArchivoConfiguracion& config)
{
    if (lectura.tipoSensor == 'E'){ return false; }

    if (lectura.tipoSensor == 'P')
    {
        bool anomaliaSistolica = true;
        bool anomaliaDiastolica = true;
        for (int i = 0; i < config.numSensores; ++i)
        {
            if(strcmp(config.sensores[i].tipoSensor, "P_SIS") == 0){
                if(lectura.valor1 >= config.sensores[i].min && lectura.valor1 <= config.sensores[i].max){ anomaliaSistolica = false; }
            }
            if(strcmp(config.sensores[i].tipoSensor, "P_DIA") == 0){
                if(lectura.valor2 >= config.sensores[i].min && lectura.valor2 <= config.sensores[i].max){ anomaliaDiastolica = false; }
            }
        }
        return anomaliaSistolica || anomaliaDiastolica;
    }

    for (int i = 0; i < config.numSensores; ++i)
    {
        if (config.sensores[i].tipoSensor[0] == lectura.tipoSensor && strlen(config.sensores[i].tipoSensor) == 1)
        {
            if (lectura.valor1 < config.sensores[i].min || lectura.valor1 > config.sensores[i].max){ return true; }
            return false;
        }
    }
    return false;
}

Sala* cargarArchivoBSF(const char* nombreArchivo, int& numSalas)
{ 
    ifstream archivo(nombreArchivo, ios::in | ios::binary); 
    if(!archivo.is_open()){ cout << "Error: No se pudo abrir el archivo binario " << nombreArchivo << endl; numSalas = 0; return NULL; } 
    
    char idSala; 
    archivo.read(&idSala, sizeof(idSala)); 
    char numMaquinasChar; 
    archivo.read(&numMaquinasChar, sizeof(numMaquinasChar)); 
    int numMaquinas = (int)(unsigned char)numMaquinasChar; 
    
    numSalas = 1; 
    Sala* salas = new Sala[numSalas]; 
    salas[0].idSala = (unsigned char)idSala; 
    salas[0].numMaquinas = numMaquinas; 
    salas[0].maquinas = new Maquina[numMaquinas]; 
    
    for(int i = 0; i < numMaquinas; ++i)
    { 
        Maquina& maquinaActual = salas[0].maquinas[i]; 
        char idMaquinaChar; 
        archivo.read(&idMaquinaChar, sizeof(idMaquinaChar)); 
        maquinaActual.idMaquina = (unsigned char)idMaquinaChar; 
        archivo.read(reinterpret_cast<char*>(&maquinaActual.numMediciones), sizeof(int)); 
        maquinaActual.mediciones = new Medicion[maquinaActual.numMediciones]; 
        
        for(int j = 0; j < maquinaActual.numMediciones; ++j)
        { 
            Medicion& medicionActual = maquinaActual.mediciones[j]; 
            archivo.read(medicionActual.idPaciente, 11); 
            archivo.read(medicionActual.fechaHora, 24); 
            archivo.read(reinterpret_cast<char*>(&medicionActual.numLecturas), sizeof(int)); 
            medicionActual.lecturas = new Lectura[medicionActual.numLecturas]; 
            
            for(int k = 0; k < medicionActual.numLecturas; ++k)
            { 
                Lectura& lecturaActual = medicionActual.lecturas[k]; 
                archivo.read(&lecturaActual.tipoSensor, sizeof(char)); 
                if(lecturaActual.tipoSensor == 'T' || lecturaActual.tipoSensor == 'O' || lecturaActual.tipoSensor == 'E'){ 
                    double valor; 
                    archivo.read(reinterpret_cast<char*>(&valor), sizeof(valor)); 
                    lecturaActual.valor1 = valor; 
                    lecturaActual.valor2 = 0.0; 
                } else if(lecturaActual.tipoSensor == 'P'){ 
                    unsigned int sist, diast; 
                    archivo.read(reinterpret_cast<char*>(&sist), sizeof(sist)); 
                    archivo.read(reinterpret_cast<char*>(&diast), sizeof(diast)); 
                    lecturaActual.valor1 = sist; 
                    lecturaActual.valor2 = diast; 
                } 
            } 
        } 
    } 
    
    archivo.close(); 
    cout << "-> Se cargaron los datos de mediciones desde " << nombreArchivo << "." << endl; 
    return salas; 
}

void liberarMemoriaUCI(Sala* salas, int numSalas)
{ 
    if(salas == NULL) return; 
    for(int i = 0; i < numSalas; ++i)
    { 
        for(int j = 0; j < salas[i].numMaquinas; ++j)
        { 
            for(int k = 0; k < salas[i].maquinas[j].numMediciones; ++k)
            { 
                delete[] salas[i].maquinas[j].mediciones[k].lecturas; 
            } 
            delete[] salas[i].maquinas[j].mediciones; 
        } 
        delete[] salas[i].maquinas; 
    } 
    delete[] salas; 
    cout << "-> Memoria de la UCI liberada." << endl; 
}

void generarReportePaciente(int idPaciente, const ArchivoPacientes& dbPacientes, const Sala* salas, int numSalas, const ArchivoConfiguracion& config)
{
    char nombreCompleto[101] = "Paciente no encontrado";
    bool pacienteEncontrado = false;
    for(int i = 0; i < dbPacientes.numPacientes; ++i) {
        if(dbPacientes.pacientes[i].id == idPaciente) {
            strcpy(nombreCompleto, dbPacientes.pacientes[i].nombres);
            strcat(nombreCompleto, " ");
            strcat(nombreCompleto, dbPacientes.pacientes[i].apellidos);
            pacienteEncontrado = true;
            break;
        }
    }
    if (!pacienteEncontrado) { cout << "Error: Paciente con ID " << idPaciente << " no encontrado." << endl; return; }

    struct MedicionCompleta { char fechaHora[24]; Lectura lectura; };
    MedicionCompleta medicionesDelPaciente[1000];
    int numMedicionesPaciente = 0;
    char idPacienteStr[11];
    sprintf(idPacienteStr, "%d", idPaciente);

    for (int s = 0; s < numSalas; ++s) {
        for (int m = 0; m < salas[s].numMaquinas; ++m) {
            for (int med = 0; med < salas[s].maquinas[m].numMediciones; ++med) {
                const Medicion& medicionActual = salas[s].maquinas[m].mediciones[med];
                if (strncmp(medicionActual.idPaciente, idPacienteStr, strlen(idPacienteStr)) == 0) {
                    for (int l = 0; l < medicionActual.numLecturas; ++l) {
                        strcpy(medicionesDelPaciente[numMedicionesPaciente].fechaHora, medicionActual.fechaHora);
                        medicionesDelPaciente[numMedicionesPaciente].lectura = medicionActual.lecturas[l];
                        numMedicionesPaciente++;
                    }
                }
            }
        }
    }

    if (numMedicionesPaciente == 0) { cout << "No se encontraron mediciones para el paciente con ID " << idPaciente << "." << endl; return; }
    
    for (int i = 0; i < numMedicionesPaciente - 1; i++) {
        for (int j = 0; j < numMedicionesPaciente - i - 1; j++) {
            if (FechaMayor(medicionesDelPaciente[j].fechaHora, medicionesDelPaciente[j + 1].fechaHora)) {
                MedicionCompleta temp = medicionesDelPaciente[j];
                medicionesDelPaciente[j] = medicionesDelPaciente[j + 1];
                medicionesDelPaciente[j + 1] = temp;
            }
        }
    }
    
    double minECG = 100000.0, maxECG = -100000.0;
    bool hayLecturasECG = false;
    for(int i = 0; i < numMedicionesPaciente; ++i){
        if(medicionesDelPaciente[i].lectura.tipoSensor == 'E'){
            hayLecturasECG = true;
            if(medicionesDelPaciente[i].lectura.valor1 < minECG) minECG = medicionesDelPaciente[i].lectura.valor1;
            if(medicionesDelPaciente[i].lectura.valor1 > maxECG) maxECG = medicionesDelPaciente[i].lectura.valor1;
        }
    }

    double limiteInfECG = 0.0, limiteSupECG = 0.0;
    for(int i = 0; i < config.numSensores; ++i){ if (strcmp(config.sensores[i].tipoSensor, "E") == 0){ limiteInfECG = config.sensores[i].min; limiteSupECG = config.sensores[i].max; break; } }
    bool anomaliaConjuntoECG = false;
    if(hayLecturasECG){ if(abs(minECG) + abs(maxECG) > abs(limiteInfECG) + abs(limiteSupECG)){ anomaliaConjuntoECG = true; } }
    
    char nombreArchivo[50];
    sprintf(nombreArchivo, "mediciones_paciente_%d.txt", idPaciente);
    ofstream reporte(nombreArchivo);
    reporte << "--- Reporte de Mediciones para Paciente ---\n";
    reporte << "ID: " << idPaciente << "\nNombre: " << nombreCompleto << "\n";

    const char tiposDeSensor[] = {'T', 'O', 'P', 'E'};
    for(char tipo : tiposDeSensor){
        reporte << "\n--- Sensor: " << tipo << " ---" << endl;
        double min = 100000, max = -100000, sum = 0; int count = 0;
        for(int i = 0; i < numMedicionesPaciente; ++i){
            const MedicionCompleta& med = medicionesDelPaciente[i];
            if(med.lectura.tipoSensor == tipo){
                reporte << med.fechaHora << " - Valor: " << med.lectura.valor1;
                if (tipo == 'P') reporte << "/" << med.lectura.valor2;
                if (tipo != 'E' && esLecturaAnomala(med.lectura, config)) { reporte << " (ANOMALIA)"; }
                reporte << "\n";
                if (med.lectura.valor1 < min) min = med.lectura.valor1;
                if (med.lectura.valor1 > max) max = med.lectura.valor1;
                sum += med.lectura.valor1;
                count++;
            }
        }
        if(tipo == 'E'){ if(anomaliaConjuntoECG){ reporte << ">>> VEREDICTO: ANOMALIA DE AMPLITUD DETECTADA EN ECG.\n"; } else if(hayLecturasECG){ reporte << ">>> VEREDICTO: ECG dentro de parametros normales.\n"; } }
        if(count > 0){ reporte << "Estadisticas -> Min: " << min << ", Max: " << max << ", Promedio: " << (sum / count) << "\n"; } 
        else{ reporte << "No se encontraron lecturas para este sensor.\n"; }
    }
    reporte.close();
    cout << "-> Reporte para paciente " << idPaciente << " generado exitosamente." << endl;
}

void generarReporteAnomaliasGlobal(const Sala* salas, int numSalas, const ArchivoConfiguracion& config, const ArchivoPacientes& dbPacientes)
{
    cout << "Generando reporte global de anomalias..." << endl;
    
    InfoAnomalia anomaliasPuntuales[2000];
    int totalAnomaliasPuntuales = 0;
    for (int s = 0; s < numSalas; ++s) {
        for (int m = 0; m < salas[s].numMaquinas; ++m) {
            for (int med = 0; med < salas[s].maquinas[m].numMediciones; ++med) {
                const Medicion& medicionActual = salas[s].maquinas[m].mediciones[med];
                for (int l = 0; l < medicionActual.numLecturas; ++l) {
                    const Lectura& lecturaActual = medicionActual.lecturas[l];
                    if (esLecturaAnomala(lecturaActual, config)) {
                        strcpy(anomaliasPuntuales[totalAnomaliasPuntuales].idPaciente, medicionActual.idPaciente);
                        strcpy(anomaliasPuntuales[totalAnomaliasPuntuales].fechaHora, medicionActual.fechaHora);
                        anomaliasPuntuales[totalAnomaliasPuntuales].lecturaAnomala = lecturaActual;
                        totalAnomaliasPuntuales++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < totalAnomaliasPuntuales - 1; i++) {
        for (int j = 0; j < totalAnomaliasPuntuales - i - 1; j++) {
            if (FechaMayor(anomaliasPuntuales[j].fechaHora, anomaliasPuntuales[j + 1].fechaHora)) {
                InfoAnomalia temp = anomaliasPuntuales[j];
                anomaliasPuntuales[j] = anomaliasPuntuales[j + 1];
                anomaliasPuntuales[j + 1] = temp;
            }
        }
    }
    
    ofstream reporte("anomalias.txt");
    if (!reporte.is_open()) { cout << "Error creando archivo anomalias.txt" << endl; return; }
    
    reporte << "--- Reporte Global de Anomalias ---\n";
    reporte << "\n=== ANOMALIAS PUNTUALES (T, O, P, etc.) ===\n";
    if (totalAnomaliasPuntuales == 0) {
        reporte << "No se encontraron anomalias puntuales en los datos.\n";
    } else {
        for (int i = 0; i < totalAnomaliasPuntuales; ++i) {
            char nombreCompleto[101] = "Nombre Desconocido";
            int idNum = atoi(anomaliasPuntuales[i].idPaciente);
            for(int p = 0; p < dbPacientes.numPacientes; ++p){ if(dbPacientes.pacientes[p].id == idNum){ strcpy(nombreCompleto, dbPacientes.pacientes[p].nombres); strcat(nombreCompleto, " "); strcat(nombreCompleto, dbPacientes.pacientes[p].apellidos); break; } }
            reporte << "\nFecha: " << anomaliasPuntuales[i].fechaHora << "\n";
            reporte << "  Paciente: " << nombreCompleto << " (ID: " << anomaliasPuntuales[i].idPaciente << ")\n";
            reporte << "  Sensor: " << anomaliasPuntuales[i].lecturaAnomala.tipoSensor << " | Valor: " << anomaliasPuntuales[i].lecturaAnomala.valor1;
            if (anomaliasPuntuales[i].lecturaAnomala.tipoSensor == 'P') reporte << "/" << anomaliasPuntuales[i].lecturaAnomala.valor2;
            reporte << "\n";
        }
    }

    reporte << "\n\n=== ANOMALIAS DE CONJUNTO (ECG) ===\n";
    bool seEncontroAnomaliaECG = false;
    for (int i = 0; i < dbPacientes.numPacientes; ++i) {
        const Paciente& pacienteActual = dbPacientes.pacientes[i];
        char idPacienteStr[11];
        sprintf(idPacienteStr, "%d", pacienteActual.id);
        Lectura lecturasECG[500];
        int numLecturasECG = 0;
        for(int s = 0; s < numSalas; ++s) { for(int m = 0; m < salas[s].numMaquinas; ++m) { for(int med = 0; med < salas[s].maquinas[m].numMediciones; ++med) {
            const Medicion& medicionActual = salas[s].maquinas[m].mediciones[med];
            if (strncmp(medicionActual.idPaciente, idPacienteStr, strlen(idPacienteStr)) == 0) {
                for (int l = 0; l < medicionActual.numLecturas; ++l) {
                    if (medicionActual.lecturas[l].tipoSensor == 'E') {
                        lecturasECG[numLecturasECG++] = medicionActual.lecturas[l];
                    }
                }
            }
        }}}
        if (numLecturasECG > 0) {
            double minECG = 100000.0, maxECG = -100000.0;
            for (int k = 0; k < numLecturasECG; ++k) {
                if (lecturasECG[k].valor1 < minECG) minECG = lecturasECG[k].valor1;
                if (lecturasECG[k].valor1 > maxECG) maxECG = lecturasECG[k].valor1;
            }
            double limInf = 0.0, limSup = 0.0;
            for (int c = 0; c < config.numSensores; ++c) { if (strcmp(config.sensores[c].tipoSensor, "E") == 0) { limInf = config.sensores[c].min; limSup = config.sensores[c].max; break; } }
            
            if (abs(minECG) + abs(maxECG) > abs(limInf) + abs(limSup)) {
                seEncontroAnomaliaECG = true;
                reporte << "\nPaciente: " << pacienteActual.nombres << " " << pacienteActual.apellidos << " (ID: " << pacienteActual.id << ")\n";
                reporte << "  - Veredicto: ANOMALIA DE AMPLITUD DETECTADA EN ECG.\n";
                reporte << "  - Min/Max Registrado: " << minECG << " / " << maxECG << "\n";
            }
        }
    }
    
    if (!seEncontroAnomaliaECG) {
        reporte << "No se encontraron anomalias de conjunto en las lecturas de ECG.\n";
    }

    reporte.close();
    cout << "-> Reporte 'anomalias.txt' generado exitosamente." << endl;
}

void exportarPacientesECGAnomalo(const ArchivoPacientes& dbPacientes, const Sala* salas, int numSalas, const ArchivoConfiguracion& config)
{
    cout << "Iniciando exportacion de pacientes con ECG anomalo..." << endl;
    ofstream archivo("pacientes_ecg_anomalos.dat", ios::out | ios::binary);
    if(!archivo.is_open()){ cout << "Error creando archivo de exportacion." << endl; return; }

    for(int i = 0; i < dbPacientes.numPacientes; ++i)
    {
        const Paciente& pacienteActual = dbPacientes.pacientes[i];
        char idPacienteStr[12] = {0};
        sprintf(idPacienteStr, "%d", pacienteActual.id);
        
        MedicionECG medicionesECG[500];
        int numMedicionesECG = 0;
        unsigned char idMaquinaDeLaLectura = 0;

        for(int s = 0; s < numSalas; ++s){
            for(int m = 0; m < salas[s].numMaquinas; ++m){
                for(int med = 0; med < salas[s].maquinas[m].numMediciones; ++med){
                    const Medicion& medicionActual = salas[s].maquinas[m].mediciones[med];
                    if(strncmp(medicionActual.idPaciente, idPacienteStr, strlen(idPacienteStr)) == 0){
                        for(int l = 0; l < medicionActual.numLecturas; ++l){
                            if(medicionActual.lecturas[l].tipoSensor == 'E'){
                                strcpy(medicionesECG[numMedicionesECG].fechaHora, medicionActual.fechaHora);
                                medicionesECG[numMedicionesECG].valor = medicionActual.lecturas[l].valor1;
                                idMaquinaDeLaLectura = salas[s].maquinas[m].idMaquina;
                                numMedicionesECG++;
                            }
                        }
                    }
                }
            }
        }

        if(numMedicionesECG > 0){
            double minECG = 100000.0, maxECG = -100000.0;
            for(int k = 0; k < numMedicionesECG; ++k){
                if(medicionesECG[k].valor < minECG) minECG = medicionesECG[k].valor;
                if(medicionesECG[k].valor > maxECG) maxECG = medicionesECG[k].valor;
            }
            double limInf = 0.0, limSup = 0.0;
            for(int c = 0; c < config.numSensores; ++c){ if(strcmp(config.sensores[c].tipoSensor, "E") == 0) { limInf = config.sensores[c].min; limSup = config.sensores[c].max; break; } }
            
            if(abs(minECG) + abs(maxECG) > abs(limInf) + abs(limSup)) {
                cout << "-> Paciente con ID " << pacienteActual.id << " tiene ECG anomalo. Exportando..." << endl;
                
                char idPacienteBytes[11] = {0};
                strcpy(idPacienteBytes, idPacienteStr);
                archivo.write(idPacienteBytes, 11);
                archivo.write(reinterpret_cast<char*>(&idMaquinaDeLaLectura), 1);
                archivo.write(reinterpret_cast<char*>(&numMedicionesECG), 4);

                for(int k = 0; k < numMedicionesECG; ++k){
                    archivo.write(medicionesECG[k].fechaHora, 24);
                    archivo.write(reinterpret_cast<char*>(&medicionesECG[k].valor), 8);
                }
            }
        }
    }
    archivo.close();
    cout << "Archivo 'pacientes_ecg_anomalos.dat' generado." << endl;
}
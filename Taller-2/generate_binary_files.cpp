#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

void escribirStringFijo(fstream& archivo, const char* texto, int tamano) {
    char buffer[100] = {0};
    strncpy(buffer, texto, tamano - 1);
    archivo.write(buffer, tamano);
}

int GenerateBinaryFile(const char* text_file_name, const char* binary_file_name);

int main() {
    GenerateBinaryFile("patient_readings_simulation_tiny.txt", "datos.bsf");
    return 0;
}

int GenerateBinaryFile(const char* text_file_name, const char* binary_file_name) {
    fstream text_file(text_file_name, ios::in);
    if (!text_file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de texto " << text_file_name << endl;
        return 1;
    }
    fstream binary_file(binary_file_name, ios::out | ios::binary);
    if (!binary_file.is_open()) {
        cerr << "Error al crear el archivo binario " << binary_file_name << endl;
        return 1;
    }

    cout << "Generando archivo binario desde " << text_file_name << "..." << endl;

    char buffer[100];
    
    text_file.getline(buffer, 100);
    char uci_id = (char)atoi(buffer);
    binary_file.write(&uci_id, sizeof(uci_id));

    text_file.getline(buffer, 100);
    unsigned char num_machines = (unsigned char)atoi(buffer);
    binary_file.write(reinterpret_cast<char*>(&num_machines), sizeof(num_machines));

    for (int i = 0; i < num_machines; i++) {
        text_file.getline(buffer, 100);
        unsigned char machine_id = (unsigned char)atoi(buffer);
        binary_file.write(reinterpret_cast<char*>(&machine_id), sizeof(machine_id));

        text_file.getline(buffer, 100);
        int num_measurements = atoi(buffer);
        binary_file.write(reinterpret_cast<char*>(&num_measurements), sizeof(num_measurements));

        for (int j = 0; j < num_measurements; j++) {
            text_file.getline(buffer, 100);
            escribirStringFijo(binary_file, buffer, 11);

            text_file.getline(buffer, 100);
            escribirStringFijo(binary_file, buffer, 24);

            text_file.getline(buffer, 100);
            int num_readings = atoi(buffer);
            binary_file.write(reinterpret_cast<char*>(&num_readings), sizeof(num_readings));

            for (int k = 0; k < num_readings; k++) {
                text_file.getline(buffer, 100);
                
                char tipo_sensor = buffer[0];
                binary_file.write(&tipo_sensor, sizeof(tipo_sensor));
                
                char* valor_str = buffer + 2; 

                if (tipo_sensor == 'T' || tipo_sensor == 'O' || tipo_sensor == 'E') {
                    double valor = atof(valor_str);
                    binary_file.write(reinterpret_cast<char*>(&valor), sizeof(valor));
                } else if (tipo_sensor == 'P') {
                    char* sist_str = strtok(valor_str, "-");
                    char* diast_str = strtok(NULL, "-");
                    unsigned int sistolica = (unsigned int)atoi(sist_str);
                    unsigned int diastolica = (unsigned int)atoi(diast_str);
                    binary_file.write(reinterpret_cast<char*>(&sistolica), sizeof(sistolica));
                    binary_file.write(reinterpret_cast<char*>(&diastolica), sizeof(diastolica));
                }
            }
        }
    }

    text_file.close();
    binary_file.close();
    cout << "Archivo '" << binary_file_name << "' generado correctamente." << endl;
    return 0;
}
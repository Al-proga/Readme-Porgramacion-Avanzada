// ======================================================================
//             INICIO DEL ARCHIVO validate_export_file.cpp (CORREGIDO)
// ======================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

bool ValidateEcgExportFile(const char* binary_filename, const char* text_filename) {
    std::ifstream binary_file(binary_filename, std::ios::in | std::ios::binary);
    if (!binary_file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo binario " << binary_filename << std::endl;
        return false;
    }

    std::ofstream text_file(text_filename);
    if (!text_file.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de texto " << text_filename << std::endl;
        binary_file.close();
        return false;
    }

    text_file << "=== VALIDACION DEL ARCHIVO DE ANOMALIAS ECG ===" << std::endl;
    text_file << "Archivo fuente: " << binary_filename << std::endl;
    text_file << "================================================" << std::endl << std::endl;

    int patient_count = 0;
    int total_measurements = 0; // Cambiado de 'anomalies' a 'measurements' para mayor claridad

    while (binary_file.peek() != EOF) {
        char patient_id_bytes[11];
        binary_file.read(patient_id_bytes, sizeof(patient_id_bytes));
        
        if (binary_file.gcount() == 0) {
            break; // Fin limpio del archivo
        }
        if (binary_file.gcount() != sizeof(patient_id_bytes)) {
            std::cerr << "Error: Lectura incompleta del ID del paciente" << std::endl;
            return false;
        }

        char patient_id_str[12] = {0};
        strncpy(patient_id_str, patient_id_bytes, sizeof(patient_id_bytes));
        
        // =================================================================
        // --- INICIO DE LA CORRECCIÓN ---
        // El validador original se olvidaba de leer el ID de la Máquina.
        // Lo añadimos aquí para que la lectura se sincronice correctamente.
        // =================================================================
        unsigned char machine_id;
        binary_file.read(reinterpret_cast<char*>(&machine_id), sizeof(machine_id));

        if (binary_file.gcount() != sizeof(machine_id)) {
            std::cerr << "Error: Lectura incompleta del ID de la maquina" << std::endl;
            return false;
        }
        // --- FIN DE LA CORRECCIÓN ---


        int num_measurements; // Cambiado de 'anomalies' a 'measurements'
        binary_file.read(reinterpret_cast<char*>(&num_measurements), sizeof(num_measurements));
        
        if (binary_file.gcount() != sizeof(num_measurements)) {
            std::cerr << "Error: Lectura incompleta del numero de mediciones" << std::endl;
            return false;
        }

        patient_count++;
        total_measurements += num_measurements;

        text_file << "PACIENTE #" << patient_count << std::endl;
        text_file << "  ID del Paciente: " << patient_id_str << std::endl;
        text_file << "  ID de la Maquina: " << (int)machine_id << std::endl; // Ahora imprimimos el ID de la máquina
        text_file << "  Numero de Mediciones ECG: " << num_measurements << std::endl;
        text_file << "  Mediciones ECG:" << std::endl;

        for (int i = 0; i < num_measurements; i++) {
            char date_time[24];
            double ecg_value;

            binary_file.read(date_time, sizeof(date_time));
            if (binary_file.gcount() != sizeof(date_time)) { /* ... manejo de error ... */ return false; }
            
            binary_file.read(reinterpret_cast<char*>(&ecg_value), sizeof(ecg_value));
            if (binary_file.gcount() != sizeof(ecg_value)) { /* ... manejo de error ... */ return false; }

            char date_time_str[25] = {0};
            strncpy(date_time_str, date_time, sizeof(date_time));

            text_file << "    Medicion " << i + 1 << ":" << std::endl;
            text_file << "      Fecha y Hora: " << date_time_str << std::endl;
            text_file << "      Valor de Medida: " << std::fixed << std::setprecision(6) << ecg_value << std::endl;
        }
        
        text_file << std::endl;
    }

    text_file << "=== RESUMEN DE VALIDACION ===" << std::endl;
    text_file << "Total de pacientes con anomalias ECG: " << patient_count << std::endl;
    text_file << "Total de mediciones ECG: " << total_measurements << std::endl;
    text_file << "Validacion completada exitosamente." << std::endl;

    binary_file.close();
    text_file.close();

    std::cout << "Validacion completada exitosamente." << std::endl;
    std::cout << "Archivo de texto generado: " << text_filename << std::endl;

    return true;
}

int main() {
    const char* binary_filename = "pacientes_ecg_anomalos.dat";
    const char* text_filename = "validation_ecg_anomalies.txt";

    std::cout << "Iniciando validacion del archivo de exportacion ECG..." << std::endl;
    
    if (ValidateEcgExportFile(binary_filename, text_filename)) {
        std::cout << "Proceso de validacion completado con exito." << std::endl;
        return 0;
    } else {
        std::cerr << "Error durante el proceso de validacion." << std::endl;
        return 1;
    }
}
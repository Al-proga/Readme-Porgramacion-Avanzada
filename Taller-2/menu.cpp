#include <iostream>
#include "funciones.cpp"

using namespace std;

void mostrarMenu() {
    cout << "\n--- MENU PRINCIPAL DE UCI ---" << endl;
    cout << "1. Cargar TODOS los archivos de datos (.csv y .bsf)" << endl;
    cout << "2. Probar comparador de fechas de medicion" << endl;
    cout << "3. Generar reporte global de anomalias (anomalias.txt)" << endl;
    cout << "4. Generar reporte de un paciente" << endl;
    cout << "5. Exportar pacientes con ECG anomalo" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    ArchivoPacientes datosPacientes;
    datosPacientes.pacientes = NULL;
    datosPacientes.numPacientes = 0;

    ArchivoConfiguracion datosConfig;
    datosConfig.sensores = NULL;
    datosConfig.numSensores = 0;
    
    Sala* datosUCI = NULL;
    int numSalas = 0;
    
    int opcion;
    do{
        mostrarMenu();
        cin >> opcion;
        cin.ignore(10000, '\n');

        switch(opcion){
            case 1: {
                if(datosPacientes.pacientes != NULL) delete[] datosPacientes.pacientes;
                if(datosConfig.sensores != NULL) delete[] datosConfig.sensores;
                if(datosUCI != NULL) liberarMemoriaUCI(datosUCI, numSalas);

                cout << "Cargando archivo 'pacientes.csv'..." << endl;
                datosPacientes = cargarArchivoPacientes("pacientes.csv");
                cout << "Cargando archivo 'configuracion.csv'..." << endl;
                datosConfig = cargarArchivoConfig("configuracion.csv");
                cout << "Cargando archivo binario 'datos.bsf'..." << endl;
                datosUCI = cargarArchivoBSF("datos.bsf", numSalas);
                break;
            }
            
            case 2: {
                cout << "\n--- Prueba del Comparador de Fechas de Medicion ---" << endl;
                const char fecha1[] = "21/10/2023 15:30:15.123";
                const char fecha2[] = "21/10/2023 15:30:10.987";
                cout << "Fecha 1: " << fecha1 << "\nFecha 2: " << fecha2 << endl;
                if (FechaMayor(fecha1, fecha2)) cout << "Resultado: Fecha 1 es MAYOR." << endl;
                else cout << "Resultado: Fecha 1 NO es mayor." << endl;
                break;
            }

            case 3: {
                 if(datosUCI == NULL) {
                    cout << "Error: Debe cargar TODOS los archivos (opcion 1) antes de generar el reporte." << endl;
                    break;
                }
                generarReporteAnomaliasGlobal(datosUCI, numSalas, datosConfig, datosPacientes);
                break;
            }
            
            case 4: {
                if(datosUCI == NULL){
                    cout << "Error: Debe cargar TODOS los archivos (opcion 1) antes de generar un reporte." << endl;
                    break;
                }

                cout << "Ingrese el ID del paciente para generar el reporte: ";
                int id;
                cin >> id;
                cin.ignore(10000, '\n');
                
                generarReportePaciente(id, datosPacientes, datosUCI, numSalas, datosConfig);
                break;
            }

            case 5: {
                if(datosUCI == NULL){
                    cout << "Error: Debe cargar TODOS los archivos (opcion 1) antes de exportar." << endl;
                    break;
                }
                exportarPacientesECGAnomalo(datosPacientes, datosUCI, numSalas, datosConfig);
                break;
            }
            
            case 0: {
                cout << "Saliendo del programa." << endl;
                break;
            }

            default: {
                cout << "Opcion no valida. Por favor, intente de nuevo." << endl;
                break;
            }
        }
    } while(opcion != 0);

    cout << "Liberando memoria antes de cerrar..." << endl;
    if(datosPacientes.pacientes != NULL) delete[] datosPacientes.pacientes;
    if(datosConfig.sensores != NULL) delete[] datosConfig.sensores;
    if(datosUCI != NULL) liberarMemoriaUCI(datosUCI, numSalas);

    cout << "Programa terminado." << endl;
    return 0;
}
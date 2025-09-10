<h1 align="center"><strong>Markdown – Proyecto Práctico: Sistemas de Monitoreo Biomédico</strong></h1>

<h2><em>Autores</em></h2>
<p><strong>Juan Cícua y Alison Diaz</strong><br>
Sistemas de Monitoreo Biomédico - Programación Avanzada<br>
Pontificia Universidad Javeriana</p>

<hr>

<h2>1. Estructuras Utilizadas</h2>
<ul>
  <li><b>LecturaSensor</b>: Guarda tipo de sensor, valor y estado.</li>
  <li><b>MediciónPaciente</b>: Contiene ID del paciente, fecha/hora, número de lecturas y lecturas asociadas.</li>
  <li><b>MáquinaUCI</b>: Representa una máquina con su ID, número de mediciones y mediciones.</li>
  <li><b>SalaUCI</b>: Agrupa máquinas por sala, con ID, número de máquinas y máquinas.</li>
  <li><b>Configuración</b>: Define umbrales min/max por sensor y un archivo de configuraciones con número de sensores.</li>
  <li><b>Paciente</b>: Información básica cargada de <code>pacientes.csv</code>.</li>
</ul>

<hr>

<h2>2. Funciones Implementadas</h2>
<ul>
  <li><b>Carga de archivos</b>: Lee <code>configuracion.txt</code>, <code>pacientes.csv</code>, <code>.bsf</code>.</li>
  <li><b>Separación de cadenas</b>: Procesa datos en formato de texto.</li>
  <li><b>Comparación de fechas</b>: Ordenamiento y validaciones.</li>
  <li><b>Detección de anomalías</b>: Para T, P, E, O.</li>
  <li><b>Reportes</b>: Por paciente y globales.</li>
  <li><b>Exportación</b>: Genera <code>anomalias.txt</code> y <code>pacientes_ecg_anomalos.dat</code>.</li>
</ul>

<hr>

<h2>3. Flujo del Programa</h2>
<ol>
  <li><b>Cargar archivos de datos</b> – Permite cargar registros.</li>
  <li><b>Mostrar datos</b> – Visualiza en pantalla la información almacenada.</li>
  <li><b>Buscar</b> – Localiza un registro específico.</li>
  <li><b>Modificar</b> – Actualiza información existente.</li>
  <li><b>Eliminar</b> – Borra un registro.</li>
  <li><b>Guardar y salir</b> – Escribe los datos en archivos y termina.</li>
</ol>

<hr>

<h2>4. Explicación de cada una de las funciones</h2>
<ol>
  <li>
    <b>char* trim(char* str)</b> – Elimina los espacios en blanco al inicio y al final de una cadena de caracteres.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Avanza el puntero <code>str</code> hasta que el primer carácter no sea un espacio.</li>
      <li>Busca desde el final hacia atrás hasta encontrar el último carácter no espacio.</li>
      <li>Coloca un <code>\0</code> justo después del último carácter válido para cortar la cadena.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Cuando leemos archivos de texto, muchas veces quedan espacios de más que entorpecen comparaciones o conversiones.</p>
  </li>

  <li>
    <b>char** separarLinea(char* linea, int& numTokens, char delimitador)</b> – Separa una línea de texto en múltiples tokens según un delimitador.
    <h3><strong>Usamos chatGPT</strong></h3>
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe una cadena de caracteres y un carácter delimitador.</li>
      <li>Recorre la línea y va construyendo cada token en un buffer temporal.</li>
      <li>Cuando encuentra el delimitador o el final de la línea, guarda ese token en un arreglo dinámico.</li>
      <li>Devuelve un arreglo de cadenas <code>char*</code>, además del número de tokens <code>numTokens</code>.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Archivos de pacientes y configuraciones vienen en formato separado por delimitadores. Esta función permite descomponer líneas en datos individuales.</p>
  </li>

  <li>
    <b>bool FechaMayor(const char fecha1[], const char fecha2[])</b> – Compara dos fechas con formato específico.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe dos fechas.</li>
      <li>Extrae día, mes, año, hora, minuto, segundo y milisegundo con <code>sscanf</code>.</li>
      <li>Compara jerárquicamente: año > mes > día > hora > minuto > segundo > milisegundo.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Para ordenar el reporte de anomalías por fecha.</p>
  </li>

  <li>
    <b>Paciente crearPacienteDesdeTokens(char** tokens)</b> – Crea un <code>Paciente</code> a partir de los tokens obtenidos en <code>separarLinea</code>.
    <h3><strong>Usamos chatGPT</strong></h3>
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Convierte el primer token en entero (<code>ID</code>).</li>
      <li>Asigna cada token al campo correspondiente de la estructura.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Cada línea del archivo representa un paciente con 11 datos. Esta función permite poblar la base de datos en memoria.</p>
  </li>

  <li>
    <b>ArchivoPacientes cargarArchivoPacientes(const char* nombreArchivo)</b> – Carga todos los pacientes desde un archivo <code>.csv</code>.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Abre el archivo y cuenta cuántas líneas tiene.</li>
      <li>Reserva memoria para ese número de pacientes.</li>
      <li>Llama a <code>separarLinea</code> y <code>crearPacienteDesdeTokens</code> para cada línea.</li>
      <li>Guarda los datos en una estructura <code>ArchivoPacientes</code>.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Inicializa la base de pacientes al inicio del programa porque necesitamos tener la base de datos de pacientes en memoria.</p>
  </li>

  <li>
    <b>ConfiguracionSensor crearConfigDesdeTokens(char** tokens)</b> – Carga la configuración de sensores desde un archivo.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Abre el archivo y cuenta cuántas líneas tiene.</li>
      <li>Llama a <code>separarLinea</code> y <code>crearConfigDesdeTokens</code> para cada línea.</li>
      <li>Guarda los datos en una estructura <code>ConfiguracionSensor</code>.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Define los valores normales y anómalos para cada sensor, base para la detección de anomalías.</p>
  </li>

  <li>
    <b>ArchivoConfiguracion cargarArchivoConfig(const char* nombreArchivo)</b> – Carga todos los sensores desde un archivo <code>.txt</code>.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Abre el archivo y cuenta cuántas líneas tiene.</li>
      <li>Reserva memoria para ese número de sensores.</li>
      <li>Llama a <code>separarLinea</code> y <code>crearConfigDesdeTokens</code> para cada línea.</li>
      <li>Guarda los datos en una estructura <code>ArchivoConfiguracion</code>.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Inicializa la base para deterctar anomalías al inicio del programa porque el sistema necesita saber qué valores son normales y cuáles son anómalos.</p>
  </li>

  <li>
    <b>esLecturaAnomala(const Lectura& lectura, const ArchivoConfiguracion& config)
</b> – Determina si una lectura está fuera de los rangos configurados.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Si es <code>E</code> (ECG), siempre retorna false (ECG se analiza en conjunto).</li>
      <li>Si es <code>P</code> (presión), revisa sistólica y diastólica por separado.</li>
      <li>Para otros sensores, compara con el rango de configuración.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Necesitamos detectar valores anormales en tiempo real y filtrar lecturas normales de anomalías.</p>
  </li>

  <li>
    <b>ecgAnomalo(const Lectura& lectura, const ArchivoConfiguracion& config)</b> – Detecta si una lectura de tipo ECG está fuera del rango definido en la configuración.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe la <code>lectura</code> y <code>configuracion</code>.</li>
      <li>Verifica si la lectura es de ECG.</li>
      <li>Recorre todos los sensores configurados.</li>
      <li>Compara el valor de la lectura con los límites del sensor.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Sirve dentro del programa para clasificar una lectura ECG como normal o anómala, lo que después alimenta reportes médicos o alertas.</p>
  </li>

  <li>
    <b>generarReportePaciente(int idPaciente, const ArchivoPacientes& dbPacientes, const ArchivoConfiguracion& config)</b> – Genera un archivo <code>anomalias.txt</code> con todas las anomalías de todos los pacientes.
    h3><strong>Usamos chatGPT</strong></h3>
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recorre todas las lecturas.</li>
      <li>Si son anómalas, las guarda en un arreglo auxiliar.</li>
      <li>Ordena por fecha usando <code>FechaMayor</code>.</li>
      <li>Escribe al archivo con nombre del paciente y detalles.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Necesitamos un reporte general de alertas sobre datos anomalos.</p>
  </li>

  <li>
    <b>Sala* cargarArchivoBSF(const char* nombreArchivo, int& numSalas)</b> – Lee el archivo binario de mediciones <code>.bsf</code>.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe <code>nombreArchivo</code> y <code>numSalas</code></li>
      <li>Lee el archivo binario con la estructura.</li>
      <li>Reconstruye en memoria esas estructuras dinámicamente (<code>new</code>) para poder procesarlas después.</li>
      <li>Retorna un puntero a un arreglo de <code>Salas</code> cargadas.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Para que el archivo <code>UCI</code> se reestructure según salas, máquinas, mediciones y las lecturas de los sensores.</p>
  </li>

  <li>
    <b>void liberarMemoriaUCI(Sala* salas, int numSalas)</b> – Libera de forma segura toda la memoria dinámica que fue asignada por <code>cargarArchivoBSF</code>.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe <code>cargarArchivosBSF</code> y <code>numSalas</code></li>
      <li>Recorre cada nivel y libera memoria con <code>delete[]</code>.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Sirve para cerrar el programa limpiamente después de procesar los datos y previene fugas de memoria o memoria de relleno.</p>
  </li>

  <li>
    <b>generarReportePaciente(int idPaciente, const ArchivoPacientes& dbPacientes, const Sala* salas, int numSalas, const ArchivoConfiguracion& config))</b> – Crea un reporte detallado de solo un paciente.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe el ID del paciente que se quiere hacer un reporte ingresado por el usuario.</li>
      <li>Busca todas las mediciones del paciente en <code>dbPacientes</code>.</li>
      <li>Genera un archivo individual <code>.txt</code>.</li>
      <li>Para ECG, analiza si la amplitud total (máx – mín) supera los valores permitidos.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Genera un reporte individual para cada paciente con mediciones fuera de la configuración.</p>
  </li>

  <li>
    <b>generarReporteAnomaliasGlobal(const Sala* salas, int numSalas, const ArchivoConfiguracion& config, const ArchivoPacientes& dbPacientes)</b> – Crea el reporte de texto <code>anomalias.txt</code>. 
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe la información de los pacientes anómalos.</li>
      <li>Busca todas las mediciones del paciente.</li>
      <li>Recopila la informacón y las ordena por fecha.</li>
      <li>Genera un archivo <code>anomalias.txt</code> con las lecturas anómalas excepto ECG.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Genera un reporte global de anomalias para cada paciente con mediciones fuera de la configuración en la UCI.</p>
  </li>

  <li>
    <b>exportarPacientesECGAnomalo(const ArchivoPacientes& dbPacientes, const Sala* salas, int numSalas, const ArchivoConfiguracion& config)</b> – Crea el archivo binario <code>pacientes_ecg_anomalos.dat</code>.
    <h4>¿Cómo funciona?</h4>
    <ol>
      <li>Recibe la lista de pacientes <code>dbPacientes</code>, <code>salas</code>, <code>numSalas</code> y limites normales del ECG <code>config</code>.</li>
      <li>Busca pacientes con ECG anómalo (comparando amplitud).</li>
      <li>Exporta sus datos a un archivo binario <code>pacientes_ecg_anomalos.dat</code>.</li>
    </ol>
    <h4>¿Para qué?</h4>
    <p>Funciona como filtro de toda la UCI, porque saca solo a los pacientes con ECG anómalo.</p>
  </li>
</ol>

<hr>

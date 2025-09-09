<head>
<h1 align="center"><strong> Markdown – Proyecto Práctico: Sistemas de Monitoreo Biomédico </strong></h1>
<h2><em>Autores</em></h2>
  <p><strong>Juan Cícua y Alison Diaz</strong><br>
  Sistemas de Monitoreo Biomédico - Programación Avanzada<br>
  Pontificia Universidad Javeriana</p>
</head>
<body>
  <hr>
  <h2> 1. Estructuras Utilizadas</h2>
  <ul>
    <li><b>LecturaSensor</b>: Guarda tipo de sensor, valor y estado.</li>
    <li><b>MediciónPaciente</b>: Contiene ID del paciente, fecha/hora y lecturas asociadas.</li>
    <li><b>MáquinaUCI</b>: Representa una máquina con su ID y mediciones.</li>
    <li><b>SalaUCI</b>: Agrupa máquinas por sala.</li>
    <li><b>Configuración</b>: Define umbrales min/max por sensor.</li>
    <li><b>Paciente</b>: Información básica cargada de <code>pacientes.csv</code>.</li>
  </ul>
  
  <hr>
  
  <h2> 2. Funciones Implementadas</h2>
  <ul>
    <li><b>Carga de archivos</b>: Lee <code>configuracion.txt</code>, <code>pacientes.csv</code>, <code>.bsf</code>.</li>
    <li><b>Separación de cadenas</b>: Procesa datos en formato de texto.</li>
    <li><b>Comparación de fechas</b>: Ordenamiento y validaciones.</li>
    <li><b>Detección de anomalías</b>: Para T, P, E, O.</li>
    <li><b>Reportes</b>: Por paciente y globales.</li>
    <li><b>Exportación</b>: Genera <code>anomalias.txt</code> y <code>pacientes_ecg_anomalos.dat</code>.</li>
  </ul>
  
  <hr>
  
  <h2> 3. Flujo del Programa</h2>
  <ol>
    <li><b>Registrar datos</b> – Permite ingresar o cargar registros.</li>
    <li><b>Mostrar datos</b> – Visualiza en pantalla la información almacenada.</li>
    <li><b>Buscar</b> – Localiza un registro específico.</li>
    <li><b>Modificar</b> – Actualiza información existente.</li>
    <li><b>Eliminar</b> – Borra un registro.</li>
    <li><b>Guardar y salir</b> – Escribe los datos en archivos y termina.</li>
  </ol>
  
  <hr>
  
  <h2> 4. Pruebas y Resultados</h2>
  <p>
  - Archivos de prueba usados. <br>
  - Ejemplo de salida esperada vs salida real. <br>
  - Capturas de pantalla o fragmentos de resultados.
  </p>
  
  <hr>
  
  <h2> 5. Consideraciones Técnicas</h2>
  <ul>
    <li>Uso de arreglos dinámicos (sin <code>vector</code>).</li>
    <li>Manejo manual de memoria.</li>
    <li>Compilación en Linux: <code>g++ programa.cpp -o programa</code>.</li>
    <li>Portabilidad probada en Raspberry Pi / VM Linux.</li>
  </ul>
  
  <hr>
  
  <h2> 6. Uso de IA</h2>
  <p>
  - Prompts utilizados (si aplica). <br>
  - Código sugerido por IA. <br>
  - Ajustes y desarrollo manual.
  </p>
  <hr>

</body>

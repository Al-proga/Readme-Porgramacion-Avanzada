<head>
  <h1 align="center"><strong> Sistemas de Monitoreo Biomédico </strong></h1>
  <h2 align="center"> Guía </h2>
</head>
<body>
  <p> El proyecto consiste en desarrollar un sistema en C++ para procesar datos biomédicos de pacientes en UCI. Se leen archivos binarios (.bsf) con lecturas de sensores como temperatura, presión, ECG y oximetría. El sistema detecta anomalías comparando los valores con umbrales definidos en un archivo de configuración. Se generan reportes por paciente, estadísticas básicas y archivos binarios con casos críticos. </p>

  <h3><strong> Archivos pre-requisitos</strong> </h3>
  <p> Debes de tener algunos archivos previos de compilar el codigo de tal manera que tengas la siguiente estructura de archivos: <br>
  <pre>
  Taller-2/
  ├── libs/
      ├── archivoPacientes.hh
      ├── configuracion.hh
      ├── lecturaSensor.hh
      ├── maquinaUCI.hh
      ├── medicionPaciente.hh
      ├── paciente.hh
      ├── salaUCI.hh
  ├── output/
    ├── data/
      ├── menu.cpp
      ├── anomalias.txt
      ├── configuracion.csv
      ├── datos.bsf
      ├── pacientes.csv
      └── Binario.exe <- Archivo generado al compilar
  </pre>
  </p>
        
  <h3><strong> Compilación y ejecución </strong></h3>
  <p>Para tener exito, lo primero que debes de hacer es ejecutar el codigo, para esto encontraras un icono de play en la parte superior derecha. Despues de ejecutar hay una barra en la parte inferior de computador llamada consola donde encontraras el menu principal, la cual puedes ajustar a tu comodidad. Posteriormente deberas leer el paso a paso de como usar el menu principal.</p>
  
  <h4><em> Menú Principal </em></h4>
  <p> En el menu encontraras:</p>
  <p>
  1. Cargar TODOS los archivos de datos (.csv y .bsf)<br>
  2. Leer archivo .bsf<br>
  3. Generar reporte global de anomalias (anomalias.txt)<br>
  4. Generar reporte de un paciente<br>
  5. Exportar pacientes con ECG anomalo<br>
  0. Salir<br>
  </p>

  <h4><em> ¿Qué debes hacer? </em></h4>
  <p> Solo sigue las siguientes instrucciones y tendrás el sistema biomedico funcionando.</p>
  <p> Lee las opciones y digita solo el número de la opción, por el orden a continuación.</p>
   <ol>
    <li><strong>Opción 1: Cargar archivos</strong><br>
      Carga todos los archivos necesarios para inicializar la base de datos y estructuras internas.
    </li>
     <li><strong>Opción 2: Leer archivo binario</strong><br></li>
       Procesa las lecturas biomédicas.
     <li><strong>Opción 3: Generar reporte global de anomalías</strong><br>
      Crea <code>anomalias.txt</code> con todas las lecturas anómalas (excepto ECG), agrupadas por paciente y por orden cronologico.
    </li>
    <li><strong>Opción 4: Generar reporte de un paciente</strong><br>
      Solicita el ID del paciente y genera <code>mediciones_paciente_&lt;ID&gt;.txt</code> con sus lecturas ordenadas y clasificadas. (Debes de saber el paciente al cual quieras generar un reporte)
    </li>
    <li><strong>Opción 5: Exportar pacientes con ECG anómalo</strong><br>
      Detecta pacientes con lecturas ECG fuera de los rangos normales y los exporta a <code>pacientes_ecg_anomalos.dat</code>.
    </li>
  </ol>
  <p> Si quieres volver a repetir una acción vuelve a digitar el número de la opción.</p>

  <h2><em>Salida</em></h2>
  <p><strong>Opción 0: Salir</strong><br>
  Finaliza la ejecución del programa.</p>

  <h2><em><strong>¡Advertencia!</strong></em></h2>
 <p>Si por alguna razón la consola o terminal le arrojo error, vuelva a darle play al codigo y repita el paso a paso con precausion. <br>
   Si el error persiste asegurese de que las carpetas tengan el mismo nombre. </p>

  <h2><em>Archivos generados</em></h2>
  <p> Dirigete a los siguientes archivos para verificar que la información sea correcta.</p>
  <ul>
    <li><code>mediciones_paciente_&lt;ID&gt;.txt</code></li>
    <li><code>pacientes_ecg_anomalos.dat</code></li>
    <li><code>anomalias.txt</code></li>
  </ul>

  <h2><em>Autores</em></h2>
  <p><strong>Juan Cícua y Alison Diaz</strong><br>
  Sistemas de Monitoreo Biomédico - Programación Avanzada<br>
  Pontificia Universidad Javeriana</p>
</body>

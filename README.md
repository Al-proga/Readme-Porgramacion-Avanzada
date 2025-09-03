<head>
  <h1 align="center"><strong> Sistemas de Monitoreo Biomédico </strong></h1>
  <h2 align="center"> Guía </h2>
</head>
<body>
  <p>Este programa en C++ permite gestionar y analizar datos biomédicos de pacientes en una Unidad de Cuidados Intensivos (UCI). A través de un menú interactivo, el usuario puede cargar archivos, generar reportes individuales y globales, y detectar anomalías en lecturas. </p>
  
  <h3><strong> Compilación y ejecución </strong></h3>
  <p>Para tener exito, lo que primero debes de hacer es ejecutar el codigo. Despues de eso, a continuación encontraras el paso a paso de como usar el menu principal.</p>
  
  <h4><em> Menú Principal </em></h4>
  <p> En el menu encontraras:</p>
  <p>
  1. Cargar TODOS los archivos de datos (.csv y .bsf)<br>
  2. Probar comparador de fechas de medicion<br>
  3. Generar reporte de un paciente<br>
  4. Exportar pacientes con ECG anomalo<br>
  5. Generar reporte global de anomalias (anomalias.txt)<br>
  0. Salir<br>
  </p>

  <h4><em> ¿Qué debes hacer? </em></h4>
  <p> Solo sigue las siguientes instrucciones y lo tendras hecho </p>
   <ol>
    <li><strong>Opción 1: Cargar archivos</strong><br>
      Carga todos los archivos necesarios para inicializar la base de datos y estructuras internas.
    </li>
    <li><strong>Opción 3: Generar reporte de un paciente</strong><br>
      Solicita el ID del paciente y genera <code>mediciones_paciente_&lt;ID&gt;.txt</code> con sus lecturas ordenadas y clasificadas.
    </li>
    <li><strong>Opción 4: Exportar pacientes con ECG anómalo</strong><br>
      Detecta pacientes con lecturas ECG fuera de los rangos normales y los exporta a <code>pacientes_ecg_anomalos.dat</code>.
    </li>
    <li><strong>Opción 5: Generar reporte global de anomalías</strong><br>
      Crea <code>anomalias.txt</code> con todas las lecturas anómalas (excepto ECG), agrupadas por paciente.
    </li>
  </ol>

  <h4><em>Opcional</em></h4>
  <p><strong>Opción 2: Probar comparador de fechas</strong><br>
  Permite verificar si una fecha de medición es posterior a otra.</p>

  <h2><em>Salida</em></h2>
  <p><strong>Opción 0: Salir</strong><br>
  Finaliza la ejecución del programa.</p>

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

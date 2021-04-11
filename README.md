PAV - P2: detección de actividad vocal (VAD)
============================================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 2](https://github.com/albino-pav/P2),
y una parte de su gestión se realizará mediante esta web de trabajo colaborativo.  Al contrario que Git,
GitHub se gestiona completamente desde un entorno gráfico bastante intuitivo. Además, está razonablemente
documentado, tanto internamente, mediante sus [Guías de GitHub](https://guides.github.com/), como
externamente, mediante infinidad de tutoriales, guías y vídeos disponibles gratuitamente en internet.


Inicialización del repositorio de la práctica.
----------------------------------------------

Para cargar los ficheros en su ordenador personal debe seguir los pasos siguientes:

*	Abra una cuenta GitHub para gestionar esta y el resto de prácticas del curso.
*	Cree un repositorio GitHub con el contenido inicial de la práctica (sólo debe hacerlo uno de los
	integrantes del grupo de laboratorio, cuya página GitHub actuará de repositorio central del grupo):
	-	Acceda la página de la [Práctica 2](https://github.com/albino-pav/P2).
	-	En la parte superior derecha encontrará el botón **`Fork`**. Apriételo y, después de unos segundos,
		se creará en su cuenta GitHub un proyecto con el mismo nombre (**P2**). Si ya tuviera uno con ese 
		nombre, se utilizará el nombre **P2-1**, y así sucesivamente.
*	Habilite al resto de miembros del grupo como *colaboradores* del proyecto; de este modo, podrán
	subir sus modificaciones al repositorio central:
	-	En la página principal del repositorio, en la pestaña **:gear:`Settings`**, escoja la opción 
		**Collaborators** y añada a su compañero de prácticas.
	-	Éste recibirá un email solicitándole confirmación. Una vez confirmado, tanto él como el
		propietario podrán gestionar el repositorio, por ejemplo: crear ramas en él o subir las
		modificaciones de su directorio local de trabajo al repositorio GitHub.
*	En la página principal del repositorio, localice el botón **Branch: master** y úselo para crear
	una rama nueva con los primeros apellidos de los integrantes del equipo de prácticas separados por
	guion (**fulano-mengano**).
*	Todos los miembros del grupo deben realizar su copia local en su ordenador personal.
	-	Copie la dirección de su copia del repositorio apretando en el botón **Clone or download**.
		Asegúrese de usar *Clone with HTTPS*.
	-	Abra una sesión de Bash en su ordenador personal y vaya al directorio **PAV**. Desde ahí, ejecute:

		```.sh
		git clone dirección-del-fork-de-la-práctica
		```

	-	Vaya al directorio de la práctica `cd P2`.
	-	Añada la etiqueta `origin` a su copia del repositorio. Esto es útil para facilitar los *push* y
		*pull* al repositorio original:
		```.sh
		git remote add origin dirección-del-fork-de-la-práctica
		```
	-	Cambie a la rama **fulano-mengano** con la orden:

		```.sh
		git checkout fulano-mengano
		```

*	A partir de este momento, todos los miembros del grupo de prácticas pueden trabajar en su directorio
	local del modo habitual.
	-	También puede utilizar el repositorio remoto como repositorio central para el trabajo colaborativo
		de los distintos miembros del grupo de prácticas; o puede serle útil usarlo como copia de
		seguridad.
	-	Cada vez que quiera subir sus cambios locales al repositorio GitHub deberá confirmar los
		cambios en su directorio local:

		```.sh
		git add .
		git commit -m "Mensaje del commit"
		```

		y, a continuación, subirlos con la orden:

		```.sh
		git push -u origin fulano-mengano
		```

*	Al final de la práctica, la rama **fulano-mengano** del repositorio GitHub servirá para remitir la
	práctica para su evaluación utilizando el mecanismo *pull request*.
	-	Vaya a la página principal de la copia del repositorio y asegúrese de estar en la rama
		**fulano-mengano**.
	-	Pulse en el botón **New pull request**, y siga las instrucciones de GitHub.


Entrega de la práctica.
-----------------------

Responda, en este mismo documento (README.md), los ejercicios indicados a continuación. Este documento es
un fichero de texto escrito con un formato denominado _**markdown**_. La principal característica de este
formato es que, manteniendo la legibilidad cuando se visualiza con herramientas en modo texto (`more`,
`less`, editores varios, ...), permite amplias posibilidades de visualización con formato en una amplia
gama de aplicaciones; muy notablemente, **GitHub**, **Doxygen** y **Facebook** (ciertamente, :eyes:).

En GitHub. cuando existe un fichero denominado README.md en el directorio raíz de un repositorio, se
interpreta y muestra al entrar en el repositorio.

Debe redactar las respuestas a los ejercicios usando Markdown. Puede encontrar información acerca de su
sintáxis en la página web [Sintaxis de Markdown](https://daringfireball.net/projects/markdown/syntax).
También puede consultar el documento adjunto [MARKDOWN.md](MARKDOWN.md), en el que se enumeran los
elementos más relevantes para completar la redacción de esta práctica.

Recuerde realizar el *pull request* una vez completada la práctica.

Ejercicios
----------

### Etiquetado manual de los segmentos de voz y silencio

- Etiquete manualmente los segmentos de voz y silencio del fichero grabado al efecto. Inserte, a 
  continuación, una captura de `wavesurfer` en la que se vea con claridad la señal temporal, el contorno de
  potencia y la tasa de cruces por cero, junto con el etiquetado manual de los segmentos.

Etiquetado manual de los segmentos, capturando también el contorno de potencia y la tasa de cruces por cero:

Vemos, aproximadamente, que el nivel de potencia en el primer segmento de silencio, es de unos -6 dB. Y la tasa de cruces por cero, es equivalente a 8000;

- A la vista de la gráfica, indique qué valores considera adecuados para las magnitudes siguientes:

	* Incremento del nivel potencia en dB, respecto al nivel correspondiente al silencio inicial, para
	  estar seguros de que un segmento de señal se corresponde con voz.
	  
	Haciendo un estudio inicial, deducimos que una diferencia de 30dB tendría que ser suficiente para discernir un segmento de voz, de uno con silencio.
	Obviamente, más tarde nos damos cuenta que esta diferencia es demasiado alta, y para programar nuestro autómata de estados, acabamos utilizando una 		diferencia mucho menor.

	* Duración mínima razonable de los segmentos de voz y silencio.

	Determinamos unos 150ms para la duración mínima de un silencio, y unos 550 ms para voz.
	
	* ¿Es capaz de sacar alguna conclusión a partir de la evolución de la tasa de cruces por cero?

	La tasa de cruces por cero nos es muy útil para diferenciar sonidos sordos de sonoros. Como bien sabemos, un sonido sonoro tiene un espectro centrado en 	 bajas frecuencias y uno sordo tiene un componente en frecuencias muy superiores. Cuando la tasa de cruces es elevada, estaremos en un segmento de la señal 	    con un contenido frecuencial muy grande. Esto nos podría ser útil si decidimos extender el programa para clasificar, dentro de un segmento de voz, el tipo de 	  sonidos que este contiene.

### Desarrollo del detector de actividad vocal

- Complete el código de los ficheros de la práctica para implementar un detector de actividad vocal tan
  exacto como sea posible. Tome como objetivo la maximización de la puntuación-F `TOTAL`.
  
 **vad.c**
 
 Para empezar, hacemos los cambios necesarios en *vad.c*, primero, definimos las *features* y las inicializamos:
 ![image](https://user-images.githubusercontent.com/80445439/114268495-b0653680-9a01-11eb-9c67-5f213b784729.png)
 
 Editamos la función *vad_close* que usaremos más tarde en el main, haremos que simplemente returne el último estado y que libere la data.
 
![image](https://user-images.githubusercontent.com/80445439/114270415-751c3500-9a0c-11eb-8695-0e3e15d0cbb8.png)

 
 Después, completaremos una de las funciones más importantes del programa, *VAD_STATE vad*, donde le pasaremos la data, el buffer, y el último estado. Esta función se hará cargo de los cambios de estado (inicial, indefinido, voz y silencio), calculando previamente los parametros *k0, k1 y k2* que serán los decisores de los cambios que realizaremos. Finalmente nos returnará el estado en el que estamos.

![image](https://user-images.githubusercontent.com/80445439/114269698-bd395880-9a08-11eb-9e07-0cb80fd36865.png)

![image](https://user-images.githubusercontent.com/80445439/114269713-ca564780-9a08-11eb-99e9-8d63235dbb55.png)

Como podemos ver, en el caso de estar en el estado inicial, calcularemos primero k0, usando la potencia y un contador de 12 tramas. A partir de k0 podremos calcular k1 (sumándole 3dB) y k2 la encontraremos sumándole 7dB a k1. Después del estado inicial, siempre pasaremos a estado de silencio.

Seguidamente, en caso de estar en silencio, simplemente comprobaremos que la potencia supera el nivel de k1, y, en caso de que no lo supere, pasaremos a estado indefinido, concretamente, *maybe voice*.

Después, con una estructura muy similar, en el estado de voz, comprobaremos que la potencia no esté por debajo de k1, en caso de que lo esté, pasaremos a estado indefinido, concretamente, *maybe silence*.

Finalmente, el estado indefinido lo dividiremos en los casos de posiblidad de voz y de silencio. En el caso de *maybe voice* comprobamos si se supera la potencia k2, para pasar a estado de voz, si no lo hace en cierto tiempo, volveremos a silencio. En el caso de *maybe silence*, también comprobaremos si superamos k2 para pasar al estado de voz, y luego que se no supere *k1+4* durante un cierto tiempo, para pasar al estado de silencio.

Una vez decidido el estado, lo returnamos.

**main_vad.c**

Con estos cambios, dejamos finalizado el *vad.c*. Ahora necesitamos editar el *main_vad.c* para que deje escritas las tramas de voz o silencio.
![image](https://user-images.githubusercontent.com/80445439/114270108-e6f37f00-9a0a-11eb-8a8f-dd3c24df0190.png)
![image](https://user-images.githubusercontent.com/80445439/114270113-ee1a8d00-9a0a-11eb-91ca-79076969c5f4.png)

Como podemos observar, iteramos trama a trama por todo el fichero de audio. Después de hacer las comprobaciones básicas, tenemos que escribir en el fichero el estado definido, pero solo si es de voz o de silencio, para ello comprobamos el último estado y la última trama en la cual hemos "escrito", antes de escribir nos aseguramos que no estamos en el estado indefinido ni inicial, de esta forma confirmaremos que solo se escriben los estados que hemos indicado.

Para la última trama, tendremos que comprobar no haberla escrito ya, y después simplemente copiar el último estado elegido.

- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 
JAVI

- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.

	Como era de esperar, el programa no es 100% preciso, aunque los valores de *k0, k1 y k2* estén bien elegidos y sean prácticamente óptimos, no podemos asegurar que los resultados sean exactamente correctos. Principalmente porque para hacerlo a la perfección necesitaríamos más parámetros y una programación más compleja, aunque, aun así, seguramente seguriría sin ser 100% preciso por factores externos, como, por ejemplo, algún error manual al etiquetar el audio con voz y sonido, entre otros.

- Evalúe los resultados sobre la base de datos `db.v4` con el script `vad_evaluation.pl` e inserte a 
  continuación las tasas de sensibilidad (*recall*) y precisión para el conjunto de la base de datos (sólo
  el resumen).
JAVI
### Trabajos de ampliación

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).

#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.


### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).
  
  Para conseguir unos mejores resultados, hemos usado los parámetros k0, k1 y k2. Siendo k0 la potencia media de las tramas iniciales, y k1 y k2 los parámetros decisores del cambio de estados. Hemos realizado tests hasta encontrar los valores óptimos para sumarle a k0 y conseguir k1 y k2 que nos permitan tener una buena precisión en nuestros resultados.
  
- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que
  considere de interés de cara a su evaluación.
  
  Para poder acabar de implementar el código escrito, y conseguir solucionar problemas mínimos que impedían la compilación del programa, hemos añadido código para que escriba por pantalla ciertos puntos clave para entender donde estaban los errores y corregirlos fácilmente.


### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.

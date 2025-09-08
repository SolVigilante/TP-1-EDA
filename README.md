# TP-1-EDA

#Trabajo de cada integrante del grupo
Sofia Tarantino: Se encargo de las funciones de view, es decir, de la renderizacion del modelo y todo lo relativo a la visualizacion del mismo.
Agustin Montoto:
Maria Sol Vigilante:

#Análisis de estabilidad
El timeStep parrece adecuado para la simulacion debido a que presenta comportamiento físico coherente. A mayor timeStep se presentan órbitas más erráticas, sobretodo con el planeta Mercurio y la direccion de los asteroides. Esto puede ser porque las fuerzas aplicadas son mas intensas. 

#Análisis de Precisión
Como en nuestro programa no multiplicamos y luego dividimos por la masa del planeta en el análisis de fuerzas entonces la precision de float nos resulta suficiente. En el caso de que hicieramos eso, deberíamos utilizar una presicion de double o hasta incluso de long double. Sino, se produce un overflow y el comportamiento de el sistema solar carecia de sentido fisico debido al numero resultante de multiplicar las masas.

#Análisis de Complejidad
Cuando se agregan 500 asteroides a la simulación ANTES de la optimización la complejidad algorítmica de la simulación es de O(N^(N-1))(N elevado a la N-1) siendo N la cantidad de cuerpos. Esto es porque los cuerpos se comparan todos con todos excepto ellos mismos. Esta es una altisima complejidad por lo tanto surgió la necesidad de una optimización.
A nivel de lógica, la masa de los asteroides resulta despreciable con respecto a la masa de los planetas o del sol entonces las fuerzas que generan también son despreciables. Como consecuencia, para esta simulación solo se toman en cuena las fuerzas generadas sobre los cuerpos por los planetas o el sol. Con esta modificación, la complejidad algoritmica es de O(N).   
Asimsimo, para mejorar la complejidad algoritmica y realizar menos calculos realizamos dos cosas. En primer lugar, agregamos un factor que relacionaba las masas de dos planetas. Entonces, los planetas a nivel coputacional en la simulacion no se veian afectados por planetas con masas mucho mas pequeñas. En segundo lugar, los asteoroides solo se comparan con el salo, siendo este el cuerpo mas masivo del sistema solar dado que al ser una gran cantidad de asteroides consideramos clave optimizar la cantidad de caclulos.
A nivel de gráficos, como los asteroides resultan ser mas pequeños que los planetas se ha decidido que se grafiquen con la funcion DrawSphereWire pues consume menos recursos que el dibujo de una esfera maciza. Además, los planetas lejanos al observador se dibujaran como puntos con el mismo fin. 

#BONUS
Encontramos el Easter egg de phi = 0
Si júpiter es 1000 veces mas masivo enonces empezará a atraer al Sol y funciona como un agujero negro. Destruye todo el Sistema Solar. 
Asimismo, en la simulacion agregamos el nombre de los planetas para poder identificarlos mas facilmente.

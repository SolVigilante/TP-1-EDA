# TP-1-EDA
#Análisis de estabilidad
El timeStep parrece adecuado para la simulacion debido a que presenta comportamiento físico coherente. A mayor timeStep se presentan órbitas más erráticas, sobretodo con el planeta Mercurio. Esto puede ser porque las fuerzas aplicadas son mas intensas. 

#Análisis de Precisión
Como en nuestro programa no multiplicamos y luego dividimos por la masa del planeta en el análisis de fuerzas entonces la precision de float nos resulta suficiente. En el caso de que hicieramos eso, deberíamos utilizar una presicion de double o hasta incluso de long double. Sino, se produce un overflow y el comportamiento de el sistema solar carecia de sentido fisico debido al numero resultante de multiplicar las masas.
#Análisis de Complejidad
Cuando se agregan 500 asteroides a la simulación ANTES de la optimización la complejidad algorítmica de la simulación es de O(N^N)(N elevado a la N) siendo N la cantidad de cuerpos. Esto es porque los cuerpos se comparan todos con todos. Esta es una altisima complejidad por lo tanto surgió la necesidad de una optimización.
A nivel de lógica, la masa de los asteroides resulta despreciable con respecto a la masa de los planetas o del sol entonces las fuerzas que generan también son despreciables. Como consecuencia, para esta simulación solo se toman en cuena las fuerzas generadas sobre los cuerpos por los planetas o el sol. Con esta modificación, la complejidad logarítima es de O(N).   
A nivel de gráficos, como los asteroides resultan ser mas pequeños que los planetas se ha decidido que se grafiquen con la funcion DrawSphereWire pues consume menos recursos que el dibujo de una esfera maciza. Además, los planetas lejanos al observador se dibujaran como puntos con el mismo fin. 

#BONUS
Encontramos el Easter egg de phi = 0
Si júpiter es 1000 veces mas masivo enonces empezará a atraer al Sol y funciona como un agujero negro. Destruye todo el Sistema Solar. 

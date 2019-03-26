## Diagrama de bloques de las aplicaciones

Para comenzar, en la entrada del parking habrá una barrera automática enlazada a un servomotor, que se activará gracias a un sensor de movimiento situado delante de la barrera, y volverá a bajarse cuando se active un segundo sensor al otro lado. 

/* Cada vez que suba y baje el contador aumentara en una unidad para controlar el número de coches que hay dentro. (Se necesitará de una variable que vaya incrementando de uno en uno, de dos comandos if/else para subir y bajar las barreras). */

Mediante un sistema de sensores de proximidad situados en cada plaza detectaremos si está ocupada o no. En cada una habrá dos LEDs, uno rojo y otro verde, que recibirán información de los sensores para cambiar de color e indicar el estado de esta.

/* (Nos hará falta el comando if para comprobar si la medida tomada por el sensor es la que mide la longitud de la plaza de aparcamiento o por el contrario medir si la distancia a disminuido por la presencia de un coche). */

En la salida habrá otra barrera con el mismo funcionamiento que la de entrada, pero esta no tendrá un semáforo, ya que no es necesario.
Todo nuestro sistema funcionará gracias a un Arduino y se conectará con el ordenador para transmitirle información sobre las plazas libres, y así este pueda mostrar un contador en la pantalla.

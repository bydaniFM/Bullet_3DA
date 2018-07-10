# Bullet Physics Tank Simulator

El programa tiene las siguientes características:

- Tanque con:
  - Ruedas. Permiten ir hacia delante, marcha atrás, girar a la derecha y girar a la izquierda
  - Torreta giratoria.
  - Cañón que se puede levantar y bajar. 
- Disparo del tanque. Se realiza con un pool de objetos.
- Llave con un trigger. En este caso la llave tiene el modelo de un molino.
- Plataforma que se desplaza horizontalmente.
- Puerta que se abre al "coger" la llave.
- Control de la cámara.

La documentación del proyecto está disponible [aquí](https://danifm.github.io/Bullet_3DA/).

## Controles

- Movimiento del tanque: WASD.
- Giro de la torreta: AD.
- Movimiento del cañón: RF.
- Disparo: SPACE.
- Pan de la cámara: Click izquierdo.
- Rotación de la cámara: Click derecho.

## Bugs y cosas a mejorar actualmente

El sistema de input recive de vez en cuando eventos de teclado sin que se haya pulsado la tecla correspondiente. Pulsar de nuevo la tecla en la que se ha ejecutado el evento por error suele arreglar el estado del input del tanque. El error parece que viene de la versión de SFML, por lo que no he podido hacer nada al respecto.

Cambiar la posición de la luz o su ángulo no afecta a cómo se ven las sombras en el suelo. He intentado mover la luz, rotarla, cambiarle la intensidad... de todas las formas posibles y no consigo variar las sombras. Éste es el motivo por el que la escena se ve casi toda del mismo color, y se hace difícil distinguir los objetos. Para poder probar el juego, recomiendo mover la cámara de manera que se vean las siluetas de los objetos con el fondo.

## Sobre el proyecto

El proyecto de Visual Studio que se incluye solo compilará en modo Debug x86.
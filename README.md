

# Introducción

En este proyecto lo que se trata de conseguir es la utilización del algoritmo de Douglas Peucker, usado para simplificación de polilineas en la simplificación de un mapa a nivel, de forma que se reduzcan considerablemente el numero de lineas usadas para la representación del mapa.

# Algoritmo de Douglas peucker

 Se trata de un algoritmo de simplificación, es decir, trata de reducir el número de puntos existentes en una polilínea.
 Se fundamenta en la búsqueda de puntos críticos a partir de una tolerancia lineal. Los puntos críticos, que constituirán la línea simplificada, serán los que progresivamente vayan alcanzando una distancia perpendicular mayor respecto a la línea base considerada, siempre superior a la tolerancia impuesta.
La primera linea es formada por el primer y último punto de la línea original. Los puntos intermedios se calculan de la siguiente manera:
- Si no hay una distancia mayor a la tolerancia, se finaliza la simplificación y solo se queda con el punto final e inicial
- Si se supera la tolerancia, el punto con mayor distancia es guardado será un punto para dividir la linea original en dos secciones una desde el inicio hasta ese punto y del punto al final, y se aplicará el algoritmo a cada una de sus partes como lineas independientes.


![image](https://github.com/jamv0007/Reductor-Lineas-Nivel/assets/84525141/31e980ab-ba8e-400b-abcb-9c827a7e134a)

El algoritmo tiene una eficiencia de O(nLogn) y en el peor de los casos es de O(n^2).




# Librerías utilizadas

Para el desarrollo del proyecto se han usado las siguientes librerías: 
- QT:  Para proporcionar una interfaz que usuario  y la visualización de OpenGL
  - Modulos: Widgets, OpenGL, OpenGLWidgets, Charts
- Assimp, GLFW, CGAL y PCL: Usados en la libreria creada en la asignatura

# Interfaz de usuario

Para el diseño de la interfaz de usuario se ha utilizado la librería QT que permite dotar de interfaz de usuario e interacción a las aplicaciones realizadas en C++ entre otros lenguajes. 
Usando la librería , que ademas de proveer de elementos gráficos, permite sustituir la librería de OpenGL por la suya obteniendo también visualización, que en conjunto con la librería matemática, se ha creado una ventana con un visualizador para mostrar gráficamente los mapas y modelos usados y a la derecha un menú vertical de interacción de usuario que permite cargar archivos, y visualizar el archivo cargado además de un desplegable para modificar la escala del mapa y un slider que permite modificar el error del algoritmo.

![image](https://github.com/jamv0007/Reductor-Lineas-Nivel/assets/84525141/b1495383-be0d-4c28-9baa-e7679057f3ea)

# Funcionamiento

![image](https://github.com/jamv0007/Reductor-Lineas-Nivel/assets/84525141/329e50c6-b977-4832-ab3f-d2b89177870a)

![image](https://github.com/jamv0007/Reductor-Lineas-Nivel/assets/84525141/7c450a1f-890a-494e-900f-3c8b3807da56)

También contiene una leyenda de las alturas de las lineas de nivel.

![image](https://github.com/jamv0007/Reductor-Lineas-Nivel/assets/84525141/a57d8244-bb08-46bb-bec8-8fb9352959a3)

# Manual de usuario

Estos son los distintos controles por teclado y ratón que tiene la aplicación:
- Tecla C: Permite resetear la posición de la cámara aunque no el zoom
- Tecla ESC: Sale de la aplicación
- Mover con ratón y botón izquierdo:  Rotar alrededor del mapa
- Mover con ratón y botón de la rueda: Mover cámara hacia arriba y lateralmente
- Rueda del ratón: Hacer zoom

## Solo permite archivos de extension .vtk





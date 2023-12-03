Instrucciones para compilar el openmp

1. Estar ubicado en el directorio openmp, ya que ahi se encuentra el makefile con el openmp.cpp.

2. Ejecutar el comando make en la terminal.

3. Para ejecutar el programa se utiliza el siguiente comando:

./openmp <input_color_image> <output_gray_image> <num_threads>, donde el input_color_image es la imagen que se quiere convertir, el output_gray_image se coloca el nombre de la imagen nueva que se obtendra y el num_threads se coloca el numero de hebras con el cual se quiere ejecutar.

El codigo establece como obligatorio el numero de hebras como parametro.

Ejemplo con la imagen Mondongo.jpg:

./openmp Mondongo.jpg MondongoGris.jpg 4

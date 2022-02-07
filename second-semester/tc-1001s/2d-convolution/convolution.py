# -------------------------------------------------
# Título: Aplicación de convolución a una imagen 2D
# Autor: Carlos César Rodríguez García
# -------------------------------------------------

import numpy as np
import cv2

# Procesamiento de imagen con OpenCV
# ----------------------------------


def procesa_imagen(imagen):
    """
    Carga la imagen de un archivo y la establece en una paleta de colores en blanco y negro. Regresa 
    la imagen procesada como un array de numpy.
    Argumentos:
        imagen (str): string que indica la ubicación del archivo.
    Returns:
        imagen_procesada (np.array): la imagen transformada en una matriz. 
    """
    imagen_procesada = cv2.imread(imagen)
    imagen_procesada = cv2.cvtColor(
        src=imagen_procesada, code=cv2.COLOR_BGR2GRAY)

    return imagen_procesada

# Implementación de convolucion 2D
# --------------------------------


def promedio_kernel(array_cuadrado, kernel):
    """
    Aplica el producto de Hadamard del kernel y una fracción de la imagen de las mismas dimensiones.
    Obtiene y regresa el promedio de la matriz resultante.
    Argumentos:
        array_cuadrado (np.array): matriz cuadrada que representa una sección de la imagen. Tiene las mismas dimensiones que el kernel.
        kernel (np.array): matriz de convolucion con la que se transforma a la imagen.
    Returns:
        promedio_transformado (float): promedio de los elementos en la matriz producto.
    """
    n_elementos = array_cuadrado.size
    array_multiplicado = array_cuadrado * kernel
    promedio_transformado = np.sum(array_multiplicado)/ n_elementos  

    return promedio_transformado


def convolucion_2D(imagen, kernel, padding=0, stride=1):
    """
    Aplica la convolución entre el kernel y la imagen, respetando un padding establecido por el usuario.
    Regresa la imagen con el filtro aplicado.
    Argumentos:
        imagen (np.array): arreglo de numpy que representa a la imagen.
        kernel (np.array): matriz de convolucion con la que se transforma a la imagen.
        padding (int): cantidad de pixeles añadidos a la imagen para poder ser procesada por el kernel.
        stride (int): indica cuántos pasos se mueve el kernel con cada paso de la convolución.
    Returns:
        imagen_filtrada (np.array): arreglo de numpy que resulta de haber aplicado el filtro a la imagen.
    """
    dimension_kernel = kernel.shape[0]
    x_imagen = imagen.shape[1]  # dimensión horizontal de la matriz
    y_imagen = imagen.shape[0]  # dimensión vertical de la matriz

    # Para calcular las dimensiones de la matriz filtrada, se utiliza la fórmula [(W−K+2P)/S]+1
    x_filtrada = int(((x_imagen - dimension_kernel + 2*padding)/stride) + 1)
    y_filtrada = int(((y_imagen - dimension_kernel + 2*padding)/stride) + 1)
    imagen_filtrada = np.zeros((y_filtrada, x_filtrada))

    # Se crea una matriz auxiliar que incluye el padding
    imagen_con_padding = imagen
    if padding != 0:
        imagen_con_padding = np.zeros(
            (y_filtrada + 2*padding, x_filtrada + 2*padding))
        # la imagen se incluye dentro de la matriz
        imagen_con_padding[padding:-padding, padding:-padding] = imagen

    for i in range(y_filtrada - dimension_kernel):
        for j in range(x_filtrada - dimension_kernel):

                fraccion_cuadrada = imagen_con_padding[i:
                                                       dimension_kernel+i, j:dimension_kernel+j]
                imagen_filtrada[i, j] = promedio_kernel(
                    fraccion_cuadrada, kernel)

    return imagen_filtrada


if __name__ == '__main__':
    imagen = procesa_imagen('Kuchau.png')

    kernel = np.array([[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]])
    imagen = convolucion_2D(imagen, kernel, padding=1)
    cv2.imshow('image', imagen)
    cv2.waitKey(0)

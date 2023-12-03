#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: ./openmp <input_color_image> <output_gray_image> <num_threads>" << endl;
        return -1;
    }

    // Obtener el número de hebras de los argumentos de entrada
    int numThreads = atoi(argv[3]);
    omp_set_num_threads(numThreads);

    // Cargar la imagen a color
    Mat colorImage = imread(argv[1], IMREAD_COLOR);
    if (colorImage.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return -1;
    }

    Mat grayImage(colorImage.rows, colorImage.cols, CV_8UC1);

    // Iniciar medición del tiempo
    auto start_time = high_resolution_clock::now();

    // Convertir la imagen a escala de grises utilizando OpenMP
    #pragma omp parallel for
    for (int i = 0; i < colorImage.rows; ++i) {
        for (int j = 0; j < colorImage.cols; ++j) {
            Vec3b intensity = colorImage.at<Vec3b>(i, j);
            grayImage.at<uchar>(i, j) = 0.299 * intensity[2] + 0.587 * intensity[1] + 0.114 * intensity[0];
        }
    }

    // Finalizar medición del tiempo y calcular la duración
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    // Mostrar el tiempo de ejecución
    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;

    // Guardar la imagen en escala de grises
    imwrite(argv[2], grayImage);

    return 0;
}
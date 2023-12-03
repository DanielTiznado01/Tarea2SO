#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: ./openmp <input_color_image> <output_gray_image>" << endl;
        return -1;
    }

    // Cargar la imagen a color
    Mat colorImage = imread(argv[1], IMREAD_COLOR);
    if (colorImage.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return -1;
    }

    Mat grayImage(colorImage.rows, colorImage.cols, CV_8UC1);

    auto start = high_resolution_clock::now(); // Iniciar el contador de tiempo

    #pragma omp parallel for
    for (int r = 0; r < colorImage.rows; ++r) {
        for (int c = 0; c < colorImage.cols; ++c) {
            Vec3b intensity = colorImage.at<Vec3b>(r, c);
            uchar grayValue = intensity[0] * 0.07 + intensity[1] * 0.72 + intensity[2] * 0.21;
            grayImage.at<uchar>(r, c) = grayValue;
        }
    }

    auto stop = high_resolution_clock::now(); // Detener el contador de tiempo
    auto duration = duration_cast<milliseconds>(stop - start); // Calcular la duración

    // Mostrar el tiempo de ejecución en milisegundos
    cout << "Tiempo de ejecucion: " << duration.count() << " ms" << endl;

    // Guardar la imagen en escala de grises
    imwrite(argv[2], grayImage);

    return 0;
}
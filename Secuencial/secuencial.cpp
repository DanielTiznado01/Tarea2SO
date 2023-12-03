#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

// Función para convertir a escala de grises (método de luminosidad)
Mat Grises(const Mat& colorImage) {
    Mat grayImage(colorImage.rows, colorImage.cols, CV_8UC1);

    for (int r = 0; r < colorImage.rows; ++r) {
        for (int c = 0; c < colorImage.cols; ++c) {
            Vec3b intensity = colorImage.at<Vec3b>(r, c);
            uchar grayValue = intensity[0] * 0.07 + intensity[1] * 0.72 + intensity[2] * 0.21;
            grayImage.at<uchar>(r, c) = grayValue;
        }
    }

    return grayImage;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: ./secuencial <input_color_image> <output_gray_image>" << endl;
        return -1;
    }

    // Cargar la imagen a color
    Mat colorImage = imread(argv[1], IMREAD_COLOR);
    if (colorImage.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return -1;
    }
    auto start = high_resolution_clock::now();

    // Convertir la imagen a escala de grises
    Mat grayImage = Grises(colorImage);

    // Guardar la imagen en escala de grises
    imwrite(argv[2], grayImage);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de ejecucion: " << duration.count() << " ms" << endl;

    return 0;
    //OLI
}


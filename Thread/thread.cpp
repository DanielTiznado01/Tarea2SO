#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <vector>

using namespace cv;
using namespace std;
using namespace std::chrono;

// Función para convertir una sección de la imagen a escala de grises (método de luminosidad)
void convertToGraySection(const Mat& colorImage, Mat& grayImage, int startRow, int endRow) {
    for (int r = startRow; r < endRow; ++r) {
        for (int c = 0; c < colorImage.cols; ++c) {
            Vec3b intensity = colorImage.at<Vec3b>(r, c);
            uchar grayValue = intensity[0] * 0.07 + intensity[1] * 0.72 + intensity[2] * 0.21;
            grayImage.at<uchar>(r, c) = grayValue;
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: ./paralelo <input_color_image> <output_gray_image>" << endl;
        return -1;
    }

    // Cargar la imagen a color
    Mat colorImage = imread(argv[1], IMREAD_COLOR);
    if (colorImage.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return -1;
    }

    int numThreads = thread::hardware_concurrency(); // Obtener el número de hilos soportados

    // Dividir la imagen en secciones para asignar a cada hilo
    vector<thread> threads;
    vector<Mat> grayImages(numThreads);
    int rowsPerThread = colorImage.rows / numThreads;
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? colorImage.rows : (startRow + rowsPerThread);
        grayImages[i] = Mat(colorImage.rows, colorImage.cols, CV_8UC1);

        threads.emplace_back(convertToGraySection, ref(colorImage), ref(grayImages[i]), startRow, endRow);
    }

    // Esperar a que todos los hilos terminen su ejecución
    for (auto& t : threads) {
        t.join();
    }

    // Combinar las secciones convertidas en una sola imagen en escala de grises
    Mat grayImage = Mat(colorImage.rows, colorImage.cols, CV_8UC1);
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? colorImage.rows : (startRow + rowsPerThread);
        grayImages[i](Rect(0, startRow, colorImage.cols, endRow - startRow)).copyTo(grayImage(Rect(0, startRow, colorImage.cols, endRow - startRow)));
    }

    // Guardar la imagen en escala de grises
    imwrite(argv[2], grayImage);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 

    
    cout << "Tiempo de ejecucion: " << duration.count() << " ms" << endl;

    return 0;
}
#include "medianfilter.h"
#include <vector>
#include <algorithm>


// расчет медианны по пикселю
std::uint8_t MedianFilter::calculateMedian (int cell){
    // старт и стоп для удобства итераций
    int start = cell - (f_Ksize -1)/2 * f_width - (f_Ksize - 1 )/2;
    int stop  = cell + (f_Ksize -1)/2 * f_width + (f_Ksize - 1 )/2;
    int index {0};
    // сохраняем в контейнер окресность
    std::vector <std::uint8_t>  neighbour (f_Ksize * f_Ksize);
    // итерируемся линейно, не вводя 2д кондинаты.
    for (int i = start; i < stop; i += f_width ) {
      for (int j = i; j < i + f_Ksize ;  ++j) {
            neighbour.at (index++) = in_img.at(j);
        }
    }
    // мне обещали здесь O(n log n)!
    std::nth_element(neighbour.begin(), neighbour.begin() + neighbour.size()/2, neighbour.end());
    return neighbour[neighbour.size()/2] ;
}

// контроль границы, границы не обрабатываем
bool MedianFilter::isBorder (int cell) {
    // верхняя
    if ( cell >= 0 && cell <= f_width * (f_Ksize - 1) / 2) { return true; }
    // левая граница
    if ( cell % f_width < (f_Ksize - 1) / 2)  { return true; }
    // нижняя
    if (  cell >= f_width * (f_height - (f_Ksize - 1) / 2)) { return true; }
    // правая
    if (cell % f_width >= f_width - (f_Ksize - 1) / 2)  { return true; }
    return false;
}

// главный цикл фильтра
void MedianFilter::run(int kernelSize){
    f_Ksize = kernelSize;
    for (int i = 0; i <  f_width * f_height ; ++i  ) {
       if (isBorder(i)) {
           out_img.at(i) = in_img.at(i);
           continue;
        }
        out_img.at(i) = calculateMedian (i) ;
    }
}

//сохранение результата
bool MedianFilter::savePng (const QString & name) {
    QImage image(out_img.data(), f_width, f_height, QImage::Format_Indexed8);
    return image.save(name+ ".png");
}


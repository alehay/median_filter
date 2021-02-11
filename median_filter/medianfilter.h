#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H


#include <QtCore>
#include <vector>
#include <QImage>

class MedianFilter
{
private:
    int f_width {0};
    int f_height {0};
    int f_Ksize {0};

    // исходные данные мы храним в незменном виде
    std::vector <std::uint8_t> in_img;
    // а результаты применяем в выходном контейнере
    std::vector <std::uint8_t> out_img;

    std::uint8_t calculateMedian (int cell);
    bool isBorder (int cell);
public:
    MedianFilter(QFile & in_file , int width, int height) : f_width(width), f_height(height),
      in_img(width * height), out_img(width * height) {
        char ch;
        size_t i = 0;
        while(!in_file.atEnd()) {
            in_file.read(&ch,sizeof(char));
            if (i >= in_img.size()) {
                qDebug() <<"warning : file size > " << width << "x" << height;
                break;
            }
            in_img[i++] = static_cast<std::uint8_t>(ch);
        }
        in_file.close();
     };
    void run(int kernelSize);
    bool savePng (const QString & path);


};

#endif // MEDIANFILTER_H

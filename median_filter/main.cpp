/* тестовое задание :
 * Реализовать медианный фильтр обработки изображния
 *  в каталоге in grayscale 8bit RAW.
 *  в каталог out сохраняются PNG после обработки
 *  выбор размера ядра произвольный
 *  OpenCV - не допускаяется
 *  floating point - не допускается.
 *
 *  минимальное количество операций.
 */
#include <QtCore>
#include <QImage>
#include "medianfilter.h"

int main(int , char *[])
{
    // дано по условию задачи:
    int w = 640;
    int h = 480;
    int size_kernel = 13; // ядро
    QString inputDir = "in/";
    QString outputDir = "out/";


    QString path = QDir::currentPath() + "/" + inputDir;
    QDir dir(path);
    // итерация по файлам
    QDirIterator iterator(dir.absolutePath(), {"*.raw"}, QDir::Files);

    while (iterator.hasNext()) {
        QFile f(iterator.next());
        f.open(QIODevice::ReadOnly);
        QString fileIndex = f.fileName();
        QString lastBit = fileIndex.section("/", -1, -1); // забираем часть после слеша
        QStringList name = lastBit.split('.'); // отсекаем точку

        qDebug() <<"processing file : "<< name[0]  ;
        MedianFilter MedianFilter (f, w, h); // инициализируем фильтр
        MedianFilter.run(size_kernel);
        QString outFileName = outputDir + name[0];
        MedianFilter.savePng(outFileName);  // сохраняем
    }

    qDebug() <<"file processing has done.";
    return 0;
}

#include "global.h"

#include "imagebuffer.h"

cv::Mat Utils::QImage2Mat(const QImage &image)
{
    using namespace cv;
    switch(image.format())
        {
            // 8-bit, 4 channel
            case QImage::Format_ARGB32:
                break;
            case QImage::Format_ARGB32_Premultiplied:
                {
                    cv::Mat mat(image.height(), image.width(),
                                CV_8UC4,
                                (void*)image.constBits(),
                                image.bytesPerLine());
                    return mat.clone();
                }

            // 8-bit, 3 channel
            case QImage::Format_RGB32:
                {
                    cv::Mat mat(image.height(),image.width(),
                                CV_8UC4,
                                (void*)image.constBits(),
                                image.bytesPerLine());

                     // drop the all-white alpha channel
                    cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
                    return mat.clone();
                }
            case QImage::Format_RGB888:
                {
                    QImage swapped = image.rgbSwapped();
                    cv::Mat mat(swapped.height(), swapped.width(),
                                CV_8UC3,
                                (void*)image.constBits(),
                                image.bytesPerLine());
                    return mat.clone();
                }

            // 8-bit, 1 channel
            case QImage::Format_Indexed8:
                {
                    cv::Mat mat(image.height(),image.width(),
                                CV_8UC1,
                                (void*)image.constBits(),
                                image.bytesPerLine());
                    return mat.clone();
                }

            // wrong
            default:
                qDebug() << "ERROR: QImage could not be converted to Mat.";
                break;
        }
        return cv::Mat();
}

QImage Utils::Mat2QImage(const cv::Mat &mat)
{
    switch (mat.type())
        {
            // 8-bit, 4 channel
            case CV_8UC4:
                {
                    QImage image(mat.data,
                                 mat.cols, mat.rows,
                                 static_cast<int>(mat.step),
                                 QImage::Format_ARGB32);

                    return image;
                }

             // 8-bit, 3 channel
             case CV_8UC3:
                {
                    QImage image(mat.data,
                                 mat.cols, mat.rows,
                                 static_cast<int>(mat.step),
                                 QImage::Format_RGB888);

                    return image.rgbSwapped();
                }

             // 8-bit, 1 channel
            case CV_8UC1:
                {
                    #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
                    QImage image(mat.data,
                                 mat.cols, mat.rows,
                                 static_cast<int>(mat.step),
                                 QImage::Format_Grayscale8);
                    #else
                    static QVector<QRgb>  sColorTable;

                    // only create our color table the first time
                    if (sColorTable.isEmpty())
                    {
                        sColorTable.resize( 256 );

                        for ( int i = 0; i < 256; ++i )
                        {
                            sColorTable[i] = qRgb( i, i, i );
                        }
                    }

                    QImage image(mat.data,
                                 mat.cols, mat.rows,
                                 static_cast<int>(mat.step),
                                 QImage::Format_Indexed8 );

                    image.setColorTable(sColorTable);
                    #endif

                    return image;
                }

            // wrong
            default:
                qDebug() << "ERROR: Mat could not be converted to QImage.";
                break;
        }
        return QImage();
}

/**********************初始化静态变量************************/
ImageBuffer GlobalVariable::imageBuffer = ImageBuffer();
QReadWriteLock GlobalVariable::lock = QReadWriteLock();

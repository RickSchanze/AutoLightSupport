#include "imagebuffer.h"

ImageBuffer::ImageBuffer(QObject *parent)
    : QObject{parent}
{

}

std::optional<cv::Mat> ImageBuffer::dequeue()
{
    if (buffer.empty()) {
        qDebug() << "缓存池为空";
        return std::nullopt;
    }
    return buffer.dequeue();
}

void ImageBuffer::enqueue(cv::Mat img)
{
    buffer.enqueue(img);
}

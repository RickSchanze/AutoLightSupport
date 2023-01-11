#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <QObject>
#include <QQueue>
#include <QDebug>

#include <optional>

#include "opencv2/imgproc.hpp"

#include "global.h"

class ImageBuffer : public QObject
{
    Q_OBJECT
public:
    explicit ImageBuffer(QObject *parent = nullptr);

    /**
     * @brief pop
     * @return 弹出图片
     */
    std::optional<cv::Mat> dequeue();

    /**
     * @brief 向队列加入图片
     * @param img
     */
    void enqueue(cv::Mat img);

signals:

private:
    QQueue<cv::Mat> buffer;
};

#endif // IMAGEBUFFER_H

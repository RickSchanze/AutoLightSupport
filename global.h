#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <QImage>
#include <QReadWriteLock>
#include <QThread>

#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

namespace Utils {

/**
 * @brief QImage转Mat
 * @param image
 * @return QImage
 *
 */
cv::Mat QImage2Mat(const QImage& image);

/**
 * @brief Mat转QImage
 * @param mat
 * @return
 */
QImage Mat2QImage(const cv::Mat& mat);
}

class ImageBuffer;

struct GlobalVariable {
    static ImageBuffer imageBuffer;
    static QReadWriteLock lock;
};

enum class WriteOption {
    FromVideo,      // 来自视频的图像将写入缓存
    FromMachine     // 来自下位机的图像将写入缓存
};

enum class LightOpertion {
    Enhance,        // 补光
    Weaken,         // 减弱光照
    DoNothing       // 啥也不用做
};

#endif // GLOBAL_H

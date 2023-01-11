#ifndef WRITER_H
#define WRITER_H
#include "global.h"

/**
 * @brief The Writer class
 * 视频和下位机数据将通过此类写入缓冲区
 */
class BufferWriter: QObject
{
    Q_OBJECT
public:
    BufferWriter();

private:
    cv::VideoCapture capture;
};

#endif // WRITER_H

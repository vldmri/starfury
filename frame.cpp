#include "frame.h"
/////////////////////////////////////////////////////////////////////////////////////
Frame::Frame() :
    _data(new uchar[0])
{}
/////////////////////////////////////////////////////////////////////////////////////
Frame::Frame(const Frame &f)
{
    this->_header = f._header;
    _data = new uchar[_header.dataSize];
    memcpy(this->_data, f._data, this->_header.dataSize);
    this->_cvmat = cv::Mat(this->_header.height,
                           this->_header.width,
                           CV_8UC1,
                           this->_data);
}
/////////////////////////////////////////////////////////////////////////////////////
Frame& Frame::operator =(const Frame &f)
{
    if(this != &f)
    {
        this->_header = f._header;
        delete []_data;
        _data = new uchar[_header.dataSize];
        memcpy(this->_data, f._data, this->_header.dataSize);
        this->_cvmat = cv::Mat(this->_header.height,
                               this->_header.width,
                               CV_8UC1,
                               this->_data);
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////////////
Frame::~Frame()
{
    delete []_data;
}
/////////////////////////////////////////////////////////////////////////////////////
void Frame::attachRawData(const FrameHeader &header,
                          const void *data)
{
    _header = header;
    delete []_data;
    _data = (uchar*)data;
}
/////////////////////////////////////////////////////////////////////////////////////
void Frame::unattachRawData()
{
    _data = 0;
}
/////////////////////////////////////////////////////////////////////////////////////
uchar* Frame::data()
{
    return _data;
}
/////////////////////////////////////////////////////////////////////////////////////
const FrameHeader& Frame::header()
{
    return _header;
}
/////////////////////////////////////////////////////////////////////////////////////
QReadWriteLock& Frame::lock()
{
    return _lock;
}
/////////////////////////////////////////////////////////////////////////////////////
cv::Mat& Frame::asCvMat()
{
    return _cvmat;
}
/////////////////////////////////////////////////////////////////////////////////////
void Frame::copyToQImage(QImage &img)
{
    img = QImage(_header.width,
                 _header.height,
                 QImage::Format_RGB32);
    uchar *ff = _data;
    QRgb *pLineStart, *pLineEnd;
    for(uint j = 0; j < _header.height; ++j)
    {
        pLineStart = (QRgb*)(img.scanLine(j));
        pLineEnd = pLineStart + _header.width;
        for(QRgb *pline = pLineStart; pline < pLineEnd; ++pline)
        {
            *pline = qRgba(*ff, *ff, *ff, 255);
            ++ff;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

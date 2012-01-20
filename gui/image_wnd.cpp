#include "image_wnd.h"
/////////////////////////////////////////////////////////////////////////////////////
void ImageWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPoint p(0, 0);
    painter.drawImage(p, _img);
}
/////////////////////////////////////////////////////////////////////////////////////
void ImageWindow::checkImgSize()
{
    if(_img.size() != _imgSize)
    {
        QRect rect;
        rect.setSize(_img.size());
        QPoint pos = this->pos();
        this->setGeometry(rect);
        this->move(pos);
        _imgSize = _img.size();
    }
}
/////////////////////////////////////////////////////////////////////////////////////
void ImageWindow::inputFrame(FrameBox *f)
{
    f->lock().lockForRead();
    f->data().copyToQImage(_img);
    f->lock().unlock();

    this->drawAll();
    this->checkImgSize();
    update();
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

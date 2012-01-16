#include "strobwnd.h"
/////////////////////////////////////////////////////////////////////////////////////
void StrobWindow::drawAll()
{
    draw::artifactMarks(_img, _picStars);
    draw::starMarks(_img, _catStars);
    draw::starConfig(_img, _eqPicStars, 2, Qt::yellow);
    draw::starConfig(_img, _eqCatStars, 1, Qt::cyan);
    _eqPicStars.clear();
    _eqCatStars.clear();
}
/////////////////////////////////////////////////////////////////////////////////////
void StrobWindow::inputPicStars(ArtifactBox *a)
{
    a->lock().lockForRead();
    _picStars = a->data();
    a->lock().unlock();
}
/////////////////////////////////////////////////////////////////////////////////////
void StrobWindow::inputCatStars(ArtifactBox *a)
{
    a->lock().lockForRead();
    _catStars = a->data();
    a->lock().unlock();

    draw::convertStarMagn(_catStars);
}
/////////////////////////////////////////////////////////////////////////////////////
void StrobWindow::inputEquatedStars(ArtifactBox *pic,
                                    ArtifactBox *cat)
{
    pic->lock().lockForRead();
    cat->lock().lockForRead();
    _eqPicStars = pic->data();
    _eqCatStars = cat->data();
    cat->lock().unlock();
    pic->lock().unlock();
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

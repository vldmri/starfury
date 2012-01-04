#ifndef STROB_WRAPPER_H
#define STROB_WRAPPER_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QThread>
#include <QSettings>
#include <QMouseEvent>
/////////////////////////////////////////////////////////////////////////////////////
#include "strob/strob.h"
#include "boxes/frame.h"
#include "common/logfile.h"
/////////////////////////////////////////////////////////////////////////////////////
class StrobWrapper : public QThread
{
    Q_OBJECT
public:
    explicit StrobWrapper(QSettings*,
                          LogFile*);
    ~StrobWrapper();
    const Strob& strob() const {return *_strob;}
private:
    StrobWrapper(const StrobWrapper&) {}
    StrobWrapper& operator =(const StrobWrapper&) {return *this;}
    LogFile *_log;
    Strob   *_strob;
private slots:
    void inputFrame(FrameBox*);
    void setPos(QMouseEvent*);
    void setPos(const int x,
                const int y);
    void setSide(const int);
    void setThreshold(const int);
signals:
    void frameReady(FrameBox*);
    void targetPos(int xTarget, int yTarget);
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // STROB_WRAPPER_H

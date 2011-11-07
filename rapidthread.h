#ifndef RAPIDTHREAD_H
#define RAPIDTHREAD_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QThread>
#include <QMutex>
#include <QSettings>
#include <QSize>
#include <QTime>
#include <QDebug>
#include "frame.h"
#include "strob.h"
/////////////////////////////////////////////////////////////////////////////////////
class RapidThread : public QThread
{
    Q_OBJECT
public:
    explicit RapidThread(QSettings *settings = 0);
    ~RapidThread();
    Strob *strob();
private:
    static const int _timeout = 20;
    Frame  *_frame;
    Strob  *_strob;
    QMutex *_mutex;
    void urgentProcessing(Frame*);
private slots:
    void frameIn(Frame*, QMutex*);
signals:
    void frameOut1(Frame*, QMutex*, int xTarget, int yTarget);
    void frameOut2(Frame*, QMutex*);
    void frameOut3(Frame*, QMutex*);
};
/////////////////////////////////////////////////////////////////////////////////////
#endif // RAPIDTHREAD_H

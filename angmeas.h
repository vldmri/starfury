#ifndef ANGMEAS_H
#define ANGMEAS_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QThread>
#include <QMutex>
#include <QSettings>
#include <QtAlgorithms>
#include <QDebug>
#include <QTime>
#include <QPoint>
#include "opencv.hpp"
#include "cvhelpfun.h"
#include "frame.h"
#include "artifact.h"
#include "calchelpfun.h"
/////////////////////////////////////////////////////////////////////////////////////
class AngMeas : public QThread
{
    Q_OBJECT
public:
    explicit AngMeas(QSettings *settings = 0);
    ~AngMeas();
private:
    static const int _timeout = 40;
    static const int _magnThresh = 2;
    QSettings      *_settings;
    Frame          *_frame;
    ArtifactVector *_artVec;
    QMutex         *_mutex;
    QPoint          _target;
    void filtering(Frame*);
    void findArtifacts(Frame*,
                       ArtifactVector*,
                       double thresh);
    void deleteTarget(ArtifactVector&,
                      QPoint &target);
private slots:
    void frameIn(Frame*, QMutex*, int xTarget, int yTarget);
signals:
    void artifactsOut(ArtifactVector*, QMutex*);
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // ANGMEAS_H

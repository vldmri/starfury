#ifndef FRAMEREC_H
#define FRAMEREC_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QThread>
#include <QSettings>
/////////////////////////////////////////////////////////////////////////////////////
#include "sharedmem.h"
#include "frame.h"
#include "strob.h"
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
class FrameReceiver : public QThread
{
    Q_OBJECT
public:
    explicit FrameReceiver(QSettings*,
                           Frame *f0,
                           Frame *f1);
    ~FrameReceiver();
    void stop();
    Strob& strob();
protected:
    void run();
private:
    static const int _timeout = 20;
    static const unsigned long _termTimeout = 500;
    QSettings      *_settings;
    Frame          *_frame0;
    Frame          *_frame1;
    SharedMem      *_sharedMem;
    volatile bool   _stopped;
    Strob          *_strob;
    void fastProc(Frame*);
signals:
    void frame0Ready(Frame*); //to Gui
    void frame1Ready(Frame*,  //to StarDetector
                     int xTarget,
                     int yTarget);
};
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // FRAMERECEIVER_H

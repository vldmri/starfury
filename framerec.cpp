#include "framerec.h"
/////////////////////////////////////////////////////////////////////////////////////
FrameReceiver::FrameReceiver(QSettings *s,
                             Frame *f0,
                             Frame *f1) :
    _settings(s),
    _frame0(f0),
    _frame1(f1),
    _sharedMem(new SharedMem(s)),
    _stopped(false),
    _strob(new Strob(s))
{
    this->moveToThread(this);
    this->start(QThread::NormalPriority);
}
/////////////////////////////////////////////////////////////////////////////////////
FrameReceiver::~FrameReceiver()
{
    this->stop();
    if(!this->wait(_termTimeout))   this->terminate();
    delete _strob;
    delete _sharedMem;
}
/////////////////////////////////////////////////////////////////////////////////////
void FrameReceiver::run()
{
    while(!_stopped)
    {
        if(_sharedMem->waitForData())
        {
            if(_frame0->lock().tryLockForWrite(_timeout))
            {
                _sharedMem->readFrame(_frame0);
                fastProc(_frame0);
                _frame0->lock().unlock();
                emit frame0Ready(_frame0); //to Gui
            }
            if(_frame1->lock().tryLockForWrite(_timeout))
            {
                _sharedMem->readFrame(_frame1);
                _frame1->lock().unlock();
                emit frame1Ready(_frame1,   //to StarDetector
                                 _strob->geometry().center().x(),
                                 _strob->geometry().center().y());
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////
void FrameReceiver::stop()
{
    _stopped = true;
}
/////////////////////////////////////////////////////////////////////////////////////
void FrameReceiver::fastProc(Frame *f)
{
    _strob->makeTracking(f);
}
/////////////////////////////////////////////////////////////////////////////////////
Strob& FrameReceiver::strob()
{
    return *_strob;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

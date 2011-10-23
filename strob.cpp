#include "strob.h"
/////////////////////////////////////////////////////////////////////////////////////
Strob::Strob(int refPointX,
             int refPointY,
             QSettings * settings)
    : FRefPoint(refPointX, refPointY)
{    
    FCenter = FRefPoint;
    FSettings = settings;
    LoadSettings(FSettings);
}
/////////////////////////////////////////////////////////////////////////////////////
Strob::~Strob()
{
    SaveSettings(FSettings);
}
///////////////////////////////////////////////////////////////////////////////////////
void Strob::LoadSettings(QSettings *settings)
{
    if(settings == 0)
    {
        FSize = DEFAULT_SIZE;
        FStdDevThreshold = DEFAULT_STDDEV_THRESHOLD;
    }
    else
    {
        FSize = settings->value(SKEY_STROB_SIZE, DEFAULT_SIZE).toInt();
        FStdDevThreshold = settings->value(SKEY_STDDEV_THRESHOLD, DEFAULT_STDDEV_THRESHOLD).toDouble();
    }
}
///////////////////////////////////////////////////////////////////////////////////////
void Strob::SaveSettings(QSettings *settings)
{
    if(settings != 0)
    {
        settings->setValue(SKEY_STROB_SIZE, FSize);
        settings->setValue(SKEY_STDDEV_THRESHOLD, FStdDevThreshold);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void Strob::StrobSlot(void *pFrame,
                      int frameWidth,
                      int frameHeight)
{
    FFrameSize.setWidth(frameWidth);
    FFrameSize.setHeight(frameHeight);
    cv::Mat mainImg(frameHeight, frameWidth, CV_8UC1, pFrame);

    //��������, ������������� ����������� � �������� �������
    int size2 = FSize / 2;
    int foneStrobSize = (int)(floor(SQRT_2 * FSize + 0.5));
    int foneStrobSize2 = foneStrobSize / 2;
    QPoint signalRoiTopLeft(FCenter.x() - size2,
                            FCenter.y() - size2);
    QPoint foneRoiTopLeft(FCenter.x() - foneStrobSize2,
                          FCenter.y() - foneStrobSize2);
    cv::Mat signalRoi(mainImg, cv::Rect(signalRoiTopLeft.x(),
                                        signalRoiTopLeft.y(),
                                        FSize,
                                        FSize));
    cv::Mat foneRoi(mainImg, cv::Rect(foneRoiTopLeft.x(),
                                      foneRoiTopLeft.y(),
                                      foneStrobSize,
                                      foneStrobSize));

    //�������������
    cv::blur(foneRoi, foneRoi, cv::Size(5,5));

    //��������� ������� � ���������� ������ � � �������
    long int sumSignal = cv::sum(signalRoi)[0];
    long int sumFone = cv::sum(foneRoi)[0];
    sumFone -= sumSignal;

    //�������� ������� ��������
    if(sumSignal > (sumFone + sqrt(sumFone)))
    {
        //��������� ����������� � ���������� ������
        int borderPixNum = (foneRoi.total() - signalRoi.total());
        double fonePerPix = sumFone / borderPixNum;
        double stdDev = sqrt(sumFone) / borderPixNum;
        int thresh = (int)floor(0.5 + fonePerPix + FStdDevThreshold * stdDev);
        cv::threshold(signalRoi,
                      signalRoi,
                      thresh,
                      0xFF * signalRoi.channels(),
                      cv::THRESH_TOZERO);

        //���������� ������ ���� �� ����������� ������
        cv::TermCriteria crit(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 2, 0.1);
        cv::Rect trackingWindow(signalRoiTopLeft.x(),
                                signalRoiTopLeft.y(),
                                FSize,
                                FSize);
        cv::meanShift(mainImg, trackingWindow, crit);
        FCenter.setX(trackingWindow.x + size2);
        FCenter.setY(trackingWindow.y + size2);
        CheckCenterRange(&FCenter,
                         frameWidth,
                         frameHeight,
                         FSize);
    }

    //������� ������� �� ��������� ��������
    emit DrawFrameSignal(pFrame, frameWidth, frameHeight);
}
/////////////////////////////////////////////////////////////////////////////////////
void Strob::CheckCenterRange(QPoint *center,
                             int frameWidth,
                             int frameHeight,
                             int roiSize)
{
    int k = 1;
    roiSize *= k;
    int xMin = 0 + roiSize;
    int xMax = frameWidth - roiSize;
    int yMin = 0 + roiSize;
    int yMax = frameHeight - roiSize;
    if(center->x() < xMin)  center->setX(xMin);
    if(center->x() > xMax)  center->setX(xMax);
    if(center->y() < yMin)  center->setY(yMin);
    if(center->y() > yMax)  center->setY(yMax);
}
/////////////////////////////////////////////////////////////////////////////////////
void Strob::ClickTarget(QMouseEvent *mousePressEvent)
{
    FCenter.setX(mousePressEvent->x());
    FCenter.setY(mousePressEvent->y());
    CheckCenterRange(&FCenter,
                     FFrameSize.width(),
                     FFrameSize.height(),
                     FSize);
}
/////////////////////////////////////////////////////////////////////////////////////
void Strob::StrobChange(int pos)
{
    FSize = pos;
}
/////////////////////////////////////////////////////////////////////////////////////
int Strob::Size()
{
    return FSize;
}

/////////////////////////////////////////////////////////////////////////////////////

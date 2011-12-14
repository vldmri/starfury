#ifndef ANGMETER_H
#define ANGMETER_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QThread>
#include <QDebug>
#include <QSettings>
#include <qmath.h>
#include <QSize>
#include <QPoint>
/////////////////////////////////////////////////////////////////////////////////////
#include "globalskeys.h"
#include "astrocalc.h"
#include "triangle.h"
#include "lincor.h"
/////////////////////////////////////////////////////////////////////////////////////
//setting keys
#define SKEY_MAX_STAR_QUANTITY        "/Angmeter/MaxStarQuantity"
#define SKEY_EQUAL_EPS                "/Angmeter/EqualEps"
#define SKEY_SIMILAR_EPS              "/Angmeter/SimilarEps"
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
class Angmeter : public QThread
{
    Q_OBJECT
public:
    explicit Angmeter(QSettings*);
    ~Angmeter();
public slots:
    void setScreenSize(const int width,
                       const int height);
private:
    static const int _timeout = 20;
    static const int _defaultScreenWidth  = 640;
    static const int _defaultScreenHeight = 480;
    static const int _defaultMaxStarQuantity = 15;
    static const double _defaultEqualEps   = 2.0;
    static const double _defaultSimilarEps = 0.25;
    QSettings     *_settings;
    QSize          _screen;
    ArtifactVector _picStars;
    ArtifactVector _catStars;
    TriangleBox    _tribox;
    int            _maxStarQuantity;
    double         _equalEps;
    double         _similarEps;
    LinCor         _lincor;
    void loadSettings(QSettings*);
    void saveSettings(QSettings*);
    void equation();
    void measureWork(int &xTarget,
                     int &yTarget);
private slots:
    void inputScreenStars(ArtifactBox*,
                          int xTarget,
                          int yTarget);
    void inputCatStars(ArtifactBox*);
signals:
    void sendTriangles(TriangleBox*);
    void sendTarget(int x, int y);
};
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // ANGMETER_H

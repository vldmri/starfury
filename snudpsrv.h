#ifndef SNUDPSRV_H
#define SNUDPSRV_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QtGlobal>
#include <QtNetwork/QUdpSocket>
#include <QSettings>
#include <QObject>
#include <QMutex>
#include <QDebug>
/////////////////////////////////////////////////////////////////////////////////////
#define SKEY_UDPSERVER_PORT "/UdpServer/Port"
#define TVA_UDPPACK_ID      0x44C5EB64038F4462 //8bytes
/////////////////////////////////////////////////////////////////////////////////////
struct TelescopeVector
{
    qint64 packID;
    qint64 timeUTC;
    double azAxis;
    double elAxis;
    double azVelAxis;
    double elVelAxis;
    double azOrient;
    double elOrient;
    double azHoriz;
    double elHoriz;
    double alpha;
    double delta;
    double LST;
};
////////////////////////////////////////////////////////////////////////////////////
class SnUdpSrv : public QObject
{
    Q_OBJECT
public:
    explicit SnUdpSrv(QSettings *settings = 0);
    ~SnUdpSrv();
private:
    static const quint16 _defaultPort = 4444;
    static const int _timeout = 20;
    QSettings       *_settings;
    quint16          _port;
    QUdpSocket      *_socket;
    TelescopeVector *_tvector;
    QMutex          *_mutex;
    void loadSettings(QSettings*);
    void saveSettings(QSettings*);
private slots:
    void read();
signals:
    void dataReady(TelescopeVector*, QMutex*);
};
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // SNUDPSRV_H

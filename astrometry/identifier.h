#ifndef IDENTIFIER_H
#define IDENTIFIER_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QtAlgorithms>
#include <QVector>
#include <QDebug>
/////////////////////////////////////////////////////////////////////////////////////
#include "boxes/artifact.h"
#include "math/astrocalc.h"
/////////////////////////////////////////////////////////////////////////////////////
class ArtifactPair
{
public:
    explicit ArtifactPair();
    explicit ArtifactPair(const Artifact *refStar,
                          const Artifact &anyStar);
    bool operator ==(const ArtifactPair &other) const {return this->_dist == other._dist;}
    bool operator !=(const ArtifactPair &other) const {return this->_dist != other._dist;}
    bool operator <(const ArtifactPair &other)  const {return this->_dist <  other._dist;}
    const Artifact& star() const {return _star;}
    const Artifact* refStar() const {return _refStar;}
    double dist() const {return _dist;}
private:
    const Artifact *_refStar;
    Artifact        _star;
    double          _dist;
};
/////////////////////////////////////////////////////////////////////////////////////
typedef QVector<ArtifactPair> ArtifactPairVector;
/////////////////////////////////////////////////////////////////////////////////////
namespace id
{
static const int    __minStarQuantity = 3;
static const double __distEps = 0.1; //���������, ��� ���������� ����� � ��������� �� __distEps
void equate(ArtifactVector &picStars,
            ArtifactVector &catStars,
            const double eps,
            const QPointF &screenCenter);
}
/////////////////////////////////////////////////////////////////////////////////////
typedef QVector<double> QVector_double;
typedef QVector<int>    QVector_int;
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // IDENTIFIER_H

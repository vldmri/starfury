#ifndef DETECTION_H
#define DETECTION_H
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#include "opencv.hpp"
#include "utils/cvhelpfun.h"
#include "math/astrocalc.h"
#include "boxes/frame.h"
#include "boxes/artifact.h"
/////////////////////////////////////////////////////////////////////////////////////
namespace detection
{
void smooth(Frame&,
            const int windowSize);
void threshold(Frame&);
void findArtifacts(Frame&,
                   ArtifactVector&,
                   const double magnThresh);
void deleteTarget(ArtifactVector &stars,
                  const ArtifactVector &target);
bool isDoubleStar(const cv::Rect&);  //������������� �� cv::floodFill
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // DETECTION_H

#ifndef DETECTION
#define DETECTION

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QString>

using namespace cv ;

int detect(const QString imageName , double scale) ;
int detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& profileCascade,
                    double scale, bool tryflip );

#endif // DETECTION


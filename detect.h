#ifndef DETECT
#define DETECT

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QString>

using namespace cv ;

bool detect(const QString &imageName , double scale ,QString cascadeName) ;
int detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    double scale, bool tryflip );
String getLogDir() ;



#endif // DETECT


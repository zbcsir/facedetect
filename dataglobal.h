#ifndef DATAGLOBAL_H
#define DATAGLOBAL_H

#include <highgui.h>
#include <QString>

class DataGlobal
{
public:
    DataGlobal();

public:
    static cv::Mat imgResult ;
    static int faceCountRes ;
    static double timeDetect ;

    static QString imgInput ;
    static double scale ;

};

#endif // DATAGLOBAL_H

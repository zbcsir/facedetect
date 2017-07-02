#include "dataglobal.h"

DataGlobal::DataGlobal()
{

}

cv::Mat DataGlobal::imgResult(480,380,CV_8UC3,1) ;
int DataGlobal::faceCountRes = 0 ;
double DataGlobal::timeDetect = 0 ;

double DataGlobal::scale = 2 ;
QString DataGlobal::imgInput = "" ;


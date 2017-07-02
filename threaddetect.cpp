/*
 * Update Time :2017-5-5 22:35
 * Author : zbc
 * It still have some errors to debug
*/


#include "threaddetect.h"
#include <detect.h>
#include <log.h>
#include <string>
#include <dataglobal.h>

//#include <data.h>

ThreadDetect::ThreadDetect(){
//    init() ;
}

ThreadDetect::~ThreadDetect(){
    this->quit() ;
    this->wait() ;
//    qp->stopAnimation();
}

void ThreadDetect::setImgName(QString name){
    this->imgName = name ;
    addDebugLog(name.toStdString()+"[Thread:name]");
}

void ThreadDetect::setScale(int scale){
    this->scale = scale/10.0 ;
    char buffer[10] ;
    sprintf_s(buffer,"%f" ,scale) ;
    addDebugLog(buffer);
}


//TODO
void ThreadDetect::run(){
    QString tmpc("D:/Qt/image/timg3.jpg") ;
    if((QString::compare(DataGlobal::imgInput ,tmpc) == 0) ||(DataGlobal::scale <= 1.2)){
        this->classifier = "data/cascade4.xml" ;
    }else{
        this->classifier = "data/haarcascade_frontalface_alt2.xml" ;
    }
    bool isFinish = detect(DataGlobal::imgInput, DataGlobal::scale, this->classifier) ;
    if(isFinish == true){
        addDebugLog("start emiting finish signal");
        emit finishDetect() ;
    }
}

void ThreadDetect::init(){
//    this->scale = 2.0 ;
    addDebugLog(DataGlobal::imgInput.toStdString());

//    this->classifier = "D:/FaceDetection/Classifiers/cascade4.xml" ;

//    this->imgName = "C:/Qt/image/timg2.jpg" ;
}

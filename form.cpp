#include "form.h"
#include "ui_form.h"
#include <QStackedLayout>
#include <btnqss.h>
#include <QMessageBox>
#include <adjustlig.h>
#include <iostream>
#include <detect.h>
#include <stdio.h>
#include <windows.h>
#include <QTimer>

using namespace std;

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    initForm();

}

Form::~Form()
{
    delete ui;
    cvReleaseCapture(&capture) ;
}

void Form::initForm(){
    setWindowTitle("应用实验室");
    setBtnQss(ui->openLight ,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->advertise ,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->screenLight ,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
}

/*
 * 每隔五分钟对电脑屏幕捕捉一张图片，若没有，下次相隔一分钟，若还是没有，第三次捕捉半分钟；否则，回到五分钟
 * 若三次均没发现，则系统休眠
 */
void Form::on_screenLight_clicked()
{

    if(takePhotoAndDL()){

    }else{
        Sleep(1000) ;
        willSleep.setWindowTitle("Notice");
        willSleep.setText("连续三次检测到屏幕前无人\n将为您休眠") ;
        willSleep.setStandardButtons(QMessageBox::Cancel) ;
        willSleep.setButtonText(QMessageBox::Cancel,"不！有人！");
        willSleep.show();
    //    willSleep.setText("");
    //    int res = willSleep.question(this,"Notice","连续三次检测到屏幕前无人\n将为您休眠",
    //                                 QMessageBox::Cancel) ;
        timer = new QTimer(this) ;
        timer->start(2000);
        QObject::connect(timer,SIGNAL(timeout()) ,this,SLOT(stopTimer())) ;
    }


//    if(QMessageBox::Cancel == )
//    if(QMessageBox::Cancel == res){
//        stopTimer();
//    }else{
//        Sleep(1000) ;
//        QMessageBox::information(this,"","休眠") ;
        //    system("rundll32 powrprof.dll,SetSuspendState") ;
//    }


//    if(takePhotoAndDL()){
//        system("rundll32 powrprof.dll,SetSuspendState") ;
//    }else{
//        cout<<"未发现人脸"<<endl ;
//    }

}

void Form::on_advertise_clicked()
{
    QMessageBox::information(this,"通知","待开发中") ;
}

/*
 * 检测到人脸后开灯
 */
void Form::on_openLight_clicked()
{

    if(takePhotoAndDL()){

    }else{
        Sleep(1000) ;
        serial.setPortName("COM4");
        serial.setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections) ;
        serial.setDataBits(QSerialPort::Data8) ;
        serial.setFlowControl(QSerialPort::NoFlowControl) ;
        serial.setParity(QSerialPort::NoParity) ;
        serial.setStopBits(QSerialPort::OneStop) ;
        serial.close();
        serial.open(QSerialPort::WriteOnly) ;

        QByteArray cmd ;
        cmd[0]= 0x40;
        cmd[1]= 0x06;
        cmd[2]= 0x01;
        cmd[3]= 0x09;
        cmd[4]= 0x06;
        cmd[5]= 0x56;
        cout<<cmd[0]<<endl ;
        serial.write(cmd) ;
        QMessageBox::information(this,"","检测到人脸，已开灯") ;
    }
//        serial.setPortName("COM4");
//        serial.setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections) ;
//        serial.setDataBits(QSerialPort::Data8) ;
//        serial.setFlowControl(QSerialPort::NoFlowControl) ;
//        serial.setParity(QSerialPort::NoParity) ;
//        serial.setStopBits(QSerialPort::OneStop) ;
//        serial.close();
//        serial.open(QSerialPort::WriteOnly) ;

//        QByteArray cmd ;
//        cmd[0]= 0x40;
//        cmd[1]= 0x06;
//        cmd[2]= 0x01;
//        cmd[3]= 0x09;
//        cmd[4]= 0x06;
//        cmd[5]= 0x56;
//        cout<<cmd[0]<<endl ;
//        serial.write(cmd) ;
//        QMessageBox::information(this,"","已发送") ;
//    }else{
//        QMessageBox::information(this,"","未发现人脸") ;
//    }
}

bool Form::takePhotoAndDL(){

    bool treturn = false ;

    capture = cvCreateCameraCapture(0);
    Mat frame, frameCopy ;
    bool tryflip = false;
    double scale = 2 ;

    CascadeClassifier cascade ;
    string cascadeName = "C:\\Qt\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }

    if( !capture )
    {
        cout << "In capture ..." << endl;
        IplImage* iplImg = cvQueryFrame( capture );
        frame = iplImg;
        if( iplImg->origin == IPL_ORIGIN_TL )
            frame.copyTo( frameCopy );
        else
            flip( frame, frameCopy, 0 );

        int count = detectAndDraw( frameCopy, cascade, scale, tryflip );
        if(count > 0)
            treturn = true ;

        if( waitKey( 10 ) >= 0 )
            goto _cleanup_;

        waitKey(0);

_cleanup_:
        cvReleaseCapture( &capture );
    }

    return treturn ;
}

void Form::stopTimer(){
    timer->stop();
    willSleep.close() ;
    system("rundll32 powrprof.dll,SetSuspendState") ;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <detect.h>
#include <qthread.h>
#include <QComboBox>
#include <log.h>
#include <data.h>
#include <dataglobal.h>
#include <btnqss.h>

//QString classifierPath = "D:/FaceDetection/Classifiers/haarcascade_frontalface_alt.xml" ;
cv::Mat imgResult ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initForms();

    td = new ThreadDetect() ;
    connect(this,SIGNAL(send_imgName(QString)),td,SLOT(setImgName(QString)),
            Qt::QueuedConnection) ;
    connect(this,SIGNAL(send_scale(int)),td,SLOT(setScale(int)),
            Qt::QueuedConnection) ;
    connect(td,SIGNAL(finishDetect()),this,SLOT(waitbarStop()),Qt::QueuedConnection) ;
    connect(td ,SIGNAL(updateCountSignal(int)) ,this ,SLOT(updateCount(int)) ,
            Qt::QueuedConnection) ;
    connect(ui->scale ,SIGNAL(valueChanged(int)),this,SLOT(displayScale(int))) ;

    //connect(this,display,stackLayout ,QStackedLayout::setCurrentIndex) ;
//    connect(ui->scale ,SIGNAL(sliderMoved(int)),this,SLOT(displayScale(int))) ;

//    connect(ui->scale,SIGNAL(valueChanged(int)),ui->detectProcess,SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 初始化控件
 */

void MainWindow::initForms(){

    imageName = "" ;
    //显示人数控件
    ui->countShow->setDigitCount(3); //最多显示3位数
    ui->countShow->display(0);

    //选择尺度控件
    ui->scale->setMinimum(1);
    ui->scale->setMaximum(22);
    ui->scale->setValue(11);
    ui->scale->setTickPosition(QSlider::TicksAbove);
    setSliderQss(ui->scale ,"#E8EDF2", "#34495E", "#34495E");

//    //选择分类器控件
//    ui->classfier->addItem(QWidget::tr("请选择分类器"));
//    ui->classfier->addItem(QWidget::tr("cascade0.xml"));
//    ui->classfier->addItem(QWidget::tr("cascade1.xml"));
//    ui->classfier->addItem(QWidget::tr("cascade3.xml"));
//    ui->classfier->addItem(QWidget::tr("cascade4.xml"));
//    ui->classfier->addItem(QWidget::tr("haarcascade_frontalface_alt.xml"));
//    ui->classfier->addItem(QWidget::tr("haarcascade_frontalface_alt2.xml"));
//    ui->classfier->addItem(QWidget::tr("lbpcascade_frontalface.xml"));

//    //进度条控件
//    setBarQss(ui->detectProcess,"#E8EDF2", "#1ABC9C");
//    ui->detectProcess->setValue(0);

    //选择文件控件
    setBtnQss(ui->choiceFile, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->help, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->aboutus, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->start ,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->lab ,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");

    //显示人数控件
    setLCDQSS("#34495E");

    ui->textBrowser->setVisible(true);
    ui->waittext->setVisible(false);

    ui->successread->clear();

    //选择文件waitBar
//    choiceFileBar = new CustomWaitBar(ui->successread) ;
//    choiceFileBar->setSize(20);

//    choiceFileBar->setColor(Qt::black);

    //检测waitBar
    qp = new QProgressIndicator(ui->successdetect) ;

    dFinishBox.setWindowTitle("检测完成");
    dFinishBox.setStandardButtons(QMessageBox::Ok) ;
    dFinishBox.setButtonText(QMessageBox::Ok ,"我知道了");

    sizeException.setWindowTitle("Error");
    sizeException.setText("照片尺寸过小，请至少选择480*380尺寸照片");
    sizeException.setStandardButtons(QMessageBox::Ok);
    sizeException.setButtonText(QMessageBox::Ok,"重新选择文件");

//    ui->imgShow->mousePressEvent(QMouseEvent *event);

//    slider = new MyCustomSlider(ui->label_2) ;
//    slider->setMinimum(1);
//    slider->setMaximum(22);
//    slider->show();

}

void MainWindow::on_choiceFile_clicked()
{
    ui->countShow->display(0);
    ui->successread->clear();
    ui->successdetect->clear();

    QImage img ;
    QImage readSuccess ;
    QImage imgOrigin ;
    imageName = QFileDialog::getOpenFileName(this,"选择照片","C:/Qt/image/",
                                             "*.jpg;;*.bmp;;*.png") ;
    cv::Mat imgtmp ;
    if(!imageName.isEmpty()){

        if(!img.load(imageName)){
            QMessageBox::information(this,"Warning","照片加载失败") ;
        }else{
            imgtmp = cv::imread(imageName.toStdString()) ;
            if(imgtmp.rows >= 300 && imgtmp.cols >= 400){
                cv::resize(imgtmp ,imgtmp ,cv::Size(480,380)) ;
                cv::cvtColor(imgtmp ,imgtmp ,CV_BGR2RGB) ;
                imgOrigin = QImage((const unsigned char*)imgtmp.data ,480 ,380 ,
                                   480*imgtmp.channels() ,QImage::Format_RGB888) ;

                QGraphicsScene *scene = new QGraphicsScene ;
                scene->addPixmap(QPixmap::fromImage(imgOrigin)) ;
                ui->imgShow->setScene(scene) ;
                ui->imgShow->show();

                if(readSuccess.load("D:/QT_Project/FaceDetect/success.png")){
                    ui->successread->setPixmap(QPixmap::fromImage(readSuccess));
                    ui->successread->show();
                }else{
                    addLog("选择图片：success.png导入失败 [选择文件]");
                }

                addDebugLog(imageName.toStdString());

            }else{
                sizeException.show();
            }

        }

    }
    else{
        QMessageBox::information(this,"Error","请选择照片") ;
    }
}


void MainWindow::on_choiceFile_pressed()
{
//    if(ui->classfier->currentText() == "请选择分类器"){
//        QMessageBox::information(this,"Warning","请先选择分类器") ;
//    }else{
//        classifierPath = "D:/FaceDetection/Classifiers/" ;
//        classifierPath.append(ui->classfier->currentText()) ;
//    }
    ui->textBrowser->setVisible(false);
//    QMessageBox::information(this,"温馨提示","您是否需要选择尺度") ;
}

/*
 * 设置进度条QSS样式
 */
void MainWindow::setBarQss(QProgressBar *bar, QString normalColor, QString chunkColor){
    int barHeight = 8;
    int barRadius = 8;

    QStringList qss;
    qss.append(QString("QProgressBar{font:9pt;height:%2px;background:%1;border-radius:%3px;text-align:center;border:1px solid %1;}").arg(normalColor).arg(barHeight).arg(barRadius));
    qss.append(QString("QProgressBar:chunk{border-radius:%2px;background-color:%1;}").arg(chunkColor).arg(barRadius));
    bar->setStyleSheet(qss.join(""));
}

void MainWindow::setSliderQss(QSlider *slider, QString normalColor, QString grooveColor, QString handleColor){
    int sliderHeight = 8;
    int sliderRadius = 4;
    int handleWidth = 13;
    int handleRadius = 6;
    int handleOffset = 3;

    QStringList qss;
    qss.append(QString("QSlider::groove:horizontal,QSlider::add-page:horizontal{height:%2px;border-radius:%3px;background:%1;}").arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::sub-page:horizontal{height:%2px;border-radius:%3px;background:%1;}").arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;margin-bottom:-%3px;border-radius:%4px;"
                       "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
               .arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));
    slider->setStyleSheet(qss.join(""));
}

void MainWindow::setButtonNormalQss(){

}

/*
 *  设置按钮属性
 *  normal* : 正常状态下按钮颜色和字体颜色
 *  hover*  : 鼠标悬浮状态下按钮颜色和字体颜色
 *  pressed : 鼠标按下状态下按钮颜色和字体颜色
*/

void MainWindow::setLCDQSS(QString borderColor){
    QStringList qss ;
    qss.append(QString("QLCDNumber{padding:1px;border-style:groove;border:2px solid %1;"
                       "border-radius:8px;;}").arg(borderColor));
    ui->countShow->setStyleSheet(qss.join(""));
}

void MainWindow::on_help_clicked()
{
    QMessageBox::information(this,"使用帮助","1.选择照片文件\n"
                                         "2.然后根据扫描精细度要求通过滑动条选择尺度\n"
                                         "3.步骤1和2完成后点击开始检测\n"
                                         "4.左侧显示圈出人脸后的结果,右下角显示照片人数\n"
                                         "5.点击应用实验室按钮可以使用人脸检测的小应用\n"
                                         "6.如有意见或问题，可点击关于我们联系作者") ;
}

void MainWindow::on_aboutus_clicked()
{
    QMessageBox::information(this,"关于我们","作     者：张本才\n学     校：山东科技大学\n"
                                         "版     本：1.0\n"
                                         "联系QQ：570724307") ;
}

void MainWindow::on_start_clicked()
{
    ui->successdetect->clear();
    DataGlobal::imgInput = imageName ;
    DataGlobal::scale = ui->scale->value()/10.0 ;
    if(imageName == ""){
        QMessageBox::information(this,"Error","请先选择照片再点击检测") ;
    }
    else if(!imageName.isEmpty()){
        td->start();

        ui->waittext->setVisible(true);
        qp->startAnimation();
        qp->show();
    }
}

void MainWindow::waitbarStop(){
    char buffer[20] ;
    sprintf_s(buffer,"%.1f",DataGlobal::timeDetect) ;

    ui->countShow->display(DataGlobal::faceCountRes) ;

    cv::cvtColor(DataGlobal::imgResult,DataGlobal::imgResult,CV_BGR2RGB) ;
    QImage imgtmp = QImage((const unsigned char*)(DataGlobal::imgResult.data),
                       480, 380 ,
       DataGlobal::imgResult.cols*DataGlobal::imgResult.channels() , //解决图像扭曲
                           QImage::Format_RGB888) ;

    QGraphicsScene *scene = new QGraphicsScene(this) ;

    scene->addPixmap(QPixmap::fromImage(imgtmp)) ;
    ui->imgShow->setScene(scene);
    ui->imgShow->show();

    //检测成功提示按钮
    QImage detectSuccess ;

//    QThread::sleep(1) ;
    qp->stopAnimation();
//    ui->waitbar->setVisible(false);
    ui->waittext->setVisible(false);
    td->terminate();

    if(detectSuccess.load("D:/QT_Project/FaceDetect/success.png")){
        ui->successdetect->setPixmap(QPixmap::fromImage(detectSuccess));
        ui->successdetect->show();
    }else{
        addLog("选择图片：success.png导入失败 [检测]");
    }

    QString dFinishInfo("检测完成! 共用时 : ") ;
    dFinishInfo.append(buffer) ;
    dFinishInfo.append(" 秒") ;

    dFinishBox.setText(dFinishInfo);
    dFinishBox.show();
}

void MainWindow::updateCount(int count){
    ui->countShow->display(double(count));
}

void MainWindow::displayScale(int scale){
    scale = scale/10.0 ;
    char buffer[10] ;
    sprintf_s(buffer ,"%.1f" ,scale) ;
    QString sscale(buffer) ;
//    ui->valueScale->setText(sscale);
}

void MainWindow::on_lab_clicked()
{
    appLab = new Form ;
    appLab->show();
}

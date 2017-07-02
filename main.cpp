#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("facedetect.ico"));
    a.setApplicationVersion("1.0");
    a.setApplicationName("基于人脸检测的照片人数统计");
//    font.setFamily("Consolas");
    int nidx = QFontDatabase::addApplicationFont("/wryh.ttf") ;
    if(nidx != -1){
        QStringList strList = QFontDatabase::applicationFontFamilies(nidx) ;
        if(strList.count() > 0){
            QFont font(strList.at(0)) ;
            font.setPointSize(10);
            a.setFont(font);
        }
    }

    MainWindow w;
    //最大化按钮不可用
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);

    w.show();

    return a.exec();
}

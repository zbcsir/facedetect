#ifndef THREADDETECT_H
#define THREADDETECT_H
#include <QThread>
#include <QPushButton>
#include <QComboBox>
#include <QSlider>

class ThreadDetect : public QThread
{
    Q_OBJECT
public:
    ThreadDetect() ;
    ~ThreadDetect();
    void run() ;

private:
    QString imgName;
    double scale;
    QString classifier ;

public slots:
    void setScale(int) ;
    void setImgName(QString) ;
//    void setClassifier(QString) ;

signals:
    void finishDetect() ;
    void updateCountSignal(int) ;

//public:
//    void connectDT(QObject *win ,QComboBox *classifierList,
//                   QSlider *scaleSlider) ;
//    void initWidget() ;
private :
    void init();

};

#endif // THREADDETECT_H

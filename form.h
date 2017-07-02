#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <highgui.h>
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void initForm() ;
    bool takePhotoAndDL() ;

private slots:
    void on_screenLight_clicked();

    void on_advertise_clicked();

    void on_openLight_clicked();

    void stopTimer() ;


private:
    Ui::Form *ui;

    QSerialPort serial ;

    QTimer *timer ;
    CvCapture* capture ;

    QMessageBox willSleep ;

};

#endif // FORM_H

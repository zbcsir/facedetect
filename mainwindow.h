/*
 * Update Time : 2017-5-6 14:47
 * Author : zbc
 * Add Signals and Slots
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>
#include <threaddetect.h>
#include <QMouseEvent>
#include <QMessageBox>
#include <mycustomslider.h>
#include <form.h>
#include <QStackedLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void send_imgName(QString) ;
    void send_scale(int) ;
    void display(int nu) ;

private slots:
    void on_choiceFile_clicked();

    void on_choiceFile_pressed();
    void initForms() ;
    void setBarQss(QProgressBar *bar, QString normalColor, QString chunkColor) ;
    void setSliderQss(QSlider *slider, QString normalColor, QString grooveColor,
                      QString handleColor) ;
    void setButtonNormalQss() ;
    void setLCDQSS(QString borderColor) ;

    void on_help_clicked();

    void on_aboutus_clicked();

    void waitbarStop() ;

    void updateCount(int) ;


    void on_start_clicked();

    void displayScale(int scale) ;

    void on_lab_clicked();

private:
    Ui::MainWindow *ui;
    ThreadDetect *td ;
    QString imageName ;
    //检测完成提示框
    QMessageBox dFinishBox ;
    MyCustomSlider *slider ;
    QMessageBox sizeException ;

    //应用实验室
    QStackedLayout *stackLayout ;
    Form *appLab ;

};

#endif // MAINWINDOW_H

#ifndef MYCUSTOMSLIDER_H
#define MYCUSTOMSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QLabel>

class MyCustomSlider : public QSlider
{
public:
    MyCustomSlider(QWidget *parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QLabel* m_displayLabel ;
};

#endif // MYCUSTOMSLIDER_H

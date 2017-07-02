#include "mycustomslider.h"

/*
 * Time : 2017-5-5 22:31
 * Author : zbc
 *
*/
MyCustomSlider::MyCustomSlider(QWidget* parent):QSlider(parent)
{
    m_displayLabel=new QLabel(this);
    m_displayLabel->setFixedSize(QSize(20,20));
    //设置游标背景为白色
    m_displayLabel->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::black);
    m_displayLabel->setPalette(palette);

    m_displayLabel->setAlignment(Qt::AlignCenter);

    m_displayLabel->setVisible(false);
    m_displayLabel->move(0,3);
}

void MyCustomSlider::mousePressEvent(QMouseEvent *event)
{
    if(!m_displayLabel->isVisible())
    {
        m_displayLabel->setVisible(true);
        m_displayLabel->setText(QString::number(this->value()));
    }
    QSlider::mousePressEvent(event);
}

void MyCustomSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_displayLabel->isVisible())
    {
        m_displayLabel->setVisible(false);
    }
    QSlider::mouseReleaseEvent(event);
}

void MyCustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    m_displayLabel->setText(QString::number(this->value()));
    m_displayLabel->move((this->width()-m_displayLabel->width())*this->value()/(this->maximum()-this->minimum()),3);
    QSlider::mouseMoveEvent(event);
}

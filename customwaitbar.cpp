#include "customwaitbar.h"

CustomWaitBar::CustomWaitBar(QWidget* parent):QProgressIndicator(parent),
    m_angle(0),
    m_timerId(-1),
    m_delay(40),
    m_displayedWhenStopped(false),
    m_color(Qt::black)
{

}

QSize CustomWaitBar::setHint() const{
    return QSize(20,20) ;
}

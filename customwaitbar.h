#ifndef CUSTOMWAITBAR_H
#define CUSTOMWAITBAR_H
#include <qprogressindicator.h>

class CustomWaitBar : public QProgressIndicator
{
public:
    CustomWaitBar(QWidget* parent = 0);
    virtual QSize setHint() const ;

private:
    int m_angle;
    int m_timerId;
    int m_delay;
    bool m_displayedWhenStopped;
    QColor m_color;

};

#endif // CUSTOMWAITBAR_H

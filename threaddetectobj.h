#ifndef THREADDETECTOBJ_H
#define THREADDETECTOBJ_H

#include <QObject>
#include <QThread>

class ThreadDetectObj : public QObject
{
    Q_OBJECT

    QThread dthread ;

public:
    ThreadDetectObj();


};

#endif // THREADDETECTOBJ_H

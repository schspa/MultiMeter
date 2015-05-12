#ifndef ADCTHREAD_H
#define ADCTHREAD_H

//#include "multimeterdevice.h"
#include <QThread>
class MultiMeterDevice;
class AdcThread : public QThread
{
public:
    bool is_run;
    static unsigned long res;
    MultiMeterDevice *dev;
    AdcThread(MultiMeterDevice *dev);
    ~AdcThread();
    void run();
};

#endif // ADCTHREAD_H

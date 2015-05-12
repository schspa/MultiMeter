#ifndef MULTIMETERDEVICE_H
#define MULTIMETERDEVICE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <measurebase.h>

//#include "adcthread.h"

#if    __GNUC_MINOR__ == 4
    #define USE_IMX287
    //std::cout<<"GCC Version "<<__VERSION__<<std::endl;
#endif


class AdcThread;

class MultiMeterDevice : public QObject
{
    Q_OBJECT
public:
    explicit MultiMeterDevice(QObject *parent = 0);
    ~MultiMeterDevice();
    AdcThread *adc_thread;

    unsigned long read_adc();


#ifdef USE_IMX287
    int dev_fd;
#endif //USE_IMX287

    void caculate_result(const unsigned long &res);
    QStringList get_measure_dev_list();
    QStringList getRangeStringList();
    void pin_ctrl(int request, int val);
signals:
//    void getResult(const unsigned long val);
    void ValueChanged(const QString &val);
    void UnitChanged(const QString &unit);
    void OriginalAdcChanged(const QString &unit);
    void RangeListChanged(const QStringList &);

public slots:
    void    ModeChanged(int index);
    void RangeChanged(int index);

private:


    QList<MeasureBase *> Measurementptr;
    int current_measurement_item;
};

#endif // MULTIMETERDEVICE_H

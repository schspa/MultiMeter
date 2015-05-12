#ifndef CURRENTMEASUREMENT_H
#define CURRENTMEASUREMENT_H
#include "measurebase.h"
#include <QStringList>
#include <QString>


class MultiMeterDevice;
class CurrentMeasurement : public MeasureBase
{
public:
    CurrentMeasurement(MultiMeterDevice *dev);
    ~CurrentMeasurement();
    QStringList getRangeStringList();
    QString get_name();
    void setMode(int index);
    virtual void setRange(int index);
    virtual void start();
    virtual void stop();
    virtual void RangeAdjust();
    virtual QString getResault(unsigned long val);
    virtual QString getUnits();
private:
    QStringList range_string_list;
    QStringList unit_string_list;
    double range_proportion[2]; // = {11*0.000478, 11*0.00131, 11*0.00942, 11*0.0911};
    int current_range;
    QString name;// = "Voltage";
    MultiMeterDevice *dev;

    void set_ragne_only(int index);
};

#endif // CURRENTMEASUREMENT_H

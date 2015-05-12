#ifndef VOLTAGEMEASUREMENT_H
#define VOLTAGEMEASUREMENT_H

#include "measurebase.h"
#include <QStringList>
#include <QString>


class MultiMeterDevice;
class VoltageMeasurement : virtual MeasureBase
{
public:
    VoltageMeasurement(MultiMeterDevice *dev);
    ~VoltageMeasurement();
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
    double range_proportion[4]; // = {11*0.000478, 11*0.00131, 11*0.00942, 11*0.0911};
    int current_range;
    int range_used;
    QString name;// = "Voltage";
    MultiMeterDevice *dev;

    void set_ragne_only(int index);
};

#endif // VOLTAGEMEASUREMENT_H

#ifndef MEASUREBASE_H
#define MEASUREBASE_H
class QStringList;
class QString;
class MultiMeterDevice;
/*
 * base class for all measurement kind
 *
 **/

class MeasureBase
{
public:
    MeasureBase(){;}; //VoltageMeasurement(MultiMeterDevice *dev);

    ~MeasureBase(){;};
public:
    virtual QStringList getRangeStringList() = 0;  //get units range information
    virtual QString get_name() = 0;
    virtual void setRange(int index) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void RangeAdjust() = 0;
    virtual QString getResault(unsigned long val) = 0;
    virtual QString getUnits() = 0;

};

#endif // MEASUREBASE_H

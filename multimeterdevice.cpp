#include "multimeterdevice.h"
#include "iostream"
#include "adcthread.h"
#include "measurebase.h"
#include <voltagemeasurement.h>
#include <currentmeasurement.h>
#include <stdio.h>
#ifdef USE_IMX287
#include <fcntl.h>

#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include "multimeter_ioctrl_num.h"

#define devfile "/dev/multi-meter"
#endif
MultiMeterDevice::MultiMeterDevice(QObject *parent) : QObject(parent)
{
#ifdef USE_IMX287
    std::cout<<"try to open dev "<< devfile << std::endl;
    dev_fd = ::open(devfile, O_RDONLY|O_EXCL);
    if(dev_fd == -1){
        qErrnoWarning(0, "open dev %s failed\r\n", devfile);
        std::cout<<"open dev "<< devfile << "failed" << std::endl;
        return;
    }
    std::cout<<"Open dev sucess"<< std::endl;
#else
    std::cout<<"Not Using it on target board, Only for Debug"<< std::endl;
#endif //   USE_IMX287
    adc_thread = new AdcThread(this);
    adc_thread->start();
    //VoltageMeasurement vm;
    Measurementptr.append((MeasureBase *)new VoltageMeasurement(this));
    Measurementptr.append((MeasureBase *)new CurrentMeasurement(this));

    std::cout<<"Total "<<Measurementptr.count()<<" measurement dev"<<std::endl;
//    for(int i=0; i<Measurementptr.count(); i++){
//        std::cout<<"Measurement "<<i<<" name:"<<Measurementptr.at(i)->get_name().toStdString()<<std::endl;
//    }
    current_measurement_item = 0;
    Measurementptr.at(current_measurement_item)->start();
}

MultiMeterDevice::~MultiMeterDevice()
{
    adc_thread->is_run = false;

}



void MultiMeterDevice::caculate_result(const unsigned long &val){
//    std::cout << "get result "<< val << std::endl;
    static unsigned long res = 0;
    static char buf[20];
    if(res != val){
        res = val;
        emit MultiMeterDevice::ValueChanged(Measurementptr.at(current_measurement_item)->getResault(val));
        //QString str = QString()<<(int)val;
        sprintf(buf, "%ld", val);
        emit OriginalAdcChanged(buf);
//        std::cout << "emit MultiMeterDevice::ValueChanged "<< val << std::endl;
//        emit MultiMeterDevice::getResult(res);
    }
}

unsigned long MultiMeterDevice::read_adc(){
    static unsigned long res;

#ifdef USE_IMX287
    ::read(dev_fd, &res, sizeof(res));
#else
    res++;
#endif

    return res;
}

void MultiMeterDevice::pin_ctrl(int request, int val){
#ifdef USE_IMX287
    ::ioctl(dev_fd, request, val);
#endif //USE_IMX287
}

void MultiMeterDevice::ModeChanged(int index)
{
    std::cout << "Change to mode "<< index << std::endl;
    Measurementptr.at(index)->start();
    current_measurement_item = index;
    /******/
    emit RangeListChanged(Measurementptr.at(current_measurement_item)->getRangeStringList());
    //adc_thread
}

void MultiMeterDevice::RangeChanged(int index){
    MeasureBase *base = Measurementptr.at(current_measurement_item);
    base->setRange(index);
//    Measurementptr.at(current_measurement_item)->setRange(index);
    emit UnitChanged(base->getUnits());
}

QStringList MultiMeterDevice::get_measure_dev_list(){
    QStringList sl;// = new QStringList;
    for(int i=0; i<Measurementptr.count(); i++){
       // Measurement.at(i).get_name();
        sl.append(Measurementptr.at(i)->get_name());
    }
    return sl;
}

QStringList MultiMeterDevice::getRangeStringList(){
    return Measurementptr.at(current_measurement_item)->getRangeStringList();
}

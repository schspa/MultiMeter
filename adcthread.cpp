#include "adcthread.h"
#include "iostream"
#include "multimeterdevice.h"


AdcThread::AdcThread(MultiMeterDevice *dev)
{
    this->dev = dev;
    is_run = true;

}

AdcThread::~AdcThread()
{

}

void AdcThread::run(){
    while(is_run){
        msleep(200);
        dev->caculate_result(dev->read_adc());
    }
}

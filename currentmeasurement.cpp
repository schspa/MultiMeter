#include "currentmeasurement.h"
#include "multimeterdevice.h"
#include "multimeter_ioctrl_num.h"
#include "stdio.h"
#include "iostream"
#include "proportion.h"

CurrentMeasurement::CurrentMeasurement(MultiMeterDevice *dev)
{
    this->dev = dev;
    //range_string_list = (QStringList() << "20A"<<"200mA");
    unit_string_list = (QStringList() <<"mA"<<"A");
    name = "Current";
    current_range = 0;
     //{11*0.000478, 11*0.00131, 11*0.00942, 11*0.0911}
    range_proportion[0] = 11*0.000478;
    range_proportion[1] = 11*0.00131;
}

CurrentMeasurement::~CurrentMeasurement()
{

}

QStringList CurrentMeasurement::getRangeStringList(){
    return range_string_list;
}
QString CurrentMeasurement::get_name(){
    return name;
}
/***There is no use for current measurement***/
void CurrentMeasurement::set_ragne_only(int index){
//    switch(index){
//        case 0:

//            std::cout<<"B1.C1.D1:"<<0<<0<<0<<std::endl;
//            break;
//        case 1:
//            dev->pin_ctrl(IOCTL_B1, 0);
//            dev->pin_ctrl(IOCTL_C1, 0);
//            dev->pin_ctrl(IOCTL_D1, 0);
//            std::cout<<"B1.C1.D1:"<<0<<0<<0<<std::endl;
//            break;
//        default:
//            break;
//    }
}
void CurrentMeasurement::setRange(int index){
    current_range = index;
    set_ragne_only(index);
}
void CurrentMeasurement::start(){
    dev->pin_ctrl(IOCTL_C2, 0);
    dev->pin_ctrl(IOCTL_R, 0);
    dev->pin_ctrl(IOCTL_A2, 1);
    dev->pin_ctrl(IOCTL_B2, 0);

    dev->pin_ctrl(IOCTL_B1, 0);
    dev->pin_ctrl(IOCTL_C1, 0);
    dev->pin_ctrl(IOCTL_D1, 0);
    setRange(0);

}
void CurrentMeasurement::stop(){

}

void CurrentMeasurement::RangeAdjust(){
    //for auto range adjustment;
}

QString CurrentMeasurement::getResault(unsigned long val){
    static char buf[20];
    double dd = val * GENERAL_PROPORTION;

    sprintf(buf,"%lf", dd);
    return QString(buf);

}

QString CurrentMeasurement::getUnits(){
    return unit_string_list.at(1);
}

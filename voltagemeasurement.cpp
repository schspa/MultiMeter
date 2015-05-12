#include "voltagemeasurement.h"
#include "multimeterdevice.h"
#include "multimeter_ioctrl_num.h"
#include "stdio.h"
#include "iostream"
#include "proportion.h"
VoltageMeasurement::VoltageMeasurement(MultiMeterDevice *dev)
{
    this->dev = dev;
    range_string_list = (QStringList() << "auto"<<"10000" << "1000" << "100" << "10");
    unit_string_list = (QStringList() <<"auto"<<"mV"<<"V"<<"kV");
    name = "Voltage";
    current_range = 0;
    range_used = 0;
     //{11*0.000478, 11*0.00131, 11*0.00942, 11*0.0911}
    range_proportion[0] = 11*0.000478;
    range_proportion[1] = 11*0.00131;
    range_proportion[2] = 11*0.00942;
    range_proportion[3] = 11*0.0911;
}

VoltageMeasurement::~VoltageMeasurement()
{

}

QStringList VoltageMeasurement::getRangeStringList(){
    return range_string_list;
}
QString VoltageMeasurement::get_name(){
    return name;
}
/*****/
void VoltageMeasurement::set_ragne_only(int index){
    switch(index){
        case 0:
            dev->pin_ctrl(IOCTL_B1, 0);
            dev->pin_ctrl(IOCTL_C1, 0);
            dev->pin_ctrl(IOCTL_D1, 0);
            std::cout<<"B1.C1.D1:"<<0<<0<<0<<std::endl;
            break;
        case 1:
            dev->pin_ctrl(IOCTL_B1, 0);
            dev->pin_ctrl(IOCTL_C1, 0);
            dev->pin_ctrl(IOCTL_D1, 0);
            std::cout<<"B1.C1.D1:"<<0<<0<<0<<std::endl;
            break;
        case 2:
            dev->pin_ctrl(IOCTL_B1, 0);
            dev->pin_ctrl(IOCTL_C1, 0);
            dev->pin_ctrl(IOCTL_D1, 1);
            std::cout<<"B1.C1.D1:"<<0<<0<<1<<std::endl;
            break;
        case 3:
            dev->pin_ctrl(IOCTL_B1, 0);
            dev->pin_ctrl(IOCTL_C1, 1);
            dev->pin_ctrl(IOCTL_D1, 1);
            std::cout<<"B1.C1.D1:"<<0<<1<<1<<std::endl;
            break;
        case 4:
            dev->pin_ctrl(IOCTL_B1, 1);
            dev->pin_ctrl(IOCTL_C1, 1);
            dev->pin_ctrl(IOCTL_D1, 1);
            std::cout<<"B1.C1.D1:"<<1<<1<<1<<std::endl;
            break;
        default:
            break;
    }
}
void VoltageMeasurement::setRange(int index){
    current_range = index;
    range_used = index;
    set_ragne_only(index);
}
void VoltageMeasurement::start(){
    dev->pin_ctrl(IOCTL_C2, 1);
    dev->pin_ctrl(IOCTL_R, 0);
    dev->pin_ctrl(IOCTL_A2, 1);
    dev->pin_ctrl(IOCTL_B2, 0);
    setRange(0);

}
void VoltageMeasurement::stop(){

}

void VoltageMeasurement::RangeAdjust(){
    //for auto range adjustment;
}

QString VoltageMeasurement::getResault(unsigned long val){
    static char buf[20];
    double dd = val * GENERAL_PROPORTION;
    if(current_range == 0){  // auto adjust the range..Work fine, test on 05/02/21:01
        if(val < 300){   // set the range down
            range_used++;
            if(range_used > 4)
                range_used = 4;
            set_ragne_only(range_used);
        }else if(val > 3000){
            range_used--;
            if(range_used < 1)
                range_used = 1;
            set_ragne_only(range_used);
        }
        dd = dd/range_proportion[range_used-1];
    }else if(current_range > 0){
        dd = dd/range_proportion[current_range-1];
    }
    sprintf(buf,"%.3f:%d", dd, range_used);
    return QString(buf);

}

QString VoltageMeasurement::getUnits(){
    return unit_string_list.at(1);
}

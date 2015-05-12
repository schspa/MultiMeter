#ifndef MULTIMETER_IOCTRL_NUM_H
#define MULTIMETER_IOCTRL_NUM_H
#include <linux/ioctl.h>

/*	IOCTL_NUM Define
    must be same to app header
*/

#define IOCTL_APP_TYPE 71 /*unique number to this app*/

/*read 操作，参数为通道数，取值为0～7 返回值存放在IOCTL返回值中*/
#define IOCTL_READ	_IOR(IOCTL_APP_TYPE, 3, unsigned long)
#define IOCTL_SET_DIV2	_IOW(IOCTL_APP_TYPE, 4, unsigned long)

#define IOCTL_CLR_DIV2	_IOW(IOCTL_APP_TYPE, 5, unsigned long)
/**
 * for Control Pin operation
 *
 **/
#define IOCTL_B1	_IOW(IOCTL_APP_TYPE, 6, unsigned long)
#define IOCTL_C1	_IOW(IOCTL_APP_TYPE, 7, unsigned long)
#define IOCTL_D1	_IOW(IOCTL_APP_TYPE, 8, unsigned long)
#define IOCTL_A2	_IOW(IOCTL_APP_TYPE, 9, unsigned long)
#define IOCTL_B2	_IOW(IOCTL_APP_TYPE, 10, unsigned long)
#define IOCTL_C2	_IOW(IOCTL_APP_TYPE, 11, unsigned long)
#define IOCTL_R		_IOW(IOCTL_APP_TYPE, 12, unsigned long)



#endif // MULTIMETER_IOCTRL_NUM_H


#ifndef HWHANDLER_H
#define HWHANDLER_H

#include <QThread>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTime>


#define XPAR_AXI_COMBINED_BASEADDR 0x43C40000;
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define VSO_PWM_ON_REG              44
#define VSO_PWM_PERIOD_REG          46

#define VSO_ON_MASK	               0x01
#define VSO_OFF_MASK               0x00



class hwHandler: public QThread
{
    Q_OBJECT
public:
    explicit hwHandler(QObject *parent = 0);
    int memfd;
    static void vso_on(double count);
    static void vso_off();
signals:

};
#endif // HWHANDLER_H

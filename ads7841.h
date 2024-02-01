#ifndef ADS7841_H
#define ADS7841_H

#include "hwhandler.h"

#include <QObject>
#include <QTimer>
#include <QLabel>

#include <stdint.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <vector>
#include <iostream>

//#define OUTPUT_MIN 0
//#define OUTPUT_MAX 4095
//#define PRESSURE_MIN 0
//#define PRESSURE_MAX 150


class ads7841 : public QObject
{
    Q_OBJECT
public:
    ads7841();
    ~ads7841();
    int convert(uint8_t channel);
    void initSPI();
    float val;
  //  void stabilize();


signals:
    void emitval(float val);
    void emitsample(int sample);

public slots:
    float stabilize();

private:
    QTimer *timer;
    int spi_fd;
    hwHandler h;
    double resolution = 0.000000005;

};

#endif // ADS7841_H

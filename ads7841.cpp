#include "ads7841.h"

#include <QDebug>

ads7841::ads7841()
{
    initSPI();

//    int freq=12000;
//    float j=0.5;
//    for(int i=30; i<=100; i+=j)
//    {
//        h.vso_ontime(((i / (100*freq)) / resolution));
//        h.vso_period((1/freq)/ resolution);
//        qDebug()<<"forloop";
//        stabilize();
//    }

//    for(float i=0; i<50; i+=0.05)
//    {
//        h.vso_ontime(((i / (100*12000)) / resolution));
//        h.vso_period((1/12000)/ resolution);
//        qDebug()<<i<<stabilize();
//    }


    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(stabilize()));
    timer->start(100);

}

void ads7841::initSPI()
{
    spi_fd = open("/dev/spidev2.0", O_RDWR);

    int mode;
    int bits = 8;
    int speed = 1000000;
    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_RD_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
}

ads7841::~ads7841()
{
    close(spi_fd);
}

float ads7841::stabilize()
{

    int sum = 0;

    for(int i=0; i<1000; i++)
    {
        sum += (int)convert(0xD7);
    }

    int avg = (sum/1000) - 40;

    val = avg * 0.17;
 //   qDebug()<<"Vaccum"<<val<<avg;


    //val = avg * 0.0236;
    //qDebug()<<"Pressure"<<val;


    emit emitval(val);

    emit emitsample(avg);

    return val;

}


int ads7841::convert(uint8_t channel)
{
    uint8_t tx[3] = {channel, 0x00, 0x00};
    uint8_t rx[3] = {0x00, 0x00, 0x00};
    uint16_t sample = 0;
    uint16_t delay = 0;
    uint8_t bits = 8;
    uint32_t speed = 1000000;

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 3,
        .speed_hz = speed,
        .delay_usecs = delay,
        .bits_per_word = bits,
    };

    /* send the cmd to start the conversion and read the result */
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);

    sample =  (rx[2] + (rx[1] << 8)) >> 3;

    //qDebug()<<"sample"<<sample;

    return sample;
}


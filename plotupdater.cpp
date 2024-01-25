#include "plotupdater.h"

#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QProcess>

#include <stdint.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <vector>
#include <iostream>

PlotUpdater::PlotUpdater(QwtPlotCurve *curve, QwtPlot *plot) : curve(curve), plot(plot) {

    initSPI();

    // Create a timer to update the plot every 1000 milliseconds
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
    timer->start(30); // milliseconds
}

void PlotUpdater::initSPI()
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

PlotUpdater::~PlotUpdater()
{
    close(spi_fd);
}

void PlotUpdater::updatePlot() {
    // Update curve data
    const int numPoints = 10000;
    QVector<double> xData(numPoints);
    QVector<double> yData(numPoints);

    for (int i = 0; i < numPoints; ++i) {
        xData[i] = i;
        yData[i] = stabilize();
        //qDebug() << xData[i] << " " << yData[i];
    }


    // Set new data for the curve
    curve->setSamples(xData, yData);

    // Replot the plot
    plot->replot();


}

float PlotUpdater::stabilize()
{
    int sum = 0;
    for(int i=0; i<1000; i++)
    {
        sum += (int)convert(0xA7);
    }
    qDebug()<<"Vaccum"<<sum/1000;
    return sum/1000;

}

float PlotUpdater::convert(uint8_t channel)
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
        .len = 2,
        .speed_hz = speed,
        .delay_usecs = delay,
        .bits_per_word = bits,
    };

    /* send the cmd to start the conversion and read the result */
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);

    sample =  (rx[2] + (rx[1] << 8)) >> 3;

    float pressure = ((sample - OUTPUT_MIN) * (PRESSURE_MAX - PRESSURE_MIN) / (OUTPUT_MAX - OUTPUT_MIN) + PRESSURE_MIN);

    return pressure;
}

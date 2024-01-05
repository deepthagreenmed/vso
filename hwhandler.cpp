#include "hwhandler.h"
#include <QDebug>

void *mapped_base, *mapped_dev_base;
off_t dev_base = XPAR_AXI_COMBINED_BASEADDR;



hwHandler::hwHandler(QObject *parent):
    QThread(parent)
{

    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd == -1) {
        //        printf("Can't open /dev/mem.\n");
        exit(0);
    }
    mapped_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, dev_base & ~MAP_MASK);
    if (mapped_base == (void *) -1) {
        //        printf("Can't map the memory to user space.\n");
        exit(0);
    }

        mapped_dev_base = mapped_base + (dev_base & MAP_MASK);
}


void hwHandler::vso_ontime(double ontime)
{
    qDebug()<<ontime;

    *((uint16_t *) (mapped_dev_base  + VSO_PWM_ON_REG ))   = (uint16_t)(ontime);
}

void hwHandler::vso_period(double count)
{
    qDebug()<<count;

    *((uint16_t *) (mapped_dev_base  + VSO_PWM_PERIOD_REG ))    = (uint16_t)(count);
}



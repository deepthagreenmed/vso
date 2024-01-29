#ifndef PLOTUPDATER2_H
#define PLOTUPDATER2_H

#include <QObject>
#include <QVector>
#include <QLabel>

class PlotUpdater2 : public QObject
{
    Q_OBJECT
public:
    PlotUpdater2();
    ~PlotUpdater2();
    int convert(uint8_t channel);
    float pressure;
    int stabilize();
    void initSPI();

public slots:
   // void updatePlot();

private:
   // QwtPlotCurve *curve;
  //  QwtPlot *plot;
    QTimer *timer;
    int spi_fd;


};

#endif // PLOTUPDATER_H

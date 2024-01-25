#ifndef PLOTUPDATER_H
#define PLOTUPDATER_H

#include <QObject>
#include <QVector>
#include <QLabel>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>


#define OUTPUT_MIN 0
#define OUTPUT_MAX 4095
#define PRESSURE_MIN 0       // min is 0 for sensors that give absolute values
#define PRESSURE_MAX 150    // in psi

class PlotUpdater : public QObject
{
    Q_OBJECT
public:
    PlotUpdater(QwtPlotCurve *curve, QwtPlot *plot);
    ~PlotUpdater();
    float convert(uint8_t channel);
    float pressure;
    float stabilize();
    void initSPI();

public slots:
    void updatePlot();

private:
    QwtPlotCurve *curve;
    QwtPlot *plot;
    QTimer *timer;
    int spi_fd;


};

#endif // PLOTUPDATER_H

#ifndef PLOTUPDATER2_H
#define PLOTUPDATER2_H

#include <QObject>
#include <QVector>
#include <QLabel>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class PlotUpdater2 : public QObject
{
    Q_OBJECT
public:
    PlotUpdater2(QwtPlotCurve *curve, QwtPlot *plot);
    ~PlotUpdater2();
    double convert();
    float pressure;

public slots:
    void updatePlot();

private:
    QwtPlotCurve *curve;
    QwtPlot *plot;
    QTimer *timer;
    int spi_fd;


};

#endif // PLOTUPDATER_H

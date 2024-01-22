#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    key = new keypad;

    layout = new QVBoxLayout;

    plot = new QwtPlot;
    plot2 = new QwtPlot;

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette(Qt::white);
    plot->setCanvas(canvas);
    plot2->setCanvas(canvas);

    layout->addWidget(plot);
    layout->addWidget(plot2);
//    layout->addWidget(key);

    curve = new QwtPlotCurve("Pressure Graph");

    QColor color(Qt::green);
    curve->setStyle(QwtPlotCurve::Lines);
    curve->setPen(QPen(color, 2));

    curve->attach(plot);

    curve2 = new QwtPlotCurve("Vaccum Graph");

    curve2->setStyle(QwtPlotCurve::Lines);
    curve2->setPen(QPen(color, 2));

    curve2->attach(plot2);


    // Set the range and scale of the x-axis
    plot->setAxisScale(QwtPlot::xBottom, 0, 1000, 50);

    // Set the range and scale of the y-axis
    plot->setAxisScale(QwtPlot::yLeft, 0, 20, 1);

    // Redraw the plot with the updated axis limits
    plot->replot();

    // Set the range and scale of the x-axis
    plot2->setAxisScale(QwtPlot::xBottom, 0, 1000, 50);

    // Set the range and scale of the y-axis
    plot2->setAxisScale(QwtPlot::yLeft, 0, 500, 10);

    // Redraw the plot with the updated axis limits
    plot2->replot();

    QwtPlot::Axis axis = QwtPlot::xBottom;
    QwtScaleWidget *sw = plot->axisWidget(axis);
    sw->setPalette(Qt::green);

    QwtPlot::Axis axis2 = QwtPlot::yLeft;
    QwtScaleWidget *sw2 = plot->axisWidget(axis2);
    sw2->setPalette(Qt::green);
    \
    QwtScaleWidget *sw3 = plot2->axisWidget(axis);
    sw3->setPalette(Qt::green);

    QwtScaleWidget *sw4 = plot2->axisWidget(axis2);
    sw4->setPalette(Qt::green);


//    // Create an object to handle dynamic updates of the plot
//    PlotUpdater plotUpdater(curve, plot);
//    PlotUpdater2 plotUpdater2(curve2, plot2);

    inc_ontime_btn = new QPushButton("increase duty cycle", this);
    inc_ontime_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(inc_ontime_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    dec_ontime_btn = new QPushButton("decrease duty cycle", this);
    dec_ontime_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(dec_ontime_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    inc_freq_btn = new QPushButton("increase frequency", this);
    connect(inc_freq_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);
    inc_freq_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    dec_freq_btn = new QPushButton("decrease frequency", this);
    connect(dec_freq_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);
    dec_freq_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    lineEdit = new QLineEdit(QString::number(timeon));
    QPalette palette = lineEdit->palette();
    palette.setColor(QPalette::WindowText, Qt::blue);
    lineEdit->setPalette(palette);

    lineEdit_2 = new QLineEdit(QString::number(freq));
    QPalette palette2 = lineEdit_2->palette();
    palette2.setColor(QPalette::WindowText, Qt::blue);
    lineEdit_2->setPalette(palette2);

    lineEdit_2->installEventFilter(this);
    lineEdit->installEventFilter(this);

    connect(key, &keypad::textsignal, this, &MainWindow::on_clicked);
    connect(key, &keypad::backsignal, this, &MainWindow::on_clickedbackspace);
    connect(key, &keypad::entersignal, this, &MainWindow::on_clickedenter);

    lineEdit->clearFocus();
    lineEdit_2->clearFocus();

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));
   // h.vso_ontime(400);
   // h.vso_period(20000);

    period = 1/freq * 1000000;
    label = new QLabel(QString::number(period));
    QPalette palette3 = label->palette();
    palette3.setColor(QPalette::WindowText, Qt::blue);
    label->setPalette(palette3);

    layout2 = new QHBoxLayout;

    // Add buttons
    layout2->addWidget(inc_ontime_btn);
    layout2->addWidget(dec_ontime_btn);
    layout2->addWidget(inc_freq_btn);
    layout2->addWidget(dec_freq_btn);

    layout2->addWidget(lineEdit);
    layout2->addWidget(lineEdit_2);
    layout2->addWidget(label);

//    QWidget *subWidget = new QWidget;
//    subWidget->setLayout(layout2);
//    layout->addWidget(subWidget);




}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == lineEdit_2 && event->type() == QEvent::MouseButtonPress)
    {
        lineEdit_2->setFocus();
        key->move(800,10);
        key->show();

    }

    if (obj == lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        lineEdit->setFocus();
        key->move(800,10);
        key->show();

    }

    return false;

}

void MainWindow::on_pushButton_clicked()
{
    timeon = timeon + 0.1;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

}

void MainWindow::on_pushButton_2_clicked()
{
    timeon = timeon - 0.1;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    label->setText(QString::number(period));

}

void MainWindow::on_pushButton_6_clicked()
{
    freq = freq - 100;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    label->setText(QString::number(period));

}

void MainWindow::on_pushButton_5_clicked()
{
    freq = freq + 100;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    label->setText(QString::number(period));

}

void MainWindow::on_clicked(const QString& digit)
{
    bool ok;
    bool ok2;
    if(lineEdit->focusWidget()) {
        lineEdit_2->clearFocus();
        if(!flag)
        {
        lineEdit->setFocus();
        lineEdit->insert(digit);

     }
    }

      if(lineEdit_2->focusWidget())
      {
         lineEdit->clearFocus();
          flag=false;
          if(!flag)
          {
            lineEdit_2->setFocus();
            lineEdit_2->insert(digit);

          }
      }


    timeon = lineEdit->text().toDouble(&ok);
    freq = lineEdit_2->text().toDouble(&ok2);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    label->setText(QString::number(period));

}

void MainWindow::on_clickedbackspace()
{
    bool ok;
    bool ok2;
    if (lineEdit->focusWidget())
    {

        QString data = lineEdit->text();
        data.chop(1);
        lineEdit->setText(data);


    }
    if(lineEdit_2->focusWidget())
    {

        QString data = lineEdit_2->text();
        data.chop(1);
        lineEdit_2->setText(data);

    }

    timeon = lineEdit->text().toDouble(&ok);
    freq = lineEdit_2->text().toDouble(&ok2);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    label->setText(QString::number(period));

}

void MainWindow::on_clickedenter()
{
    key->hide();

    lineEdit->clearFocus();
    lineEdit_2->clearFocus();

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    label->setText(QString::number(period));


}

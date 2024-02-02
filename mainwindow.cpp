#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    key = new keypad;

    adc = new ads7841;

    connect(adc, &ads7841::emitval, this, &MainWindow::printval);

    connect(adc, &ads7841::emitsample, this, &MainWindow::printsample);


    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit->installEventFilter(this);

    connect(key, &keypad::textsignal, this, &MainWindow::on_clicked);
    connect(key, &keypad::backsignal, this, &MainWindow::on_clickedbackspace);
    connect(key, &keypad::entersignal, this, &MainWindow::on_clickedenter);

    ui->lineEdit->clearFocus();
    ui->lineEdit_2->clearFocus();

//    timeon=0;
//    freq=65536;
//    h.vso_ontime(((timeon / (100*freq)) / resolution));
//    h.vso_period((1/freq)/ resolution);

   // h.vso_ontime(400);
   // h.vso_period(20000);

    ui->lineEdit->setText("duty cycle: " + QString::number(timeon));
    ui->lineEdit_2->setText("frequency: " + QString::number(freq));
    ui->label->setText("period: " + QString::number(period));

  //  script();

    //ui->label_2->setText(QString::number(adc->val));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printval(float val)
{
    ui->label_2->setText("VACCUM: " + QString::number(val));
}

void MainWindow::printsample(int sample)
{
    ui->label_3->setText(QString::number(sample));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == ui->lineEdit_2 && event->type() == QEvent::MouseButtonPress)
    {
        ui->lineEdit_2->setFocus();
        key->move(800,600);
        key->show();

    }

    if (obj == ui->lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        ui->lineEdit->setFocus();
        key->move(800,600);
        key->show();

    }

    return false;

}

void MainWindow::on_pushButton_clicked()
{
    timeon=0;
    freq=65536;
    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period((1/freq) / resolution);

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));
    //ui->label_2->setText(QString::number(adc->val));

}

void MainWindow::on_pushButton_2_clicked()
{
    timeon = timeon + 0.05;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));
   // ui->label_2->setText(QString::number(adc->val));

}

void MainWindow::on_pushButton_3_clicked()
{
    timeon = timeon - 0.05;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    ui->label->setText(QString::number(period));
    //ui->label_2->setText(QString::number(adc->val));
}

void MainWindow::on_pushButton_4_clicked()
{
    timeon = timeon + 2;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));
   // ui->label_2->setText(QString::number(adc->val));

//    freq = freq + 100;

//    h.vso_ontime(((timeon / (100*freq)) / resolution));
//    h.vso_period(((1 / freq) / resolution));

//    ui->lineEdit->setText(QString::number(timeon));
//    ui->lineEdit_2->setText(QString::number(freq));

//    period = 1/freq * 1000000;
//    ui->label->setText(QString::number(period));
//    //ui->label_2->setText(QString::number(adc->val));
}

void MainWindow::on_pushButton_5_clicked()
{
    timeon = timeon - 2;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    ui->label->setText(QString::number(period));
    //ui->label_2->setText(QString::number(adc->val));

//    freq = freq - 100;

//  h.vso_ontime(((timeon / (100*freq)) / resolution));
//    h.vso_period(((1 / freq) / resolution));

//    ui->lineEdit->setText(QString::number(timeon));
//    ui->lineEdit_2->setText(QString::number(freq));

//    period = 1/freq * 1000000;
//    ui->label->setText(QString::number(period));
//    //ui->label_2->setText(QString::number(adc->val));
}

void MainWindow::on_clicked(const QString& digit)
{
    bool ok;
    bool ok2;
    if(ui->lineEdit->focusWidget()) {
        ui->lineEdit_2->clearFocus();
        if(!flag)
        {
        ui->lineEdit->setFocus();
        ui->lineEdit->insert(digit);

     }
    }

      if(ui->lineEdit_2->focusWidget())
      {
         ui->lineEdit->clearFocus();
          flag=false;
          if(!flag)
          {
            ui->lineEdit_2->setFocus();
            ui->lineEdit_2->insert(digit);

          }
      }


    timeon = ui->lineEdit->text().toDouble(&ok);
    freq = ui->lineEdit_2->text().toDouble(&ok2);

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    ui->label->setText(QString::number(period));
   // ui->label_2->setText(QString::number(adc->val));
}

void MainWindow::on_clickedbackspace()
{
    bool ok;
    bool ok2;
    if (ui->lineEdit->focusWidget())
    {

        QString data = ui->lineEdit->text();
        data.chop(1);
        ui->lineEdit->setText(data);


    }
    if(ui->lineEdit_2->focusWidget())
    {

        QString data = ui->lineEdit_2->text();
        data.chop(1);
        ui->lineEdit_2->setText(data);

    }

    timeon = ui->lineEdit->text().toDouble(&ok);
    freq = ui->lineEdit_2->text().toDouble(&ok2);

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    ui->label->setText(QString::number(period));
    //ui->label_2->setText(QString::number(adc->val));
}

void MainWindow::on_clickedenter()
{
    key->hide();

    ui->lineEdit->clearFocus();
    ui->lineEdit_2->clearFocus();

   h.vso_ontime(((timeon / (100*freq)) / resolution));
   h.vso_period(((1 / freq) / resolution));

    ui->lineEdit->setText(QString::number(timeon));
    ui->lineEdit_2->setText(QString::number(freq));

    period = 1/freq * 1000000;
    ui->label->setText(QString::number(period));
    //ui->label_2->setText(QString::number(adc->val));

}

void MainWindow::script()
{
    adc->initSPI();

    float freq = 12000;

    for(float i=30; i<100; i+=0.1)
    {
        h.vso_ontime(((i / (100*freq)) / resolution));
        h.vso_period((1/freq)/ resolution);
        qDebug()<<i<<adc->stabilize();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    script();
}

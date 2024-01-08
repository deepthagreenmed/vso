#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    key = new keypad;

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
    timeon=timeon+5;

    h.vso_ontime(((timeon / (100*freq)) / resolution));
    h.vso_period(((1 / freq) / resolution));

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(freq));

}

void MainWindow::on_pushButton_2_clicked()
{
    timeon=timeon-5;

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

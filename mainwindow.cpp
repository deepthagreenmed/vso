#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    key = new keypad;

    inc_ontime_btn = new QPushButton("increase on time", this);
    inc_ontime_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(inc_ontime_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    dec_ontime_btn = new QPushButton("decrease on time", this);
    dec_ontime_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(dec_ontime_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    inc_period_btn = new QPushButton("increase period", this);
    connect(inc_period_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);
    inc_period_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    dec_period_btn = new QPushButton("decrease period", this);
    connect(dec_period_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);
    dec_period_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    lineEdit = new QLineEdit(QString::number(timeon));
    QPalette palette = lineEdit->palette();
    palette.setColor(QPalette::WindowText, Qt::blue);
    lineEdit->setPalette(palette);

    lineEdit_2 = new QLineEdit(QString::number(period));
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
    timeon=timeon+1;
    h.vso_ontime(timeon);
    h.vso_period(period);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));

}

void MainWindow::on_pushButton_2_clicked()
{
    timeon=timeon-1;
    h.vso_ontime(timeon);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));

}

void MainWindow::on_pushButton_5_clicked()
{
//    if(period > 0.083)
//    {
//       period = period - 0.117;
//    }

    period=period+100;
    h.vso_ontime(timeon);
    h.vso_period(period);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));

}

void MainWindow::on_pushButton_6_clicked()
{
//    if(period < 0.2)
//    {
//        period = period + 0.117;
//    }

    period=period-100;
    h.vso_ontime(timeon);
    h.vso_period(period);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));

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
    period = lineEdit_2->text().toDouble(&ok2);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));

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
    period = lineEdit_2->text().toDouble(&ok2);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));

}

void MainWindow::on_clickedenter()
{
    key->hide();

    lineEdit->clearFocus();
    lineEdit_2->clearFocus();

    h.vso_ontime(timeon);
    h.vso_period(period);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));


}

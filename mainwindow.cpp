#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    key = new keypad;

    on_btn = new QPushButton("ON", this);
    on_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(on_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    off_btn = new QPushButton("OFF", this);
    off_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(off_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    inc_period_btn = new QPushButton("increase period", this);
    connect(inc_period_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);
    inc_period_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    dec_period_btn = new QPushButton("decrease period", this);
    connect(dec_period_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);
    dec_period_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    lineEdit = new QLineEdit(QString::number(period));
    QPalette palette = lineEdit->palette();
    palette.setColor(QPalette::WindowText, Qt::blue);
    lineEdit->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    h.vso_on(period);
}

void MainWindow::on_pushButton_2_clicked()
{
    h.vso_off();
}

void MainWindow::on_pushButton_5_clicked()
{
    if(period > 0.083)
    {
       period = period - 0.117;
    }

    qDebug()<<period;
}

void MainWindow::on_pushButton_6_clicked()
{
    if(period < 0.2)
    {
        period = period + 0.117;
    }

    qDebug()<<period;

}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hwhandler.h"
#include "keypad.h"
#include "ads7841.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QtWidgets>
#include <QGridLayout>
#include <QTimer>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject* object, QEvent* event);

    double timeon = 10;
    double freq = 8000;

    double period;

    QLabel *label;

    QVBoxLayout *layout;
    QHBoxLayout *layout2;

    keypad *key;


public slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_clicked(const QString& digit);

     void on_clickedbackspace();

     void on_clickedenter();

     void printval(float val);

     void printsample(int sample);

private slots:


private:
    Ui::MainWindow *ui;
    hwHandler h;
    bool flag = false;
    double resolution = 0.000000005;
    ads7841 *adc;


};
#endif // MAINWINDOW_H

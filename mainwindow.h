#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "hwhandler.h"
#include "keypad.h"

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPushButton *on_btn;
    QPushButton *off_btn;

    QPushButton *inc_period_btn;
    QPushButton *dec_period_btn;

    QLineEdit *lineEdit;

    double period;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    hwHandler h;
    keypad *key;

};
#endif // MAINWINDOW_H

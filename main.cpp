#include "mainwindow.h"
#include "keypad.h"
#include "plotupdater.h"
#include "plotupdater2.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // Create a main window
    QWidget mainWindow;
    MainWindow window;

    PlotUpdater* p = new PlotUpdater(window.curve, window.plot);
    PlotUpdater2* p2 = new PlotUpdater2(window.curve2, window.plot2);


    // Create the QGridLayout
    QGridLayout gridLayout;


    // Add the QHBoxLayout and QVBoxLayout to the QGridLayout
    gridLayout.addLayout(window.layout, 0, 0);
    gridLayout.addLayout(window.layout2, 1, 0);

    QLabel psi;
    psi.setText("Pressure:" + QString::number(p->pressure));
    psi.show();

    QLabel mmhg;
    mmhg.setText("Vaccum:" + QString::number(p2->pressure));
    mmhg.show();

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(&psi);
    layout3->addWidget(&mmhg);

    gridLayout.addLayout(layout3, 2, 0);


    // Create a separate thread for handling plot updates
    QThread* updateThread = new QThread();



    // Move the plot updater object to the update thread
    p->moveToThread(updateThread);
    p2->moveToThread(updateThread);

    // Start the update thread
    updateThread->start();

    // Clean up the thread and plot updater object when done
//    updateThread->quit();
//    updateThread->wait();

//    delete p;
//    delete p2;


    // Set the QGridLayout as the layout for the main window
    mainWindow.setLayout(&gridLayout);

    // Show the main window
    mainWindow.show();

   // window.show();

    // Enter the application main loop
    return app.exec();
}




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

    // Create the QGridLayout
    QGridLayout gridLayout;

    // Add the QHBoxLayout and QVBoxLayout to the QGridLayout
    gridLayout.addLayout(window.layout, 0, 0);
    gridLayout.addLayout(window.layout2, 1, 0);

    // Create an object to handle dynamic updates of the plot
    PlotUpdater plotUpdater(window.curve, window.plot);
    PlotUpdater2 plotUpdater2(window.curve2, window.plot2);

    // Set the QGridLayout as the layout for the main window
    mainWindow.setLayout(&gridLayout);

    // Show the main window
    mainWindow.show();

   // window.show();

    // Enter the application main loop
    return app.exec();
}




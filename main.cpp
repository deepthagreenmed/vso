#include "mainwindow.h"
#include "keypad.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    // Enter the application main loop
    return app.exec();
}




#include <QApplication>
#include "MainWindow.hpp" // Make sure this path matches the location of your MainWindow class

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow; // Create an instance of MainWindow
    mainWindow.show();     // Show the main window

    return app.exec(); // Enter the Qt event loop
}

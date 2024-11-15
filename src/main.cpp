#include "main_window/mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Initializing MainWindow to be the entry point of app
    MainWindow w;
    w.show();

    return QApplication::exec();
}

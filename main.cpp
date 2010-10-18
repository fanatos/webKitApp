#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("test1");
    app.setApplicationName("test2");

    MainWindow w;
    w.show();

    return app.exec();
}

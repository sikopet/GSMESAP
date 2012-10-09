#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("GSMESAP");
    QCoreApplication::setApplicationName("GSMESAP");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}

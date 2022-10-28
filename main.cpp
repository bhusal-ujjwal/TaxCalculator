#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QCoreApplication::setOrganizationName("UTB");
    QCoreApplication::organizationDomain();
    QCoreApplication::setApplicationName("TAXER");

    w.show();
    return a.exec();
}

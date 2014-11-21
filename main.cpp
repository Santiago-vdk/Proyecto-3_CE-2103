#include "GUI.h"
#include <QApplication>
#include "iostream"
#include <mainwindow.h>


using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // GUI w;
    // w.show();
    MainWindow w;
    w.show();
    return a.exec();
}

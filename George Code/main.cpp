// C/C++ Libraries
#include <iostream>

// Qt Libraries
#include "mainwindow.h"
#include <QApplication>


using namespace std;


int main(int argc, char *argv[])
{
    cout << "----------------------------------------" << endl;
    cout << "-----   Segmentation Application   -----" << endl;
    cout << "----------------------------------------" << endl;

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}

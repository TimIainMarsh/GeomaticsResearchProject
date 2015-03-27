#include <iostream>

#include <QCoreApplication>

#include "fileops.h"
#include "pointcreator.h"
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Start" << endl;
//    QString filename = "random_points.csv";

//    FileOps fo;
//    fo.ReadFile(filename);

    PointCreator PC;
    int aNumber = PC.ValueReturn();

    cout <<"A Number " << aNumber << endl;

    return a.exec();
}


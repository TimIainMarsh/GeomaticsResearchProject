#include "fileops.h"

#include <iostream>

#include <QFile>

#include <QList>

FileOps::FileOps()
{
}

void FileOps::ReadFile(QString path)
{

    QList<QString> points;

    std::cout << "start of fileOps" << std::endl;
    std::cout << "Path: " << path.toStdString() << std::endl;

    QFile data(path);

    if (data.open(QFile::ReadOnly))
    {
        QTextStream in(&data);
        QString line;
//        std::cout << "" << std::endl;

        do
        {

            line = in.readLine();
            if(!line.isNull())
            {



                QStringList pieces = line.split( ", " );
                QString X = pieces.value(0);
                QString Y = pieces.value(1);
//                std::cout << "X: " << X.toStdString() << "  Y: " << X.toStdString() << std::endl;

            }

        }while (!line.isNull());



    }

}



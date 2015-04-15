#include <QCoreApplication>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>


using namespace std;

int globalVariable;

double* child()
{
    double* pdLocalVar = new double;
    return pdLocalVar;
}

void displayArray(char charArr[], int ArrSize)
{


    char* pntr = charArr;
    for (int i = 0; i<ArrSize ; i++, pntr++)
    {
        cout << i << ": "<< *pntr << endl;
    }

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Start" << endl;

    char* szString = "Randy";
    cout << "String is : "<< szString << endl;

    char* pszString = szString;

    while(*pszString)
    {
        cout << *pszString++;

    }
    cout << endl;












    cout << "End" << endl;
    return a.exec();
}

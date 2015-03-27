#ifndef POINTCREATOR_H
#define POINTCREATOR_H
#include <string>
class PointCreator
{
public:
    PointCreator();


    int ValueReturn(){return value;}

    void setValue(int newValue){value = newValue;}


    private:
        int value;


}




#endif // POINTCREATOR_H

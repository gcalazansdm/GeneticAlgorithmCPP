//
// Created by root on 15/09/2019.
//

#ifndef UNTITLED_CITY_H
#define UNTITLED_CITY_H


class City {
private:
    float x;
    float y;
public:
    City(float x_,float y_):x(x_),y(y_){}

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }
};


#endif //UNTITLED_CITY_H

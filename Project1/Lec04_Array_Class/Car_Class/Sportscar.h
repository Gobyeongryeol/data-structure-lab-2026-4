#pragma once
#include "Car.h"

class Sportscar : public Car {
public:
    bool bTurbo;

    Sportscar(int s, const char* n, int g, bool t)
        : Car(s, n, g) {
        bTurbo = t;
    }

    void setTurbo(bool bTur) {
        bTurbo = bTur;
    }

    void speedUp() {
        if (bTurbo)
            speed += 20;
        else
            Car::speedUp();
    }
};
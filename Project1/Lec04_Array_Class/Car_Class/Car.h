#pragma once
#include <stdio.h>
#include <cstring>

class Car {
protected:
    int speed;
    char name[40];

public:
    int gear;

    // 기본 생성자
    Car() {
        speed = 0;
        gear = 0;
        strcpy_s(name, "None");
    }

    // 생성자
    Car(int s, const char* n, int g)
        : speed(s), gear(g) {
        strcpy_s(name, n);
    }

    void changeGear(int g = 4) {
        gear = g;
    }

    void speedUp() {
        speed += 5;
    }

    void display() {
        printf("[%s] : Gear = %d, Speed = %d km/h\n", name, gear, speed);
    }

    void whereAmI() {
        printf("Object Address = %p\n", this);
    }
};
#include "Sportscar.h"
#include<stdio.h>

int main() {
    Sportscar s(50, "Ferrari", 3, true);

    printf("Initial State\n");
    s.display();

    printf("Accelerate\n");
    s.speedUp();
    s.display();

    printf("Accelerate without Turbo\n");
    s.setTurbo(false);
    s.speedUp();
    s.display();

    return 0;
}
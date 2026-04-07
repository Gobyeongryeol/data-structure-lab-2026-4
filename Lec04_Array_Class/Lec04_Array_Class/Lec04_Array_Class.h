#pragma once
#include <iostream>
using namespace std;

#define HEIGHT 8
#define WIDTH 8

class ArrayMax {
private:
    int image[HEIGHT][WIDTH];  

public:
    // 생성자
    ArrayMax(int a [HEIGHT][WIDTH]) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                image[i][j] = a [i][j];
            }
        }
    }

    int getArrayMax() {
        int max = image[0][0];

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (image[i][j] > max) {
                    max = image[i][j];
                }
            }
        }
        return max;
    }
};
#pragma once

#include "Duck.h"
#include <random>

float Duck::generateRandomDuckAngle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(10, 170);

    int x = distr(gen);

    if (x >= 80 && x <= 100) x = x / 2;

    return x * M_PI / 180;
}

// We generate a starting position between start and end.
int Duck::generateRandomDuckStartingPosition(int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(start, end);

    int x = distr(gen);

    return x;
}
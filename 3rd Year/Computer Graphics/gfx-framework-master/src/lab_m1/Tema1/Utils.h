#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

// Basic punction for power of a number
float pow(float x) {
    return x * x;
}

float checkPlayerNearby(float coordinate, int resolution, float circleCoord, int index) {

    // Compute a base case for coordinates
    if (index % 2 == 0) {
        coordinate = 4.f * (rand() % resolution);
    }
    else {
        coordinate = -4.f * (rand() % resolution);
    }

    // If they are too close to the player, reroll the coordinates
    while (abs(coordinate - circleCoord) <= 200) {
        if (index % 2 == 0) {
            coordinate = 4.f * (rand() % resolution);
        }
        else {
            coordinate = -4.f * (rand() % resolution);
        }
    }

    return coordinate;
}

float checkPlayerNearbyPow(float coordinate, int resolution, float circleCoord, int index) {

    // Compute a base case for coordinates
    if (index % 2 == 0) {
        coordinate = 4.f * (rand() % resolution * 2.f);
    }
    else {
        coordinate = -4.f * (rand() % resolution * 2.f);
    }

    // If they are too close to the player, reroll the coordinates
    while (abs(coordinate - circleCoord) <= 200) {
        if (index % 2 == 0) {
            coordinate = 4.f * (rand() % resolution * 2.f);
        }
        else {
            coordinate = -4.f * (rand() % resolution * 2.f);
        }
    }

    return coordinate;
}

float deleteElement(float arr[], float n, float index)
{
    // Search index in array
    float i;
    for (i = 0; i < n; i++)
        if (i == index)
            break;

    // If x found in array
    if (i < n)
    {
        // reduce size of array and move all
        // elements on space ahead
        n = n - 1;
        for (int j = i; j < n; j++)
            arr[j] = arr[j + 1];
    }

    return n;
}

double deleteRadians(double arr[], float n, float index)
{
    // Search index in array
    float i;
    for (i = 0; i < n; i++)
        if (i == index)
            break;

    // If x found in array
    if (i < n)
    {
        // reduce size of array and move all
        // elements on space ahead
        n = n - 1;
        for (int j = i; j < n; j++)
            arr[j] = arr[j + 1];
    }

    return n;
}

int deleteChance(int arr[], float n, float index)
{
    // Search index in array
    float i;
    for (i = 0; i < n; i++)
        if (i == index)
            break;

    // If x found in array
    if (i < n)
    {
        // reduce size of array and move all
        // elements on space ahead
        n = n - 1;
        for (int j = i; j < n; j++)
            arr[j] = arr[j + 1];
    }

    return n;
}

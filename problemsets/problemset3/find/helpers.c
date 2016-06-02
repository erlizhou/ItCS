/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
        return false;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (values[mid] == value)
            return true;
        else if (values[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && values[j - 1] > values[j]) {
            int temp = values[j];
            values[j] = values[j - 1];
            values[j - 1] = temp;
            j--;
        }
    }
}

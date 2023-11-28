/*
 * Name: Mac Howe
 * Date Submitted: 10/2/23
 * Lab Section: 2
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>

// Implements linear search algorithm to find a target value in a vector.
template <class T>
int linearSearch(std::vector<T> data, T target)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i] == target)
        {
            return i;
        }
    }
    return -1;
}

// Implements binary search algorithm to find a target value in a sorted vector.
template <class T>
int binarySearch(std::vector<T> data, T target)
{
    int lowI = 0, midI;
    int highI = data.size() - 1;
    while (lowI != highI)
    {
        midI = (lowI + highI) / 2;
        if (target == data[midI])
        {
            return midI;
        }
        else if (target > data[midI])
        {
            lowI = midI + 1;
        }
        else
        {
            highI = midI - 1;
        }
    }
    midI = lowI;
    if (target == data[midI])
        return midI;
    else
        return -1;
}

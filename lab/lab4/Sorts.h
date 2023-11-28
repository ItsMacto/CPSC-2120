/*
 * Name: Mac Howe
 * Date Submitted: 10/2/23
 * Lab Section: 2
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>
#include <cstdlib>


//Implements the merge sort algorithm on a vector of elements.
template <class T>
std::vector<T> mergeSort(std::vector<T> lst)
{
    // Base case
    if (lst.size() <= 1)
    {
        return lst;
    }

    std::vector<T> left = std::vector<T>(lst.begin(), lst.begin()+lst.size()/2);
    std::vector<T> right = std::vector<T>(lst.begin() + lst.size()/2,lst.end());

    left = mergeSort(left);
    right = mergeSort(right);

    std::vector<T> sorted;

    int l = 0;
    int r = 0;
    while (l < left.size() && r < right.size())
    {
        if (left[l] <= right[r])
        {
            sorted.push_back(left[l]);
            l++;
        }
        else
        {
            sorted.push_back(right[r]);
            r++;
        }
    }

    while (l < left.size())
    {
        sorted.push_back(left[l]);
        l++;
    }

    while (r < right.size())
    {
        sorted.push_back(right[r]);
        r++;
    }

    return sorted;
}


//Implements the quicksort algorithm on a vector of elements.
template <class T>
std::vector<T> quickSort(std::vector<T> lst)
{
    // Base case
    if (lst.size() <= 1)
    {
        return lst;
    }

    int pivotI = rand() % lst.size();
    T pivotV = lst[pivotI];
    std::swap(lst[0], lst[pivotI]);
    pivotI = 0;
    for (int i = 1; i < lst.size(); i++)
    {
        if (lst[i] < pivotV)
        {
            pivotI++;
            std::swap(lst[i], lst[pivotI]);
        }
    }
    std::swap(lst[0], lst[pivotI]);

    std::vector<T> left = std::vector<T>(lst.begin(), lst.begin() + pivotI);
    std::vector<T> right = std::vector<T>(lst.begin() + pivotI + 1, lst.end());

    // Recursively sort the two parts
    left = quickSort(left);
    right = quickSort(right);

    // Merge and return the sorted list
    left.push_back(pivotV);
    left.insert(left.end(), right.begin(), right.end());

    return left;
}

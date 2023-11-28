// Mac Howe Pmhowe@clemson.edu
// Nov 27 2023

#include "minHeap.h"

void minHeap::insert(int value)
{
    heap.push_back(value);
    siftUp(heap.size() - 1);
}

int minHeap::removeMin()
{
    int min = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    siftDown(0);
    return min;
}

void minHeap::siftUp(int pos)
{
    if (pos == 0)
        return;
    int parent = (pos - 1) / 2;
    if (heap[pos] < heap[parent])
    {
        int temp = heap[pos];
        heap[pos] = heap[parent];
        heap[parent] = temp;
        siftUp(parent);
    }
}

void minHeap::siftDown(int pos)
{
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;
    int min = pos;
    if (left < heap.size() && heap[left] < heap[min])
        min = left;
    if (right < heap.size() && heap[right] < heap[min])
        min = right;
    if (min != pos)
    {
        int temp = heap[pos];
        heap[pos] = heap[min];
        heap[min] = temp;
        siftDown(min);
    }
}

minHeap::minHeap(vector<int> data)
{
    heap = data;
    for (int i = heap.size() / 2 - 1; i >= 0; i--)
    {
        siftDown(i);
    }
}
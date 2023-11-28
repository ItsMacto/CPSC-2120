#include "IntegerArrayQueue.h"

bool IntegerArrayQueue::enqueue(int value)
{
    if ((back + 2) % size == front){
        return false;
    }

    back = (back + 1) % size;

    array[back] = value;

    return true;

}

int IntegerArrayQueue::dequeue()
{
    if(front == (back - 1) % size){
        return 0;
    }

    int value = array[front];
    array[front] = 0;
    front = (front + 1) % size;
    
    return value;
}
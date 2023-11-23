#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    // start from the first element
    int *firstElementPointer = itemptr;
    int greatest = *itemptr;
    while (itemptr < firstElementPointer + size) // last index = size -1
    {
        greatest = (*itemptr > greatest) ? *itemptr : greatest;
        // shift ptr to right
        itemptr ++;
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = *itemptr;
    while (itemptr < endptr)
    {
        greatest = (*itemptr > greatest) ? *itemptr : greatest;
        // shift ptr to right
        itemptr ++;
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while (itemptr < endptr)
    {
        *targetptr = *itemptr ;
        itemptr ++;
        targetptr ++;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    int temp;
    rightptr --;
    while (leftptr < rightptr)
    {
        temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;

        // shift
        leftptr ++;
        rightptr --;
    }
}

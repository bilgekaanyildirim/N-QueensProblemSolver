//
// Created by Bilge Kaan Yıldırım on 28.10.2024.
//

#ifndef STACK_CPP
#define STACK_CPP

#include "stack.h"

using namespace std;

//Default constructor
template <class obj>
MyStack<obj>::MyStack()
{
    sizeS = 0;
    stackP = nullptr;
    top = -1;
}

// Constructor
template <class obj>
MyStack<obj>::MyStack(int size)
{
    sizeS = size;
    stackP = new obj[sizeS]; // Allocates memory
    top = -1;
}

// Destructor
template <class obj>
MyStack<obj>::~MyStack()
{
    delete[] stackP; // Deallocate memory
}

// Checks that is array empty
template <class obj>
bool MyStack<obj>::IsEmpty() const
{
    return top == -1;
}

// Checks that is array full
template <class obj>
bool MyStack<obj>::IsFull() const
{
    return top == sizeS - 1;
}

// Makes array empty
template <class obj>
void MyStack<obj>::Empty()
{
    top = -1;
}

// Pushes an element to the top of the array
template <class obj>
void MyStack<obj>::Push(const obj &object)
{
    if (IsFull())
    {
        throw Overflow();
    }
    top++;
    stackP[top] = object;
}

// Pops the element on the top of the array
template <class obj>
obj MyStack<obj>::Pop()
{
    if (IsEmpty())
    {
        throw Underflow();
    }
    obj topElement = stackP[top];
    top--;
    return topElement;
}

template <class obj>
obj MyStack<obj>::getTop() {
    return stackP[top];
}

#endif
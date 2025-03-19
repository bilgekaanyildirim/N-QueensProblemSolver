//
// Created by Bilge Kaan Yıldırım on 28.10.2024.
//

#ifndef HW1RE2_STACK_H
#define HW1RE2_STACK_H

#include <stdio.h>
#include <stdexcept>
#include <iostream>


class Underflow : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Underflow Exception";
    }
};

class Overflow : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "My Overflow Exception";
    }
};

template <class obj>
class MyStack
{
private:
    obj* stackP;    // Pointer to the dynamic array
    int top;        // Index of the top
    int sizeS;      // Capacity of the stack

public:
    MyStack();                          // Default constructor
    MyStack(int size);                  // Constructor
    ~MyStack();                         // Destructor
    bool IsEmpty() const;               // Checks that is array empty
    bool IsFull() const;                // Checks that is array full
    void Empty();                       // Makes array empty
    void Push(const obj & object);      // Pushes an element to the top of the array
    obj Pop();                          // Pops the element on the top of the array
    obj getTop();
};

#include "stack.cpp"

#endif //HW1RE2_STACK_H

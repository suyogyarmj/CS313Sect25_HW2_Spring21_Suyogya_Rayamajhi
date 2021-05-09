/*
	@Suyogya Rayamajhi
	@CSCI-313
	@Date: 04/11/21
    Homework 2 Program 1 Part a
    Stack Linked List Commenting
*/
//Header File: linkedStack.h 

#ifndef H_StackType // Header guards to prevent multiple inclusions of C++ header files
#define H_StackType
 
#include <iostream>
#include <cassert> // defines a macro function that can be used as a standard debugging tool
 
#include "stackADT.h"

using namespace std;

template <class Type> // Template function that is independent of any data type

// Declaring linked list node
struct nodeType
{
    Type info; // information in the node
    nodeType<Type> *link; // pointer to the next node
};

template <class Type>
class linkedStackType: public stackADT<Type>
{
public: // Overloading the assignment operator
    const linkedStackType<Type>& operator=
                              (const linkedStackType<Type>&);


    bool isEmptyStack() const; // When stack is empty, return 'true'


    bool isFullStack() const; // When stack is full, returns 'true'


    void initializeStack(); // Initializes the Stack by setting a new stack or by deleting the node of a stack until its empty 
    // After: 'stackTop = nullptr'

    void push(const Type& newItem); // Adds newItem in the stack
    // Before: there exists a non-full stack
    // After: newItem is added to the top of the stack

    Type top() const; // returns the top of the stack
    // Before: there exists a non-empty stack
    // After: If stack = empty, program terminates, ELSE, returns top element in the stack

    void pop(); // removes the top of the stack
    // Before: There exists a non-empty stack
    // After: Top element is removed from the stack


    linkedStackType(); // default constructor
    // After: stackTop = nullptr

    linkedStackType(const linkedStackType<Type>& otherStack); // copy constructor
  

    ~linkedStackType(); // destructor
    // After: The stack is freed by removing all elements from the stack
private:
    nodeType<Type> *stackTop; //pointer to the stack

    void copyStack(const linkedStackType<Type>& otherStack); // makes a copy of the otherStack

};


    
template <class Type> 
linkedStackType<Type>::linkedStackType() // Default constructor
{
    stackTop = nullptr; // pointer that points to nullptr
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr); // returns true if the stack es empty
} 

template <class Type>
bool linkedStackType<Type>:: isFullStack() const
{
    return false; // Since stack is implemented in linked list, it can't be full
} 

template <class Type>
void linkedStackType<Type>:: initializeStack()
{
    nodeType<Type> *temp; // A temp pointer that serves to delete the node after stackTop has been moved

    while (stackTop != nullptr) // while the stack is non-empty, it will not be equal to nullptr
    {
        temp = stackTop; // temp is set to the current node
                           
        stackTop = stackTop->link; // stackTop moves to the next node
                                   
        delete temp; // freeing the memory space by deleting 'temp'
    }
} 

template <class Type>
void linkedStackType<Type>::push(const Type& newElement) // push function
{
    nodeType<Type> *newNode; // pointer to new node

    newNode = new nodeType<Type>; // new node creation

    newNode->info = newElement; // storing the newElement 
    newNode->link = stackTop; // placing newNode on the top of the old stackTop
    stackTop = newNode; // making stackTop the new top     
                             
} //end push


template <class Type>
Type linkedStackType<Type>::top() const
{
    assert(stackTop != nullptr); // exit if the stack is empty
                              
    return stackTop->info; // returns information in the stackTop
}//end top

template <class Type>
void linkedStackType<Type>::pop()
{
    nodeType<Type> *temp; // Another temp pointer that serves to delete the node after moving the stackTop

    if (stackTop != nullptr) // checking if the stack is empty
    {
        temp = stackTop; // set temp node equal to the node that we are deleting

        stackTop = stackTop->link; // move the stackTop to the node below the current top
                                    
        delete temp; // deleting temp node again
    }
    else
        cout << "Cannot remove from an empty stack." << endl; // if empty stack then do nothing
}//end pop

template <class Type> 
void linkedStackType<Type>::copyStack
(const linkedStackType<Type>& otherStack)
{
    nodeType<Type> *newNode, *current, *last; // create multiple pointers for the process

    if (stackTop != nullptr) 
        initializeStack(); // making the stack empty if its non-empty

    if (otherStack.stackTop == nullptr) // if stack is empty then we're done
        stackTop = nullptr;
    else // else, start copying the stack
    {
        current = otherStack.stackTop; // setting current = top of the otherStack

          
        stackTop = new nodeType<Type>;  // new node creation

        stackTop->info = current->info; // copying the info from otherStack node to the new stackTop
        stackTop->link = nullptr;  // the newStack top is set to nullptr
                               
        last = stackTop;  // last points to the node as we move on      
        current = current->link; // moving current to the next node in the otherStack  

           
        while (current != nullptr) // while current points to a node, copy the remaining nodes of otherStack
        {
            newNode = new nodeType<Type>; // new node creation

            newNode->info = current->info; // newNode info is set to the info of the current node
            newNode->link = nullptr; // newNode's link is set to nullptr
            last->link = newNode; // adding newNode to the stack bottom by setting last's link to newNode
            last = newNode; // another node added to the stack bottom 
            current = current->link; // advancing the current in the otherStack
        }
    }
} 

 
template <class Type>  
linkedStackType<Type>::linkedStackType( // copy constructor
    const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr; // new stack creation
    copyStack(otherStack); // copyStack function duplicates the otherStack
}

  
template <class Type> 
linkedStackType<Type>::~linkedStackType() // desctructor
{
    initializeStack(); // deletes all the nodes in the stack
}
    
template <class Type>   
const linkedStackType<Type>& linkedStackType<Type>::operator=
    const linkedStackType<Type>& otherStack) // assignment operator overload
{   
    if (this != &otherStack) // check for "self-assignment" in copy constructor
        copyStack(otherStack); // rewriting the stack as otherStack

    return *this; 
}

#endif // matching the #ifndef directive
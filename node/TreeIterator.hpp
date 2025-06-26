#pragma once

#include <iostream>
#include <iterator>
#include "Node.hpp"


//We need all five parameters because the C++98 standard requires them to make your iterator compatible with the standard library algorithms and containers. 
//These type definitions tell the standard library exactly how to work with your custom iterator.
//If we only provided the iterator category, the standard library wouldn't know what type of objects your iterator points to or how 
//to handle pointer/reference operations with it.

/*Each argument serves a specific purpose in the iterator interface:

- Iterator Category (std::bidirectional_iterator_tag):
This defines what operations the iterator supports
A bidirectional iterator can move both forward and backward
- Value Type (Node<T>):
The type of object the iterator points to
This is what you get when you dereference the iterator with *it
- Distance Type (std::ptrdiff_t):
Used to represent the difference between iterators
Required for operations like it1 - it2 or advancing an iterator by N steps
- Pointer Type (Node<T>*):
The pointer to the value type
Used when you access members with the arrow operator (it->member)
- Reference Type (Node<T>&):
The reference to the value type
Used when you dereference the iterator (*it)*/

template<typename T>
class TreeIterator : public std::iterator<std::bidirectional_iterator_tag, Node<T>, std::ptrdiff_t, Node<T>*, Node<T>&> 
{
private:
    Node<T>* current;
    Node<T>* previous;

public:
    TreeIterator() : current(NULL), previous(NULL) {}
    TreeIterator(Node<T>* node) : current(node), previous(NULL) {}
    TreeIterator(const TreeIterator& other) : current(other.current), previous(other.previous) {}
    ~TreeIterator() {}

    TreeIterator& operator=(const TreeIterator& other) {
        if (this != &other) {
            current = other.current;
            previous = other.previous;
        }
        return *this;
    }
    
    //to dereference 
    Node<T>& operator*() const { 
       //maybe check if it's null??
        return *current; 
    }
    
    //to access from pointer 
    Node<T>* operator->() const { 
        return current; 
    }
    

    // This moves from a node to its parent
    TreeIterator& operator++() {
        if (current) {
            previous = current;
            current = current->parent; 
        }
        return *this;
    }
    
    TreeIterator operator++(int) {
        TreeIterator tmp(*this);
        ++(*this);
        return tmp;
    }
    
    // This moves from a parent back to the child we came from
    TreeIterator& operator--() {
        if (previous && (previous->parent == current)) {
            
            current = previous;
            previous = NULL; //i don't know how to know the previous, i set it to null
        }
        return *this;
    }
    
    TreeIterator operator--(int) {
        TreeIterator tmp(*this);
        --(*this);
        return tmp;
    }
    
    //added these two just in case you need them, probably need to add more operators but for now I only did the basic
    bool operator==(const TreeIterator& other) const {
        return current == other.current;
    }
    
    bool operator!=(const TreeIterator& other) const {
        return current != other.current;
    }
};
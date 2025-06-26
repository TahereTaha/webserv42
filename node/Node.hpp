#pragma once

#include <vector>
#include <string>

// Hey Taha! How are you doing? Btw here is the implementation of the node
// that I came up with. I am going to add comments to explain the various parts
// let me know if something needs to be changed or added
template <typename T>
class Node
{
    public:
        T token; // here you will store the value
        std::vector<Node<T>*> children; //this is a vector for the babies
        Node<T>* parent; // this is a pointer to the parent, it is set to NULL at construction and then set
                        // to the parent adress when child is added to the vector of that particular node

        enum Type
        {
            ROOT,
            BRANCH,
            LEAF
        };

        Node(const T& tok);
        ~Node(); // I thought in the destructor should delete also the childern,
                // but tell me if I am mistaken 

        //should we add copy constructor and copy assignment operator???

        void addChild(Node<T>* child);

        Type getNodeType() const; //I put here this function that returns the type of the node,
                                //let me know if you also want to store the type in a variable 
};
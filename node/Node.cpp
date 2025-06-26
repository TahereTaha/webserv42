#include "node.hpp"

template <typename T>
Node<T>::Node(const T& tok) : token(tok), parent(NULL){}

template <typename T>
Node<T>::~Node()
{
    for (size_t i = 0; i < children.size(); ++i)
    {
        delete children[i]; 
    }
    children.clear();  // is this overkilling?? xD Maybe we don't need it 
}

template <typename T>
void Node<T>::addChild(Node<T>* child)
{
    children.push_back(child);
    child->parent = this;
}

template <typename T>
typename Node<T>::Type Node<T>::getNodeType() const
{   
    if (parent == NULL)
        return ROOT;
    if (children.empty())
        return LEAF;
    return BRANCH;
}


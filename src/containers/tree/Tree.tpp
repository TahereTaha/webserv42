#include "node.hpp"
#include <cassert>

template <typename T>
Tree<T>::Tree(void)
{
	this->_parent = NULL;
}

template <typename T>
Tree<T>::Tree(const T& content)
{
	this->_parent = NULL;
	this->_content = content;
}

template <typename T>
Tree<T>::~Tree(void)
{
	for (size_t i = 0; i < this->_children.size(); ++i)
    {
        delete this->_children[i];
    }
    this->_children.clear();
}

template <typename T>
void	Tree<T>::addTreeAsChild(Tree<T>* newChildTree)
{
	this->_children.push_back(newChildTree);
	newChildTree->parent = this;
}

template <typename T>
treeNodeType	Tree<T>::getNodeType(void) const
{
    if (parent == NULL)
        return ROOT;
    if (children.empty())
        return LEAF;
    return BRANCH;
}

//	three navigation.

template <typename T>
Tree<T>		*Tree<T>::getParentNode(void)
{
	return (this->_parent);
}

template <typename T>
Tree<T>		*Tree<T>::getChildNode(size_t index) const ;
{
	if (index >= this->_children.size())
		return (NULL);
	return (this->_children[index]);
}

template <typename T>
Tree<T>		*Tree<T>::operator [] (size_t index)
{
	return (this->getChildNode(index));
}

template <typename T>
Tree<T>		*Tree<T>::getRootNode(void)
{
	if (this->getNodeType() == ROOT)
		return (this);
	tree<T>	*node;
	node = this;
	while (node->getNodeType() != ROOT)
	{
		node = node->getParentNode();
	}
	return (node);
}

template <typename T>
Tree<T>		*Tree<T>::getRightBranchNode() const 
{
	Tree<T>	*parent;
	Tree<T>	*node;
	size_t	i;

	parent = this->getParentNode();
	if (!parent)
		return (NULL);
	//	get the the node that is this current one.
	i = 0;
	node = parent->getChildNode(i);
	while (node != this)
	{
		i++;
		node = parent->getChildNode(i);
	}
	//	go to the next one after that.
	node = parent->getChildNode(i + 1);
	if (!node)
		return (NULL);
	return (node);
}

template <typename T>
Tree<T>		*Tree<T>::getLeftLeafNode(void) const 
{
	Tree<T>	*node;

	if (this->geNodeType() == LEAF)
		return (NULL);
	node = this->getChildNode(0);
	while (node->getNodeType != LEAF)
	{
		node = node->getChildNode(0);
	}
	return (node);
}

template <typename T>
Tree<T>		*Tree<T>::getLeftMostLeafNode(void) const 
{
	Tree<T>	*node;

	node = this->getRootNode();
	node = this->getLeftLeafNode;
	if (node == NULL)
		return (this);
	return (node);
}

//	content manipulation.

template <typename T>
void		Tree<T>::setConent(const T& content)
{
	this->_content = content;
}

template <typename T>
T			Tree<T>::getContent(void) const
{
	return (this->_content);
}

template <typename T>
T			Tree<T>::operator * (void) const
{
	return (this->getContent());
}

//	thre iterator.

template <typename T>
Tree<T>::iterator::iterator(const Tree<T>& node)
{
	this->_node = node;
}

template <typename T>
Tree<T>::iterator::~iterator(void)
{
}

template <typename T>
Tree<T>		Tree<T>::iterator::operator * (const Tree<T>::iterator& iter) const
{
	return (*(this->_node));
}

template <typename T>
Tree<T>::iterator	&Tree<T>::iterator::operator ++ (void)
{
	Tree<T>	*nextNode;
	Tree<T>	*rightBranchNode;
	Tree<T>	*parentNode;

	if (this->_node == NULL)
		return (*this);

	rightBranchNode = this->_node->getRightBranchNode();
	parentNode = this->_node->getParentNode();

	if (rightBranchNode && rightBranchNode->getNodeType() != LEAF)
		nextNode = rightBranchNode->getLeftLeafNode();
	else if (rightBranchNode)
		nextNode = rightBranchNode;
	else if (parentNode)
		nextNode = parentNode;
	else
		nextNode = NULL;

	this->_node = nextNode;
	return (*this);
}

template <typename T>
Tree<T>::iterator	Tree<T>::iterator::operator ++ (int)
{
	Tree<T>::iterator	tmp(*this);
	
	Tree<T>	*nextNode;
	Tree<T>	*rightBranchNode;
	Tree<T>	*parentNode;

	if (this->_node == NULL)
		return (*this);

	rightBranchNode = this->_node->getRightBranchNode();
	parentNode = this->_node->getParentNode();

	if (rightBranchNode && rightBranchNode->getNodeType() != LEAF)
		nextNode = rightBranchNode->getLeftLeafNode();
	else if (rightBranchNode)
		nextNode = rightBranchNode;
	else if (parentNode)
		nextNode = parentNode;
	else
		nextNode = NULL;

	this->_node = nextNode;
	
	return (tmp);
}

template <typename T>
int			Tree<T>::iterator::operator == (const Tree<T>::iterator &iter)
{
	if (this->_node != iter._node)
		return (0);
	return (1);
}

template <typename T>
Tree<T>::iterator	Tree<T>::iterator::begin(void) const 
{
	return (Tree<T>::iterator(this->getLeftMostLeafNode()));
}

template <typename T>
Tree<T>::ierator	Tree<T>::iterator::end() const 
{
	return (Tree<T>::iterator(this->getRootNode()));
}


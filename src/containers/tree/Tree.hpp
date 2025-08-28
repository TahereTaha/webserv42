#pragma once

#include <vector>
#include <string>

typedef enum
{
	ROOT,
	BRANCH,
	LEAF
}	treeNodeType;

template <typename T>
class Tree
{
	private:
		T						_content;
		std::vector<Tree<T>*>	_children;
		Tree<T>*				_parent;
		
		Tree(void);
		Tree(const T& content);
	protected:
	public:

		~Tree();

		void			addTreeAsChild(Tree<T>* newChildTree);
		treeNodeType	getNodeType(void) const;

		//	tree navigation.

		Tree<T>			*getParentNode(void) const ;
		Tree<T>			*getChildNode(size_t index) const ;
		Tree<T>			*operator [] (size_t index) const ;
		Tree<T>			*getRootNode(void) const ;
		Tree<T>			*getRightBranchNode(void) const ;
		Tree<T>			*getLeftLeafNode(void) const ;
		Tree<T>			*getLeftMostLeafNode(void) const ;

		//	content manipulation.

		void			setContent(const T& content);
		T				getContent(void) const ;

		T				operator * (void) const ;

		//	tree iterators.

		//	this iterator only suports postorder traversal.
		class iterator
		{
			private:
				Tree<T>		*_node;
			protected:
			public:
				iterator(Tree<T> *node);
				~iterator(void);

				Tree<T>		*operator * (const Tree::iterator& iter) const ;

				Tree<T>::iterator	&operator ++ (void);
				Tree<T>::iterator	operator ++ (int);

				int			operator == (const Tree<T>::iterator &iter);
		}
		Tree<T>::iterator	begin(void) const ;
		Tree<T>::iterator	end(void) const ;
};

#include <Tree.tpp>


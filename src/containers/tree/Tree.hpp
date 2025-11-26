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

		static Tree<T>	*makeTreeNode(const T& content);
		~Tree();

		void			addTreeAsChild(Tree<T>* newChildTree);
		treeNodeType	getNodeType(void) const;

		//	tree navigation.

		Tree<T>				*getParentNode(void) ;
		size_t				getChildNodeSize(void) const ;
		Tree<T>				*getChildNode(size_t index) ;
		Tree<T>				*operator [] (size_t index) ;
		Tree<T>				*getRootNode(void) ;
		Tree<T>				*getRightBranchNode(void) ;
		Tree<T>				*getLeftLeafNode(void) ;
		Tree<T>				*getLeftMostLeafNode(void) ;

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

				Tree<T>		*operator * (void) const ;

				iterator	&operator ++ (void);
				iterator	operator ++ (int);

				int			operator == (const Tree<T>::iterator &iter);
				int			operator != (const Tree<T>::iterator &iter);
		};
		Tree<T>::iterator	begin(void);
		Tree<T>::iterator	end(void);
};

#include <Tree.tpp>


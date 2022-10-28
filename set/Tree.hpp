# ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
// #include "../iterator_traits.hpp"
// #include "iterator.hpp"
#include <cstddef>
#include <cstdlib>
//#in

/* Red-Black Tree is a self-balanced Binary Tree */
// Search and Insert and Remove this operation in O log(n) time complexity
// Ressource:
/*
	https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea

	https://www.youtube.com/watch?v=w5cvkTXY0vQ&t=474s&ab_channel=Jenny%27slecturesCS%2FITNET%26JRF
*/

template <class value_type, class key_compare, class alloc>
class Tree {

private:
		typedef ::Node<value_type> Node;
		//typedef typename ::Node<const typename ft::iterator_traits<value_type*>::value_type> constNode;
		
		typedef typename alloc:: template rebind<Node>::other Node_alloc;


		size_t _size;
		Node* _end_node; 		// We suppose that: Root = end_node->left_child
		Node* _begin_node; // swap
		alloc _allocator;
		Node_alloc _node_alloc; // f constructor
		key_compare _compare;

		Node *_createNode(value_type value)
        {
            Node *newNode;

			// 1- allocate Node
            newNode = _node_alloc.allocate(1);
			_node_alloc.construct(newNode, Node());
			// 2- allocate pair
            newNode->value = _allocator.allocate(1);
			// 3- construct pair to value
            _allocator.construct(newNode->value, value);			//newNode->value = value; NOOO
            return newNode;
        }

        void _deleteNode(Node *node)
        {
            _allocator.destroy(node->value);
			_allocator.deallocate(node->value, 1);
            _node_alloc.deallocate(node, 1);
            //node->value = NULL;
			node = NULL;
        }
    
public:
    
// -------------------------- Constructor ----------------------------
    Tree(alloc map_alloc, key_compare comp) : _allocator(map_alloc), _compare(comp) {
		//std::cout << "Default Tree constructor\n";
		_size = 0;
		_end_node = _createNode(value_type()); 		//_end_node = new Node();
		_begin_node = _end_node;

	}

	virtual ~Tree() {
		//std::cout << "Tree Destructor\n";
		_deleteNode(_end_node);
	}

// -------------------------- Getters -----------------------------
	
 // root
	Node* get_root() const {
		return get_end()->l_child;
	}

	// constNode* get_root() const {
	// 	return get_end()->l_child;
	// }

	void set_root(Node* root) {
		get_end()->l_child = root;
		root->parent = _end_node;
	}

 // size
	size_t getSize() const {
		return _size;
	}

	void setSize(size_t size) {
		_size = size;
	}
	
 // begin

	Node* get_begin() const { // don't use const, bcuz iterator in case of iterator
		return _begin_node;
	}

	// constNode* get_begin() const { // don't use const, bcuz iterator in case of iterator
	// 	return (constNode*)_begin_node;
	// }

	void set_begin(Node* begin) {
		_begin_node = begin;
	}

 // end

	Node* get_end() const { // don't use const, bcuz iterator in case of iterator
		return _end_node;
	}

	// constNode* get_end() const { // don't use const, bcuz iterator in case of iterator
	// 	return (constNode*)_end_node;
	// }

	void set_end(Node* end) {
		_end_node = end;
	}

//  --------------------- Print Tree --------------------------

	/*void printHelper(Node *root, std::string indent, bool last) {
    if (root != _end_node) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      } else {
        std::cout << "L----";
        indent += "|  ";
      }

      std::string sColor = root->color == Red ? "RED" : "BLACK";
      std::cout << " { " << root->value.first << " | " << root->value.second << " }" << "(" << sColor << ")" << std::endl;
      printHelper(root->l_child, indent, false);
      printHelper(root->r_child, indent, true);
    }
  }
  void printTree() {
    if (get_root()) {
      printHelper(get_root(), "", true);
    }
  }*/
// --------------------------- SearchByKey ------------------------

    bool isRoot(Node* node) const {
	    if (node == get_root())
		    return true;
	    return false;
    }

    Node*	searchByKey(const value_type& key) const{
	    Node* tmp = get_root();
	
		if (tmp == NULL)  // if (_size == 0)
		{
			//std::cout << " 		SearchByKey() in Empty Tree  \n";
			return NULL;//return &_end_node; // return NULL;
		}
	    while (tmp->is_null() == false)
	    {
			//std::cout << " 		 SearchByKey() in NOT Empty Tree " << i << " \n";
		    if (_compare(*(tmp->value), key) == 0 && _compare(key, *(tmp->value)) == 0) //((tmp->value).first == key)
			{
				//std::cout << "   Yes please this is the node :\n";
				//tmp->printNode();
			    return tmp;
			}
		    else
		    {
			    if (_compare(*(tmp->value), key) == 1)  //((tmp->value).first < key)
				    tmp = tmp->r_child;
			    else
				    tmp = tmp->l_child;
		    }
	    }
		//std::cout << "-------KEY NOT FOUND searchByKey()-------\n";
	    return NULL;
    }

	Node*	searchLowerKey(const value_type& key) const 
	{

	    Node* tmp = get_root();
		Node* res = _end_node;

		if (tmp == NULL)
			return _end_node;
	    while (tmp->is_null() == false)
	    {
		    if (_compare(*(tmp->value), key) == 1)
				tmp = tmp->r_child;
			else if (_compare(key, *(tmp->value)) == 1)
			{
				res = tmp;
				tmp = tmp->l_child;
			}
		   	else
			    return tmp;
		}
		return res;  // may return null
    }

// ------------------------- Next/Previous Node -------------------------

	Node* next_node(Node* curr) const{
		//std::cout << "next node \n";
		// if (_begin_node == &_end_node)
		// {
		// 	//std::cout << "==> Ana Tree 5awya and nta fl end_node and you are looking for my next node, ali makaynch aslan\n";
		// 	return curr;
		// }
		if (curr == _end_node)
		{
			// std::cout << "==> Ana Tree 3aaamra and nta fl end_node and you are looking for my next node, which is the max element before end??\n";
			return previous_node(curr);			
		}
		//curr->printNode();
		if ((curr->r_child)->is_null())
		{
			if (curr->isLeft())
				return curr->parent;
			else {
				Node* p = curr->parent;
				while (isRoot(p) == false && p->isRight())
					p = p->parent;
				return p->parent; // return end_node OR another node
			}
		}
		else
			return curr->inOrderSuccessor();
	}

	Node* previous_node(Node* curr) const {
		//std::cout << "previous node \n";

		if ((curr->l_child)->is_null())
		{
			//std::cout << "ROOT is null\n";
			if (curr->isRight())
				return curr->parent;
			else {
				Node* p = curr->parent;
				while (isRoot(p) == false && p->isLeft())
					p = p->parent;
				return p->parent; // return end_node OR another node
			}
		}
		else
		{
			//std::cout << "==> my left is root\n";
			return curr->inOrderPredecessor();
		}
	}

// ----------------------- Insertion --------------------------

        ////////////////////////////////////
        //          Insertion             //
        ////////////////////////////////////


void	insertion_BST(Node* parent, Node* curr, Node* new_node) {
	// Just insert the new Node, no need to do anything else
	if (curr->is_null())
	{
		if (_compare(*new_node->value, *parent->value) == 1)//parent->value > new_node->value)
		{
			parent->l_child = new_node;
			new_node->parent = parent;
		}
		else
		{
			parent->r_child = new_node;
			new_node->parent = parent;
		}
	}
	else
	{
		if (_compare(*(new_node->value), *(curr->value)) == 1)//curr->value > new_node->value)
			insertion_BST(curr, curr->l_child, new_node);
		else
			insertion_BST(curr, curr->r_child, new_node);
	}
}

Node* insertion_RBTree(const value_type& val) {

	Node* new_node;

	// 1- Create (alloc and construct a new node) //new_node = new Node(val);

	new_node = _createNode(val);
	new_node->color = Red;
	new_node->l_child = _end_node;
	new_node->r_child = _end_node;
	new_node->_is_null = 1;
	//new_node->printNode();

	// 2- increment the size of the container
	_size++;
	// 3- Insert in the Tree
	if (get_root() == NULL) 	// case 1: Empty Tree
	{
		//std::cout << "Empty Tree\n";

		_end_node->l_child = new_node;
		get_root()->parent = _end_node;
		_end_node->l_child = get_root();

		// 4- Update begin of Tree
		_begin_node = new_node;
	}
	else 	// case 2: Recursive
	{
		insertion_BST(get_root(), get_root(), new_node);
		// 4- Update begin of Tree
		if (_compare(val, *(_begin_node->value)) == 1)//val < _begin_node->value)
			_begin_node = new_node;
	}
	// 5- Balance the RedBlack Tree
	balancing_insertion(new_node); // new_node is not a "NIL node"
	//printTree();
	return new_node;
}

void	balancing_insertion(Node* new_node) {
	Node* parent = new_node->parent;

	// Case 1:
	if (isRoot(new_node))
	{
		new_node->color = Black;
		return ;
	}	
	// Case 2:
	if (parent->color == Black)
		return ;
	// Case 3:
	else { // if(parent.color == Red)
		
		Node* uncle = parent->sibling();    // Maybe uncle could be NIL
		Node* grandParent = parent->parent;

		// Case 3.1:
		if (uncle->color == Red) // Parent && Uncle are Red
		{
			parent->color = Black;
			uncle->color = Black;
			grandParent->color = Red;
			balancing_insertion(grandParent);
		}
		// Case 3.2:
		else // Parent is Red && Uncle is Black and Maybe in this Case Uncle is NIL
		{
			if (parent->isRight() && new_node->isRight())
				case_1Insertion(grandParent);
			else if (parent->isRight() && new_node->isLeft()) {
				parent->right_Rotation();
				// 1- After Rotation, Update the _root
				//get_root() = _end_node.l_child;
				// new_node become the parent of Parent
				// 2- call case 3.2.1
				case_1Insertion(grandParent);
			}
			else if (parent->isLeft() && new_node->isLeft())
				case_2Insertion(grandParent);
			// if (parent.isLeft() && new_node.isRight())
			else {
				// So with rotation parent will go down and new_node will go up 
				parent->left_Rotation();
				// 1- After Rotation, Update the _root
				//get_root() = _end_node.l_child;
				// new_node become the parent of Parent
				// 2- call case 3.2.2
				case_2Insertion(grandParent);
			}
		}
	}
	
}

void case_1Insertion(Node* grandParent) {
	grandParent->left_Rotation();
	// 1- After Rotation, Update the _root
	//_root = _end_node.l_child;
	// grandParent is sibling now
	// 2- Recoloring
	grandParent->color = Red;
	(grandParent->sibling())->color = Red;
	(grandParent->parent)->color = Black;
}

void	case_2Insertion(Node* grandParent) {
	grandParent->right_Rotation();
	// 1- After Rotation, Update the _root
	//_root = _end_node.l_child;
	// grandparent is sibling now
	// 2- Recoloring
	grandParent->color = Red;
	(grandParent->sibling())->color = Red;
	(grandParent->parent)->color = Black;
}

// ----------------------- Deletion ------------------------

        ////////////////////////////////////
        //        Deletion                //
        ///////////////////////////////////

void	delete_leaf(Node* node) {
	// Node to be "deleted" has no children : i.e, it is a lead node
	
	Node* parent = node->parent;

	_size--;

	if (node == _begin_node)
	{
		//std::cout << "You gonna deleate the begin node\n";
		_begin_node = next_node(node);
	}
	
	// if (isRoot(node))    // 3ad zatha, and it works and fix the problem
	// {

	// 	//std::cout << "delete leaf which is Root\n";
	// 	//printTree();
	// 	_root = NULL;

	// }
	if (node->isLeft())
		parent->l_child = node->l_child;
	else
		parent->r_child = node->r_child;
	
	// delete node;
	_deleteNode(node);
}

size_t erase(const value_type& key)
{
	Node* node_to_delete = searchByKey(key);


	if (node_to_delete)
	{
		deletion_RBTree(node_to_delete);
		return 1;
	}
	return 0;
}

//void deletion_RBTree(Node& node_to_delete)
void deletion_RBTree(Node* node_to_delete)
{
	// std::cout << "deletion_RBTree\n";
	// node_to_delete->printNode();

	// Case 1:
	if (isRoot(node_to_delete) && node_to_delete->is_leaf())
	{
	//	std::cout << "I think this is the case, the case of deleting a root node\n";
		delete_leaf(node_to_delete);
		_end_node->l_child = NULL;
	}
	// Case 2:
	else if (node_to_delete->is_leaf() && node_to_delete->color == Red)
		delete_leaf(node_to_delete); // is Red leaf
	// Case 3:
	else if (node_to_delete->is_leaf() && node_to_delete->color == Black)
	{
		//std::cout << "Node to delete is leaf and black\n";
		//Node	*parent = node_to_delete->parent;// parent
		if (node_to_delete->isRight())
		{
			//std::cout << "Black leaf Right\n";
			//delete_leaf(node_to_delete);
			// Node* new_node = new Node(); // is Black Null Node
			// new_node->_is_null = 0;
			// new_node->parent = parent;
			// parent->r_child = new_node;
			// new_node->l_child = &_NIL;
			// new_node->r_child = &_NIL;
			// new_node->color = DB; // enum {RED, Black, DB}
			//std::cout << "DB new node \n";
			//new_node->printNode();
			//fix_DB(new_node);
			//delete_leaf(new_node);
			node_to_delete->color = DB;
			fix_DB(node_to_delete);
			delete_leaf(node_to_delete);
		}
		else // isLeft()
		{
			//this->printTree();
			//std::cout << "Black leaf Left\n";
			//(node_to_delete->parent)->printNode();
			// delete_leaf(node_to_delete);
			// Node* new_node = new Node();
			// parent->l_child = new_node;
			// new_node->_is_null = 0; // yes null
			// new_node->parent = parent;
			// new_node->l_child = &_NIL;
			// new_node->r_child = &_NIL;
			// new_node->color = DB;
			//std::cout << "DB new node --> ";
			//new_node->printNode();
			// fix_DB(new_node);
			// delete_leaf(new_node);
			node_to_delete->color = DB;
			fix_DB(node_to_delete);
			delete_leaf(node_to_delete);
		}
	}
	// Case 4: Internal Node
	else
	{
		//std::cout << "----Delete Internal node with color " << node_to_delete->color << " --------\n";

		// In this case of Internal Node, we don't delete the node:
		// 		==> Actually we replace the node.
		// Replace it with his InOrderSuccessor OR InOrderPredecessor
		//    and delete the actual node(node_to_delete)

		Node* node_replace;
	
		node_replace = choose_replacement_of_node(node_to_delete);
		// std::cout << "---- Replacement node ";
		// node_replace->printNode();
		//exit(1);
		if (node_replace != node_to_delete->l_child && node_replace != node_to_delete->r_child)
		{
			//std::cout << "Replacement node is not a special case aka one of his children\n";
			//std::cout << "Swap node \n";
			//node_replace->printNode();
			//std::cout << "Parent of replacement node \n";
			//if(!(node_replace->parent)->is_null())
			//	(node_replace->parent)->printNode();
			//std::cout << "Node to delete \n";
			//node_to_delete->printNode();
			node_to_delete->swap(node_replace);
			//_root = _end_node.l_child;
			//std::cout << "Replacement node \n";
			//node_replace->printNode();
			//std::cout << "Parent of node to delete \n";
			//(node_to_delete->parent)->printNode();
			//std::cout << "Node to delete \n";
			//node_to_delete->printNode();
		}
		else
		{
			// Special case of : Swap node with one of his children
			if (node_to_delete->isLeft())
			{
				(node_to_delete->parent)->l_child = node_replace;
				// swap with left child
				if (node_replace->isLeft())
				{
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->r_child = node_to_delete->r_child;
					if (!(node_replace->r_child)->is_null())
						(node_replace->r_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->l_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;
				}
				// swap with right child
				else // node_replace is right
				{
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->l_child = node_to_delete->l_child;
					if (!(node_replace->l_child)->is_null())
						(node_replace->l_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->r_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;				
				}
			}
			else
			{
				//std::cout << "Node to delete is Right\n";
				//node_to_delete->printNode();
				(node_to_delete->parent)->r_child = node_replace;
					// swap with left child
				if (node_replace->isLeft())
				{
					//std::cout << "Replacement node is Left\n";
					//node_replace->printNode();
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->r_child = node_to_delete->r_child;
					if (!(node_replace->r_child)->is_null())
						(node_replace->r_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->l_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;
				}
				// swap with right child
				else // node_replace is right
				{
					//std::cout << "Replacement node is Right\n";
					//node_replace->printNode();
					node_replace->parent = node_to_delete->parent;
					Node* left_child = node_replace->l_child;
					Node* right_child = node_replace->r_child;

					// swap r_child of node to delete to node replace
					node_replace->l_child = node_to_delete->l_child;
					if (!(node_replace->l_child)->is_null())
						(node_replace->l_child)->parent = node_replace;
					// swap parent of node to delete to node replace
					node_replace->r_child = node_to_delete;
					node_to_delete->parent = node_replace;
					// give children of node_replace to the node to delete
					node_to_delete->l_child = left_child;
					node_to_delete->r_child = right_child;		
				}					
			}
		}
		Color color = node_replace->color;
		node_replace->color = node_to_delete->color;
		node_to_delete->color = color;
		// ==> After Rotation, Update the _root
		//_root = _end_node.l_child;
		deletion_RBTree(node_to_delete); // is leaf or one child those are the only cases
	}
}

Node* choose_replacement_of_node(Node* node_to_delete)
{
	// Replace the node to be deleted With RED node if possible
	// 	 [ InOrderSuccessor OR InOrderPredecessor ]
	// Node* InOrderSuccessor = node_to_delete->inOrderSuccessor();
	// Node* InOrderPredecessor = node_to_delete->inOrderPredecessor();

	// if (!InOrderSuccessor)//(InOrderSuccessor->is_null())
	// 	return InOrderPredecessor;
	// else if (!InOrderPredecessor)//(InOrderPredecessor->is_null())
	// 	return InOrderSuccessor;


	if ((node_to_delete->r_child)->is_null() || node_to_delete->inOrderSuccessor()->color == Black)
		return node_to_delete->inOrderPredecessor();
	return node_to_delete->inOrderSuccessor();

	// This solution
	// else
	//  	return InOrderSuccessor;
	// Or this :
	// else if (InOrderSuccessor->color == Red)  
	// 	return InOrderSuccessor;
	// return InOrderPredecessor;
}

void fix_DB(Node* DB_node)
{
	// Case 0:
	if (isRoot(DB_node))
		DB_node->color = Black;
	else
	{
		Node* sibling = DB_node->sibling();
		// if (sibling->is_null())
		// 	std::cout << "ana endnode\n\n\n\n";
		// std::cout << "DB node ";
		// DB_node->printNode();
		// std::cout << "DB node parent ";
		// DB_node->parent->printNode();
		// if (sibling->is_null())
		// {
		// 	std::cout << "DB node sibling is NULL" << " with color "<< sibling->color <<"\n";
		// 	//printTree();
		// 	exit(1);
		// }
		// else
		// {
		// 	std::cout << "DB sibling node ";
		// 	sibling->printNode();
		// }
		// printHelper(sibling->parent, 0, true);
		//DB_node->printNode(); // hellio
		// Case 1: // sibling is Black and Both of this children are black
		// if (sibling->color == Black && sibling->is_null()) // NEEEEEEEEEEEEEEW CASe
		// {
		// 	std::cout << "sibling is null\n";
		// 	case_0Deletion(DB_node);
		// }
		if (sibling->color == Black && 
			(sibling->l_child)->color == Black &&
			(sibling->r_child)->color == Black)
			case_1Deletion(DB_node);
		// Case 2: // sibling is Red
		else if (sibling->color == Red)
			case_2Deletion(DB_node);
		// Case 3: // sibling is Red, Sibling's child far from DB is black, 
		//    Sibling's chilf near to DB in red
		else if (sibling->color == Black &&
			(DB_node->far_child_sibling())->color == Black &&
			(DB_node->near_child_sibling())->color == Red)
			case_3Deletion(DB_node);
		else // if (sibling.color == Black && (DB_node.far_child_sibling()).color == Red)
			case_4Deletion(DB_node);
	}
}

// Case 1: sibling is Black and Both of this children are black
void case_1Deletion(Node* DB_node) {
	//std::cout << "case_1Deletion\n";
	Node* sibling = DB_node->sibling();

	DB_node->color = Black;
	sibling->color = Red;
	if ((DB_node->parent)->color == Black)
	{
		(DB_node->parent)->color = DB;
		fix_DB(DB_node->parent);
	}
	else
		(DB_node->parent)->color = Black;
}

// Case 2: // sibling is Red
void case_2Deletion(Node* DB_node) {
	//std::cout << "case_2Deletion\n";
	Node* sibling = DB_node->sibling();
	Node* parent = DB_node->parent;

	// Step 1: Swap DB's parent color with DB's sibling color
	parent->color = Red;
	sibling->color = Black;

	// Step 2: Perform Rotation at parent node in the direction of DB node
	if (DB_node->isLeft())
	{
		parent->left_Rotation();
		// ==> After Rotation, Update the _root
		//_root = _end_node.l_child;
	}
	else
	{
		parent->right_Rotation();
		// ==> After Rotation, Update the _root
		//_root = _end_node.l_child;
	}
	fix_DB(DB_node);
}

// Case 3: // sibling is Red, Sibling's child far from DB is black, 
	//    Sibling's child near to DB in red
void	case_3Deletion(Node* DB_node)
{
	//std::cout << "case_3Deletion\n";
	Node* sibling = DB_node->sibling();

	// Step 1: color sibling with Red, and red child sibling with black (swap color)
	sibling->color = Red;
	(DB_node->near_child_sibling())->color = Black;
	// Step 2: Perform Rotation at sibling node in direction opposite of DB node
	if (DB_node->isLeft())
	{
		sibling->right_Rotation();
		// ==> After Rotation, Update the _root
		//_root = _end_node.l_child;
	}
	else
	{
		sibling->left_Rotation();
		// ==> After Rotation, Update the _root
		//_root = _end_node.l_child;
	}
	// Step 3: Call the case 4
	case_4Deletion(DB_node);
}

// Case 4: // if (sibling.color == Black && (DB_node.far_child_sibling()).color == Red)
void case_4Deletion(Node* DB_node)
{
	//std::cout << "case_4Deletion\n";
	Node* sibling = DB_node->sibling();
	Node* far_child_sibling = DB_node->far_child_sibling();
	Node* parent = DB_node->parent;

	// Step 1: Swap color of DB's parent with DB's sibling's color
	sibling->color = parent->color;
	parent->color = Black;
	// Step 2: Perform rotation at DB's parent in direction of DB
	if (DB_node->isLeft())
	{
		parent->left_Rotation();
		// ==> After Rotation, Update the _root
		//_root = _end_node.l_child;
	}
	else
	{
		parent->right_Rotation();
		// ==> After Rotation, Update the _root
		//_root = _end_node.l_child;
	}
	// Step 3: Remove DB sign
	DB_node->color = Black;
	// Step 4: Change color of DB's sibling far child from Red to Black
	far_child_sibling->color = Black;
}

};


#endif
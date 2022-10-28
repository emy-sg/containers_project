# ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

enum Color {
    Red,
    Black,
    DB,
};

template <class value_type>
class Node {
    public:
        int _is_null;  // 0 is null and 1 is !null
        value_type* value;
        Color color;

        Node* parent;
        Node* l_child;
        Node* r_child;

    public:
        // Constructor
        Node() : value() { //: value()
        	_is_null = 0;  // 0 is null and 1 is !null
			//value should be initialzed
			parent = NULL;
			l_child = NULL;
			r_child = NULL;
			color = Black;
			//std::cout << "Default Node Constructor\n";
		}
        Node(value_type value) : value(value) {
			_is_null = 1;
			//parent = nullptr;
			//l_child = nullptr;
			//r_child = nullptr;
			color = Red;
			//std::cout << "Parameterized Node Constructor\n";
		}
        Node(const Node& inst) {
			//std::cout << "Copy Node Construtor\n";
			*this = inst;
		}
        Node& operator=(const Node& inst) {
			// deep and shallow problem I
			_is_null = inst._is_null;
			value = inst.value;
			//*(int *)0 = 0;
			color = inst.color;
			parent = inst.parent;
			l_child = inst.l_child;
			r_child = inst.r_child;
			//std::cout << "Copy Assignement Node operator\n";
			return *this;
		}
        ~Node() {
			//std::cout << "Node Destructor\n";
		}

    // -------------  Methods  ------------ //

        /////////////////////////////////
        //      Check position of Node //
        /////////////////////////////////

	// void printNode() {
	// 	if (is_null())
	// 		std::cout << "is_null: yes | ";
	// 	else
	// 		std::cout << "is_null: no | ";
	// 	if (color == Red)
	// 		std::cout << "color: Red | ";
	// 	else if (color == Black)
	// 	 	std::cout << "color: Black | ";
	// 	else
	// 	 	std::cout << "color: DB | ";
	// 	if (isLeft())
	// 		std::cout << "is_Left: yes | ";
	// 	else
	// 	 	std::cout << "is_right: yes | ";
	// 	std::cout << " key: " << value->first << " | value: " << value->second << " | parent value: " << parent->value.first;
	// 	if (!(this->l_child)->is_null())
	// 		std::cout << " | l_child value: " << (this->l_child)->value.first;
	// 	else
	// 	 	std::cout << " | l_child value: is NIL";
	// 	if (!(this->r_child)->is_null())
	// 		std::cout << " | r_child value: " << (this->r_child)->value.first;
	// 	else
	// 	 	std::cout << " | r_child value: is NIL";
	// 	std::cout << std::endl;
	// }

    bool is_null() {
	    if (this->_is_null == 0)
		    return true;
	    return false;
    }
    
    bool isRight() {
	    Node* parent = this->parent;
	    if (parent->r_child == this)
		    return true;
	    return false;
    }

    bool isLeft() {
	    Node* parent = this->parent;
	    if ((parent->l_child) == this)
		    return true;
	    return false;
    }

    bool is_leaf() {
	    if ((this->l_child)->is_null() && (this->r_child)->is_null())
		    return true;
	    return false;
    }

    Node* sibling() {
	    Node* parent = this->parent;
	    if ((*this).isLeft())
		    return parent->r_child;
	    return parent->l_child;
    }

    Node* far_child_sibling() {
	    Node* node = this;
	    Node* sibling = node->sibling();
	    if (node->isLeft())
		    return sibling->r_child;
	    return sibling->l_child;
    }

    Node* near_child_sibling() {
	    Node* node = this;
	    Node* sibling = node->sibling();
	    if (node->isLeft())
		    return sibling->l_child;
	    return sibling->r_child;
    }

        ////////////////////////////////////
        //     Successor and Predecessor  //
        ////////////////////////////////////
		
	Node* next_node(Node* end_node) {
		//Node* curr = this;
		Node* root = end_node->l_child;

		if (this == end_node)
		{
			//std::cout << "==> Ana Tree 3aaamra and nta fl end_node and you are looking for my next node, which is the max element before end??\n";
			return this->previous_node(end_node);			
		}
		//this->printNode();
		if ((this->r_child)->is_null())
		{
			if (this->isLeft())
				return this->parent;
			else {
				Node* p = this->parent;
				while ((p != root) && p->isRight())
					p = p->parent;
				return p->parent; // return end_node OR another node
			}
		}
		else
			return this->inOrderSuccessor();
	}

	Node* previous_node(Node* end_node) {
		//Node* this = this;
		Node* root = end_node->l_child;
		//std::cout << "previous node \n";

		if ((this->l_child)->is_null())
		{
			//std::cout << "ROOT is null\n";
			if (this->isRight())
				return this->parent;
			else {
				Node* p = this->parent;
				while ((p != root) && p->isLeft())
					p = p->parent;
				return p->parent; // return end_node OR another node
			}
		}
		else
		{
			//std::cout << "==> my left is root\n";
			return this->inOrderPredecessor();
		}
	}

    Node* inOrderSuccessor() {
	    // What is node's Successor in a BST ?
	    // ==> It is the Smallest value present in its right subtree.
	    Node* right_child = this->r_child;
	    // getMinimumkey of right child
		if (right_child->is_null())
			return NULL;// instead of this (return this)
	    return getMinimumKey(right_child);
    }

    Node* getMinimumKey(Node* curr) {
	    while (!(curr->l_child)->is_null())
		    curr = curr->l_child;
	    return curr;
    }

    Node* inOrderPredecessor() {
		//std::cout << "They think that is so long\n";
	    // What is node's Predecessor in a BST ?
	    // ==> It is the Greatest value in its left subtree.
	    Node* left_child = this->l_child;
	    // getMaximumkey of left child
		if (left_child->is_null())
			return NULL;
	    return getMaximumKey(left_child);
    }

    Node* getMaximumKey(Node* curr) {
		//std::cout << "==> Return maximum key\n";
	    while (!(curr->r_child)->is_null())
		    curr = curr->r_child;
	    return curr;
    }

        /////////////////////////////////
        //           Rotation          //
        /////////////////////////////////

    void left_Rotation() {
		//std::cout << "begin left_Rotation\n";
		Node* node = this;
	    Node* parent = node->parent;
	    Node* right_child = node->r_child;

	    if (node->isRight())
		    parent->r_child = right_child;
	    else
		    parent->l_child = right_child;
	    node->parent = right_child;
	    node->r_child = right_child->l_child;
		if (!(node->r_child)->is_null()) // is not NIL
			(node->r_child)->parent = node;
	    right_child->l_child = node;
		right_child->parent = parent;
    }

    void right_Rotation() {
		//std::cout << "begin right_Rotation\n";
		Node* node = this;
	    Node* parent = node->parent;
	    Node* left_child = node->l_child;

	    if (node->isRight())
		    parent->r_child = left_child;
	    else
		    parent->l_child = left_child;
	    node->parent = left_child;
	    node->l_child = left_child->r_child;
		if (!(node->l_child)->is_null()) // is not NIL
			(node->l_child)->parent = node;
	    left_child->r_child = node;
		left_child->parent = parent;
    }

        ///////////////////////////////////
        //   Swap position of two nodes  //
        ///////////////////////////////////

	void swap(Node* replace_node) {
		//std::cout << "Call to SWAP function\n";
		Node* this_parent = this->parent;
		Node* replace_parent = replace_node->parent;
		Node* left_child = replace_node->l_child;
		Node* right_child = replace_node->r_child;
		//Color color = replace_node->color;

		// 1- We discuss here some cases 
		if (this->isLeft())
			this_parent->l_child = replace_node;
		else
			this_parent->r_child = replace_node;

		if (replace_node->isLeft())
			replace_parent->l_child = this;
		else
		 	replace_parent->r_child = this;
		
		// 2- switch parent
		this->parent = replace_parent;
		replace_node->parent = this_parent;
		// 3- switch children 
		replace_node->l_child = this->l_child;
		if (!(this->l_child)->is_null())
			(this->l_child)->parent = replace_node;
		replace_node->r_child = this->r_child;
		if (!(this->r_child)->is_null())
			(this->r_child)->parent = replace_node;

		this->l_child = left_child;
		if (!left_child->is_null())
			left_child->parent = this;
		this->r_child = right_child;
		if (!right_child->is_null())
			right_child->parent = this;

		// 4- switch colors
		// replace_node->color = this->color;
		// this->color = color;
	}

};


#endif
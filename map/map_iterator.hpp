# ifndef map_ITERATOR_HPP
#define map_ITERATOR_HPP

#include "../iterator_traits.hpp"
#include "../pair.hpp"
#include "node.hpp"
#include <iterator>
#include <utility>

// First question why implementing this Fucker of constIterator, when we already have an iterator ??
/*
    Well, we gonna need this fucker, exactly in the copyConstructor of the vector.
    If we used the constructor of vector(begin(), end()) within the copyConstructor, who took an const reference to vector.
    well const_iterator begin() will be called automatically.
    And so we need to implement a const_iterator for those fuckers and thank u. 
*/

// Second question const_iterator is an iterator with small diff, what are those differences ?
/*
    Good question, But I don't have the answear, let's try to find one.
    But let's define what is const_iterator first:
        const_iterator it just don't allow you to change the values that they point to, when regular iterator does.
    That's good start.
    So our const_iterator are not suppose to return a reference or pointer to the value.
    Second thing to mention, if we have our iterator it->first ==> suppose that we cannot change anything here
    and same for (*it).
    We also have operator=() that returns reference and change the pointer, what Am i suppose to do with that too.
    ===> Well opeator=()will take as parameter const_iterator like (const_iterator begin() const;), and well return const_reference.
*/

namespace ft {

template <class T> // value_type is std::pair
class Iterator_map {
    public:
        // typedef ::Node<T> Node;

        // typedef ptrdiff_t                                        difference_type;
        // typedef T                                                value_type;
        // typedef T*                                                pointer;
        // typedef T&                                                reference;
        // typedef typename ::Node<value_type>                         Node;
        // typedef typename ::Node<const typename iterator_map_traits<value_type*>::value_type>    const_node;

        typedef typename ft::iterator_traits<T*>::value_type        value_type;
        typedef typename ft::iterator_traits<T*>::pointer           pointer;
        typedef typename ft::iterator_traits<T*>::reference         reference;
        typedef typename ft::iterator_traits<T*>::difference_type    difference_type;
        typedef std::bidirectional_iterator_tag                     iterator_category;
        typedef ::Node<value_type>                                  Node;


    private:
        Node* _end_node;
        Node* _Node;

    public:
        // Constructor
        Iterator_map() {
            //std::cout << "Default iterator_map\n";
            _end_node = NULL;
            _Node = NULL;
        }
        Iterator_map(Node* end_node, Node* curr) { //Initalization constructor
            //std::cout << "Parameterized Iterator_map Constructor\n";
            _end_node = end_node;
            _Node = curr;
            // else
            // {
            //     std::cout << "affichhi had node ali 3titek f iterator_map\n";
            //     _Node->printNode();
            // }
            // std::cout << "Normalement 5asou yaffichi node 9banma ya5roj\n";
        }
        
        // template< class IT> // conversion constructor
        // Iterator_map(const Iterator_map<IT>& iter) {
        Iterator_map(const Iterator_map& iter) {
            //std::cout << "Copy Constructor iterator_map\n";
            *this = iter;
            // _end_node = iter._end_node;
            // _Node = iter._Node;
        }

        // template< class IT>
        // Iterator_map& operator=(const Iterator_map<IT>& iter) {
        Iterator_map& operator=(const Iterator_map& iter) {
            //std::cout << "Assignement Copy Constructor iterator_map\n";
            this->_end_node = iter._end_node ;//.base()).first;
            this->_Node = iter._Node;//.base()).second;
            //std::cout << _Node << " " << iter._Node << "\n";
            // if (_Node != _Tree->get_end())
            //     _Node->printNode();
            //std::cout << "walo\n";
            return *this;
        }
        ~Iterator_map() {
            //std::cout << "Destructor iterator_map\n";
        }

    // --------------------------------------------

    operator Iterator_map<const value_type>() {
        return Iterator_map<const value_type>(_end_node, _Node);
    }

    ft::pair<Node*, Node*> base() const {
        return ft::make_pair(_end_node, _Node);
    }

    // 1- operator->() return pointer to value_type aka pointer to std::pair

    //pointer operator->() const;
    pointer operator->() const {
        return _Node->value;
            // bcuz I don't know if value or *value in NOde class
    }

    // 2- operator*() return reference to value_type aka reference to std::pair
    
    // reference operator*() const;
    reference operator*() const {
        return *(_Node->value);
    }

    // Step 3: Member Methods increment/decrement : operator++() && operator--()
    
    // 1- Prefix increment:
    Iterator_map& operator++() {
        //std::cout << "\n ------------ Pre increment ----------------- \n";
        _Node = _Node->next_node(_end_node);
        return *this;
    }
    // 2- Prefix decrement:
    Iterator_map& operator--() {
        //std::cout << "\n ------------ Pre idecrement ----------------- \n";
        _Node = _Node->previous_node(_end_node);
        return *this;
    }
    // 3- Postfix increment
    Iterator_map operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        Iterator_map tmp = *this; // create a copy
        //std::cout << tmp->first << "\n";
        ++(*this); // ++(*this); // call pre increment for *this
        //std::cout << tmp->first << "\n";
        return tmp;
    }
    // 4- Postfix decrement
    Iterator_map operator--(int) {
        Iterator_map tmp(*this); // create a copy
        --(*this); // ==>   --(*this); 
        return tmp;
    }

    // Step 4: Member friends : The operators [== != ]
    friend bool operator==(const Iterator_map& a, const Iterator_map& b) {
        return a._Node->value == b._Node->value;
    }

    friend bool operator!=(const Iterator_map& a, const Iterator_map& b) {
        // compare end_node deleted;
        return a._Node->value != b._Node->value;
    }
};
}

#endif
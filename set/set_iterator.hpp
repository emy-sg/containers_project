# ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP

#include "../pair.hpp"
#include "../iterator_traits.hpp"
#include "node.hpp"
#include <iterator>
#include <utility>

namespace ft {

template <class T> // value_type is std::pair
class Iterator_set {
    public:
        // typedef ::Node<T> Node;

        // typedef ptrdiff_t                                        difference_type;
        // typedef T                                                value_type;
        // typedef T*                                                pointer;
        // typedef T&                                                reference;
        // typedef typename ::Node<value_type>                         Node;
        // typedef typename ::Node<const typename iterator_set_traits<value_type*>::value_type>    const_node;

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
        Iterator_set() {
            //std::cout << "Default iterator_set\n";
            _end_node = NULL;
            _Node = NULL;
        }
        Iterator_set(Node* end_node, Node* curr) { //Initalization constructor
            //std::cout << "Parameterized Iterator_set Constructor\n";
            _end_node = end_node;
            _Node = curr;
            // else
            // {
            //     std::cout << "affichhi had node ali 3titek f iterator_set\n";
            //     _Node->printNode();
            // }
            // std::cout << "Normalement 5asou yaffichi node 9banma ya5roj\n";
        }
        // Iterator_set(Iterator_set<const T> iter)
        // {
        //     iter.base();
        //     _Node = iter._Node;
        // }

        template< class IT> // conversion constructor
        Iterator_set(const Iterator_set<IT>& iter) {
        // Iterator_set(const Iterator_set& iter) {
            //std::cout << "Copy Constructor iterator_set\n";
            *this = iter;
            // _end_node = iter._end_node;
            // _Node = iter._Node;
        }

        template< class IT>
        Iterator_set& operator=(const Iterator_set<IT>& iter) {
        // Iterator_set& operator=(const Iterator_set& iter) {
            //std::cout << "Assignement Copy Constructor iterator_set\n";
            this->_end_node = (iter.base()).first;
            this->_Node = (iter.base()).second;
            //std::cout << _Node << " " << iter._Node << "\n";
            // if (_Node != _Tree->get_end())
            //     _Node->printNode();
            //std::cout << "walo\n";
            return *this;
        }
        ~Iterator_set() {
            //std::cout << "Destructor iterator_set\n";
        }

    // --------------------------------------------

    operator Iterator_set<const value_type>() {
        return Iterator_set<const value_type>(_end_node, _Node);
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
    Iterator_set& operator++() {
        //std::cout << "\n ------------ Pre increment ----------------- \n";
        _Node = _Node->next_node(_end_node);
        return *this;
    }
    // 2- Prefix decrement:
    Iterator_set& operator--() {
        //std::cout << "\n ------------ Pre idecrement ----------------- \n";
        _Node = _Node->previous_node(_end_node);
        return *this;
    }
    // 3- Postfix increment
    Iterator_set operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        Iterator_set tmp = *this; // create a copy
        //std::cout << tmp->first << "\n";
        ++(*this); // ++(*this); // call pre increment for *this
        //std::cout << tmp->first << "\n";
        return tmp;
    }
    // 4- Postfix decrement
    Iterator_set operator--(int) {
        Iterator_set tmp(*this); // create a copy
        --(*this); // ==>   --(*this); 
        return tmp;
    }

    // Step 4: Member friends : The operators [== != ]
    friend bool operator==(const Iterator_set& a, const Iterator_set& b) {
        return a._Node->value == b._Node->value;
    }

    friend bool operator!=(const Iterator_set& a, const Iterator_set& b) {
        // compare end_node deleted;
        return a._Node->value != b._Node->value;
    }
};
}

#endif
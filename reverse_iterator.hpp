# ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

    template <class Iter>
    class reverse_iterator {

    public:
        typedef typename ft::iterator_traits<Iter>::difference_type difference_type; // we need that in a-b
        typedef typename ft::iterator_traits<Iter>::value_type value_type;
        typedef typename ft::iterator_traits<Iter>::pointer pointer; // operator ->()
        typedef typename ft::iterator_traits<Iter>::reference reference; // operator []() && operator*() && operator=(int)
        typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category; 
    
    
    private:
        Iter _iterator;

    public:
        // Step 1: Constructors
        reverse_iterator() : _iterator() { // Default constructor
            //std::cout << "Default Iterator Constructor\n";
        }
        reverse_iterator(Iter iter) : _iterator(iter) { //Initalization constructor
            //std::cout << "Parameterized Iterator Constructor\n";
        }

        template< class IT>  // suppose Rak conversion constructor and we did not use conversion operator like the iterator
        reverse_iterator(const reverse_iterator<IT>& inst) {
        //reverse_iterator(const reverse_iterator& inst) { // Copy constructor
            //std::cout << "Copy Constructor of Iterator\n";
            *this = inst;
        }

        template< class IT>
        reverse_iterator& operator=(const reverse_iterator<IT>& inst) {
        //reverse_iterator& operator=(const reverse_iterator& inst) { // Assignement operator
            //std::cout << "Assignement Constructor of Iterator\n";
            this->_iterator = inst.base();
            return *this;
        }
        ~reverse_iterator() { // Destructor
            //std::cout << "Destructor of Iterator\n";
        }

    // Step 2: Implementing an iterator something like from STL
    // iterator is a nested class in your container.

//  ------------------ Accessors operator =, * and -> --------------------------- 

    // https://en.cppreference.com/w/cpp/language/cast_operator (No need to conversion I already use base() in iterator o)
    // You need to implement conversion constructor instead of conversion operator
    // template <class It>
    // reverse_iterator(const reverse_iterator<It>& inst) {
    //     this->_iterator = --inst.base();
    // }

    Iter base() const {
        return _iterator;
    }

    reference operator*() const {
        Iter tmp = _iterator;
        tmp--;
        return *(tmp);
    }
    reference operator[] (difference_type n) const { return *(_iterator - n -1);}

    pointer operator->() {
        Iter tmp = _iterator;
        tmp--;
        return tmp.operator->();
    }

//  --------------------  [iter + n] [iter - n]  ---------------------------------

    // 1- operator+(difference_type n) : 
        /* std::my_ReverseIterator::operator+
            my_ReverseIterator operator+(difference_type n) const;
        */
    reverse_iterator operator+(difference_type n) const {
        reverse_iterator  iter_addition(*this);
        iter_addition._iterator -= n;
        return iter_addition;
    }
    // 2- operator-(difference_type n) :
        /* std::my_ReverseIterator::operator-
            my_ReverseIterator operator-(difference_type n) const;
        */
    reverse_iterator operator-(difference_type n) const {
        reverse_iterator iter_soustraction(*this);
        iter_soustraction._iterator += n;
        return iter_soustraction;
    }
    // 3- operator+=(difference_type n) : 
        /* std::my_ReverseIterator::operator+=
            my_ReverseIterator operator+=(difference_type n) const;
        */
    reverse_iterator operator+=(difference_type n) {
        _iterator -= n;
        return *this;
    }
    // 4- operator-=(difference_type n) : 
        /* std::my_ReverseIterator::operator-=
            my_ReverseIterator operator-=(difference_type n) const;
        */
    reverse_iterator operator-=(difference_type n) {
        _iterator += n;
        return *this;
    }

// --------------------- Pre / Post crementation  --------------------------------

   // What is the diff between pre and post (increment/decrement) operator ??

    /*
        pre: [++it] ==> operator++()
            increment/decrement the variable, before assigning the value to the variable.
        post: [it++] ==> operator++(int)
            increment/decrement the variable, after assigning the value to the variable.
    */

    // 1- Prefix increment:
    reverse_iterator& operator++() {
        _iterator--;
        return *this;
    }
    // 2- Prefix decrement:
    reverse_iterator& operator--() {
        _iterator++;
        return *this;
    }
    // 3- Postfix increment
    reverse_iterator operator++(int) {
        //std::cout << "\n ------------ Post increment ----------------- \n";
        reverse_iterator tmp = *this; // create a copy
        _iterator--; // ==> ++(*this)
        return tmp;
    }
    // 4- Postfix decrement
    reverse_iterator operator--(int) {
        reverse_iterator tmp(*this); // create a copy
        _iterator++; // ==>   --(*this); 
        return tmp;
    }

//  ---------------------- Non-member (friend methods) -----------------------------------

    // Step 4: Member friends : The operators [n + a]
    /*  Template friend : [n + a]
        template <value_type>
        friend my_ReverseIterator<value_type> operator+(difference_type n, const my_ReverseIterator<value_type>& iter);
    */
    template <class Iterator>
    friend reverse_iterator operator+(difference_type n, const reverse_iterator<Iterator>& iter) {
    // friend reverse_iterator operator+(difference_type n, const reverse_iterator& iter) {
        return (iter + n);
    }
    // -------------------------------------------

    // Step 5: Member friends : The operators [== != ]  > < >= <= ]
    // template <class Iterator1, class Iterator2>
    // friend bool operator==(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b) {
    friend bool operator==(const reverse_iterator& a, const reverse_iterator& b) {    
        return a.base() == b.base();
    }

    // template <class Iterator1, class Iterator2>
    // friend bool operator!=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b) {
    friend bool operator!=(const reverse_iterator& a, const reverse_iterator& b) {
        return a.base() != b.base();
    }

    // Step 6: Member friends : The operators [iter1 - iter2]
    
    /* Template friend : [a - b]
        template <value_type>
        friend difference_type operator-(const my_ReverseIterator<value_type>& lhs, const my_ReverseIterator<value_type>& rhs);
    */
    // template <class Iterator1, class Iterator2>
    // friend difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    friend difference_type operator-(const reverse_iterator& lhs, const reverse_iterator& rhs) {
        //std::cout << "operator - \n";
        // return std::distance(rhs.base(), lhs.base());  // distance(first, last) = last - first; ==> (rhs, lhs) = lhs - rhs;
        return (rhs.base() - lhs.base());
    }
    // ---------------------------------------------

    // Step 7: Member friends : The operators [ > < >= <= ]
    
    // template <class Iterator1, class Iterator2>
    // friend bool operator>(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b) {
    friend bool operator>(const reverse_iterator& a, const reverse_iterator& b) {
        // if ((a.base() - b.base()) > 0)
            // return true;
        // return false;
        return a.base() < b.base();
    }
    
    // template <class Iterator1, class Iterator2>
    // friend bool operator>=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b) {
    friend bool operator>=(const reverse_iterator& a, const reverse_iterator& b) {
        // return !(a < b);
        // if (a == b || a > b)
        //     return true;
        // return false;
        return a.base() <= b.base();
    }

    // template <class Iterator1, class Iterator2>
    // friend bool operator<(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b) {
    friend bool operator<(const reverse_iterator& a, const reverse_iterator& b) {
        // return !(a >= b);
        // if (a >= b)
        //     return false;
        // return true;
        return a.base() > b.base();
    }

    // template <class Iterator1, class Iterator2>
    // friend bool operator<=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b) {
    friend bool operator<=(const reverse_iterator& a, const reverse_iterator& b) {   
        // return (a.base() >= b.base());
    //     if (a > b)
    //         return false;
    //     return true;
        return a.base() >= b.base();
    }
};

}

#endif
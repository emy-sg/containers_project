# ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"


namespace ft {

template <class T, class Container = ft::vector<T> >
class stack
{
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

    protected:
        container_type c;
    
    public:
        explicit stack( const Container& cont = Container()) : c(cont) {
            // std::cout << "default constructor\n";
        }

        ~stack(){};
        
        stack& operator=( const stack& other ) {
            c = other.c;
        }

        bool empty() const {
            return c.empty();
        }

        size_type size() const {
            return c.size();
        }

        value_type& top() {
            return c.back();
        }
        
        const value_type& top() const {
            return c.back();
        }   

        void push (const value_type& val) {
            c.push_back(val);
        }

        void pop() {
            c.pop_back();
        }

     // Relational operators

    /*
        The "equality comparison" aka (operator==) is performed by first comparing sizes,
            and if they match aka sizes, the elements are compared sequentially using 
            operator==, stopping at the first mismatch aka "equal"
    */

    friend bool operator== (const stack& lhs, const stack& rhs) {
        return (lhs.c == rhs.c);
    }

    friend bool operator!= (const stack& lhs, const stack& rhs) {
        return (lhs.c != rhs.c);
    }
    
    /*
        The "lexicographical less-than" comparison:
            Returns "true" if the range [first, last1) compares "lexicographically less" than the range [first2, last2).
    */

    friend bool operator<  (const stack& lhs, const stack& rhs) {
        return (lhs.c < rhs.c);
    }

    friend bool operator<= (const stack& lhs, const stack& rhs) {
        return (lhs.c <= rhs.c);
    }

    friend bool operator>  (const stack& lhs, const stack& rhs) {
        return (lhs.c > rhs.c);
    }

    friend bool operator>= (const stack& lhs, const stack& rhs) {
        return (lhs.c >= rhs.c);
    }

};

}


#endif
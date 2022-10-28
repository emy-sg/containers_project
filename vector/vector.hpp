# ifndef vector_HPP
#define vector_HPP

/* vectors are just like arrays, 
 * 	cuz vectors use contiguous storage locations for their elements
 * 	but unlike arrays, their size can change dynamically, their storage being handled automatically by the container.
*
*  This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it.
*/
#include "../reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include "../enable_if.hpp"
#include "../compare.hpp"

#include <cstddef>
#include <exception>
#include <iostream>
#include <memory.h>
#include <new>
#include <stdexcept>


//  Why use of "explicit" keyword in C++ ? [ used with constructors ]
//==> It is used to mark "constructors" to not implicitly convert types in C++.


namespace ft {
    template <
        class T,
        class Alloc = std::allocator<T> >

class vector {
    
    public:

        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

    private:

        pointer _array; // value_type *_array;
        size_t _size;
        size_t _capacity;
        allocator_type _alloc;

    public:   // Member Methods of vector

// ---------------------- 1- Iterator -------------------------------------------

        // The first implementation of iterator that works fine, ma5adamch m3a const iterator
        typedef Iterator<value_type> iterator;
        typedef Iterator<const value_type>  const_iterator;

        // The second implementation of iterator that didn't work in the first time, but now all it's good
        // typedef my_Iterator<pointer> iterator;
        // typedef my_Iterator<const_pointer>  const_iterator;     

    //  -------------------------- [begin(), end()] ---------------------------------

        /*
            Returns an iterator pointing to the first element in the vector.
        */

        // iterator begin();  
        iterator begin() {
            return iterator(_array); // _array; // why not ? return iterator(_array);
        }
        // const_iterator begin()
        const_iterator begin() const {
            return const_iterator(_array);
        }

        /*
            Return:
                The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
        */
        // iterator end();
        iterator end() {
            return iterator(_array + size()); // WHY NOT? return iterator(_array + size());
        }
        //const_iterator end() const;
        const_iterator end() const {
            return const_iterator(_array + size());
        }

// --------------------- 2- Reverse_iterator ------------------------------------

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator; 

        //  -------------------------- [rbegin(), rend()] ---------------------------------

        //reverse_iterator rbegin();
        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }
        //const_reverse_iterator rbegin() const;
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        //reverse_iterator rbegin();
        reverse_iterator rend() {
            return reverse_iterator(begin());
        }
        //const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

// --------------------- 3- _alloc -------------------------------------

    /*
        Returns a copy of the allocator object associated with the vector
    */
 
    allocator_type get_allocator() const
    {
        //return allocator_type();
        return _alloc;
    }
        
// --------------------- 4- default constructor ---------------------------------
        //vector() {
        explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
            //std::cout << "Default vector constructor\n";
            _size = 0;
            _capacity = 0;
            _array = NULL;

            //std::cout << _array << "\n";
            //std::cout << "size " << i.size() << std::endl;  // size = 0
	        //std::cout << "max_size " << i.max_size() << std::endl; // max_size = 4611686018427387903
	        //std::cout << "capacity " << i.capacity() << std::endl; // capacity = 0
        }

        // 2- fill vector size n, with the same value
        //explicit vector (size_type n, value_type var) {
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
        {
            if (n == 0)
            {
                _size = 0;
                _capacity = 0;
                _array = NULL;
            }
            else
            {
            //std::cout << "Constructor fill vector size :" << n << "\n";
            _size = n;
            _capacity = n;

            // Step 1: Allocate for n value:
            // P.S: Calls to "Allocator::allocate" may throw (bad_allocator)
            // ==> throw an exception of type std::bad_alloc or a class derived from std::bad_alloc
            _array = _alloc.allocate(n);
            // Step 2: Construct for value_type var
            for (size_type i=0; i<n; i++)
                _alloc.construct(_array + i, val);
            }
        }

        // 3- range Constructor
        // ===> https://eli.thegreenplace.net/2014/sfinae-and-enable_if/
        template < class InputIterator >
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if <!ft::is_integral<InputIterator>::value, int>::type* = 0) : _alloc(alloc)
        {
            // std::cout << "Range Constructor of vector\n";
                
            // Step 1: Create an array of value_type;
            _size = 0;
            _capacity = 0;
            _array = NULL;
            
            // Step 2: Add new element in the vector[ Allocate && Construct ]
            // while (first != last)
            //     push_back(*(first++));
            assign(first, last);
        }

        // 4- Copy Constructor
        vector(const vector& inst) {
            //std::cout << "Copy Constructor of vector\n";
            _size = 0;
            _capacity = 0;
            _array = NULL;
            *this = inst;
        }

        vector& operator=(const vector& inst) {
            //std::cout << "Assignement copy Constructor of vector\n";

            //1- deallocate the _size element of _array
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_array + i);

            // 2- deallocate space for _capacity of _array
            if (_capacity > 0)
                _alloc.deallocate(_array, _capacity);

            // 3- Initialize capacity and size to default
            _capacity = inst._capacity;
            _size = inst._size;
            _alloc = inst._alloc;

            // 4- fill the array
            if (_capacity != 0)
            {
                _array = _alloc.allocate(_capacity);
                for (size_type j=0; j < inst._size; j++)
                    _alloc.construct(_array + j, inst._array[j]);
            }
            else
                _array = NULL;
            return *this;
        }

        // 5- Destructor
        ~vector() {
            //std::cout << "Destructor of vector\n";
            
            //3- destroy the _size element of _array
            // for (size_type i = 0; i < _size; i++)
            //     _alloc.destroy(_array + i);
            clear();
            // 4- deallocate space for _capacity of _array
            if (_capacity > 0)
                _alloc.deallocate(_array, _capacity);
    
        }

// ------- 5- empty(), size(),capacity(), max_size() ----------------------------

        bool empty() const {
            if (_size == 0)
                return true;
            return false;
        }
        size_type size() const {
            return _size;
        }
        size_type capacity() const {
            return _capacity;
        }
        //  What is max_size() ?
        // ==> It's the theoretical maximum number of items that could be put in your vector.
        size_type max_size() const {
            // if (sizeof(value_type) == 1)
            //     return (9223372036854775807); // case of char
            // else
                return (_alloc.max_size());
        }

// ----- 6- Accessors: at, operator[], front(), back(), data() ------------------

 // 5.1- std::vector::operator[]
    /*
        Returns a reference to the element at position n in the vector container.

        P.S:
            Calling front() on an empty container causes undefined behavior.
    */
    // reference operator[](size_type n);
    reference operator[](size_type n) {
        return _array[n];
    }
    // const_reference operator[](size_type n) const;
    const_reference operator[](size_type n) const {
        return _array[n];
    }

 // 5.2- std::vector::at()
    /*
        Returns a reference to the element at position n in the vector.
        
        The function automatically checks whether n is within the bounds of valid elements in the vector,
            if not, it throw an out_of_range exception.
    */
    // reference at(size_type n);
    reference at(size_type n) {
        if (n < _size)
            return _array[n];
        else
            throw std::out_of_range("vector::_M_range_check: __n >= this->size()");
    }
    // const_reference at(size_type n) const;
    const_reference at(size_type n) const {
        if (n < _size)
            return _array[n];
        else
            throw std::out_of_range("vector::_M_range_check: __n >= this->size()");
    }

 // 5.3- std::vector::front()
    /*
        This fct returns a reference to the First element in the vector.
        ==> Unlike vector::begin, which returns an iterator to this same element, 
            this returns a direct reference to it.
        P.S:
            Calling front() on an empty container causes undefined behavior.
    */
    // reference front();
    reference front() {
        return _array[0]; // First element has a position of O
    }
    // const_reference front() const;
    const_reference front() const {
        return _array[0]; // First element has a position of O
    }

 // 5.4- std::vector::back()
     /*
        This fct returns a reference to the past-the-end element in the vector.
        ==> Which is the theoretical element that would follow the last element in the vector.

        ==> Unlike vector::end, which returns an iterator to this same element, 
            this returns a direct reference to it.
        P.S:
            Calling back() on an empty container causes undefined behavior.
    */
    // reference back();
    reference back() {
        return _array[_size - 1]; //
    }
    // const_reference back() const;
    const_reference back() const {
        return _array[_size - 1]; // 
    }

 // 5.5- std::vector::data()
    /*
        Returns a direct pointer to the memory array used internally by the vector,
            to store its owned elements.
    */
    // pointer data();
    pointer data() {
        return _array;
    }
    // const_pointer data() const;
    const_pointer data() const {
        return _array;
    }

// -------- 7- reserve(), resize(), push_back, and pop_back ---------------------
 
 // 6.1- void reserve(size_type n);
    /*
        Reserve, request a change in capacity.
        if (n > capacity())
            reallocate for n elements
    */
    void reserve(size_type n)
    {
        // std::cout << "reserve fct \n";
        value_type* arr;

        if (n > capacity()) // reserve
        {
            //std::cout << "reserve()\n";
            // if (n > max_size())
            //     throw std::length_error("");
            //else
            {
                // 1- Allocate space:
                arr = _alloc.allocate(n);
                // 2- Construct:
                for (size_type i = 0; i < size(); i++)
                    _alloc.construct(arr+ i, _array[i]);

                // // 3- Destroy the other _array;
                for (size_type i = 0; i < size(); i++)
                    _alloc.destroy(_array + i);
                // 4- Deallocate the other _array;
                if (_capacity > 0)
                    _alloc.deallocate(_array, capacity());

                // 5- upgrade the capacity()
                _capacity = n;
                // 6- assign the new array to the _array
                _array = arr;
                
                //std::cout << "After reserve ==> size: " << size() <<  " | capacity " << capacity() << "\n";
            }
        }
    }

 // 6.2- void resize(size_type n, value_type val = value_type());

    /*
        Resizes the container so that it contains n elements.
        if (n < size()) // n is smaller than the current size
            reduce the container to its n first element (using pop_back aka destroy elemnents)
        else // n is greater than the current size, 
            expend the container to n size by adding new element at the end (using push_back)
    */
    void resize(size_type n, value_type val = value_type())
    {
        // std::cout << "resize() " << capacity() << " | " << size()  << "\n";

        // if (size() == n)
        //     return ;
        if (size() > n) // size > n value ==> pop_back()
        {
            //std::cout << "case 1\n";
            while (size() > n)
                pop_back();
        }
        else if (capacity() >= n) // capacity >= n value ==> construct new element
        {
            //std::cout << "case 2 " <<  size() << "\n";
            while (size() < n)
            {
                _alloc.construct(_array + size(), val);
                _size++;
            }
            // -------------- OR -----------------

            // while (size() > n)
            //     push_back(val);

        }
        else  // if capacity < n ==> reserve(upgrade capacity) then construct
        {
            //std::cout << "case 3\n";
            // if (capacity() % 2 == 0)
            //     reserve(capacity() * 2);
            // else
                reserve(n);
            //std::cout << "size: " << size() << "\n";
            while (size() < n)
            {
                _alloc.construct(_array + size(), val);
                _size++;
            }
        }
    }

 // 6.3- void push_back (const value_type& val);
    
    /*
        Adds a new element to the end of the vector.
        This effectively increases the container size by one,
            which causes an automatic reallocation if needed.
    */
    void push_back (const value_type& val) {
        // std::cout << "push_back " << size() << " | " << capacity()<< "\n";
        
        // 1- check if there is enough space to add new element
        if (size() == capacity())
        {
            // std::cout << "push_back double capacity\n";
            if (capacity() == 0)
                reserve(capacity() + 1);
            else
                reserve(capacity() * 2);
        }

        // ==> Still idk if I can replace those two beautiful lines by resize()
        //  SHOULD test if resize duplicate the capacity in case it's even number case
        //std::cout << "push_back kayn capacity\n";
        // 2- construct for the new element
        //std::cout << *(_array + _size - 1) << " " << (_array + _size) << std::endl;
        _alloc.construct(_array + _size, val);
        // std::cout << "end push_back kayn capacity\n";
        // 3- upgrade the size of the container
        _size++;
    }

 // 6.4- void pop_back();

    /*
        Removes the last element in the vector.
    */
    void pop_back() {
        //std::cout << "pop_back\n";
        // 1- Destroy the last element
        _alloc.destroy(_array + (_size - 1));

        // 2- increase the size of the container by one
        _size--;
    }

// --------------------- 8- erase (), clear() -----------------------------------
    /*
        Return an iterator pointing to the element that followed the element erased by the function.
        P.S:
            If position refers to the last element, then the end() iterator is returned.
            ...
            ...
    */
    iterator erase (iterator position)
    {
        iterator iter;
        
        iter = position + 1;

        while (iter != end())
        {
            _alloc.destroy((iter - 1).base());
            _alloc.construct((iter - 1).base(), *iter);
            ++iter;
        }
        _alloc.destroy((iter - 1).base());
        --_size;
        //iter = end(); 
        return position;
    }

    iterator erase (iterator first, iterator last)
    {
        //std::cout << "erase(range)\n";
        iterator iter = first;
        size_type n = 0;
        while (iter != last)
        {
            _alloc.destroy(iter.base());
            iter++;
            n++;
        }
        iter = first;
        while (last != end())
        {
            _alloc.construct(first.base(), *last);
            _alloc.destroy(last.base());
            first++;
            last++;
        }
        _size -= n;

        // while (first != last--)
        // {
        //     //std::cout << *first << std::endl;
        //     erase(first);
        // }
        //std::cout << "done erase range\n";
        return iter;
    }

    // void clear();
    /*
        Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
    */
    void clear() {
        //3- destroy the _size element of _array
        for (size_type i = 0; i < _size; i++)
            _alloc.destroy(_array + i);
        _size = 0;
    }

// --------------------- 9- Diff btw Assign() VS Insert() -----------------------

 // 9.1- assign()

    /*
        With assign vector content, 
            The container destroy all the content, and construct n new values.
        ==> The capacity of the container will not change only the size.

    */

    //void assign (size_type n, const value_type& val);
    void assign (size_type n, const value_type& val)
    {    
        //std::cout << "assign one element\n";   
        clear();
        //reserve(n * 2);  /// why ???????
        resize(n, val);
    }

    //template <class InputIterator>  void assign (InputIterator first, InputIterator last);
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last, typename ft::enable_if <!ft::is_integral<InputIterator>::value, int>::type* = 0) {
    //    std::cout << "assign of range\n";
        
        
        if ( first != last)
        {
            vector v;
            for (; first != last; first++)
                v.push_back(*first);
            
            clear();
            if (_capacity > 0)
                _alloc.deallocate(_array, _capacity);
            //*this = v;

            _array = _alloc.allocate(v.size());
            _size = v.size();
            _capacity = v.size();
            int i = 0;
            while (i < _size)
            {
                _alloc.construct(_array + i, v[i]);
                i++;
            }
        }
        // std::cout << "end of assign range\n";
        // else {
        // //     // 1- clear the vector
        //     clear();
        //     // 2- push_back
        //     while (first != last)
        //         push_back(*(first++));
        // // }
    }

 // 9.2- insert()

    /*
        With insert, no clearing of the container.
        ==> Inserting elements in positions other than the "vector end",
             causes the container to relocate all the elements after position.
             bcuz vectors use an array as their underlying storage.

        Return:
            An iterator that points to the first of the newly inserted elements.
    */

    //iterator insert (iterator position, const value_type& val);
    iterator insert (iterator position, const value_type& val) {
        //std::cout << "insert one element\n";

        size_type pos = position - begin();
        // if (position == end()) // case 1: position = end
        // {
        //     //std::cout << "case 1\n";
        //     push_back(val);
        //     position = _array + pos;
        // }
        // else
        // {
            if (_capacity < (size() + 1))
            {
                if (_capacity == 0)
                    reserve(1);
                // else
                //     reserve(_capacity * 2); // cuz 0*2 = 0
                else if ((_size + 1) <= (_capacity * 2))
                    reserve(_capacity * 2);
                else
                    reserve(_size + 1);
                position = _array + pos;
            }
            iterator iter;
            iter = end();
            _alloc.construct(iter.base(), value_type());
            while (iter != position) // already position changed
            {
                *iter = *(iter -1);
                iter--;
                //*iter = *(--iter);  // WHY ma5admatch 
            }
            *iter = val;  //_alloc.construct(iter.base(), val);
            ++_size;
            // 2- update the size 
        // }
        return position;
    }

    //void insert (iterator position, size_type n, const value_type& val);
    void insert (iterator position, size_type n, const value_type& val) {
        
        size_type pos = position - begin();
  
        // if (position == end()) // case 1: position = end
        // {
        //     while (n--)
        //         push_back(val);
        //     position = begin() + pos;
        // }
        // else ==> reserve
        if (n != 0)
        {
            if (_capacity < (size() + n))
            {
                if (_capacity == 0)
                    reserve(n);
                else if ((_size + n) <= (_capacity * 2))
                    reserve(_capacity * 2);
                else
                    reserve(_size + n);
                position = _array + pos;
            }

            // 2- 
            iterator iter;
            iter = end();  // iter = end()

            while (iter != (end() + n)) // iter = new_end
            {
                _alloc.construct(iter.base(), value_type());
                iter++;
            }
            if (iter != end())
                iter--;
            // 3-
            while (iter != (position + n - 1))
            {
                *iter = *(iter - n);
                iter--;
                // *iter = *(--iter);  // WHY ma5admatch  
            }
            
            // 4- fill the n position
            size_type j = 0;
            while (j++ < n)
            {
                *iter = val;
                iter--;
            }   
            // 5- update the size 
            _size += n;
        }
    }

    //template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last);
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if <!ft::is_integral<InputIterator>::value, int>::type* = 0) {
        // std::cout << "error Insert range\n";
        //1- create a tmp vector
        if (first != last )
        {
        vector tmp(first, last);
        // 2- size of tmp
        size_type n = tmp.size();
        size_type pos = position - begin();
        // 3- reserve enough storage
        if (_capacity < (size() + n))
        {
            if (_capacity == 0)
                reserve(n);
            else if ((_size + n) <= (_capacity * 2))
                reserve(_capacity * 2);
            else
                reserve(_size + n);
            position = _array + pos;
        }

        // 4- like [insert fill method]
        iterator iter;
        iter = end();  // iter = end()
        while (iter != (end() + n)) // iter = new_end
        {
            _alloc.construct(iter.base(), value_type());
            iter++;
        }
        iter--;
        while (iter != (position + n - 1))
        {
             *iter = *(iter - n);
            iter--;
        }       
        // 4- fill the n position
        iterator tmp_iter = tmp.end();
        if (tmp.end() != tmp.begin())
            tmp_iter--;
        while (tmp_iter >= tmp.begin())
        {
            *iter = *tmp_iter;
            iter--;
            tmp_iter--;
        }   
        // 5- update the size 
        _size += n;
        }
        // while (first != last)
        // {
        //     position = insert(position, *(first)); // return new position
        //     position++;
        //     first++;
        // }
    }

// ---------------------- 10- swap ----------------------------------------------

    /*
    */

    // void swap (vector& x);
    void swap (vector& x) {
        std::swap(_alloc, x._alloc);
        std::swap(_size, x._size);
        std::swap(_capacity, x._capacity);
        std::swap(_array, x._array);
    }

// ---------------------- 11- Non Members functions  -----------------------



 // Relational operators

    /*
        The "equality comparison" aka (operator==) is performed by first comparing sizes,
            and if they match aka sizes, the elements are compared sequentially using 
            operator==, stopping at the first mismatch aka "equal"
    */

    friend bool operator== (const vector& lhs, const vector& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator!= (const vector& lhs, const vector& rhs) {
        if (lhs.size() != rhs.size())
            return true;
        return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    /*
        The "lexicographical less-than" comparison:
            Returns "true" if the range [first, last1) compares "lexicographically less" than the range [first2, last2).
    */

    friend bool operator<  (const vector& lhs, const vector& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    friend bool operator<= (const vector& lhs, const vector& rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>  (const vector& lhs, const vector& rhs) {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    friend bool operator>= (const vector& lhs, const vector& rhs) {
        return !(lhs < rhs);
    }
};

// // ------- 11- Non Members functions aka friend -----------------------

//     template <class T, class Alloc>
//     void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
//         x.swap(y);
//     }

//  // Relational operators

//     /*
//         The "equality comparison" aka (operator==) is performed by first comparing sizes,
//             and if they match aka sizes, the elements are compared sequentially using 
//             operator==, stopping at the first mismatch aka "equal"
//     */

//     template <class T, class Alloc>
//     bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
//         if (lhs.size() != rhs.size())
//             return false;
//         return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
//     }

//     template <class T, class Alloc>
//     bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
//         if (lhs.size() != rhs.size())
//             return true;
//         return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
//     }
    
//     /*
//         The "lexicographical less-than" comparison:
//             Returns "true" if the range [first, last1) compares "lexicographically less" than the range [first2, last2).
//     */

//     template <class T, class Alloc>
//     bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
//         return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
//     }

//     template <class T, class Alloc>
//     bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
//         return !(lhs > rhs);
//     }

//     template <class T, class Alloc>
//     bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
//         return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
//     }

//     template <class T, class Alloc>
//     bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
//         return !(lhs < rhs);
//     }

    template< class T, class Alloc >
    void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
    {
        lhs.swap(rhs);
    }

}

#endif
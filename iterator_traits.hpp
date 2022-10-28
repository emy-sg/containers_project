# ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iostream>

// Few Infos About Templates:
/*
    "The only portable way of using templates is to implement them in header files by using inline functions"
    ==> "inline" means "implementation at the place of declaration, (inside the class)"
    Why?
     bcuz the compiler create an instance of the template class/function each time
    ==> Templated classes/functions must be defined in the header files while implementation.
Hachi ali gal "Hellio" bach ga3ma yatla3 lina error f compilation dial template instantiation"
*/
// Ressource:
//  https://en.cppreference.com/w/cpp/iterator/iterator_traits

namespace ft {

/*
    std::iterator_traits : is the type trait class that provides uniform interface to the properties of 
        iterator types.
*/

// Iter : is the "iterator type" to retrieve properties for;
template <class Iter>
struct iterator_traits {
    public:
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
    typedef typename Iter::iterator_category iterator_category;
};

// This type trait, may be specialized for user-provided types that may be used as iterators.
// The standard library provides partial specializations for pointer types "T*", which makes it possible to use all iterator-based algorithms with raw pointers.
template <class T>
struct iterator_traits<T*> {
    public:
    typedef typename std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
    public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef std::random_access_iterator_tag iterator_category; 
};

}

 /*If you go by dictionary, a trait means feature/attribute.
In C++, iterator traits means also the featrue/attribute of C++ iterator.

Before digging further, let's understand the basic design of iterator c++.

In STL(Standard Template Library), 3 things are meaningful and important:
	1- Containers: 
	2- Algorithms
	3- Iterator

	//////////////////////////////////////////////
	
Documentation:
	https://accu.org/journals/overload/9/43/frogley_442/
*/

#endif
# ifndef SET_HPP
#define SET_HPP


#include "../pair.hpp"
#include "../compare.hpp"
#include "Tree.hpp"
#include "set_iterator.hpp"
#include "../reverse_iterator.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <cstddef>
#include <memory.h>

namespace ft {

template <
	class T,
	class Compare = std::less<T>,
	class Alloc = std::allocator<T> >
class set {

// --------------------------- 1- Members Types are public ------------------------------
	
	public:

        typedef T	key_type;
        typedef T	value_type;

		typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef Compare key_compare;
		typedef Compare value_compare;

        typedef Alloc allocator_type;

        typedef value_type& reference;
        typedef const value_type& const_reference;

        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

// --------------------------- 2- Private attributes ------------------------------------

	private:
	
		Tree<key_type, key_compare, allocator_type> _Tree; // Idk why: when I use pointer to _Tree* ==> I get segmentation dump
		allocator_type _alloc;  // type of allocator used in this set
		key_compare _compare;	// type of comparetor used in this set



public: // ===> 3- Public Member Methods of set 

//	-------------------------- 3.1- Canonical Form of set ---------------------------------

	explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _Tree(alloc, comp), _alloc(alloc), _compare(comp)
	{
		
		//std::cout << "Default constructor of set\n";
	}
	
	~set()
	{
		//std::cout << "set destructor\n";
		clear();
	}

	template <class InputIterator>
	set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _Tree(alloc, comp), _alloc(alloc), _compare(comp)
	{
		while (first != last)
			insert(*(first++));
	}

	set(const set& inst) : _Tree(inst._alloc, inst._compare)
	{
		//std::cout << "Copy constructor of set\n";

		// Problem deep copy and shallow copy
		insert(inst.begin(), inst.end());
	}

	set& operator=(const set& inst) {
		//std::cout << "Assignemenet copy constructor of set\n";
		// Problem deep copy and shallow copy
		//This path is very wrong[Za3ma calling the _Tree assignement operator] *_Tree = *(inst._Tree);
		// Which is in this case useless, we can call insert for use
		clear();
		insert(inst.begin(), inst.end());
		return *this;
	}

// --------------------------- 3.2- get_allocator(), key_comp(), value_comp() -------------

	// -------------------- get_allocator() --------------
	/*
		Returns a copy of the allocator object associated with the set.
	*/

	allocator_type get_allocator() const {
		return allocator_type();
	}

	// -------------------- key_comp() --------------
	/*
		key_comp() : return "key comparison" object.
	*/
	//key_compare key_comp() const ==> Returns a copy of the comparison object used by the container to compare keys.

	key_compare key_comp() const {
		return key_compare();
	}

	// ------------------- value_comp() --------------
	/*
		value_comp(): return value_comp() object.
		==> An object of the class that we had just declared inside the class
	*/
	// value_compare value_comp() const;

	value_compare value_comp() const {
		return value_compare(key_comp());
	}

// --------------------------- 3.3- size() and max_size() ---------------------------------

    // 1- std::set::empty() ==> [bool empty() const;]
    bool empty() const {
        if (size() == 0)
            return true;
        return false;
    }
    // 2- std::set::size() ==> [return the size (number of elements)]
    size_type size() const {
	    return _Tree.getSize();
    }
    // 3- std::set::max_size() 
	size_type max_size() const {
        // if (sizeof(value_type) == 1)
        //     return (9223372036854775807);
        // else
            return (get_allocator().max_size());
    }

//  -------------------- 3.4- Typedef of Iterator [begin(), end()] ------------------------

	
		// typedef typename ft::Iterator_set<RBTree<key_type, value_type, allocator_type>, value_type > iterator;
		// typedef typename ft::Iterator_set<RBTree<key_type, value_type, key_compare, allocator_type>, value_type > iterator;
		// typedef typename ft::Iterator_set<RBTree<key_type, value_type, key_compare, allocator_type>, const value_type > const_iterator;
	
	
	typedef typename ft::Iterator_set<value_type> iterator;
	typedef typename ft::Iterator_set<const value_type> const_iterator;

	/*
		Returns an iterator referring to the first element in the set container.
	*/
	// iterator begin();
	iterator begin() {
		//return _Tree.get_begin();
    	return iterator(_Tree.get_end(), _Tree.get_begin());
		
	}
	// const_iterator begin() const {};
	const_iterator begin() const {
		// return const_iterator((Node<const value_type>*)_Tree.get_end(), (Node<const value_type>*)_Tree.get_begin());
		return const_iterator(_Tree.get_end(), _Tree.get_begin());

	}

	/*
		Returns an iterator referring to the past-the-end element in the set container
	*/
	// iterator end();
	iterator end() {
		//return _Tree.get_end();
    	return iterator(_Tree.get_end(), _Tree.get_end());
	}
	// const_iterator end() const {};
	const_iterator end() const {
		//return _Tree.get_end();
    	// return const_iterator((Node<const value_type>*)_Tree.get_end(), (Node<const value_type>*)_Tree.get_end());
    	return const_iterator(_Tree.get_end(), _Tree.get_end());

	}

//  ------------------ 3.5- Typedef of reverse_iterator [rbegin(), rend()]--------------------
	
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;

	/*
		Returns a reverse iterator pointing to the last element in the container (reverse beginning).
	*/
	//reverse_iterator rbegin();
	reverse_iterator rbegin() {
	    return reverse_iterator(end());
	}
	//const_reverse_iterator rbegin() const;
	const_reverse_iterator rbegin() const {
	    return const_reverse_iterator(end());
	}

	/*
		Returns a reverse iterator pointing to the theoretical element before the first element in the set container (reverse end).
	*/
	//reverse_iterator rbegin();
	reverse_iterator rend() {
	    return reverse_iterator(begin());
	}
	//const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const {
	    return const_reverse_iterator(begin());
	}

//	------------------------ 3.7- find(), count(), lower/uperbound(), equal_range() -------
 
 // 4- std::set::find() 

    // iterator find(const key_type& k);
    iterator find(const key_type& k) {
        Node<value_type>* node;
        iterator it;


		//std::cout <<  "--------------------------- Lets search for this Key ==> " << k << " --------------------------------------\n";
        node = _Tree.searchByKey(k);
		//std::cout << " --------------------------- search done -------------------------------------------------- \n";
        if (!node)
		{
			//std::cout << "=====> NOOO node find() WITH THAT KEY ==> " << k << "\n\n";
            return (this->end()); // return _end_node
		}
		//std::cout << "=====> Node find() WITH THAT KEY ==> " << k << " " << node << "\n\n";
		//node->printNode();
        it = iterator(_Tree.get_end(), node);//it = node; // Is this construct from node to Iterator and How ????????????
		//std::cout << "\n The content of the iterator in find() method " << it->first << " | " << it->second << "\n";
        return it;
    }

    // const_iterator find(const key_type& k) const;
	const_iterator find(const key_type& k) const {
		Node<value_type>* node;
        const_iterator it;


		//std::cout <<  "--------------------------- Lets search for this Key ==> " << k << " --------------------------------------\n";
        node = _Tree.searchByKey(k);
		//std::cout << " --------------------------- search done -------------------------------------------------- \n";
        if (!node)
		{
			//std::cout << "=====> NOOO node find() WITH THAT KEY ==> " << k << "\n\n";
            return (this->end()); // return _end_node
		}
		//std::cout << "=====> Node find() WITH THAT KEY ==> " << k << " " << node << "\n\n";
		//node->printNode();
        it = const_iterator(_Tree.get_end(), node);//it = node; // Is this construct from node to Iterator and How ????????????
		//std::cout << "\n The content of the iterator in find() method " << it->first << " | " << it->second << "\n";
        return it;
	}

 // 5- std::set::count()

	/*
		Searches in the container for the elements with a key equivalent to K.

		And because all elements in a set container have unique key, the fct can only
			return 1 (if the element is found) or zero (otherwise);
	*/
	
	// size_type count (const key_type& k) const;
	size_type count (const key_type& k) const {
		//if (_Tree.searchByKey(k) == NULL)
		if (find(k) == end())
			return (0);
		return 1;
	}

 // 6- std::set::upper_bound

	/*
		Returns an iterator pointing to the first element that is greater than key.
		==> If no such element is found, past-the-end (end() iterator) is returned.

		The function returns an iterator pointing to the immediate next element which is just greater than k.
		If the key passed in the parameter exceeds the maximum key in the container, then returned iterator points to set_name.end().

	*/

	// iterator upper_bound( const Key& key );
	iterator upper_bound( const value_type& key ) {
		//return lower_bound(key);
		iterator it = iterator(_Tree.get_end(), _Tree.searchLowerKey(key));
		if (it == end())
			return it;
		if (*it == key)
			return ++it;
		// else
		 	return it;
		// Node<value_type>* node;


		// node = _Tree.searchByKey(key);
		// if (node)
		// 	return iterator(_Tree.get_end(), _Tree.next_node(node));
		// return end();
	}

	// const_iterator upper_bound( const Key& key ) const;
	const_iterator upper_bound( const value_type& key ) const {

		const_iterator it = const_iterator(_Tree.get_end(), _Tree.searchLowerKey(key));
		if (it == end())
			return it;
		if (*it == key)
			return ++it;
		// else
		 	return it;
		//return iterator(_Tree.get_end(), _Tree.searchUpperKey(key));
		// return lower_bound(key);
		// Node<value_type>* node;

		
		// node = _Tree.searchByKey(key);
		// if (node)
		// 	return iterator(_Tree.get_end(), _Tree.next_node(node));
		// return end();
	}

 // 7- std::set::lower_bound

	/*
		The function returns an iterator pointing to the key in the set container which is equivalent to k passed in the parameter.
		In case k is not present in the set container, the function returns an iterator pointing to the immediate next element which is just greater than k.
		If the key passed in the parameter exceeds the maximum key in the container, then the returned iterator points to the number of elements in the set as key and element= any element
	*/

	//iterator lower_bound( const Key& key );
	iterator lower_bound( const value_type& key ) {
		return iterator(_Tree.get_end(), _Tree.searchLowerKey(key));
		// // node = _Tree.searchLowerKey(key);
		// node = _Tree.searchByKey(key);
		// if (node)
		// 	return iterator(_Tree.get_end(), node);
		// return end();
	}

	//const_iterator lower_bound( const Key& key ) const;
	const_iterator lower_bound( const value_type& key ) const {
		// Node<value_type>* node;

		return const_iterator(_Tree.get_end(), _Tree.searchLowerKey(key));
		// node = _Tree.searchByKey(key);

		// if (node)
		// {
		// 	return iterator(_Tree.get_end(), node);
		// }
		// return end();
	}

 // 8- std::set::equal_range

	/*
		Returns the bounds of a range includes the elements in the container.
			aka [lower_bound, upper_bound]
		
		==> If no matches are found, the range returned has a length of zero,
			with both iterators pointing to the first element thas has a key
	*/

	//pair<iterator,iterator> equal_range (const key_type& k);
	ft::pair<iterator,iterator> equal_range (const key_type& k) {
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}

	//pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
	ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}

//	-------------------------- 3.8- Methods insert(), erase() -----------------------------
 
 // 11- std::set::insert
    
	// 11.1- std::pair<iterator, bool> insert(const value_type& val);
	ft::pair<iterator, bool> insert(const_reference val) {
		
		iterator iter_exist;

        //if (empty())
		//	std::cout << "--- set is empty ----\n";

		iter_exist = find(val);
		if (iter_exist == this->end())
		{
		//	std::cout << "        --------Element not found -------                \n";
			iter_exist = iterator(_Tree.get_end(), _Tree.insertion_RBTree(val));
			//_Tree.printTree();
		//	std::cout << (*iter_exist) << " | " << (*iter_exist).second << "\n";
		//	std::cout << "-----------------------------------------------------------\n";
			return ft::make_pair(iter_exist, true);
		}
		return ft::make_pair(iter_exist, false);
	}
	
	// 5.2- iterator insert(iterator position, const value_type& val);
	iterator insert(iterator position, const_reference val) {
		iterator iter;
		
		iter = find(val);
		if (iter == position)
			return position;
		else
		 	return (insert(val).first);
	}
	
	// 5.3- template <class Iterator> void inset(InputIterator first, InputIterator last);
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last)
		{
			insert(*first);
			first++;
		}
	}

 // 6- std::set::erase

	// 6.1- size_type erase(const key_type& k);
	size_type erase(const key_type& key)
	{
		return _Tree.erase(key);
	}
	
	// 6.2- void erase(iterator position);
	void erase(iterator position)
	{
		_Tree.erase(*(position));
	}
    
	// 6.3- void erase(iterator first, iterator last);
	void erase(iterator first, iterator end)
	{
		while (first != end)
		{
			//std::cout << first->first << " | " << first->second << "\n";
			erase(first++); // use of preincrementation and not postincrementation, thank U
		}
		// std::cout << _Tree._end_node << "\n";
		// _Tree._begin_node = &_Tree._end_node;
	}

 // 7- clear
	void clear()
	{
		// if (empty())
		// {
		// 	//std::cout << "Can't clear anything the tree is empty\n";
		// }
		// else
			erase(begin(), end());
	}

// 	----------------------------- 3.9- swap() ---------------------------------------------

	/*
		Exchanges the content of the container by the content of inst[which is another set of the same type]/

		==> Notice that a non-member function exists with the same name.

		P.S:
			- Exchanges the contents of the container with those of "other".
			==> Does not invoke any "move", "copy", or "swap operations on individual elements".
	*/

	// void swap (set& inst);
	void swap(set& inst) {

		std::swap(_alloc, inst._alloc);
		std::swap(_compare, inst._compare);  // we can't swap two sets with different compare

		size_type size;
		size = inst._Tree.getSize();
		inst._Tree.setSize(_Tree.getSize());
		_Tree.setSize(size);

		Node<value_type> * begin;
		begin = inst._Tree.get_begin();	
		inst._Tree.set_begin(_Tree.get_begin());
		_Tree.set_begin(begin);

		Node<value_type> * end;
		end = inst._Tree.get_end();	
		inst._Tree.set_end(_Tree.get_end());
		_Tree.set_end(end);

	}

// ---------------------- 11- Non Members functions  -----------------------

 // Relational operators

    /*
        The "equality comparison" aka (operator==) is performed by first comparing sizes,
            and if they match aka sizes, the elements are compared sequentially using 
            operator==, stopping at the first mismatch aka "equal"
    */

    friend bool operator== (const set& lhs, const set& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator!= (const set& lhs, const set& rhs) {
        if (lhs.size() != rhs.size())
            return true;
        return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    /*
        The "lexicographical less-than" comparison:
            Returns "true" if the range [first, last1) compares "lexicographically less" than the range [first2, last2).
    */

    friend bool operator<  (const set& lhs, const set& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    friend bool operator<= (const set& lhs, const set& rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>  (const set& lhs, const set& rhs) {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    friend bool operator>= (const set& lhs, const set& rhs) {
        return !(lhs < rhs);
    }



};

template< class Key, class Compare, class Alloc >
void swap( set<Key,Compare,Alloc>& lhs,
           set<Key,Compare,Alloc>& rhs )
	{
        lhs.swap(rhs);
    }

}

#endif
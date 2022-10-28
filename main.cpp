#include "pair.hpp"
#include "vector/vector.hpp"
#include "stack/stack.hpp"
#include "set/set.hpp"
#include "map/map.hpp"
#include <iterator>
#include <vector>

int main()
{

    std::cout << "use tester\n";

    // ft::vector<int> v(5, 5);

    // ft::vector<int>::iterator it = v.begin();
    // ft::vector<int>::const_iterator cit = v.end();

    // while (it != cit)
    // {
    //     std::cout << *(it++) << "\n";
    // }
    // while (cit != it)
    // {
    //     std::cout << *(it++) << "\n";
    // }

    //  --------------------------------------

    // ft::vector<int> v(5, 5);
    // ft::vector<int> v1(5, 1);


    // ft::vector<int>::iterator it = v.begin();
    // ft::vector<int>::const_iterator it1 = v1.begin();

    // while (it != v.end() && it1 != v1.end())
    // {
    //     std::cout << *(it++) << " | " <<  *(it1++)<< "\n";
    // }
    // std::cout << "Calling swap\n";
    // ft::swap(v, v1);

    // ft::vector<int>::iterator s_it = v.begin();
    // ft::vector<int>::const_iterator s_it1 = v1.begin();

    //  while (s_it != v.end() && s_it1 != v1.end())
    // {
    //     std::cout << *(s_it++) << " | " <<  *(s_it1++)<< "\n";
    // }

    // -----------------------------------------

    //  ft::vector<int> v(5, 5);
    // ft::vector<int> v1(5, 1);

    // if (v > v1)
    //     std::cout << "v is greater than v1\n";
    // else if (v == v1)
    //     std::cout << "v is equal to v1\n";
    // else
    //     std::cout << "v is less strict to v1\n";

    // --------------------MAP ---------------------

    // ft::map<int, int> m;

    // m[0] = 1;
    // m[1] = 2;
    
    // m.insert(m.begin(), ft::make_pair(1, 1));
    // m.insert(m.begin(), ft::make_pair(2, 1));
    // m.insert(ft::make_pair(1, 5));

    // ft::map<int, int>::iterator it = m.begin();
    // ft::map<int, int>::const_iterator cit = m.end();

    // //std::cout << m.size() << "\n";
    // while (it != cit)
    // {
    //     std::cout << it->first <<  " | " << (it)->second << "\n";
    //         it++;
    // }

    // while (cit != it)
    // {
    //     std::cout << (it)->first << " | " << (it)->second << "\n";
    //     it++;
    // }

    //  --------------------------------------

    // ft::map<int, int> m;

    // m.insert(m.begin(), ft::make_pair(1, 1));
    // m.insert(m.begin(), ft::make_pair(2, 1));
    // m.insert(ft::make_pair(1, 5));
    // // m.insert(ft::make_pair(3, 5));
    // ft::map<int, int>::iterator it = m.begin();
    // ft::map<int, int>::const_iterator cit = m.end();

    // while (it != cit)
    // {
    //     std::cout << it->first <<  " | " << (it)->second << "\n";
    //         it++;
    // }


    // ft::map<int, int> m1;

    // m1.insert(m.begin(), ft::make_pair(9, 9));
    // m1.insert(m.begin(), ft::make_pair(2, 2));
    // m1.insert(ft::make_pair(1, 1));

    // ft::map<int, int>::iterator it1 = m1.begin();
    // ft::map<int, int>::const_iterator cit1 = m1.end();

    // //std::cout << m.size() << "\n";

    // while (cit1 != it1)
    // {
    //     std::cout << (it1)->first << " | " << (it1)->second << "\n";
    //     it1++;
    // }

    // std::cout << "Calling swap\n";

    // ft::swap(m, m1);

    // ft::map<int, int>::iterator s_it = m.begin();
    // ft::map<int, int>::const_iterator s_cit = m.end();

    // while (s_it != s_cit)
    // {
    //     std::cout << s_it->first <<  " | " << (s_it)->second << "\n";
    //         s_it++;
    // }

    // ft::map<int, int>::iterator s_it1 = m1.begin();
    // ft::map<int, int>::const_iterator s_cit1 = m1.end();

    // while (s_cit1 != s_it1)
    // {
    //     std::cout << (s_it1)->first << " | " << (s_it1)->second << "\n";
    //     s_it1++;
    // }

    //  ------------------------------

  // ft::map<int, int> m;

    // m.insert(m.begin(), ft::make_pair(1, 1));
    // m.insert(m.begin(), ft::make_pair(2, 1));
    // m.insert(ft::make_pair(1, 5));
    // // m.insert(ft::make_pair(3, 5));
    // ft::map<int, int>::iterator it = m.begin();
    // ft::map<int, int>::const_iterator cit = m.end();

    // while (it != cit)
    // {
    //     std::cout << it->first <<  " | " << (it)->second << "\n";
    //         it++;
    // }


    // ft::map<int, int> m1;

    // m1.insert(m.begin(), ft::make_pair(9, 9));
    // m1.insert(m.begin(), ft::make_pair(2, 2));
    // m1.insert(ft::make_pair(1, 1));

    // if (m > m1)
    //      std::cout << "m is greater than m1\n";
    // else if (m == m1)
    //     std::cout << "m is equal to m1\n";
    // else
    //     std::cout << "m is less strict to m1\n";


}
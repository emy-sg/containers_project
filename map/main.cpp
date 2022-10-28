#include "map.hpp"
#include <map>
#include <type_traits>
#include <strings.h>

int main() {
    // ft::map<int, int> me;

    // if (me.empty())
    //     std::cout << "map is empty\n";
    // else
    //     std::cout << "size of map is " << me.size() << "\n";

    // -------- Test Iterator ---------------
    // std::map<int, int> m;
    
    // m[0] = 1;
    // m[1] = 2;
    // m[2] = 3;

    // std::map<int, int>::iterator iter(m.begin());
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";
    // --iter;
    // std::cout << iter->second << "\n";

    ////////////////////////////////////////////

    // ft::map<int, int> m;
    // ft::map<int, int>::iterator iter;

    // std::map<int, int> m;
    // std::map<int, int>::iterator iter;

    // iter = m.begin();
    // //iter++;
    // std::cout << iter->second << "\n";
    // iter++;
    // std::cout << iter->second << "\n";
    // iter++;
    // std::cout << iter->second << "\n";

//  -------------- at() and operator[] and erase ---------------
    // ft::map<int, int> my;
    // my[1] =1;
    // my[2] = 2;
    // my[3] =3;
    // my[100] = 100;

    // ft::map<int, int>::iterator it = my.begin();
    // //while (it != my.end())
    // {
    //     std::cout << my.size() << "\n";
    //     std::cout << "begin  " << my.begin()->first << "\n";
    //     my.erase(it);
    //     std::cout << my.size() << "\n";
    //     std::cout << "begin  " << my.begin()->first << "\n";
    //     it++;
    // }
    //my.call_print();
    //my.erase(2);
    //my.call_print();
    // my.insert(std::make_pair("I", 0));
    // my.insert(std::make_pair("YOU", 1));
    // my.insert(std::make_pair("HE", 2));
    // std::cout << "         --------------------- TEST find() ------------------------           \n \n";
    // // std::cout <<  my.find("YOU")->first << " | " <<  my.find("YOU")->second << "\n";
    // std::cout <<  my.find("I")->first << " | " <<  my.find("I")->second << "\n";
    //my.call_print();

//  ---------------- swap() -------------------------
    // std::map<int, int> m1;
    // m1[1] =5;
    // m1[2] = 6;
    // m1[3] =7;
    // m1[4] = 8;

    // std::map<int, int> m2;
    // m2[1] =1;
    // m2[2] = 2;

    // m1.swap(m2);
    // std::cout << "m1 size: " << m1.size() << "\n";
    // std::map<int, int>::iterator it1 = m1.begin();
    // while(it1 != m1.end())
    // {
    //     std::cout << it1->second <<"\n";
    //     it1++;
    // }

    // std::cout << "m2 size: " << m2.size() << "\n";
    // std::map<int, int>::iterator it2 = m2.begin();
    // while(it2 != m2.end())
    // {
    //     std::cout << it2->second <<"\n";
    //     it2++;
    // }

    //////////////// erase and clear  -------------------
        // std::map<char, int> m;
        // ft::map<char, int> ft_m;
        // m['x'] = 100;
        // m['y'] = 200;
        // m['z'] = 300;

        // ft_m['x'] = 100;
        // ft_m['y'] = 200;
        // ft_m['z'] = 300;

        // m.clear();
        // ft_m.clear();

        // m['a'] = 1101;
        // m['b'] = 2202;

        // ft_m['a'] = 1101;
        // ft_m['b'] = 2202;

        // ft_m.call_print();
        
        // m.clear();
        // ft_m.clear();

        // ft_m.call_print();

        // std::cout << m.size() << " | " << ft_m.size() << "\n";

    ////////////////// assign() and insert() -------------------------

        // ft::map<char, int> m;

        // m.clear();

    ///////////////////  iterator --------------------
//     const ft::map<int, int> my_map;
// ft::map<int, int>::const_iterator it = my_map.begin();

    /////////////// swap ----------------------

        std::map<char, int> foo, bar;
        ft::map<char, int> ft_foo, ft_bar;

        foo['x'] = 100;
        foo['y'] = 200;

        ft_foo['x'] = 100;
        ft_foo['y'] = 200;

        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;

        ft_bar['a'] = 11;
        ft_bar['b'] = 22;
        ft_bar['c'] = 33;

        //ft_bar.call_print();
        foo.swap(bar); // 3 | 2
        ft_foo.swap(ft_bar);
        // ft_foo.call_print();
        // ft_bar.call_print();

}
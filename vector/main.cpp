#include "vector.hpp"
#include <iterator>
#include <vector>

int main() {

    //ft::vector<int> vec; // default constructor
    //ft::vector<int> vec(5, 6);

   //   --------------------------  std::vector<int>::iterator().base();  ----------------------------------
    
    // ft::vector<int> v(3, 4);
    // ft::vector<int>::iterator it, it1;

    // ft::vector<int> v(3, 4);
    // ft::vector<int>::iterator it, it1;

    // --------- at() && [] ----------------

    // std::cout << v[0] << "\n";
    // std::cout << v[2] << "\n";
    // std::cout << "size: " << v.size() << "\n";
    // v[3] = 9;
    // v[4] = 4;
    // v[5] = 6;
    // std::cout << "size: " << v.size() << "\n";
    // std::cout << v[9] << "\n";

    // it = v.begin();
    // it1 = v.begin() + 1;

    // std::cout << (it <= it1) << "\n";
    // /*----------------------------------*/
    // /*------------ ft::vector ---------*/
    // ft::vector<int> my_v(3, 4);
    // ft::vector<int>::iterator my_it, my_it1, tmp;
    // my_it = my_v.begin();
    // my_it1 = my_v.begin() + 1;

    // std::cout << (my_it <= my_it1) << "\n";
    
//--------------------------------------------------------

 
//  -----------------------------------------

    /*ft::vector<int> v(2, 5);
    std::vector<int> vec(2, 5);

    ft::vector<int>::iterator iter;
    iter = v.begin();
    std::cout << "v size " << v.size() << " ==> " << v[0] << " | " << v[1] << " | " << v[2] << "\n";
    std::cout << *(iter) << " | " << iter[0] << " | " << iter[1] << "\n";
    std::cout << *(++iter) << " | " << iter[0] << " | " << iter[1] << "\n";

    std::vector<int>::iterator ite;
    ite = vec.begin();
    std::cout << "vec size " << vec.size()  << " ==> " << vec[0] << " | " << vec[1] << " | " << vec[2] << "\n";
    std::cout << *(ite) << " | " << ite[0] << " | " << ite[1] << "\n";
    std::cout << *(++ite) << " | " << ite[0] << " | " << ite[1] << "\n";*/
    //////////////////////////////////

    // std::cout << v.at(2) << "\n";
    // std::cout << v[5] << "\n";

    // std::cout << v.at(2) << "\n";
    // std::cout << v[5] << "\n";



    ////////////////////////////////////
    
    //ft::vector<int>::iterator iter;
    
    //ft::vector<int>::iterator iter; 
    // for(iter = v.begin(); iter != v.end(); iter++)
    //     std::cout << *iter << " -- ";
    // std::cout << "\n";

    // std::cout << "size: " << v.size() << "\n";
    // std::cout << "capacity: " << v.capacity() << "\n";
    //std::cout << "max size: " << v.max_size() << "\n";

    //std::cout << v[1] << "\n"; 

    //      ----------------------------------------

    // std::cout << "-------------- const Iterators -----------------------\n";

    // ft::vector<int> v(3, 4);
    // ft::vector<int>::iterator it, it1;
    
    // std::cout << v[0] << "\n";
    // std::cout << v[2] << "\n";
    // std::cout << "size: " << v.size() << "\n";
    // v[3] = 9;
    // v[4] = 4;
    // v[5] = 6;
    // std::cout << "size: " << v.size() << "\n";
    // std::cout << v[9] << "\n";
    // ft::vector<int> v2;

    // v2 = v;
    // ft::vector<int>::const_iterator ci;

    // ci = v2.begin(); // call const_iterator begin();

    ////////////////////// reserve  ---------------------

    // ft::vector<int> v;

    // v.reserve(5);

    // std::cout << v.size() << " | " << v.capacity() << "\n";


    ////////////////////// push_back -------------------

    //  ft::vector<int> v;
    // //std::vector<int> v;

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.push_back(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //////////////////////// resize ----------------------

    // ft::vector<int> v(3, 4);

    // v.resize(2);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //     v.resize(4);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //     v.resize(5);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //     v.resize(6);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    ///////////////////////// erase  --------------------------

    // ft::vector<int> v;
    // std::vector<int> v;

    // v.push_back(5);
    // v.push_back(10);
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // std::cout << *(v.erase(v.begin())) << "\n";
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    // v.clear();
    // std::cout << v.size() << " | " << v.capacity() << "\n";

    //////////////////////// reserve ----------------------------

    // std::cout << "Reserve\n";
    // ft::vector<int> v;
    // std::vector<int> v1;

    // v.push_back(1);
    // v.push_back(2);
    // v.push_back(3);
    // v.push_back(4);

    // v1.push_back(1);
    // v1.push_back(2);
    // v1.push_back(3);
    // v1.push_back(4);

    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    //  std::cout << "--------------------------\n";
    // v.reserve(5);
    // v1.reserve(5);
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    // std::cout << "--------------------------\n";
    // v.clear();
    // v1.clear();
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";

    /////////////////////// resize --------------------------

//     std::cout << "\nResize\n";
//     ft::vector<int> f;
//     std::vector<int> f1;

//     f.push_back(1);
//     f.push_back(2);
//     f.push_back(3);
//     f.push_back(4);
//     f.push_back(5);

//     f1.push_back(1);
//     f1.push_back(2);
//     f1.push_back(3);
//     f1.push_back(4);
//     f1.push_back(5);
    
//     std::cout << f.size() << " | " <<  f.capacity() << "\n";
//     std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
    
//     // f.resize(2, 5);
//     // f1.resize(2, 5);
//    // std::cout << "--------------------------\n";
//     // f.resize(6, 5);
//     // f1.resize(6, 5);
//     //std::cout << "--------------------------\n";
//     f.resize(100, 5);
//     f1.resize(100, 5);

//     std::cout << f.size() << " | " <<  f.capacity() << "\n";
//     std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
//     std::cout << "--------------------------\n";
//     f.clear();
//     f1.clear();
//     std::cout << f.size() << " | " <<  f.capacity() << "\n";
//     std::cout << f1.size() << " | " <<  f1.capacity() << "\n";

    /////////////////// max_size -----------------------------

    // std::vector<int> v;
    // std::vector<char> vc;

    // ft::vector<int> v1;
    // ft::vector<char> v1c;

    // std::cout << v.max_size() << " | " <<  vc.max_size() << "\n";
    // std::cout << v1.max_size() << " | " <<  v1c.max_size() << "\n";

    // std::cout << sizeof(int) << "\n";

    /////////////////// front && back -----------------------------

    // ft::vector<int> f;
    // std::vector<int> f1;

    // f.push_back(1);
    // f.push_back(2);
    // f.push_back(3);
    // f.push_back(4);

    // f1.push_back(1);
    // f1.push_back(2);
    // f1.push_back(3);
    // f1.push_back(4);
    
    // std::cout << f.front() << " | " <<  f.back() << "\n";
    // std::cout << f1.front() << " | " <<  f1.back() << "\n";

    /////////////////// erase  --------------------------------

    // std::cout << "erase\n";
    // ft::vector<int> v;
    // std::vector<int> v1;

    // v1.erase(v1.end());
    // v.push_back(1);
    // v.push_back(2);
    // v.push_back(3);
    // v.push_back(4);

    // v1.push_back(1);
    // v1.push_back(2);
    // v1.push_back(3);
    // v1.push_back(4);

    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    //  std::cout << "--------------------------\n";
    // v.reserve(5);
    // v1.reserve(5);
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";
    // std::cout << "--------------------------\n";
    // v.clear();
    // v1.clear();
    // std::cout << v.size() << " | " <<  v.capacity() << "\n";
    // std::cout << v1.size() << " | " <<  v1.capacity() << "\n";


    /////////////////// assign ------------------------------

    // std::cout << "\nAssign\n";
    // ft::vector<int> f;
    // std::vector<int> f1;

    // f.push_back(1);
    // f.push_back(2);
    // f.push_back(3);
    // f.push_back(4);

    // f1.push_back(1);
    // f1.push_back(2);
    // f1.push_back(3);
    // f1.push_back(4);
    
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
    //  std::cout << "--------------------------\n";
    // f.resize(5, 1);
    // f1.resize(5, 1);
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";
    // std::cout << "--------------------------\n";
    // f.clear();
    // f1.clear();
    // std::cout << f.size() << " | " <<  f.capacity() << "\n";
    // std::cout << f1.size() << " | " <<  f1.capacity() << "\n";

    ////////////////////////// weird error ---------------------------
    // std::vector<std::string> v1(10, "hi ");
    // std::string s1;
    // std::string ft_s1;
    // ft::vector<std::string> ft_v1(10, "hi ");

    // for (size_t i = 0; i < v1.size(); ++i)
    //         s1 += v1[i];

    // for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
    //         ft_s1 += *it;    std::cout << vec.size() << " | " <<  vec.capacity() << "\n";
    //std::cout << ft_vec.size() << " | " <<  ft_vec.capacity() << "\n";

    // std::cout << (s1==ft_s1) << "\n";

    //////////////////////////// insert && assign ------------------------------------

//     std::vector<int> vec;
//     ft::vector<int> ft_vec;

//     vec.push_back(1);
//     vec.push_back(2);
//     vec.push_back(3);
//     vec.push_back(4);

//     ft_vec.push_back(1);
//     ft_vec.push_back(2);
//     ft_vec.push_back(3);
//     ft_vec.push_back(4);

//     std::cout << "------------assign 5 elements--------------\n";

//     vec.assign(5, 5);
//     ft_vec.assign(5, 5);
//     std::cout << vec.size() << " | " ;
//     std::cout << ft_vec.size()  << "\n";

//     std::cout << "------------assign range of 5 elements--------------\n";

//     vec.assign(ft_vec.begin(), ft_vec.end());
//     ft_vec.assign(vec.begin(), vec.end());
//     std::cout << vec.size() << " | " ;
//     std::cout << ft_vec.size()  << "\n";

//     std::cout << "-------------insert one element-------------\n";

//     vec.insert(vec.begin(), 5);
//     ft_vec.insert(ft_vec.begin(), 5);
//     std::cout << vec.size() << " | " ;
//     std::cout << ft_vec.size() << "\n";

//     std::cout << "--------------insert another element------------\n";
// //    vec.clear();
// //     ft_vec.clear();

//     vec.insert(vec.begin(), 5);
//     ft_vec.insert(ft_vec.begin(), 5);
//     std::cout << vec.size() << " | " ;
//     std::cout << ft_vec.size() << "\n";

// //     std::cout << "-----------insert n elements---------------\n";
// //     // vec.clear();
// //     // ft_vec.clear();

//     vec.insert(vec.end(), 5, 6);
//         std::cout << "vector size after insertion "<< vec.size() <<  "\n";
//     ft_vec.insert(ft_vec.end(), 5, 6);
//     std::cout << vec.size() << " | " ;
//     std::cout << ft_vec.size() << "\n";

//     std::cout << "--------------------------\n";
//     // vec.clear();
//     // ft_vec.clear();
//     std::cout << vec.size() << " | ";
//     std::cout << ft_vec.size() << "\n";


// --------------------- test riterator

    std::vector<int> v(3, 4);
    std::reverse_iterator<std::vector<int>::iterator> rit(v.end()), rit_1(v.end() - 1);
    /*----------------------------------*/
    /*------------ ft::reverse_iterator ---------*/
    ft::reverse_iterator<std::vector<int>::iterator> my_rit(v.end()), my_rit1(v.end() - 1);
    std::cout << ((rit > rit_1) == (my_rit > my_rit1)) << std::endl;

}
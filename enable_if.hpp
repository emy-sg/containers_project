# ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

/*
    enable_if : is a Templace class.
    ==> The type T is enabled as "member type" if "enable_if::Cond" is true.

    Wich means if "bool" aka "Cond" is true, "std::enable_if" has a public "member typedef" "type", equal to T.
    otherwise, there is no member typedef "type".

    Last think to mention is that "std::enable_if" can be used in many forms, but in our case we gonna need it with:
        SFINAE (to choose the right constructor to the vector)
        and The Cond (condition) would be "std::is_integral"

    https://en.cppreference.com/w/cpp/types/enable_if
*/

#include <type_traits>
namespace ft {

    template < bool Cond, class T = void >
    struct enable_if {};

    template < class T>
    struct enable_if<true, T> {
        typedef T type;
    };
}

//  ------------------------------ is_integral -----------------------

/*
    is_integral : is a template class.
    It inherits from "std::integral_constant" as being either "true_type" or "false_type", depending on T.

    ==> Trait class that checks whether the template parameter T is an "integral type".
    It provides the "member constants value" true(which is a public static member constant type), if T is the type:
        bool, char, char16_t, char32_t, wchar_t, short, int, long, long long.
    Otherwise it return value is equal to false.

    https://en.cppreference.com/w/cpp/types/is_integral
    Member types:
        value_type  bool;
        type        std::integral_constant<bool, value>;

    Member constants: aka static
        value[static]; "true" if T is an integral type, "false" otherwise.

    Member functions:
    operator bool() {}; // converts the object to bool, and returns value




*/

//enable_if< ! is_integral<InputIterator>::value , InputIterator >::type b = inputiterator()

namespace ft {

	template<typename T>
    struct is_integral {
		static const bool value = false;
	};

	template<>
	struct is_integral<char> {
		static const bool value = true;
	};

	template<>
	struct is_integral<bool> {
		static const bool value = true;
	};

	template<>
	struct is_integral<char16_t> {
		static const bool value = true;
	};

	template<>
	struct is_integral<char32_t> {
		static const bool value = true;
	};

	template<>
	struct is_integral<signed char> {
		static const bool value = true;
	};

	template<>
	struct is_integral<short int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<long int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<long long int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned char> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned short int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned long int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned long long int> {
		static const bool value = true;
	};

}

#endif 
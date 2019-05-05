/*
 * =====================================================================================
 *
 *       Filename:  lib.h
 *
 *    Description:  Definition of lists of types using metarogramming.
 *                  The meta-functions defined are heavily inspired by the standard ones
 *                  in the Haskell programming language.
 *
 *        Version:  0.1.0
 *        Created:  04.05.2019 00:19:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SimGus
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

//=================== Definitions ========================
// Uninstantiable definition for debugging purposes
template<typename> struct debug;

// List definition
struct nil {};
template<typename H, typename T>
struct TList
{
    H head;
    T tail;
};

// Building helper
template<typename...> struct buildTypes;
template<typename H, typename... Ts>
struct buildTypes<H, Ts...>
{
    using type = TList<H, typename buildTypes<Ts...>::type>;
};
template<> struct buildTypes<> {using type = nil;};

template<typename... Types>
using buildTList = typename buildTypes<Types...>::type;

// Get the type of the head of the list
template<typename...> struct Head;
template<typename H, typename T>
struct Head<TList<H, T>>
{
    using type = H;
};
template<> struct Head<nil>
{
    using type = nil;
};

//=================== Getters for parts of the lists ===============
// Get the type of the tail of the list
template<typename...> struct Tail;
template<typename H, typename T>
struct Tail<TList<H, T>>
{
    using type = T;
};
template<> struct Tail<nil>
{
    using type = nil;
};

// Get the last element of the list
template<typename...> struct Last;
template<typename H, typename T>
struct Last<TList<H, T>>
{
    using type = typename Last<T>::type;
};
template<typename H>
struct Last<TList<H, nil>>
{
    using type = H;
};

// Get the list of elements except the last one
template<typename...> struct Init;
template<typename H, typename T>
struct Init<TList<H, T>>
{
    using type = TList<H, typename Init<T>::type>;
};
template<typename H>
struct Init<TList<H, nil>>
{
    using type = nil;
};

// Get the list of elements after index `n` (included)
template<int, typename...> struct AfterIndex;
template<int n, typename H, typename T>
struct AfterIndex<n, TList<H, T>>
{
    using type = typename AfterIndex<n-1, T>::type;
};
template<typename H, typename T>
struct AfterIndex<0, TList<H, T>>
{
    using type = TList<H, T>;
};
template<int n>
struct AfterIndex<n, nil>
{
    using type = nil;
};

// Get the list of elements before index `n` (excluded)
template<int, typename...> struct BeforeIndex;
template<int n, typename H, typename T>
struct BeforeIndex<n, TList<H, T>>
{
    using type = TList<H, typename BeforeIndex<n-1, T>::type>;
};
template<typename H, typename T>
struct BeforeIndex<0, TList<H, T>>
{
    using type = nil;
};
template<int n>
struct BeforeIndex<n, nil>
{
    using type = nil;
};

//================== Useful info about the lists ====================
// Tests whether the list is empty
template<typename...> struct IsEmpty;
template<typename H, typename T>
struct IsEmpty<TList<H, T>>
{
    static constexpr bool ans = false;
};
template<>
struct IsEmpty<nil>
{
    static constexpr bool ans = true;
};

// Computes the length of the list
template<typename...> struct Length;
template<typename H, typename T>
struct Length<TList<H, T>>
{
    static constexpr unsigned int value = 1 + Length<T>::value;
};
template<>
struct Length<nil>
{
    static constexpr unsigned int value = 0;
};

//==================== Different types of concatenation ===================
// Concatenates two lists
template<typename...> struct Concat;
template<typename H1, typename T1, typename H2, typename T2>
struct Concat<TList<H1, T1>, TList<H2, T2>>
{
    using type = TList<H1, typename Concat<T1, TList<H2, T2>>::type>;
};
template<typename H, typename T>
struct Concat<nil, TList<H, T>>
{
    using type = TList<H, T>;
};

// Appends an element to a list
template<typename...> struct Append;
template<typename H, typename T, typename E>
struct Append<TList<H, T>, E>
{
    using type = TList<H, typename Append<T, E>::type>;
};
template<typename E>
struct Append<nil, E>
{
    using type = TList<E, nil>;
};


// Prepends an element to a list
template<typename...> struct Prepend;
template<typename H, typename T, typename E>
struct Prepend<TList<H, T>, E>
{
    using type = TList<E, TList<H, T>>;
};
template<typename E>
struct Prepend<nil, E>
{
    using type = TList<E, nil>;
};

//=================== Operations on lists ==============================
// Creates a list obtained by applying a metafunction to all elements of the list
template<template<typename...> typename, typename...> struct Map;
template<template<typename...> typename f, typename H, typename T>
struct Map<f, TList<H, T>>
{
    using type = TList<typename f<H>::type, typename Map<f, T>::type>;
};
template<template<typename...> typename f>
struct Map<f, nil>
{
    using type = nil;
};

// Returns the same type as was provided
template<typename> struct Identity;
template<typename T> struct Identity
{
    using type = T;
};

// Returns `int` whichever the pvided type
template<typename> struct Int;
template<typename T> struct Int
{
    using type = int;
};

// Reverse the order of the list
template<typename...> struct Reverse;
template<typename H, typename T>
struct Reverse<TList<H, T>>
{
    using type = typename Append<typename Reverse<T>::type, H>::type;
};
template<typename H>
struct Reverse<TList<H, nil>>
{
    using type = TList<H, nil>;
};

// Add an element in-between each elements of a list
template<typename...> struct Intersperse;
template<typename H, typename T, typename E>
struct Intersperse<TList<H, T>, E>
{
    using type = TList<H, TList<E, typename Intersperse<T, E>::type>>;
};
template<typename E>
struct Intersperse<nil, E>
{
    using type = nil;
};

// Transpose the rows and columns of the arguments
template<typename...> struct Transpose;
template<typename H1, typename T1, typename H2, typename T2>
struct Transpose<TList<H1, T1>, TList<H2, T2>>
{
    using type = TList<TList<H1, TList<H2, nil>>, typename Transpose<T1, T2>::type>;
};
template<>
struct Transpose<nil, nil>
{
    using type = nil;
};


/* // Special `Prepend` to use with `Map` */
/* template<typename> struct PrependForMap; */
/* template<typename E> */
/* struct PrependForMap */
/* { */
/*     template<typename L> */
/*     struct lambda */
/*     { */
/*         using type = Prepend<L, E>; */
/*     }; */
/* }; */

/* // Computes all the subsequences of the provided list */
/* template<typename...> struct Subsequences; */
/* template<typename H, typename T> */
/* struct Subsequences<TList<H, T>> */
/* { */
/*     using enumeration = TList<TList<H, nil>, */
/*                               TList<typename Subsequences<T>::enumeration, */
/*                                     typename Map<PrependForMap<H>::lambda, typename Subsequences<T>::enumeration>::type>>; */
/*     // This doesn't work because of `H` in the last line for some reason */
/* }; */
/* template<> */
/* struct Subsequences<nil> */
/* { */
/*     using enumeration = nil; */
/* }; */

//+================== Predicates on lists =====================
//------------------- Searching ----------------------------
// Tests whether a type is in the list
template<typename...> struct Elem;
template<typename H, typename T>
struct Elem<TList<H, T>, H>
{
    static constexpr bool value = true;
};
template<typename H, typename T, typename E>
struct Elem<TList<H, T>, E>
{
    static constexpr bool value = Elem<T, E>::value;
};
template<typename E>
struct Elem<nil, E>
{
    static constexpr bool value = false;
};


// Opposite of `Elem`
template<typename...> struct NotElem;
template<typename H, typename T>
struct NotElem<TList<H, T>, H>
{
    static constexpr bool value = true;
};
template<typename H, typename T, typename E>
struct NotElem<TList<H, T>, E>
{
    static constexpr bool value = NotElem<T, E>::value;
};
template<typename E>
struct NotElem<nil, E>
{
    static constexpr bool value = false;
};

// Finds a provided type in the list and returns it (or `nil` if it isn't found)
template<typename...> struct Find;
template<typename H, typename T>
struct Find<TList<H, T>, H>
{
    using type = H;
};
template<typename H, typename T, typename E>
struct Find<TList<H, T>, E>
{
    using type = typename Find<T, E>::type;
};
template<typename E>
struct Find<nil, E>
{
    using type = nil;
};

// Computes the first index of a provided type
// (the size of the list if it isn't present in the list)
template<typename...> struct ElemIndex;
template<typename H, typename T>
struct ElemIndex<TList<H, T>, H>
{
    static constexpr int value = 0;
};
template<typename H, typename T, typename E>
struct ElemIndex<TList<H, T>, E>
{
    static constexpr int value = 1 + ElemIndex<T, E>::value;
};
template<typename E>
struct ElemIndex<nil, E>
{
    static constexpr int value = 0;
};


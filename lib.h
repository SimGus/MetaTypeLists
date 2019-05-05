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

// Reverse the order of the list
/* template<typename...> struct Reverse; */
/* template<typename H, typename T> */
/* struct Reverse<TList<H, T>> */
/* { */
/*     using type = */ 
/* }; */
/* template<typename H> */
/* struct Reverse<TList<H, nil>> */
/* { */
/*     using type = TList<H, nil>; */
/* }; */


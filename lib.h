/*
 * =====================================================================================
 *
 *       Filename:  lib.h
 *
 *    Description:  Contains the meta-functions defining lists and the functions that
 *                  should be defined to work with them. Those functions are
 *                  heavily influenced by the functions on list in the Haskell
 *                  programming language.
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

// Print utility
template<typename T>
void printValue(T value)
{
    cout << value << endl;
}

// List definition
struct nil {};
template<typename Head, typename Tail>
struct TList
{
    Head head;
    Tail tail;
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


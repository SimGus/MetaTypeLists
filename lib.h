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


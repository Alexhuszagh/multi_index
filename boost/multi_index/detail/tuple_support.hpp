
#pragma once


#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <boost/tuple/tuple.hpp>
#include <array>
#include <type_traits>
#include <brigand/adapted/tuple.hpp>

namespace boost
{

//template <int N, typename T, typename... Ts>
//struct tuple_creator_impl<N, T, tuple<Ts...>>
//{
//  typedef tuple<T, Ts...> U;
//  static const int length = std::tuple_size<U>::value;
//
//  typedef typename brigand::eval_if_c<
//    N!=length,
//    tuple_creator_impl<N+1, T, U>,
//    brigand::identity<U>
//  >::type type;
//};
//
//
//// TODO: write a recursive implementation....
//
//template <int N, typename T>
//struct tuple_creator_impl
//{
//    using impl = typename tuple_creator_impl<N-1, T>::type;
//    using type = to_tuple<impl, T>;
//};



//
//template <typename T>
//struct tuple_creator_impl<10, T>
//{
//    using type = tuple<T, T, T, T, T, T, T, T, T, T>;
//};

template <int N, typename T>
using tuple_creator = typename tuple_creator_impl<N, T>::type;

}   /* boost */

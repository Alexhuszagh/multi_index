
#pragma once


#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <boost/tuple/tuple.hpp>
#include <array>
#include <type_traits>
#include <brigand/adapted/tuple.hpp>

namespace boost
{

template <int, typename ... Ns>
struct tuple_builder_impl;

template <int I, typename N, typename ... Ns>
struct tuple_builder_impl<I, N, Ns...>
{
    using type = typename brigand::eval_if_c<
        I == 0,
        brigand::identity<tuple<Ns...>>,
        tuple_builder_impl<I - 1, N, N, Ns...>
    >::type;
};

template <int N, typename T>
using tuple_builder = typename tuple_builder_impl<N, T>::type;

}   /* boost */

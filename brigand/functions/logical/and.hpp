/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_LOGICAL_AND_HPP
#define BOOST_BRIGAND_FUNCTIONS_LOGICAL_AND_HPP
#include <brigand/types/integral_constant.hpp>

namespace brigand
{
  template<typename... Ts>
  struct and_;

  template<>
  struct and_<>: true_type {};

  template<typename T, typename... Ts>
  struct and_<T, Ts...> : brigand::integral_constant < typename T::value_type, T::value && and_<Ts...>::value > {};
}
#endif

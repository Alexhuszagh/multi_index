/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/empty.hpp>
#include <boost/mpl/is_sequence.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
struct is_index_list
{
  static const bool mpl_sequence = mpl::is_sequence<T>::value;
  static const bool non_empty = !mpl::empty<T>::value;
  static const bool value = mpl_sequence&&non_empty;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

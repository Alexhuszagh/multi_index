/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/no_duplicate_tags.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace multi_index{

namespace detail{

struct tag_marker{};

template<typename T>
struct is_tag: is_base_and_derived<tag_marker, T>
{};

} /* namespace multi_index::detail */

// TODO: convert this to brigand::list
template<typename... Ts>
struct tag: private detail::tag_marker
{
  typedef mpl::vector<Ts...> type;
  static_assert(detail::no_duplicate_tags<type>::value, "");
};

} /* namespace multi_index */

} /* namespace boost */

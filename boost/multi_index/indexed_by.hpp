/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <brigand/sequences/list.hpp>
#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/vector.hpp>         // TODO: remove


namespace boost{
namespace multi_index{

template<
  typename... Ts
>
struct indexed_by:
  mpl::vector<Ts...>
{
    // Need to get everything that isn't null...
    using list = brigand::list<Ts...>;
};

} /* namespace multi_index */
} /* namespace boost */

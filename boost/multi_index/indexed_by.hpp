/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <tuple>

namespace boost{
namespace multi_index{

template<typename... Ts>
using indexed_by = std::tuple<Ts...>;

} /* namespace multi_index */
} /* namespace boost */

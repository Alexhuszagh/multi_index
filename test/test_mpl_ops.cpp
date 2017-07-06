/* Boost.MultiIndex test for MPL operations.
 *
 * Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_mpl_ops.hpp"

#include <brigand/adapted/list.hpp>
#include <brigand/adapted/tuple.hpp>
#include <brigand/sequences/front.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>

using namespace boost::multi_index;

void test_mpl_ops()
{
  typedef multi_index_container<
    int,
    indexed_by<
      ordered_unique<identity<int> >,
      ordered_non_unique<identity<int> >
     >
  >                           indexed_t1;

  static_assert((std::is_same<
    std::tuple_element<0, indexed_t1::index_specifier_type_list>::type,
    ordered_unique<identity<int> > >::value), "");
  static_assert((std::is_same<
    std::tuple_element<1, indexed_t1::index_specifier_type_list>::type,
    ordered_non_unique<identity<int> > >::value), "");

  using list_type = brigand::as_list<
    typename indexed_t1::index_specifier_type_list
  >;

  using index_list_t_impl = brigand::push_front<
    indexed_t1::index_specifier_type_list,
    sequenced<>
  >;

  using index_list_t = brigand::as_tuple<index_list_t_impl>;

  typedef multi_index_container<
    int,
    index_list_t
  >                           indexed_t2;

  static_assert((std::is_same<
    std::tuple_element<0, indexed_t2::index_specifier_type_list>::type,
    sequenced<> >::value), "");
  static_assert((std::is_same<
    std::tuple_element<1, indexed_t2::index_specifier_type_list>::type,
    std::tuple_element<0, indexed_t1::index_specifier_type_list>::type>::value), "");
  static_assert((std::is_same<
    std::tuple_element<2, indexed_t2::index_specifier_type_list>::type,
    std::tuple_element<1, indexed_t1::index_specifier_type_list>::type>::value), "");

  typedef multi_index_container<
    int,
    boost::multi_index::indexed_by<
      ordered_unique<identity<int> >,
      ordered_non_unique<identity<int> >
    >
  >                           indexed_t3;

  static_assert((std::is_same<
    std::tuple_element<0, indexed_t3::index_specifier_type_list>::type,
    std::tuple_element<0, indexed_t1::index_specifier_type_list>::type>::value), "");
  static_assert((std::is_same<
    std::tuple_element<1, indexed_t3::index_specifier_type_list>::type,
    std::tuple_element<1, indexed_t1::index_specifier_type_list>::type>::value), "");
}

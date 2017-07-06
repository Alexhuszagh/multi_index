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

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/push_front.hpp>

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

// TODO: restore
#if 0
  static_assert((boost::is_same<
    boost::mpl::at_c<indexed_t1::index_specifier_type_list,0>::type,
    ordered_unique<identity<int> > >::value), "");
  static_assert((boost::is_same<
    boost::mpl::at_c<indexed_t1::index_specifier_type_list,1>::type,
    ordered_non_unique<identity<int> > >::value), "");

  typedef boost::mpl::push_front<
    indexed_t1::index_specifier_type_list,
    sequenced<>
  >::type                     index_list_t;

  typedef multi_index_container<
    int,
    index_list_t
  >                           indexed_t2;

  static_assert((boost::is_same<
    boost::mpl::at_c<indexed_t2::index_specifier_type_list,0>::type,
    sequenced<> >::value), "");
  static_assert((boost::is_same<
    boost::mpl::at_c<indexed_t2::index_specifier_type_list,1>::type,
    boost::mpl::at_c<indexed_t1::index_specifier_type_list,0>::type>::value), "");
  static_assert((boost::is_same<
    boost::mpl::at_c<indexed_t2::index_specifier_type_list,2>::type,
    boost::mpl::at_c<indexed_t1::index_specifier_type_list,1>::type>::value), "");

  typedef multi_index_container<
    int,
    boost::multi_index::indexed_by<
      ordered_unique<identity<int> >,
      ordered_non_unique<identity<int> >
    >
  >                           indexed_t3;

  static_assert((boost::is_same<
    boost::mpl::at_c<indexed_t3::index_specifier_type_list,0>::type,
    boost::mpl::at_c<indexed_t1::index_specifier_type_list,0>::type>::value), "");
  static_assert((boost::is_same<
    boost::mpl::at_c<indexed_t3::index_specifier_type_list,1>::type,
    boost::mpl::at_c<indexed_t1::index_specifier_type_list,1>::type>::value), "");
  #endif
}

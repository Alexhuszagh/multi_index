/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <brigand/algorithms/fold.hpp>
#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/bind.hpp>
#include <boost/mpl/reverse_iter_fold.hpp>
#include <boost/multi_index_container_fwd.hpp>
#include <boost/multi_index/detail/header_holder.hpp>
#include <boost/multi_index/detail/index_node_base.hpp>
#include <boost/multi_index/detail/is_index_list.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* MPL machinery to construct the internal node type associated to an
 * index list.
 */

struct index_node_applier
{
  template<typename IndexSpecifierIterator,typename Super>
  struct apply
  {
    using index_specifier = typename IndexSpecifierIterator::type;
    typedef typename index_specifier::template node_class<Super>::type type;
  };
};


template<typename IndexSpecifierIterator,typename Super>
struct next_index_node
{
  using index_specifier = IndexSpecifierIterator;
  using type = typename index_specifier::template node_class<Super>::type;
};


// TODO: need a single converter
template < typename T, typename R >
struct to_tuple2;


template < typename... Ts, typename X >
struct to_tuple2< std::tuple< Ts... >, X >
{
  typedef std::tuple< Ts..., X > type;
};



template <typename... Ts>
struct multi_index_node_type_impl;

// TODO: lols
template <typename Value, typename Allocator, typename... Ts>
struct multi_index_node_type_impl<Value, Allocator, std::tuple<Ts...>>
{
//  using list = brigand::reverse_fold<
//    brigand::list<Ts...>,
//    index_node_base<Value,Allocator>,
//    brigand::bind<next_index_node, brigand::_2, brigand::_1>
//  >;

  typedef typename mpl::reverse_iter_fold<
    mpl::vector<Ts...>,
    index_node_base<Value,Allocator>,
    mpl::bind2<index_node_applier,mpl::_2,mpl::_1>
  >::type type;
};


template<typename Value,typename IndexSpecifierList,typename Allocator>
struct multi_index_node_type
{
  static_assert(detail::is_index_list<IndexSpecifierList>::value, "");

  typedef typename mpl::fold<
    IndexSpecifierList,
    std::tuple<>,
    to_tuple2<mpl::_1, mpl::_2>
  >::type tuple;

  using type = typename multi_index_node_type_impl<Value, Allocator, tuple>::type;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

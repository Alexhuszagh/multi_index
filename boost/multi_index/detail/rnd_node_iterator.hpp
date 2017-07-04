/* Copyright 2003-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/operators.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* Iterator class for node-based indices with random access iterators. */

template<typename Node>
class rnd_node_iterator:
  public random_access_iterator_helper<
    rnd_node_iterator<Node>,
    typename Node::value_type,
    std::ptrdiff_t,
    const typename Node::value_type*,
    const typename Node::value_type&>
{
public:
  /* coverity[uninit_ctor]: suppress warning */
  rnd_node_iterator(){}
  explicit rnd_node_iterator(Node* node_):node(node_){}

  const typename Node::value_type& operator*()const
  {
    return node->value();
  }

  rnd_node_iterator& operator++()
  {
    Node::increment(node);
    return *this;
  }

  rnd_node_iterator& operator--()
  {
    Node::decrement(node);
    return *this;
  }

  rnd_node_iterator& operator+=(std::ptrdiff_t n)
  {
    Node::advance(node,n);
    return *this;
  }

  rnd_node_iterator& operator-=(std::ptrdiff_t n)
  {
    Node::advance(node,-n);
    return *this;
  }

  /* get_node is not to be used by the user */

  typedef Node node_type;

  Node* get_node()const{return node;}

private:
  Node* node;
};

template<typename Node>
bool operator==(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return x.get_node()==y.get_node();
}

template<typename Node>
bool operator<(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return Node::distance(x.get_node(),y.get_node())>0;
}

template<typename Node>
std::ptrdiff_t operator-(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return Node::distance(y.get_node(),x.get_node());
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

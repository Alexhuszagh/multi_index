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

/* Iterator class for hashed indices.
 */

struct hashed_index_global_iterator_tag{};
struct hashed_index_local_iterator_tag{};

template<typename Node,typename BucketArray,typename Category>
class hashed_index_iterator:
  public forward_iterator_helper<
    hashed_index_iterator<Node,BucketArray,Category>,
    typename Node::value_type,
    std::ptrdiff_t,
    const typename Node::value_type*,
    const typename Node::value_type&>
{
public:
  /* coverity[uninit_ctor]: suppress warning */
  hashed_index_iterator(){}
  hashed_index_iterator(Node* node_):node(node_){}

  const typename Node::value_type& operator*()const
  {
    return node->value();
  }

  hashed_index_iterator& operator++()
  {
    this->increment(Category());
    return *this;
  }

  /* get_node is not to be used by the user */

  typedef Node node_type;

  Node* get_node()const{return node;}

private:

  void increment(hashed_index_global_iterator_tag)
  {
    Node::increment(node);
  }

  void increment(hashed_index_local_iterator_tag)
  {
    Node::increment_local(node);
  }

  Node* node;
};

template<typename Node,typename BucketArray,typename Category>
bool operator==(
  const hashed_index_iterator<Node,BucketArray,Category>& x,
  const hashed_index_iterator<Node,BucketArray,Category>& y)
{
  return x.get_node()==y.get_node();
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

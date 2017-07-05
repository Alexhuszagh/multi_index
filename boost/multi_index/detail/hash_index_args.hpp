/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/functional/hash.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/multi_index/tag.hpp>
#include <functional>
#include <type_traits>

namespace boost{

namespace multi_index{

namespace detail{

/* Hashed index specifiers can be instantiated in two forms:
 *
 *   (hashed_unique|hashed_non_unique)<
 *     KeyFromValue,
 *     Hash=boost::hash<KeyFromValue::result_type>,
 *     Pred=std::equal_to<KeyFromValue::result_type> >
 *   (hashed_unique|hashed_non_unique)<
 *     TagList,
 *     KeyFromValue,
 *     Hash=boost::hash<KeyFromValue::result_type>,
 *     Pred=std::equal_to<KeyFromValue::result_type> >
 *
 * hashed_index_args implements the machinery to accept this
 * argument-dependent polymorphism.
 */

template<typename KeyFromValue>
struct index_args_default_hash
{
  // TODO: this sucks... Needs to be std::hash, ideally
    typedef ::boost::hash<typename KeyFromValue::result_type> type;
};

template<typename KeyFromValue>
struct index_args_default_pred
{
    typedef std::equal_to<typename KeyFromValue::result_type> type;
};

template<typename Arg1,typename Arg2,typename Arg3,typename Arg4>
struct hashed_index_args
{
  typedef is_tag<Arg1> full_form;

  typedef typename std::conditional<
    full_form::value,
    Arg1,
    tag< > >::type                                   tag_list_type;
  typedef typename std::conditional<
    full_form::value,
    Arg2,
    Arg1>::type                                      key_from_value_type;
  typedef typename std::conditional<
    full_form::value,
    Arg3,
    Arg2>::type                                      supplied_hash_type;
  typedef typename brigand::eval_if<
    mpl::is_na<supplied_hash_type>,
    index_args_default_hash<key_from_value_type>,
    brigand::identity<supplied_hash_type>
  >::type                                            hash_type;
  typedef typename std::conditional<
    full_form::value,
    Arg4,
    Arg3>::type                                      supplied_pred_type;
  typedef typename brigand::eval_if<
    mpl::is_na<supplied_pred_type>,
    index_args_default_pred<key_from_value_type>,
    brigand::identity<supplied_pred_type>
  >::type                                            pred_type;

  static_assert(is_tag<tag_list_type>::value, "");
  static_assert(!mpl::is_na<key_from_value_type>::value, "");
  static_assert(!mpl::is_na<hash_type>::value, "");
  static_assert(!mpl::is_na<pred_type>::value, "");
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

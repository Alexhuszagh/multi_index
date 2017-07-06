/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#pragma once

#include <functional>
#include <type_traits>

namespace multi_index{

namespace detail{

/* global_fun is a read-only key extractor from Value based on a given global
 * (or static member) function with signature:
 *
 *   Type f([const] Value [&]);
 *
 * Additionally, global_fun  and const_global_fun are overloaded to support
 * referece_wrappers of Value and "chained pointers" to Value's. By chained
 * pointer to T we  mean a type P such that, given a p of Type P
 *   *...n...*x is convertible to T&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. T** or unique_ptr<T*>.)
 */

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct const_ref_global_fun_base
{
  typedef typename std::remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

  typename std::enable_if<
    !std::is_convertible<const ChainedPtr&,Value>::value,Type>::type

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Value x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(
    const std::reference_wrapper<
      typename std::remove_reference<Value>::type>& x)const
  {
    return operator()(x.get());
  }

  Type operator()(
    const std::reference_wrapper<
      typename std::remove_const<
        typename std::remove_reference<Value>::type>::type>& x

  )const
  {
    return operator()(x.get());
  }
};

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct non_const_ref_global_fun_base
{
  typedef typename std::remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

  typename std::enable_if<
    !std::is_convertible<ChainedPtr&,Value>::value,Type>::type

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Value x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(
    const std::reference_wrapper<
      typename std::remove_reference<Value>::type>& x)const
  {
    return operator()(x.get());
  }
};

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct non_ref_global_fun_base
{
  typedef typename std::remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

  typename std::enable_if<
    !std::is_convertible<const ChainedPtr&,const Value&>::value,Type>::type

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(const Value& x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(const std::reference_wrapper<const Value>& x)const
  {
    return operator()(x.get());
  }

  Type operator()(
    const std::reference_wrapper<typename std::remove_const<Value>::type>& x)const
  {
    return operator()(x.get());
  }
};

} /* namespace multi_index::detail */

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct global_fun:
  std::conditional<
    std::is_reference<Value>::value,
    typename std::conditional<
      std::is_const<typename std::remove_reference<Value>::type>::value,
      detail::const_ref_global_fun_base<Value,Type,PtrToFunction>,
      detail::non_const_ref_global_fun_base<Value,Type,PtrToFunction>
    >::type,
    detail::non_ref_global_fun_base<Value,Type,PtrToFunction>
  >::type
{
};

} /* namespace multi_index */

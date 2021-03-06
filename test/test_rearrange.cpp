/* Boost.MultiIndex test for rearrange operations.
 *
 * Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_rearrange.hpp"

#include "lightweight_test.hpp"
#include <multi_index_container.hpp>
#include <multi_index/sequenced_index.hpp>
#include <multi_index/random_access_index.hpp>
#include <preprocessor/seq/enum.hpp>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

using namespace multi_index;

#undef CHECK_EQUAL
#define CHECK_EQUAL(p,check_seq) \
{\
  int v[]={BOOST_PP_SEQ_ENUM(check_seq)};\
  std::size_t size_v=sizeof(v)/sizeof(int);\
  BOOST_TEST(std::size_t(std::distance((p).begin(),(p).end()))==size_v);\
  BOOST_TEST(std::equal((p).begin(),(p).end(),&v[0]));\
}

#undef CHECK_VOID_RANGE
#define CHECK_VOID_RANGE(p) BOOST_TEST((p).first==(p).second)

template<typename Sequence>
static void local_test_rearrange()
{
  typedef typename Sequence::iterator   iterator;
  typedef typename Sequence::value_type value_type;

  Sequence sc;
  sc.push_back(0);
  sc.push_back(1);
  sc.push_back(2);
  sc.push_back(3);
  sc.push_back(4);
  sc.push_back(5);

  iterator it;

  it=sc.begin();
  std::advance(it,3);
  sc.relocate(sc.begin(),it);
  CHECK_EQUAL(sc,(3)(0)(1)(2)(4)(5));
  BOOST_TEST(it==sc.begin());

  sc.relocate(it,it);
  CHECK_EQUAL(sc,(3)(0)(1)(2)(4)(5));

  std::advance(it,3);
  sc.relocate(sc.end(),it,sc.end());
  CHECK_EQUAL(sc,(3)(0)(1)(2)(4)(5));

  sc.relocate(sc.begin(),it,it);
  CHECK_EQUAL(sc,(3)(0)(1)(2)(4)(5));

  iterator it2;

  it2=sc.begin();
  ++it2;
  sc.relocate(it2,it,sc.end());
  CHECK_EQUAL(sc,(3)(2)(4)(5)(0)(1));
  BOOST_TEST(std::distance(it,it2)==3);

  sc.relocate(std::prev(sc.end()),it,it2);
  CHECK_EQUAL(sc,(3)(0)(2)(4)(5)(1));

  std::vector<std::reference_wrapper<const value_type> > v;
  for(iterator it3=sc.begin();it3!=sc.end();++it3){
    v.push_back(std::cref(*it3));
  }

  sc.rearrange(v.begin());
  BOOST_TEST(std::equal(sc.begin(),sc.end(),v.begin()));

  std::reverse(v.begin(),v.end());
  sc.rearrange(v.begin());
  BOOST_TEST(std::equal(sc.begin(),sc.end(),v.begin()));

  std::sort(v.begin(),v.end());
  sc.rearrange(v.begin());
  BOOST_TEST(std::equal(sc.begin(),sc.end(),v.begin()));

  std::reverse(v.begin(),v.begin()+v.size()/2);
  sc.rearrange(v.begin());
  BOOST_TEST(std::equal(sc.begin(),sc.end(),v.begin()));
}

void test_rearrange()
{
  typedef multi_index_container<
    int,
    indexed_by<sequenced<> >
  > int_list;

  local_test_rearrange<int_list>();

  typedef multi_index_container<
    int,
    indexed_by<random_access<> >
  > int_vector;

  local_test_rearrange<int_vector>();
}

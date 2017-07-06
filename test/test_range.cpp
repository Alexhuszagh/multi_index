/* Boost.MultiIndex test for range().
 *
 * Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_range.hpp"

#include <algorithm>
#include <functional>
#include "lightweight_test.hpp"
#include <multi_index_container.hpp>
#include <multi_index/identity.hpp>
#include <multi_index/ordered_index.hpp>


using namespace multi_index;

typedef multi_index_container<int>  int_set;
typedef int_set::iterator int_set_iterator;

template <typename Pair>
static void check_range(Pair &p, int* range, int length)
{
  BOOST_TEST(std::size_t(std::distance((p).first,(p).second))==length);
  BOOST_TEST(std::equal((p).first,(p).second,&range[0]));
}


template <typename Pair>
static void check_void_range(Pair &p)
{
  BOOST_TEST((p).first==(p).second);
}


void test_range()
{
  int_set is;

  for(int i=1;i<=10;++i)is.insert(i);

  std::pair<int_set::iterator,int_set::iterator> p;

  int i1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  p=is.range(unbounded,unbounded);
  check_range(p, i1, 10);

  int i2[] = {6, 7, 8, 9, 10};
  p=is.range(
    std::bind1st(std::less<int>(),5), /* 5 < x */
    unbounded);
  check_range(p, i2, 5);

  int i3[] = {8, 9, 10};
  p=is.range(
    std::bind1st(std::less_equal<int>(),8), /* 8 <= x */
    unbounded);
  check_range(p, i3, 3);

  p=is.range(
    std::bind1st(std::less_equal<int>(),11), /* 11 <= x */
    unbounded);
  check_void_range(p);

  int i4[] = {1, 2, 3, 4, 5, 6, 7};
  p=is.range(
    unbounded,
    std::bind2nd(std::less<int>(),8)); /* x < 8 */
  check_range(p, i4, 7);

  int i5[] = {1, 2, 3, 4};
  p=is.range(
    unbounded,
    std::bind2nd(std::less_equal<int>(),4)); /* x <= 4 */
  check_range(p, i5, 4);

  p=is.range(
    unbounded,
    std::bind2nd(std::less_equal<int>(),0)); /* x <= 0 */
  check_void_range(p);

  int i6[] = {7, 8, 9};
  p=is.range(
    std::bind1st(std::less<int>(),6),        /* 6 <  x */
    std::bind2nd(std::less_equal<int>(),9)); /* x <= 9 */
  check_range(p, i6, 3);

  int i7[] = {4};
  p=is.range(
    std::bind1st(std::less_equal<int>(),4), /* 4 <= x */
    std::bind2nd(std::less<int>(),5));      /* x <  5 */
  check_range(p, i7, 1);

  int i8[] = {10};
  p=is.range(
    std::bind1st(std::less_equal<int>(),10),  /* 10 <=  x */
    std::bind2nd(std::less_equal<int>(),10)); /*  x <= 10 */
  check_range(p, i8, 1);

  int i9[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  p=is.range(
    std::bind1st(std::less<int>(),0),   /* 0 <  x */
    std::bind2nd(std::less<int>(),11)); /* x < 11 */
  check_range(p, i9, 10);

  p=is.range(
    std::bind1st(std::less<int>(),7),        /* 7 <  x */
    std::bind2nd(std::less_equal<int>(),7)); /* x <= 7 */
  check_void_range(p);
  BOOST_TEST(p.first==is.upper_bound(7));

  p=is.range(
    std::bind1st(std::less_equal<int>(),8), /* 8 <= x */
    std::bind2nd(std::less<int>(),2));      /* x <  2 */
  check_void_range(p);
  BOOST_TEST(p.first==is.lower_bound(8));

  p=is.range(
    std::bind1st(std::less<int>(),4),  /* 4 < x */
    std::bind2nd(std::less<int>(),5)); /* x < 5 */
  check_void_range(p);
  BOOST_TEST(p.first!=is.end());
}

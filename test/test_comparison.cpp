/* Boost.MultiIndex test for comparison functions.
 *
 * Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_comparison.hpp"

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include "employee.hpp"
#include <boost/detail/lightweight_test.hpp>

using namespace boost::multi_index;

template<typename Value>
struct lookup_list{
  typedef multi_index_container<
    Value,
    indexed_by<
      sequenced<>,
      ordered_non_unique<identity<Value> >
    >
  > type;
};

template<typename Value>
struct lookup_vector{
  typedef multi_index_container<
    Value,
    indexed_by<
      random_access<>,
      ordered_non_unique<identity<Value> >
    >
  > type;
};

void test_comparison()
{
  employee_set              es;
  employee_set_by_name&     i1=get<1>(es);
  employee_set_by_age&      i2=get<2>(es);
  employee_set_as_inserted& i3=get<3>(es);
  employee_set_by_ssn&      i4=get<4>(es);
  employee_set_randomly&    i5=get<5>(es);
  es.insert(employee(0,"Joe",31,1123));
  es.insert(employee(1,"Robert",27,5601));
  es.insert(employee(2,"John",40,7889));
  es.insert(employee(3,"Albert",20,9012));
  es.insert(employee(4,"John",57,1002));

  employee_set              es2;
  employee_set_by_name&     i12=get<by_name>(es2);
  employee_set_by_age&      i22=get<age>(es2);
  employee_set_as_inserted& i32=get<3>(es2);
  employee_set_by_ssn&      i42=get<4>(es2);
  employee_set_randomly&    i52=get<5>(es2);
  es2.insert(employee(0,"Joe",31,1123));
  es2.insert(employee(1,"Robert",27,5601));
  es2.insert(employee(2,"John",40,7889));
  es2.insert(employee(3,"Albert",20,9012));

  BOOST_TEST(es==es&&es<=es&&es>=es&&
             i12==i12&&
             i22==i22&&i22<=i22&&i22>=i22&&
             i32==i32&&i32<=i32&&i32>=i32&&
             i42==i42&&
             i52==i52&&i52<=i52&&i52>=i52);
  BOOST_TEST(es!=es2&&es2<es&&es>es2&&!(es<=es2)&&!(es2>=es));
  BOOST_TEST(i1!=i12);
  BOOST_TEST(i2!=i22&&i22<i2&&i2>i22&&!(i2<=i22)&&!(i22>=i2));
  BOOST_TEST(i3!=i32&&i32<i3&&i3>i32&&!(i3<=i32)&&!(i32>=i3));
  BOOST_TEST(i4!=i42);
  BOOST_TEST(i5!=i52&&i52<i5&&i5>i52&&!(i5<=i52)&&!(i52>=i5));
}

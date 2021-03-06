/* Boost.MultiIndex basic test.
 *
 * Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_basic.hpp"

#include <algorithm>
#include <vector>
#include "employee.hpp"
#include "lightweight_test.hpp"

using namespace multi_index;

struct less_by_employee_age
{
  bool operator()(const employee& e1,const employee& e2)const
  {
    return e1.age<e2.age;
  }
};

void test_basic()
{
  employee_set          es;
  std::vector<employee> v;

  employee_set_by_name& i1=es.get<by_name>();
  const employee_set_by_age& i2=get<2>(es);
  employee_set_as_inserted&  i3=get<3>(es);
  employee_set_by_ssn&       i4=get<ssn>(es);
  employee_set_randomly&     i5=get<randomly>(es);

  es.insert(employee(0,"Joe",31,1123));
  es.insert(employee(5,"Anna",41,1123));      /* clash*/
  i1.insert(employee(1,"Robert",27,5601));
  es.insert(employee(2,"John",40,7889));
  i3.push_back(employee(3,"Albert",20,9012));
  i4.insert(employee(4,"John",57,1002));
  i5.push_back(employee(0,"Andrew",60,2302)); /* clash */

  v.push_back(employee(0,"Joe",31,1123));
  v.push_back(employee(1,"Robert",27,5601));
  v.push_back(employee(2,"John",40,7889));
  v.push_back(employee(3,"Albert",20,9012));
  v.push_back(employee(4,"John",57,1002));

  {
    /* by insertion order */

    BOOST_TEST(std::equal(i3.begin(),i3.end(),v.begin()));
    BOOST_TEST(std::equal(i5.begin(),i5.end(),v.begin()));
  }

  {
    /* by id */

    std::sort(v.begin(),v.end());
    BOOST_TEST(std::equal(es.begin(),es.end(),v.begin()));
  }

  {
    /* by age */

    std::sort(v.begin(),v.end(),less_by_employee_age());
    BOOST_TEST(std::equal(i2.begin(),i2.end(),v.begin()));
  }

}

/* Boost.MultiIndex test for replace(), modify() and modify_key().
 *
 * Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_update.hpp"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include "employee.hpp"
#include <boost/detail/lightweight_test.hpp>

struct do_nothing
{
  template<typename T>
  void operator()(const T&)const{}
};

struct null_hash
{
  template<typename T>
  std::size_t operator()(const T&)const{return 0;}
};

struct assign_value
{
  assign_value(int n):n_(n){}

  void operator()(int& x)const{x=n_;}

  int n_;
};

template<class MultiIndexContainer>
void test_stable_update()
{
  typedef typename MultiIndexContainer::iterator  iterator;
  typedef typename MultiIndexContainer::size_type size_type;

  MultiIndexContainer c;
  c.insert(0);
  c.insert(1);c.insert(1);
  c.insert(2);c.insert(2);c.insert(2);c.insert(2);
  c.insert(3);
  c.insert(4);c.insert(4);c.insert(4);
  c.insert(5);c.insert(5);
  c.insert(6);
  c.insert(7);
  size_type num_elems=
    c.count(0)+c.count(1)+c.count(2)+c.count(3)+
    c.count(4)+c.count(5)+c.count(6)+c.count(7);

  for(size_type n=c.size();n--;){
    iterator it=std::next(c.begin(),n);

    c.replace(it,*it);
    BOOST_TEST((size_type)std::distance(c.begin(),it)==n);

    c.modify(it,do_nothing());
    BOOST_TEST((size_type)std::distance(c.begin(),it)==n);

    c.modify(it,do_nothing(),do_nothing());
    BOOST_TEST((size_type)std::distance(c.begin(),it)==n);

    for(int i=0;i<=8;++i){
      MultiIndexContainer cpy(c);
      bool b=c.modify(it,assign_value(i),assign_value(*it));
      BOOST_TEST(b||(size_type)std::distance(c.begin(),it)==n);
      BOOST_TEST(c.count(0)+c.count(1)+c.count(2)+c.count(3)+c.count(4)+
                  c.count(5)+c.count(6)+c.count(7)+c.count(8)==num_elems);
      if(b){
        c=cpy;
        it=std::next(c.begin(),n);
      }
    }
  }
}

using namespace boost::multi_index;

void test_update()
{
  employee_set              es;
  employee_set_as_inserted& i=get<as_inserted>(es);
  employee_set_randomly&    r=get<randomly>(es);

  es.insert(employee(0,"Joe",31,1123));
  es.insert(employee(1,"Robert",27,5601));
  es.insert(employee(2,"John",40,7889));
  es.insert(employee(3,"Olbert",20,9012));
  es.insert(employee(4,"John",57,1002));

  employee_set::iterator             it=es.find(employee(0,"Joe",31,1123));
  employee_set_as_inserted::iterator it1=
    project<as_inserted>(es,get<name>(es).find("Olbert"));
  employee_set_randomly::iterator    it2=
    project<randomly>(es,get<age>(es).find(57));

  BOOST_TEST(es.replace(it,*it));
  BOOST_TEST(i.replace(it1,*it1));
  BOOST_TEST(r.replace(it2,*it2));
  BOOST_TEST(!es.replace(it,employee(3,"Joe",31,1123))&&it->id==0);
  BOOST_TEST(es.replace(it,employee(0,"Joe",32,1123))&&it->age==32);
  BOOST_TEST(i.replace(it1,employee(3,"Albert",20,9012))&&it1->name==
                "Albert");
  BOOST_TEST(!r.replace(it2,employee(4,"John",57,5601)));

  {
    typedef multi_index_container<
      int,
      indexed_by<
        ordered_non_unique<identity<int> >
      >
    > int_multiset;
    test_stable_update<int_multiset>();

    typedef multi_index_container<
      int,
      indexed_by<
        hashed_unique<identity<int> >
      >
    > int_hashed_set;
    test_stable_update<int_hashed_set>();

    typedef multi_index_container<
      int,
      indexed_by<
        hashed_unique<identity<int> >
      >
    > int_hashed_multiset;
    test_stable_update<int_hashed_multiset>();

    typedef multi_index_container<
      int,
      indexed_by<
        hashed_unique<identity<int>,null_hash>
      >
    > degenerate_int_hashed_set;
    test_stable_update<degenerate_int_hashed_set>();

    typedef multi_index_container<
      int,
      indexed_by<
        hashed_non_unique<identity<int>,null_hash>
      >
    > degenerate_int_hashed_multiset;
    test_stable_update<degenerate_int_hashed_multiset>();
  }
}

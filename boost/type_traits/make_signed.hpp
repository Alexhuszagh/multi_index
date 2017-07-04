
//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#pragma once

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_volatile.hpp>
#include <type_traits>

namespace boost {

template <class T>
struct make_signed
{
private:
   static_assert(( ::boost::is_integral<T>::value || ::boost::is_enum<T>::value), "The template argument to make_signed must be an integer or enum type.");
   static_assert(!(::boost::is_same<typename remove_cv<T>::type, bool>::value), "The template argument to make_signed must not be the type bool.");

   typedef typename remove_cv<T>::type t_no_cv;
   typedef typename std::conditional<
      (::boost::is_signed<T>::value
      && ::boost::is_integral<T>::value
      && ! ::boost::is_same<t_no_cv, char>::value
      && ! ::boost::is_same<t_no_cv, wchar_t>::value
      && ! ::boost::is_same<t_no_cv, bool>::value),
      T,
      typename std::conditional<
         (::boost::is_integral<T>::value
         && ! ::boost::is_same<t_no_cv, char>::value
         && ! ::boost::is_same<t_no_cv, wchar_t>::value
         && ! ::boost::is_same<t_no_cv, bool>::value),
         typename std::conditional<
            is_same<t_no_cv, unsigned char>::value,
            signed char,
            typename std::conditional<
               is_same<t_no_cv, unsigned short>::value,
               signed short,
               typename std::conditional<
                  is_same<t_no_cv, unsigned int>::value,
                  int,
                  typename std::conditional<
                     is_same<t_no_cv, unsigned long>::value,
                     long,
#if defined(BOOST_HAS_LONG_LONG)
#ifdef BOOST_HAS_INT128
                     typename std::conditional<
                        sizeof(t_no_cv) == sizeof(boost::long_long_type),
                        boost::long_long_type,
                        boost::int128_type
                     >::type
#else
                     boost::long_long_type
#endif
#elif defined(BOOST_HAS_MS_INT64)
                     __int64
#else
                     long
#endif
                  >::type
               >::type
            >::type
         >::type,
         // Not a regular integer type:
         typename std::conditional<
            sizeof(t_no_cv) == sizeof(unsigned char),
            signed char,
            typename std::conditional<
               sizeof(t_no_cv) == sizeof(unsigned short),
               signed short,
               typename std::conditional<
                  sizeof(t_no_cv) == sizeof(unsigned int),
                  int,
                  typename std::conditional<
                     sizeof(t_no_cv) == sizeof(unsigned long),
                     long,
#if defined(BOOST_HAS_LONG_LONG)
#ifdef BOOST_HAS_INT128
                     typename std::conditional<
                        sizeof(t_no_cv) == sizeof(boost::long_long_type),
                        boost::long_long_type,
                        boost::int128_type
                     >::type
#else
                     boost::long_long_type
#endif
#elif defined(BOOST_HAS_MS_INT64)
                     __int64
#else
                     long
#endif
                  >::type
               >::type
            >::type
         >::type
      >::type
   >::type base_integer_type;

   // Add back any const qualifier:
   typedef typename std::conditional<
      is_const<T>::value,
      typename add_const<base_integer_type>::type,
      base_integer_type
   >::type const_base_integer_type;
public:
   // Add back any volatile qualifier:
   typedef typename std::conditional<
      is_volatile<T>::value,
      typename add_volatile<const_base_integer_type>::type,
      const_base_integer_type
   >::type type;
};

} // namespace boost


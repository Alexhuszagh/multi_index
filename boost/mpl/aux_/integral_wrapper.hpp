
// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

#include <boost/preprocessor/cat.hpp>

#if !defined(AUX_WRAPPER_NAME)
#   define AUX_WRAPPER_NAME BOOST_PP_CAT(AUX_WRAPPER_VALUE_TYPE,_)
#endif

#if !defined(AUX_WRAPPER_PARAMS)
#   define AUX_WRAPPER_PARAMS(N) BOOST_MPL_AUX_NTTP_DECL(AUX_WRAPPER_VALUE_TYPE, N)
#endif

#if !defined(AUX_WRAPPER_INST)
#   define AUX_WRAPPER_INST(value) BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::AUX_WRAPPER_NAME< value >
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< AUX_WRAPPER_PARAMS(N) >
struct AUX_WRAPPER_NAME
{
    static const AUX_WRAPPER_VALUE_TYPE value = N;
    typedef AUX_WRAPPER_NAME type;
    typedef AUX_WRAPPER_VALUE_TYPE value_type;
    typedef integral_c_tag tag;
    typedef AUX_WRAPPER_INST(static_cast<AUX_WRAPPER_VALUE_TYPE>(value + 1)) next;
    typedef AUX_WRAPPER_INST(static_cast<AUX_WRAPPER_VALUE_TYPE>(value - 1)) prior;

    // enables uniform function call syntax for families of overloaded
    // functions that return objects of both arithmetic ('int', 'long',
    // 'double', etc.) and wrapped integral types (for an example, see
    // "mpl/example/power.cpp")
    constexpr operator AUX_WRAPPER_VALUE_TYPE() const { return static_cast<AUX_WRAPPER_VALUE_TYPE>(this->value); }
};

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< AUX_WRAPPER_PARAMS(N) >
AUX_WRAPPER_VALUE_TYPE const AUX_WRAPPER_INST(N)::value;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#undef AUX_WRAPPER_NAME
#undef AUX_WRAPPER_PARAMS
#undef AUX_WRAPPER_INST
#undef AUX_WRAPPER_VALUE_TYPE

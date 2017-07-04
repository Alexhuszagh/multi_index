//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#pragma once

#include <boost/config.hpp>
#include <type_traits>

//
// Helper macros for builtin compiler support.
// If your compiler has builtin support for any of the following
// traits concepts, then redefine the appropriate macros to pick
// up on the compiler support:

// The following can also be defined: when detected our implementation is greatly simplified.
//
//
// define BOOST_TT_DISABLE_INTRINSICS to prevent any intrinsics being used (mostly used when testing)
//


#if defined(BOOST_CLANG) && defined(__has_feature) && !defined(__CUDACC__)
//
// Note that these intrinsics are disabled for the CUDA meta-compiler as it appears
// to not support them, even though the underlying clang compiler does so.
// This is a rubbish fix as it basically stops type traits from working correctly,
// but maybe the best we can do for now.  See https://svn.boost.org/trac/boost/ticket/10694
//
//
// Note that even though these intrinsics rely on other type traits classes
// we do not #include those here as it produces cyclic dependencies and
// can cause the intrinsics to not even be used at all!
//
#   include <cstddef>

#   if __has_feature(is_final)
#     define BOOST_IS_FINAL(T) __is_final(T)
#   endif
#endif

#if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5130)
#   define BOOST_IS_FINAL(T) __oracle_is_final(T)
#endif

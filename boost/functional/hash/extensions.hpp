
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18.

// This implements the extensions to the standard.
// It's undocumented, so you shouldn't use it....

#pragma once

#include <boost/config.hpp>

#include <boost/functional/hash/hash.hpp>
#include <boost/detail/container_fwd.hpp>
//#include <boost/preprocessor/repetition/repeat_from_to.hpp>
//#include <boost/preprocessor/repetition/enum_params.hpp>

#include <array>
#include <tuple>
#include <type_traits>
#include <memory>


namespace boost
{
    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const&);
    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const&);
    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v);
    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v);

    template <class T>
    std::size_t hash_value(std::complex<T> const&);

    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const& v)
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, v.first);
        boost::hash_combine(seed, v.second);
        return seed;
    }

    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T>
    std::size_t hash_value(std::complex<T> const& v)
    {
        boost::hash<T> hasher;
        std::size_t seed = hasher(v.imag());
        seed ^= hasher(v.real()) + (seed<<6) + (seed>>2);
        return seed;
    }

    template <class T, std::size_t N>
    std::size_t hash_value(std::array<T, N> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    namespace hash_detail {
        template <std::size_t I, typename T>
        inline typename std::enable_if<(I == std::tuple_size<T>::value),
                void>::type
            hash_combine_tuple(std::size_t&, T const&)
        {
        }

        template <std::size_t I, typename T>
        inline typename std::enable_if<(I < std::tuple_size<T>::value),
                void>::type
            hash_combine_tuple(std::size_t& seed, T const& v)
        {
            boost::hash_combine(seed, std::get<I>(v));
            boost::hash_detail::hash_combine_tuple<I + 1>(seed, v);
        }

        template <typename T>
        inline std::size_t hash_tuple(T const& v)
        {
            std::size_t seed = 0;
            boost::hash_detail::hash_combine_tuple<0>(seed, v);
            return seed;
        }
    }

    template <typename... T>
    inline std::size_t hash_value(std::tuple<T...> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template <typename T>
    inline std::size_t hash_value(std::shared_ptr<T> const& x) {
        return boost::hash_value(x.get());
    }

    template <typename T, typename Deleter>
    inline std::size_t hash_value(std::unique_ptr<T, Deleter> const& x) {
        return boost::hash_value(x.get());
    }

    //
    // call_hash_impl
    //

    // On compilers without function template ordering, this deals with arrays.

    //
    // boost::hash
    //

    template <class T> struct hash
        : boost::hash_detail::hash_base<T>
    {
        std::size_t operator()(T const& val) const
        {
            return hash_value(val);
        }
    };
}

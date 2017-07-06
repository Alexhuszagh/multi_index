## Removing boost

- Re-factor all the Boost.mpl-specific logic to take variadic templates
  - Only boost::multi_index_container should require an mpl::vector.
  - Remove `mpl.fold`, `mpl.reverse_iter_fold`.
  - Reimplement in terms of brigand.

- Remove mpl::deref from here:
    - node_type.hpp

- Remove reverse_iter_fold from here:
    - node_type.hpp

- Convert the following macros
    - ULONG_MAX
    - BOOST_PP_REPEAT
    - BOOST_PP_SEQ_SIZE
    - BOOST_PP_SEQ_ENUM
        - Converts the macro to a comma-separated list
            - `BOOST_PP_SEQ_ENUM((x)(y)(z))` -> `x, y, z`
    - BOOST_PP_SEQ_ELEM(n, a)
        - Get n-element from array (a)

- Move allocator_utilities to boost/multi_index

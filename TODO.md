## Removing boost

- Re-factor all the Boost.mpl-specific logic to take variadic templates
  - Only boost::multi_index_container should require an mpl::vector.
  - Remove `mpl.fold`, `mpl.reverse_iter_fold`.
  - Reimplement in terms of brigand.


- Remove boost/operators from here:
    - bidir_node_iterator.hpp

- Remove mpl::deref from here:
    - node_type.hpp

- Remove reverse_iter_fold from here:
    - node_type.hpp

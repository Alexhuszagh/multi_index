## Removing boost

- Re-factor all the Boost.mpl-specific logic to take variadic templates
  - Only boost::multi_index_container should require an mpl::vector.
  - Remove `mpl.fold`, `mpl.reverse_iter_fold`.
  - Reimplement in terms of brigand.

#pragma once

#include <vector>
namespace ankicpp {
template <typename T, typename K, typename D> class Repository {
  std::vector<T> read();

  T readById(K id);
  T create(T entity);
  T update(T entity);
  T del(T entity);
};
} // namespace ankicpp

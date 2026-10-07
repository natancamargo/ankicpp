#pragma once

#include <tuple>
#include <vector>
namespace ankicpp {
template <typename D, typename K> class Repository {
public:
  std::tuple<std::vector<D>, bool> read() const;
  std::tuple<std::vector<D>, bool> readById(K key) const;
  bool create(D dto) const;
  bool update(D dto) const;
  bool del(D dto) const;
};
} // namespace ankicpp

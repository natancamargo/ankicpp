#pragma once

#include <vector>
namespace ankicpp {
template <typename T, typename K, typename M> class Repository {
 public:  
  std::vector<T> read();
  T readById(K id);
  T create(T dto);
  T update(T dto);
  T del(T dto);

  T modelToDTO(M model);
  M modelFromDTO(T dto);
};
} // namespace ankicpp

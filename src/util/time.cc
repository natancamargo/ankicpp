#include "util/time.h"

namespace ankicpp {
  int64_t getNow() {
    int64_t epoch_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(
                                                            std::chrono::system_clock::now().time_since_epoch()
                                                            ).count();
    return epoch_ms;
  }
}

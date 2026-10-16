#include "util/crypto.h"
#include <cstring>
#include <openssl/sha.h>
#include <string>

namespace ankicpp {
std::string sha1(const char *in) {
  const unsigned char *uChar = reinterpret_cast<const unsigned char *>(in);
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(uChar, std::strlen(in), hash);
  return std::string{ hash, hash + SHA_DIGEST_LENGTH };
}
} // namespace ankicpp

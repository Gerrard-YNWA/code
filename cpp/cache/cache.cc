#include "cache.h"

#include "lru_cache.h"

namespace gerrard {
namespace cache {
Cache::Cache(int size) {
}

CachePtr Cache::GetCache(CacheType c, int size) {
    return std::make_shared<LruCache>(size);
}

Cache::~Cache() {
}
}  // namespace cache
}  // namespace gerrard

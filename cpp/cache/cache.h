#ifndef MAGNUS_RUNTIME_SERVER_UTILS_CACHE_CACHE_H
#define MAGNUS_RUNTIME_SERVER_UTILS_CACHE_CACHE_H

#include <memory>
#include <string>

namespace gerrard {
namespace cache {

constexpr auto CACHE_MAX_SIZE = 1024;

enum class CacheType {
    LRU = 0,
};

struct CacheData {
    std::string key;
    std::string value;
    int ttl;
    CacheData(std::string k, std::string v, int t) : key(k), value(v), ttl(t) {
    }
};

typedef std::shared_ptr<CacheData> CacheDataPtr;

class Comparator {
   public:
    bool operator()(const CacheDataPtr l, const CacheDataPtr r) {
        return l->ttl > r->ttl;
    }
};

class Cache;
typedef std::shared_ptr<Cache> CachePtr;

class Cache {
   public:
    Cache(int size = CACHE_MAX_SIZE);

    virtual std::string Get(const std::string& key) = 0;

    virtual void Put(const std::string& key, const std::string& value, int ttl = -1) = 0;

    virtual void DeleteByKey(const std::string& key) = 0;

    virtual void Clear() = 0;

    static CachePtr GetCache(CacheType c, int size = CACHE_MAX_SIZE);

    virtual void Print() = 0;

    ~Cache();
};
}  // namespace cache
}  // namespace gerrard
#endif /* MAGNUS_RUNTIME_SERVER_UTILS_CACHE_CACHE_H */

#ifndef MAGNUS_RUNTIME_SERVER_UTILS_CACHE_LRU_CACHE_H
#define MAGNUS_RUNTIME_SERVER_UTILS_CACHE_LRU_CACHE_H

#include <algorithm>
#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "cache.h"

namespace gerrard {
namespace cache {

template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
class Heap : public std::priority_queue<T, std::vector<T>, Compare> {
   public:
    void Remove(const T& value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }
    }
};

class LruCache : public Cache {
   public:
    LruCache(int size = CACHE_MAX_SIZE);

    std::string Get(const std::string& key);

    void Put(const std::string& key, const std::string& value, int ttl = -1);

    void DeleteByKey(const std::string& key);

    void Clear();

    ~LruCache();

    void Print();

   private:
    void EvictExpired();

    void EvictLru();

    void RemoveTtl(CacheDataPtr ptr);

    void RefreshLru(CacheDataPtr ptr);

    int Size();

   private:
    std::unordered_map<std::string, CacheDataPtr> m_;
    std::list<CacheDataPtr> lru_;
    Heap<CacheDataPtr, std::vector<CacheDataPtr>, Comparator> min_heap_;

    std::mutex mu_;
    int capacity_;
};
}  // namespace cache
}  // namespace gerrard
#endif /* MAGNUS_RUNTIME_SERVER_UTILS_CACHE_LRU_CACHE_H */

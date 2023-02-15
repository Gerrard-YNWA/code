#include "lru_cache.h"

#include <chrono>
#include <climits>
#include <iostream>

namespace gerrard {
namespace cache {
LruCache::LruCache(int size) : capacity_(size) {
}

LruCache::~LruCache() {
    Clear();
}

std::string LruCache::Get(const std::string& key) {
    EvictExpired();

    std::string value;
    std::lock_guard<std::mutex> lock(mu_);
    auto it = m_.find(key);
    if (it != m_.end()) {
        value = it->second->value;
        RefreshLru(it->second);
    }

    return value;
}

void LruCache::Put(const std::string& key, const std::string& value, int ttl) {
    EvictExpired();

    auto it = m_.find(key);
    if (it == m_.end()) {  // new
        ttl = ttl > 0 ? ttl + (int)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() : INT_MAX;
        auto cache_ptr = std::make_shared<CacheData>(key, value, ttl);
        mu_.lock();
        if (m_.size() >= capacity_) {
            EvictLru();
        }
        m_.emplace(key, cache_ptr);
        lru_.push_front(cache_ptr);
        min_heap_.push(cache_ptr);
        mu_.unlock();
    } else {
        mu_.lock();
        DeleteByKey(key);
        mu_.unlock();
        Put(key, value, ttl);
    }
}

void LruCache::DeleteByKey(const std::string& key) {
    auto it = m_.find(key);
    if (it != m_.end()) {
        auto lru_it = std::find(lru_.begin(), lru_.end(), it->second);
        if (lru_it != lru_.end()) {
            lru_.erase(lru_it);
        }
        RemoveTtl(it->second);
        m_.erase(it);
    }
}

void LruCache::Clear() {
    m_.clear();
    lru_.clear();
    while (!min_heap_.empty()) {
        min_heap_.pop();
    }
}

void LruCache::EvictExpired() {
    int time = (int)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    mu_.lock();
    while (min_heap_.size() > 0) {
        auto top = min_heap_.top();
        if (top->ttl > time) {
            break;
        }
        min_heap_.pop();
        DeleteByKey(top->key);
    }
    mu_.unlock();
}

void LruCache::EvictLru() {
    auto ptr = lru_.back();
    lru_.pop_back();
    DeleteByKey(ptr->key);
}

void LruCache::RemoveTtl(CacheDataPtr ptr) {
    min_heap_.Remove(ptr);
}

void LruCache::RefreshLru(CacheDataPtr ptr) {
    auto it = std::find(lru_.begin(), lru_.end(), ptr);
    if (it != lru_.end()) {
        lru_.erase(it);
    }
    lru_.push_front(ptr);
}

int LruCache::Size() {
    return m_.size();
}

void LruCache::Print() {
    std::cout << "map size:" << m_.size() << std::endl;
    auto print = [](const auto& e) { std::cout << "key:" << e.first << ", value: " << e.second->value << ", ttl: " << e.second->ttl << std::endl; };
    std::for_each(m_.begin(), m_.end(), print);
}
}  // namespace cache
}  // namespace gerrard

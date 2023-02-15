#include <chrono>
#include <iostream>
#include <thread>

#include "cache.h"

int main() {
    gerrard::cache::CachePtr lru_cache = gerrard::cache::Cache::GetCache(gerrard::cache::CacheType::LRU, 5);

    lru_cache->Put("aaa", "123", 10);
    lru_cache->Print();
    lru_cache->Put("bbb", "234", 5);
    lru_cache->Print();
    lru_cache->Put("ccc", "345", 2);
    lru_cache->Print();
    lru_cache->Put("ddd", "456", 15);
    lru_cache->Print();
    lru_cache->Put("eee", "567", 3);
    lru_cache->Print();
    lru_cache->Put("fff", "678", 8);
    lru_cache->Print();

    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    std::cout << "key fff, value: " << lru_cache->Get("fff") << std::endl;
    lru_cache->Print();
    return 0;
}

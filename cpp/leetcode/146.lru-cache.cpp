/*
 * @lc app=leetcode id=146 lang=cpp
 *
 * [146] LRU Cache
 */
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;
// @lc code=start
class LRUCache {
   public:
    LRUCache(int capacity) : _capacity(capacity) {
    }

    /*
    int get(int key) {
        auto value = -1;
        auto it = m.find(key);
        if (it != m.end()) {
            // refresh cache
            refresh(key);
            value = it->second;
        }

        return value;
    }

    void put(int key, int value) {
        // corner case, if key already in map, no need to evict
        if (m.size() == _capacity && m.find(key) == m.end()) {
            evict();
        }
        // refresh cache
        refresh(key);
        m.erase(key);
        m.insert(make_pair(key, value));
    }
    */

    int get(int key) {
        if (m.find(key) == m.end()) {
            return -1;
        }
        auto it = k_it.find(key);
        if (it != k_it.end()) {
            lru.erase(it->second);
        }
        lru.push_front(key);
        k_it[key] = lru.begin();
        return m[key];
    }

    void put(int key, int value) {
        auto it = k_it.find(key);
        if (lru.size() == _capacity && it == k_it.end()) {  //不在cache中且满了, 驱逐
            auto dirty = lru.back();
            lru.pop_back();
            m.erase(dirty);
            k_it.erase(dirty);
        } else if (it != k_it.end()) {  //在cache中, 先移除
            lru.erase(it->second);
        }

        m[key] = value;
        lru.push_front(key);
        k_it[key] = lru.begin();
    }

   private:
    unordered_map<int, int> m;
    unordered_map<int, list<int>::iterator> k_it;
    list<int> lru;
    int _capacity;

    /*
    void refresh(int key) {
        auto it = k_it.find(key);
        if (it != k_it.end()) {
            lru.erase(it->second);
            k_it.erase(it);
        }
        lru.push_front(key);
        k_it.insert(make_pair(key, lru.begin()));
    }

    void evict() {
        auto dirty = lru.back();
        lru.pop_back();
        k_it.erase(dirty);
        m.erase(dirty);
    }
    */
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

int main() {
    cout << "==============" << endl;
    auto cache = new LRUCache(2);
    cache->put(1, 1);
    cache->put(2, 2);
    cout << cache->get(1) << endl;
    cache->put(3, 3);
    cout << cache->get(2) << endl;
    cache->put(4, 4);
    cout << cache->get(1) << endl;
    cout << cache->get(3) << endl;
    cout << cache->get(4) << endl;

    //["LRUCache","put","put","get","put","put","get"]
    //[[2],[2,1],[2,2],[2],[1,1],[4,1],[2]]
    // expected [null,null,null,2,null,null,-1]
    // actual [null,null,null,1,null,null,-1]
    //
    // map.insert will do nothing when key already exists in map
    // when insert an existed key, need to erase first
    // while [] operator will auto overwrite

    cout << "==============" << endl;
    cache = new LRUCache(2);
    cache->put(2, 1);
    cache->put(2, 2);
    cout << cache->get(2) << endl;
    cache->put(1, 1);
    cache->put(4, 1);
    cout << cache->get(2) << endl;
    //
    //["LRUCache","get","put","get","put","put","get","get"]
    //[[2],[2],[2,6],[1],[1,5],[1,2],[1],[2]]
    // Answer[null, -1, null, -1, null, null, 2, -1]
    // Expected Answer[null, -1, null, -1, null, null, 2, 6]

    cout << "==============" << endl;
    cache = new LRUCache(2);
    cout << cache->get(2) << endl;
    cache->put(2, 6);
    cout << cache->get(1) << endl;
    cache->put(1, 5);
    cache->put(1, 2);
    cout << cache->get(1) << endl;
    cout << cache->get(2) << endl;

    //["LRUCache","put","put","put","put","get","get"]
    //[[2],[2,1],[1,1],[2,3],[4,1],[1],[2]]
    // Answer
    //[null,null,null,null,null,1,-1]
    // Expected Answer
    //[null,null,null,null,null,-1,3]
    cout << "==============" << endl;
    cache = new LRUCache(2);
    cache->put(2, 1);
    cache->put(1, 1);
    cache->put(2, 3);
    cache->put(4, 1);
    cout << cache->get(1) << endl;
    cout << cache->get(2) << endl;

    return 0;
}

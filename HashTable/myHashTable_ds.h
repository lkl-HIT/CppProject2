//
// Created by 86135 on 2025/4/20.
//

#ifndef HASHTABLE_MYHASHTABLE_DS_H
#define HASHTABLE_MYHASHTABLE_DS_H
#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 哈希表节点（键值对）
template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode(K k, V v) : key(k), value(v) {}
};

// 哈希表类
template <typename K, typename V>
class HashTable {
private:
    vector<list<HashNode<K, V>>> buckets; // 桶数组，每个桶是一个链表（链地址法）
    int capacity;                        // 桶的数量
    int size;                            // 元素总数
    const double LOAD_FACTOR = 0.75;     // 负载因子阈值

    // 哈希函数（简单取模，实际STL使用更复杂的哈希）
    int hashFunction(K key) {
        return hash<K>{}(key) % capacity; // 使用标准库hash生成哈希值
    }

    // 扩容并重新哈希
    void rehash() {
        int oldCapacity = capacity;
        capacity *= 2; // 扩容为原来的两倍
        vector<list<HashNode<K, V>>> newBuckets(capacity);

        // 将旧桶中所有元素重新哈希到新桶
        for (auto &bucket : buckets) {
            for (auto &node : bucket) {
                int newIndex = hashFunction(node.key);
                newBuckets[newIndex].push_back(node);
            }
        }
        buckets = move(newBuckets); // 移动语义优化性能
    }

public:
    HashTable(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        buckets.resize(capacity);
    }

    ~HashTable() = default;

    // 插入或更新键值对
    void insert(K key, V value) {
        int index = hashFunction(key);
        for (auto &node : buckets[index]) {
            // 如果键已存在，更新值
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        // 键不存在，插入新节点
        buckets[index].emplace_back(key, value);
        size++;

        // 触发扩容
        if ((double)size / capacity > LOAD_FACTOR) {
            rehash();
        }
    }

    // 查找值
    V* find(K key) {
        int index = hashFunction(key);
        for (auto &node : buckets[index]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr; // 未找到返回空指针
    }

    // 删除键值对
    bool erase(K key) {
        int index = hashFunction(key);
        auto &bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                size--;
                return true;
            }
        }
        return false;
    }

    int getSize() const { return size; }
};
#endif //HASHTABLE_MYHASHTABLE_DS_H

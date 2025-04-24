#include <iostream>
#include "myHashTable_ds.h"

using namespace std;

int main() {
    HashTable<string, int> ht;

    // 插入数据
    ht.insert("Alice", 90);
    ht.insert("Bob", 85);
    ht.insert("Charlie", 95);

    // 查找测试
    int* score = ht.find("Bob");
    if (score) {
        cout << "Bob's score: " << *score << endl; // 输出 85
    }

    // 更新测试
    ht.insert("Bob", 88);
    cout << "Bob's updated score: " << *ht.find("Bob") << endl; // 输出 88

    // 删除测试
    ht.erase("Charlie");
    cout << "Size after deletion: " << ht.getSize() << endl; // 输出 2

    return 0;
}

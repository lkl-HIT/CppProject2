#include "my.h"
#include <iostream>



int main() {
    // 创建一个 Deque 对象
MyDeque<int> myDeque;

int N;
std::cin >> N;
// 读走回车
getchar();
std::string line;
// 接收命令
for (int i = 0; i < N; i++) {
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::string command;
    iss >> command;
    int value;

    if (command == "push_back") {
        iss >> value;
        myDeque.push_back(value);
    }

    if (command == "push_front") {
        iss >> value;
        myDeque.push_front(value);
    }

    if (command == "pop_back") {
        if (myDeque.size() == 0) {
            continue;
        }
        myDeque.pop_back();
    }

    if (command == "pop_front") {
        if (myDeque.size() == 0) {
            continue;
        }
        myDeque.pop_front();
    }

    if (command == "clear") {
        myDeque.clear();
    }

    if (command == "size") {
        std::cout << myDeque.size() << std::endl;
    }

    if (command == "get") {
        iss >> value;
        std::cout << myDeque[value] << std::endl;
    }

    if (command == "print") {
        if (myDeque.size() == 0) {
            std::cout << "empty" << std::endl;
        } else {
            myDeque.printDeque();
        }
    }
}
return 0;
}
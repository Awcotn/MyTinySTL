#include <iostream>
#include "MyHashTable.h"

int main() {
  // 创建一个哈希表实例
  MyHashTable<int, int> hashTable;

  int N;
  std::cin >> N;
  getchar();

  std::string line;
  for (int i = 0; i < N; i++) {
      std::getline(std::cin, line);
      std::istringstream iss(line);
      std::string command;
      iss >> command;
      
      int key;
      int value;

      if (command == "insert") {
          iss >> key >> value;
          hashTable.insert(key, value);
      }

      if (command == "erase") {
          if (hashTable.size() == 0) {
              continue;
          }
          iss >> key;
          hashTable.erase(key);
      }

      if (command == "find") {
          if (hashTable.size() == 0) {
              std::cout << "not exist" << std::endl;
              continue;
          }
          iss >> key;
          int* res = hashTable.find(key);
          if (res != nullptr) {
              std::cout << *res << std::endl;
          } else {
              std::cout << "not exist" << std::endl;
          }
      }

      if (command == "print") {
          if (hashTable.size() == 0) {
              std::cout << "empty" << std::endl;
          } else {
              hashTable.print();
          }
      }

      if (command == "size") {
          std::cout << hashTable.size() << std::endl;
      }

      if (command == "clear") {
          hashTable.clear();
      }
  }
  return 0;
}
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class MyHashTable{
  class HashNode{
   public:
    Key key;
    Value value;

    //构造
    explicit HashNode(const Key& key) : key(key) ,value() {}
    HashNode(const Key& key,const Value& value) : key(key) ,value(value) {}

    //比较
    bool operator== (const HashNode& other) const { return key == other.key; }

    bool operator!= (const HashNode& other) const { return key != other.key; }

    bool operator< (const HashNode& other) const { return key < other.key; }

    bool operator> (const HashNode& other) const { return key > other.key; }

    bool operator== (const Key& _key) const { return key == _key; }

    void print() const {
      std::cout << "key:" << key << " value:" << value << std::endl;
    }
  };

 private:
  using Bucket = std::list <HashNode>; //定义桶的类型
  std::vector<Bucket> buckets;  //存储所有桶
  Hash hashFunction; //hash函数
  size_t tableSize; //hash表大小
  size_t numElements; //元素数量  

  float maxLoadFactor = 0.75; //最大负载

  //计算hash，映射到桶的索引
  size_t hash(const Key& key) const { return hashFunction(key) % tableSize; }

  // 当元素数量超过最大负载因子定义的容量时，增加桶的数量并重新分配所有键
  void rehash(size_t newSize) {
    std::vector<Bucket> newBuckets(newSize);

    for (Bucket& bucket: buckets) {
      for (HashNode& hashNode: bucket){
        size_t newIndex = hashFunction(hashNode.key) % newSize;
        newBuckets [newIndex].push_back(hashNode);
      }
    }
    buckets = std::move(newBuckets); 
    tableSize = newSize;
  }

 public:
  MyHashTable (size_t size = 10, const Hash& hashFunc = Hash()) 
    : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0){}

  void insert (const Key& key, const Value& value) {
    if ((numElements +1) > maxLoadFactor *  tableSize) {
      if (tableSize == 0) tableSize = 1;
      rehash(tableSize*2);
    }

    size_t index = hash(key);

    std::list<HashNode>& bucket = buckets[index];

    auto it = std::find(bucket.begin(), bucket.end(), key);
    if (it == bucket.end()) {
      bucket.push_back(HashNode(key,value));
      ++numElements;
    }
    // else {
    //   bucket.erase(it);
    //   bucket.push_back(HashNode(key,value));
    // }
  }

  void insertKey(const Key& key) { insert(key, Value{});}

  void erase(const Key& key) {
    size_t index = hash(key);
    auto& bucket = buckets[index];
    auto it = std::find(bucket.begin(), bucket.end(), key);
    if( it != bucket.end()) {
      bucket.erase(it);
      numElements--;
    }
  }

  Value *find(const Key& key) {
    size_t index = hash(key);
    auto& bucket = buckets[index];

    auto ans = std::find(bucket.begin(), bucket.end(), key);
    if (ans != bucket.end()) {
      return &ans->value;
    }
    return nullptr;
  }

  size_t size() const { return numElements; }

  void print() const {
    for (size_t i = 0; i < buckets.size(); i++) {
      for (const HashNode& element : buckets[i]) {
        element.print();
      }
    }
    std::cout << std::endl;
  }

  void clear() {
    this->buckets.clear();
    this->numElements = 0;
    this->tableSize = 0;
  }
};

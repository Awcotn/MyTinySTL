#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class MyVector {
 private:
  T* elements;
  size_t size;
  size_t capacity;
 public:
  //构造函数
  MyVector() : elements(nullptr), size(0), capacity(0) {}

  //析构函数
  ~MyVector() {
    delete[] elements;
  }

  //拷贝构造函数
  MyVector(const MyVector& other) :  size(other.size), capacity(other.capacity) {
    elements = new T[capacity]; 
    std::copy(other.elements, other.elements + size, elements);
  }

  //拷贝赋值操作符
  MyVector &operator=(const MyVector &other){
    if (this == &other) {
      return *this;
    }
    delete[] elements;
    capacity = other.capacity;
    size = other.size;
    elements = new T[capacity];
    std::copy(other.elements, other.elements + size, elements);
    return *this;
  }
  
  //push_back
  void push_back(const T &value){
    if(size==capacity){
      reserve(capacity==0?1:2*capacity);
    }
    elements[size++]=value;
  }

  //获取数组中元素个数
  size_t get_size() const {
    return size;
  }

  //获取数组中元素容量
  size_t get_capacity() const {
    return capacity;
  }

  //获取数组中元素
  T& operator[](size_t index){
    if(index>=size){
      throw std::out_of_range("Index out of range");
    }
    return elements[index];
  }

  //获取数组中元素
  const T& operator[](size_t index) const {
    if(index>=size){
      throw std::out_of_range("Index out of range");
    }
    return elements[index];
  }

  //在指定位置插入元素
  void insert(size_t index , const T& value){
    if ( index > size ) {
      throw std::out_of_range("Index out of range");
    }
    if ( size == capacity ) {
      reserve( capacity == 0 ? 1 : 2*capacity );
    }
    for ( size_t i=size ; i>index ; i--) {
      elements[i] = elements[i-1];
    }
    elements[index] = value;
    size++;
  }

  //删除数组末尾的元素
  void pop_back() {
    if( size > 0 ) {
      size--;
    }
  }

  //清空数组
  void clear() {
    size = 0;
  }

  //使用迭代器遍历数组的开始位置
  T* begin() {
    return elements;
  }

  //使用迭代器遍历数组的结束位置
  T* end() {
    return elements + size;
  }

  //使用迭代器遍历数组的开始位置
  const T* begin() const {
    return elements;
  }

  //使用迭代器遍历数组的结束位置
  const T* end() const {
    return elements+size;
  }

  //打印数组中的元素
  void printElements() const {
    for (size_t i = 0; i < size; i++) {
      std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
  }

 private:
  //reserve
  void reserve(size_t new_capacity){
    if(new_capacity<=capacity){
      return;
    }
    T* new_elements = new T[new_capacity];
    std::copy(elements, elements + size, new_elements);
    delete[] elements;
    elements = new_elements;
    capacity = new_capacity;
  }
};
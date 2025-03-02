#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class MyDeque{
 private:
  T* elements;
  size_t size;
  size_t capacity;
  size_t frontIndex;
  size_t backIndex;
 public:

  //构造函数
  MyDeque() : elements(nullptr), size(0), capacity(0), frontIndex(0), backIndex(0) {}

  //析构函数
  ~MyDeque() {
    //clear();
    delete[] elements;
  }
  
  //前端插入元素
  void push_front(const T& value) {
    //检查空间大小
    if(size == capacity) {
      resize();
    }

    //计算索引
    frontIndex = ( frontIndex - 1 + capacity ) %capacity;
    
    //插入
    elements[frontIndex] =value;
    size++;
  }

  //后端插入元素
  void push_back(const T& value) {
    //检查空间大小
    if(size == capacity) {
      resize();
    }

    //插入
    elements[backIndex] =value;
    size++;

    //计算索引
    backIndex = ( backIndex + 1 + capacity ) %capacity;
  }

  //前端删除元素
  void pop_front() {
    //检查是否为空
    if(size == 0){
      throw std::out_of_range("Deque is empty");
    }
    
    //更新frontIndex
    frontIndex = (frontIndex + 1) %capacity;
    size--;
  }

  //前端删除元素
  void pop_back() {
    //检查是否为空
    if(size == 0){
      throw std::out_of_range("Deque is empty");
    }

    //更新frontIndex
    backIndex = (backIndex - 1) %capacity;
    size--;
  }

  //随机访问
  T& operator [](int index) {
    if (index < 0 || index >= size) {
      throw  std::out_of_range("Index out of range");
    }
    return elements[ (frontIndex + index ) %capacity ];
  }

  //获取元素数量
  size_t getSize() const {
    return size;
  }

  //清空数组
  void clear(){
    while(size){
      pop_front();
    }
  }

  //打印
  void printElements() const {
    size_t index = frontIndex;
    for (size_t i = 0 ; i< size ; i++) {
      std::cout << elements[index] << " ";
      index = (index + 1) % capacity;
    }
    std::cout << std::endl;
  }

 private:
  //扩展数组
  void resize() {
    //计算新的容量
    size_t newCapacity = capacity == 0 ? 1 : 2*capacity;

    //创建新数组
    T* newElements = new T [newCapacity];

    //移动元素
    size_t index = frontIndex ;
    for( int i=0; i<size; i++) {
      newElements[i] = elements[index];
      index = (index + 1)%capacity;
    }

    //删除旧指针
    delete[] elements;

    //更改成员变量
    elements = newElements;
    frontIndex = 0;
    backIndex = size;
    capacity = newCapacity;
  }
};
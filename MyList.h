#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
struct Node {
  T data;
  Node* next;
  Node* prev;

  Node (const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr ) : data(value), next(nextNode), prev(prevNode) {}

};

template <typename T>
class MyList{

 private:
  Node<T>* head;
  Node<T>* tail;
  size_t size;

 public:
  //构造函数
  MyList() : head(nullptr), tail(nullptr), size(0) {}

  //拷贝构造函数
  MyList(const MyList& other) : size(other.size) {
    head = new Node<T>(other.head->data);
    tail = new Node<T>(other.tail->data);
    Node<T>* current = head;
    Node<T>* otherCurrent = other.head;
    while (otherCurrent->next != nullptr) {
      current->next = new Node<T>(otherCurrent->next->data);
      current->next->prev = current;
      current = current->next;
      otherCurrent = otherCurrent->next;
    }
  }

  //move拷贝构造函数
  MyList(MyList&& other) : head(other.head), tail(other.tail), size(other.size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
  }

  //拷贝赋值操作符
  MyList& operator=(const MyList& other) {
    if (this == &other) {
      return *this;
    }
    while (head != nullptr) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
    size = other.size;
    head = new Node<T>(other.head->data);
    tail = new Node<T>(other.tail->data);
    Node<T>* current = head;
    Node<T>* otherCurrent = other.head;
    while (otherCurrent->next != nullptr) {
      current->next = new Node<T>(otherCurrent->next->data);
      current->next->prev = current;
      current = current->next;
      otherCurrent = otherCurrent->next;
    }
    return *this;
  }

  //move赋值操作符
  MyList& operator=(MyList&& other) {
    if (this == &other) {
      return *this;
    }
    while (head != nullptr) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
    size = other.size;
    head = other.head;
    tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
    return *this;
  }

  //析构函数
  ~MyList() {
    while (head != nullptr) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }

    tail=nullptr;
    size=0;
  }

  //在链表末尾添加元素
  void push_back(const T& value) {
    //创建新节点
    Node<T>* newNode = new Node<T>(value);
    size++;
    //如果链表为空
    if(head==nullptr){
      head = newNode;
      tail = newNode;
    } else {
      //将新节点添加到链表末尾
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  //在链表头部添加元素
  void push_front(const T& value) {
    //创建新节点
    Node<T>* newNode = new Node<T>(value);
    size++;
    //如果链表为空
    if(head==nullptr){
      head = newNode;
      tail = newNode;
    } else {
      //将新节点添加到链表头部
      head->prev = newNode;
      newNode->next = head;
      head = newNode;
    }
  }

  //删除链表末尾的元素
  void pop_back() {
    if (size == 0) {
      return;
    }
    size--;
    //如果链表只有一个元素
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } 
    else {
      //删除链表末尾的元素
      Node<T>* temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
    }
  }

  //删除链表头部的元素
  void pop_front() {
    if (size == 0) {
      return;
    }
    size--;
    //如果链表只有一个元素
    if ( head == tail ) {
      delete head;
      head = nullptr;
      tail = nullptr;
    }
    else {
      //删除链表头部的元素
      Node<T>* temp=head;
      head =head->next;
      head -> prev =nullptr;
      delete temp;
    }
  }

  //获取链表中节点个数
  size_t get_size() const {
    return size;
  }

  //访问链表中的元素
  T& operator[](size_t index){
    if(index>=size){
      throw std::out_of_range("Index out of range");
    }
    Node<T>* current = head;
    while(index--){
      current = current->next;
    }
    return current->data;
  }

  //访问链表中的元素
  const T& operator[](size_t index) const {
    if(index>=size){
      throw std::out_of_range("Index out of range");
    }
    Node<T>* current = head;
    while(index--){
      current = current->next;
    }
    return current->data;
  }

  //获取制定值的节点
  Node<T>* get_node(const T& value){
    Node<T>* current = head;
    while(current!=nullptr) {
      if(current->data==value){
        return current;
      }
    }
    return nullptr;
  }

  //删除指定值的节点
  void remove(const T& value){
    Node<T>* current =head;
    while ( current != nullptr && current->data != value ) {
      current = current->next;
    }
    if ( current ==nullptr ) {
      return;
    }
    
    if( current == head ) {
      pop_front();
    }
    else if ( current == tail) {
      pop_back();
    }
    else{
      current->prev->next = current->next;
      current->next->prev = current->prev;
      delete current;
      size --;
    }
  }

  bool empty() const {
    return size == 0;
  }

  //清空链表
  void clear() {
    while (head != nullptr) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
    tail=nullptr;
    size=0;
  }

  Node<T>* begin() {
    return head;
  }

  Node<T>* end() {
    return nullptr;
  }

  const Node<T>* begin () const {
    return head;
  }

  const Node<T>* end () const {
    return nullptr;
  }

  void printElements() const {
    Node<T>* current = head;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }
};
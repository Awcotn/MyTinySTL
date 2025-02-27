#include <iostream>
#include "MyVector.h"
#include <vector>
int main(){
  std::vector<int> v;
  std::cout<<v.size();
  v.pop_back();
}
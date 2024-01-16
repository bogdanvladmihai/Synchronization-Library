#include "../src/ReadersWriters.h"
#include <iostream>
#include <thread>
#include <cassert>
#include <algorithm>
#include <numeric>

std::vector<int> items;

void read(){
  for(int x: items){
    std::cout<<x<<" ";
  }
}
void write(int i){
  items.push_back(i);
}

int main() {
  const int WORKERS = 1000;

  RW_WriterPriority RW;

  
  std::vector<int> l(WORKERS);

  std::vector<std::thread> threads;
  std::iota(l.begin(), l.end(), 0);
  for (int &i : l) {
    if (i % 2 == 1) {
      //reader
      threads.push_back(std::thread ([&RW, &i]() {
        RW.aquire_reader();
        std::cout<<"Reader "<<i<<": ";
        read();
        std::cout<<"\n";
        RW.release_reader();
      }));
    } else {
      //writer
      threads.push_back(std::thread ([&RW, i]() {
        RW.aquire_writer();
        std::cout<<"Writer "<<i<<"\n";
        write(i);
        RW.release_writer();
      }));
    }
  }

  for(auto &t: threads){
    t.join();
  }
  
  std::cout << "Test passed!" << std::endl;

  return 0;
}